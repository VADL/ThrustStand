/** @file    load_cell_sensor.cpp 
 *  @author  
 *  @date    2016-07-14T11:13:11-05:00
 *  @brief   This file contains definitions for the load_cell_sensor class; 
 */

#include "hardware_interfaces/load_cell_sensor.hpp"

// User Definitions
//::::/v/m/6/T/w::::Definitions::::


// Component Initialization 
void load_cell_sensor::init_timer_operation(const NAMESPACE::TimerEvent& event)
{
  // User Initialization Code
  //::::/v/m/6/T/w::::Initialization::::
  adcpin = config["User Configuration"]["ADC Pin"].asInt();


//fs.open("load_cell_data.log", std::fstream::out);
  init_timer.stop();
}

// Timer Operation - Timer
void load_cell_sensor::Timer_operation(const NAMESPACE::TimerEvent& event)
{
  //::::/v/m/6/T/w/E::::Operation::::
  adc_get_value(adcpin, &adcvalue);

logger->log("DEBUG", "%d", adcvalue);

//fs << adcvalue << "\n";
}



// Destructor - Cleanup Ports & Timers
load_cell_sensor::~load_cell_sensor()
{
  Timer.stop();
  // User Destruction
  //fs.close();
}

// Startup - Setup Component Ports & Timers
void load_cell_sensor::startUp()
{
  NAMESPACE::NodeHandle nh;
  std::string advertiseName;
  ros::Duration deadline;
  bool isOneShot;

  // Identify the pwd of Node Executable
  char szTmp[32];
  char pBuf[1024];
  memset(pBuf, 0, 1024);
  sprintf(szTmp, "/proc/%d/exe", getpid());
  readlink(szTmp, pBuf, 1024);

  std::string s = pBuf;
  std::string exec_path = s;
  std::string delimiter = "/";
  std::string exec, procDir;
  size_t pos = 0;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    exec = s.substr(0, pos);
    s.erase(0, pos + delimiter.length());
  }
  exec = s.substr(0, pos);
  procDir = exec_path.erase(exec_path.find(exec), exec.length());

  logger->create_file(procDir + '/' + config["Logging"]["Component Log FileName"].asString());
  logger->set_is_periodic(config["Logging"]["Enabled"].asBool());
  logger->set_max_log_unit(config["Logging"]["Unit"].asInt());

#ifdef USE_ROSMOD
  if ( config["Logging"]["Enabled"].asBool() ) {
    comp_queue.ROSMOD_LOGGER->enable_logging();
    comp_queue.ROSMOD_LOGGER->create_file( procDir + '/' + config["Logging"]["ROSMOD Log FileName"].asString());
    comp_queue.ROSMOD_LOGGER->set_max_log_unit(config["Logging"]["Unit"].asInt());
  }
#endif    
  
#ifdef USE_ROSMOD 
  this->comp_queue.scheduling_scheme = config["SchedulingScheme"].asString();
  rosmod::ROSMOD_Callback_Options callback_options;
#endif  

  // Servers
  // Clients
  // Publishers
  // Subscribers

  // Init Timer
#ifdef USE_ROSMOD    
  callback_options.alias = "init_timer_operation";
  callback_options.priority = 99;
  callback_options.deadline.sec = 1;
  callback_options.deadline.nsec = 0;
#endif
  NAMESPACE::TimerOptions timer_options;
  timer_options = 
    NAMESPACE::TimerOptions
    (ros::Duration(-1),
     boost::bind(&load_cell_sensor::init_timer_operation, this, _1),
     &this->comp_queue,
#ifdef USE_ROSMOD     
     callback_options,
#endif     
     true,
     false); 
  this->init_timer = nh.createTimer(timer_options);
  this->init_timer.stop();

  // Timers
  // Component Timer - Timer
#ifdef USE_ROSMOD   
  callback_options.alias = "Timer_operation";
  
  callback_options.priority = config["Timers"]["Timer"]["Priority"].asInt();
  deadline = ros::Duration(config["Timers"]["Timer"]["Deadline"].asFloat());
  callback_options.deadline.sec = deadline.sec;
  callback_options.deadline.nsec = deadline.nsec;
#endif
  isOneShot = (config["Timers"]["Timer"]["Period"].asFloat() == 0) ? true : false;
  timer_options = 
    NAMESPACE::TimerOptions
    (ros::Duration(config["Timers"]["Timer"]["Period"].asFloat()),
     boost::bind(&load_cell_sensor::Timer_operation, this, _1),
     &this->comp_queue,
#ifdef USE_ROSMOD     
     callback_options,
#endif 
     isOneShot,
     false);
  this->Timer = nh.createTimer(timer_options);
  this->Timer.stop();

  // Start the timers
  this->init_timer.start();
  this->Timer.start();
}

extern "C" {
  Component *maker(Json::Value &config) {
    return new load_cell_sensor(config);
  }
}

