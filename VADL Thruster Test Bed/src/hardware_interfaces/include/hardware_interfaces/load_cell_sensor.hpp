/** @file    load_cell_sensor.hpp 
 *  @author  
 *  @date    2016-07-14T11:13:11-05:00
 *  @brief   This file declares the load_cell_sensor class; 
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
//::::/v/m/6/T/w::::Forwards::::
#include <stdlib.h>
#include "bbbgpio/gpio.h"
//#include <fstream> 

/**
 * @brief load_cell_sensor class
 */
class load_cell_sensor : public Component
{
public:
  /**
   * @brief load_cell_sensor Constructor.
   * @param _config Component configuration parsed from deployment JSON
   */
  load_cell_sensor(Json::Value& _config)
  : Component(_config) {}

  /**
   * @brief load_cell_sensor Initializer
   * This operation is executed immediately after startup.
   * @param[in] event a oneshot timer event
   * @see startUp()
   */
  void init_timer_operation(const NAMESPACE::TimerEvent& event);

  /**
   * @brief Timer_operation; 
   *
   * This operation is executed every time the  
   * Timer operation request is serviced 
   * @param[in] event a timer event
   *
   * 
   */
  void Timer_operation(const NAMESPACE::TimerEvent& event);



 /**
   * @brief Component startup function
   *
   * This function configures all the component ports and timers
   */ 
  void startUp();

 /**
   * @brief load_cell_sensor Destructor
   */ 
  ~load_cell_sensor();

private:

  NAMESPACE::Timer Timer;  /*!< Timer Component Timer */

  /** 
   * User-defined private variables
   */
  //::::/v/m/6/T/w::::Members::::
  int adcpin;

unsigned int adcvalue;

//std::fstream fs;
};

#endif

