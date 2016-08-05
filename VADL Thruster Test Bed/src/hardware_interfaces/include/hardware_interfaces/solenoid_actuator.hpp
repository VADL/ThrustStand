/** @file    solenoid_actuator.hpp 
 *  @author  
 *  @date    2016-07-14T11:13:11-05:00
 *  @brief   This file declares the solenoid_actuator class; 
 */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "node/Component.hpp"

/**
 * Component Message and Service Headers
 */

#ifdef USE_ROSMOD
  #include "rosmod/rosmod_ros.h"
#else
  #ifdef USE_ROSCPP
    #include "ros/ros.h"
  #endif
#endif

/**
 * Forward declarations
 */
//::::/v/m/6/T/D::::Forwards::::


/**
 * @brief solenoid_actuator class
 */
class solenoid_actuator : public Component
{
public:
  /**
   * @brief solenoid_actuator Constructor.
   * @param _config Component configuration parsed from deployment JSON
   */
  solenoid_actuator(Json::Value& _config)
  : Component(_config) {}

  /**
   * @brief solenoid_actuator Initializer
   * This operation is executed immediately after startup.
   * @param[in] event a oneshot timer event
   * @see startUp()
   */
  void init_timer_operation(const NAMESPACE::TimerEvent& event);




 /**
   * @brief Component startup function
   *
   * This function configures all the component ports and timers
   */ 
  void startUp();

 /**
   * @brief solenoid_actuator Destructor
   */ 
  ~solenoid_actuator();

private:


  /** 
   * User-defined private variables
   */
  //::::/v/m/6/T/D::::Members::::
  
};

#endif

