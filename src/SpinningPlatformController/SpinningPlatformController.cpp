// ----------------------------------------------------------------------------
// SpinningPlatformController.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "../SpinningPlatformController.h"


using namespace spinning_platform_controller;

SpinningPlatformController::SpinningPlatformController()
{
}

void SpinningPlatformController::setup()
{
  // Parent Setup
  StepperController::setup();

  // Variable Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Interrupts

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
                              properties_,
                              parameters_,
                              functions_,
                              callbacks_);

  // Properties
  modular_server::Property & channel_count_property = modular_server_.property(step_dir_controller::constants::channel_count_property_name);
  channel_count_property.setDefaultValue(constants::channel_count);
  channel_count_property.setValue(constants::channel_count);
  channel_count_property.setRange(step_dir_controller::constants::channel_count_min,constants::channel_count);

  modular_server::Property & steps_per_position_units_property = modular_server_.property(step_dir_controller::constants::steps_per_position_units_property_name);
  steps_per_position_units_property.setDefaultValue(constants::steps_per_position_units_default);
  steps_per_position_units_property.setValue(constants::steps_per_position_units_default);
  steps_per_position_units_property.setRange(constants::steps_per_position_units,constants::steps_per_position_units);

  modular_server::Property & microsteps_per_step_property = modular_server_.property(stepper_controller::constants::microsteps_per_step_property_name);
  microsteps_per_step_property.setDefaultValue(constants::microsteps_per_step_default);
  microsteps_per_step_property.setValue(constants::microsteps_per_step_default);
  microsteps_per_step_property.setRange(constants::microsteps_per_step,constants::microsteps_per_step);

  // Parameters

  // Functions
  modular_server::Function & get_platform_position_function = modular_server_.createFunction(constants::get_platform_position_function_name);
  get_platform_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PlatformController::getPlatformPositionHandler));
  get_platform_position_function.setResultTypeLong();

  modular_server::Function & get_platform_target_position_function = modular_server_.createFunction(constants::get_platform_target_position_function_name);
  get_platform_target_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PlatformController::getPlatformTargetPositionHandler));
  get_platform_target_position_function.setResultTypeLong();

  modular_server::Function & platform_at_target_position_function = modular_server_.createFunction(constants::platform_at_target_position_function_name);
  platform_at_target_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PlatformController::platformAtTargetPositionHandler));
  platform_at_target_position_function.setResultTypeBool();

  // Callbacks

  zeroAll();
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type
