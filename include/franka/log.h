// Copyright (c) 2017 Franka Emika GmbH
// Use of this source code is governed by the Apache-2.0 license, see LICENSE
#pragma once

#include <vector>

#include <franka/control_types.h>
#include <franka/robot_state.h>

/**
 * @file log.h
 * Contains helper types for logging sent commands and received robot states.
 */

namespace franka {

/**
 * Command sent to the robot. Structure used only for logging purposes.
 */
struct RobotCommand {
  /**
   * q_d sent to the robot.
   */
  JointPositions joint_positions{0, 0, 0, 0, 0, 0, 0};
  /**
   * dq_d sent to the robot.
   */
  JointVelocities joint_velocities{0, 0, 0, 0, 0, 0, 0};
  /**
   * O_T_EE_d sent to the robot.
   */
  CartesianPose cartesian_pose{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
  /**
   * O_dP_EE sent to the robot.
   */
  CartesianVelocities cartesian_velocities{0, 0, 0, 0, 0, 0};
  /**
   * tau_J_d sent to the robot.
   */
  Torques torques{0, 0, 0, 0, 0, 0, 0};
};

/**
 * One row of the log, containing the received robot state
 * and the corresponding robot command. Provided by the ControlException.
 */
struct Record {
  /**
   * Received robot state.
   */
  RobotState state;
  /**
   * Command sent after receiving that state.
   */
  RobotCommand command;
};

/**
 * Writes the log to a string in CSV format. If the string is not empty, the first row contains the
 * header with names of columns. The following lines contain rows of values separated by commas.
 *
 * If the log is empty, the function returns an empty string.
 *
 * @param[in] log Log provided by the ControlException.
 *
 * @return a string in CSV format, or empty string.
 */
std::string logToCSV(const std::vector<Record>& log);
}  // namespace franka
