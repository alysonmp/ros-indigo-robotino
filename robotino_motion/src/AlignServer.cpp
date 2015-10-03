/**
 *  AlignServer.cpp
 *
 *  Version: 1.0.0.0
 *  Created on: 01/10/2015
 *  Modified on: ??/10/2015
 *  Author: Adriano Henrique Rossette Leite (adrianohrl@gmail.com)
 *  Maintainer: Expertinos UNIFEI (expertinos.unifei@gmail.com)
 */

#include "AlignServer.h"

/**
 *
 */
AlignServer::AlignServer(ros::NodeHandle nh, std::string ns) : 
	Server(nh, "Align", ns),
	server_(nh, "align", boost::bind(&AlignServer::executeCallback, this, _1), false)
{
	readParameters();
	distance_sensors_sub_ = nh_.subscribe("distance_sensors", 1, &AlignServer::distanceSensorsCallback, this);

	state_ = alignStates::UNINITIALIZED;
	percentage_ = 0;

	left_index_ = 0;
	right_index_ = 0;
	lateral_ = false;
}

/**
 *
 */
AlignServer::~AlignServer() 
{
	distance_sensors_sub_.shutdown();
	server_.shutdown();
}

/**
 *
 */
bool AlignServer::isActing()
{
	return state_ != alignStates::UNINITIALIZED && state_ != alignStates::IDLE;
}

/**
 *
 */
void AlignServer::start()
{
	if (state_ == alignStates::UNINITIALIZED)
	{
		server_.start();
		state_ = alignStates::IDLE;
	}
}

/**
 *
 */
void AlignServer::stop()
{
	setVelocity(0, 0, 0);
	publishVelocity();
	state_ = alignStates::IDLE;
	result_.goal_achieved = false;
	result_.message = "Unexpected emergency stop request!!!";
	server_.setAborted(result_, result_.message);
}

/**
 *
 */
void AlignServer::controlLoop()
{	
	double vel_x = 0, vel_y = 0, vel_phi = 0;
	float K = .9, K_PHY = 10;
	float min_tolerance = 0.25, max_tolerance = 0.30, phy_tolerance = 0.005;
	float mean_value = (fabs(left_ir_) + fabs(right_ir_)) / 2;
	float error_min = mean_value - min_tolerance;
	float error_max = mean_value - max_tolerance;
	float error_phy = left_ir_ - right_ir_;
	ROS_DEBUG("Align %s", AlignmentModes::toString(alignment_mode_).c_str());
	switch (alignment_mode_)
	{
		case alignmentModes::FRONT:
			if (error_max > 0)
			{
				vel_x = K * error_max;
				vel_y = 0;
				vel_phi = 0;
			}
			else if (error_min < 0)
			{
				vel_x = K * error_min;
				vel_y = 0;
				vel_phi = 0;
			}
			else if (fabs(error_phy) > phy_tolerance)
			{
				vel_x = 0;
				vel_y = 0;
				vel_phi = -K_PHY * error_phy;
			}
			break;
		case alignmentModes::RIGHT:
			if (error_max > 0)
			{
				vel_x = 0;
				vel_y = -K * error_max;
				vel_phi = 0;
			}
			else if (error_min < 0)
			{
				vel_x = 0;
				vel_y = -K * error_min;
				vel_phi = 0;
			}
			else if (fabs(error_phy) > phy_tolerance)
			{
				vel_x = 0;
				vel_y = 0;
				vel_phi = -K_PHY * error_phy;
			}
			break;
		case alignmentModes::LEFT:
			if (error_max > 0)
			{
				vel_x = 0;
				vel_y = K * error_max;
				vel_phi = 0;
			}
			else if (error_min < 0)
			{
				vel_x = 0;
				vel_y = K * error_min;
				vel_phi = 0;
			}
			else if (fabs(error_phy) > phy_tolerance)
			{
				vel_x = 0;
				vel_y = 0;
				vel_phi = K_PHY * error_phy;
			}
			break;
		case alignmentModes::BACK:
			if (error_max > 0)
			{
				vel_x = -K * error_max;
				vel_y = 0;
				vel_phi = 0;
			}
			else if (error_min < 0)
			{
				vel_x = -K * error_min;
				vel_y = 0;
				vel_phi = 0;
			}
			else if (fabs(error_phy) > phy_tolerance)
			{
				vel_x = 0;
				vel_y = 0;
				vel_phi = - K_PHY * error_phy;
			}
		default:
			ROS_ERROR("Alignment Mode not supported yet!!!");
			return;
	}
	if (vel_x == 0 && vel_y == 0 && vel_phi ==0)	
	{
		percentage_ = 100;
		state_ = alignStates::FINISHED;
	}
	setVelocity(vel_x, vel_y, vel_phi);
	publishVelocity();
	publishFeedback();
}

/**
 *
 */
void AlignServer::executeCallback(const robotino_motion::AlignGoalConstPtr& goal)
{
	ros::Rate loop_rate(20);
	if(!validateNewGoal(goal))
	{
		ROS_WARN("Goal not accepted!!!");
		return;
	}
	while(nh_.ok())
	{
		if(server_.isPreemptRequested())
		{
			if(server_.isNewGoalAvailable() && !validateNewGoal(server_.acceptNewGoal()))
			{
				ROS_WARN("Goal not accepted!!!");
				return;
			}
			ROS_INFO("Cancel request!!!");
			server_.setPreempted();
			state_ = alignStates::IDLE;
			setVelocity(0, 0, 0);
			publishVelocity();
			return;
		}
		controlLoop();
		if(state_ == alignStates::FINISHED)
		{
			state_ = alignStates::IDLE;
			setVelocity(0, 0, 0);
			publishVelocity();
			result_.goal_achieved = true;
			result_.message = "Goal achieved with success!!!";
			server_.setSucceeded(result_);
			return;
		}
		ros::spinOnce();
		loop_rate.sleep();
	}
	state_ = alignStates::IDLE;
	setVelocity(0, 0, 0);
	publishVelocity();
	result_.goal_achieved = false;
	result_.message = "Aborting on the goal because the node has been killed!!!";
	server_.setAborted(result_, result_.message);
}

/**
 *
 */
bool AlignServer::validateNewGoal(const robotino_motion::AlignGoalConstPtr& goal)
{
	if(state_ == alignStates::UNINITIALIZED)
	{
		result_.goal_achieved = false;
		result_.message = "Odometry not initialized yet!!!";
		server_.setAborted(result_, result_.message);
		ROS_ERROR("%s", result_.message.c_str());
		return false;
	}
	alignment_mode_ = AlignmentModes::newInstance(goal->alignment_mode);
	switch (alignment_mode_)
	{
		case alignmentModes::FRONT: 
			left_index_ = 8;
			right_index_ = 1;
			lateral_ = false;
			break;
		case alignmentModes::RIGHT: 
			left_index_ = 6;
			right_index_ = 7;
			lateral_ = true;
			break;
		case alignmentModes::LEFT: 
			left_index_ = 2;
			right_index_ = 3;
			lateral_ = true;
			break;
		case alignmentModes::BACK: 
			left_index_ = 4;
			right_index_ = 5;
			lateral_ = false;
			break;
		case alignmentModes::FRONT_RIGHT: 
		case alignmentModes::FRONT_LEFT: 
		case alignmentModes::BACK_RIGHT: 
		case alignmentModes::BACK_LEFT:
			result_.goal_achieved = false;
			result_.message = "Alignment mode not supported yet: " + AlignmentModes::toString(alignment_mode_) + "!!!";
			server_.setAborted(result_, result_.message);
			ROS_ERROR("%s", result_.message.c_str());
			return false;
		default:
			result_.goal_achieved = false;
			result_.message = "Invalid alignment mode code!!!";
			server_.setAborted(result_, result_.message);
			ROS_ERROR("Invalid alignment mode code: %d!!!", goal->alignment_mode);
			return false;
	}
	distance_mode_ = DistanceModes::newInstance(goal->distance_mode);
	switch (distance_mode_)
	{
		case distanceModes::NORMAL: 
		case distanceModes::CLOSE:
		case distanceModes::FAR: 
			result_.goal_achieved = false;
			result_.message = "Distance mode not supported yet: " + DistanceModes::toString(distance_mode_) + "!!!";
			server_.setAborted(result_, result_.message);
			ROS_ERROR("%s", result_.message.c_str());
			return false;
		default:
			result_.goal_achieved = false;
			result_.message = "Invalid distance mode code!!!";
			server_.setAborted(result_, result_.message);
			ROS_ERROR("Invalid distance mode code: %d!!!", goal->distance_mode);
			return false;
	}
	percentage_ = 0;
	state_ = alignStates::ALIGNING;
	ROS_INFO("Goal accepted, aligning in %s %s mode!!!", DistanceModes::toString(distance_mode_).c_str(), AlignmentModes::toString(alignment_mode_).c_str());
	return true;
}

/**
 *
 */
void AlignServer::publishFeedback()
{
	feedback_.percentage = percentage_;
	feedback_.state = AlignStates::toString(state_);
	server_.publishFeedback(feedback_);
}


/**
 *
 */
void AlignServer::distanceSensorsCallback(const sensor_msgs::PointCloud& msg)
{
	if (!lateral_)
	{
		left_ir_ = msg.points[left_index_].x; 
		right_ir_ = msg.points[right_index_].x; 
	}
	else
	{
		left_ir_ = msg.points[left_index_].y; 
		right_ir_ = msg.points[right_index_].y;
	}
}

/**
 *
 */
void AlignServer::readParameters()
{
	
}