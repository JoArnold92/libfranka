#pragma once

#include <memory>
#include <string>

#include <franka/exception.h>
#include <franka/robot_state.h>

/**
 * @file robot.h
 * Contains the Robot class.
 */

namespace franka {

/**
 * Maintains a connection to FRANKA CONTROL and provides the current
 * robot state.
 */
class Robot {
 public:
  /**
   * Version of the server running on FRANKA.
   */
  using ServerVersion = uint16_t;

  /**
   * Tries to establish a connection with the FRANKA robot.
   *
   * @throw NetworkException if the connection is unsuccessful.
   * @throw IncompatibleVersionException if this library is not supported by
   * FRANKA CONTROL
   * @throw ProtocolException if data received from the host is invalid
   *
   * @param[in] franka_address IP/hostname of FRANKA CONTROL
   */
  explicit Robot(const std::string& franka_address);
  ~Robot() noexcept;

  /**
   * Blocks until new robot state arrives. When the function returns true, the
   * reference from getRobotState() points to new data.
   *
   * @throw NetworkException if the connetion is lost, e.g. after a timeout.
   * @throw ProtocolException if received data has invalid format.
   *
   * @return True if a new robot state arrived, false if the connection is
   * cleanly closed.
   */
  bool waitForRobotState();

  /**
   * Returns last obtained robot state. Updated after a call to
   * waitForRobotState().
   *
   * @return const reference to RobotState structure
   */
  const RobotState& robotState() const noexcept;

  /**
   * Returns the version reported by the connected server.
   *
   * @return Version of the connected server.
   */
  ServerVersion serverVersion() const noexcept;

  Robot(const Robot&) = delete;
  Robot& operator=(const Robot&) = delete;

 protected:
  class Impl;

 private:
  std::unique_ptr<Impl> impl_;
};

}  // namespace franka