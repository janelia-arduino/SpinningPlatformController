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

  // Reset Watchdog
  resetWatchdog();

  // Variable Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Pins
  modular_server::Pin & bnc_a_pin = modular_server_.pin(modular_device_base::constants::bnc_a_pin_name);
  modular_server::Pin & btn_a_pin = modular_server_.pin(modular_device_base::constants::btn_a_pin_name);

#if defined(__MK64FX512__)
  modular_server::Pin & bnc_b_pin = modular_server_.pin(modular_device_base::constants::bnc_b_pin_name);
  modular_server::Pin & btn_b_pin = modular_server_.pin(modular_device_base::constants::btn_b_pin_name);
#endif

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
  steps_per_position_units_property.setValue(constants::steps_per_position_units_default,constants::CHANNEL_COUNT);
  steps_per_position_units_property.setRange(constants::steps_per_position_units,constants::steps_per_position_units);

  modular_server::Property & microsteps_per_step_property = modular_server_.property(stepper_controller::constants::microsteps_per_step_property_name);
  microsteps_per_step_property.setDefaultValue(constants::microsteps_per_step_default);
  microsteps_per_step_property.setValue(constants::microsteps_per_step_default,constants::CHANNEL_COUNT);
  microsteps_per_step_property.setRange(constants::microsteps_per_step,constants::microsteps_per_step);

  modular_server_.createProperty(constants::platform_position_min_property_name,constants::platform_position_min_default);

  modular_server_.createProperty(constants::platform_position_max_property_name,constants::platform_position_max_default);

  // Parameters
  modular_server::Parameter & platform_position_parameter = modular_server_.createParameter(constants::platform_position_parameter_name);
  platform_position_parameter.setTypeLong();

  // Functions
  modular_server::Function & move_platform_softly_to_function = modular_server_.createFunction(constants::move_platform_softly_to_function_name);
  move_platform_softly_to_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SpinningPlatformController::movePlatformSoftlyToHandler));
  move_platform_softly_to_function.addParameter(platform_position_parameter);
  move_platform_softly_to_function.setResultTypeBool();

  modular_server::Function & get_platform_position_function = modular_server_.createFunction(constants::get_platform_position_function_name);
  get_platform_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SpinningPlatformController::getPlatformPositionHandler));
  get_platform_position_function.setResultTypeLong();

  modular_server::Function & get_platform_target_position_function = modular_server_.createFunction(constants::get_platform_target_position_function_name);
  get_platform_target_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SpinningPlatformController::getPlatformTargetPositionHandler));
  get_platform_target_position_function.setResultTypeLong();

  modular_server::Function & platform_at_target_position_function = modular_server_.createFunction(constants::platform_at_target_position_function_name);
  platform_at_target_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SpinningPlatformController::platformAtTargetPositionHandler));
  platform_at_target_position_function.setResultTypeBool();

  // Callbacks
  modular_server::Callback & increment_platform_target_position_callback = modular_server_.createCallback(constants::increment_platform_target_position_callback_name);
  increment_platform_target_position_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&SpinningPlatformController::incrementPlatformTargetPositionHandler));
  increment_platform_target_position_callback.attachTo(bnc_a_pin,modular_server::pin::mode_falling);
  increment_platform_target_position_callback.attachTo(btn_a_pin,modular_server::pin::mode_falling);

  modular_server::Callback & decrement_platform_target_position_callback = modular_server_.createCallback(constants::decrement_platform_target_position_callback_name);
  decrement_platform_target_position_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&SpinningPlatformController::decrementPlatformTargetPositionHandler));
#if defined(__MK64FX512__)
  decrement_platform_target_position_callback.attachTo(bnc_b_pin,modular_server::pin::mode_falling);
  decrement_platform_target_position_callback.attachTo(btn_b_pin,modular_server::pin::mode_falling);
#endif

  zeroAll();
}

bool SpinningPlatformController::movePlatformSoftlyTo(const long absolute_platform_position)
{
  long position = limitedPlatformPosition(absolute_platform_position);
  position = platformPositionToPosition(position);
  moveSoftlyTo(constants::platform_channel,position);
  return true;
}

long SpinningPlatformController::getPlatformPosition()
{
  long platform_position = getPosition(constants::platform_channel);
  platform_position = positionToPlatformPosition(platform_position);

  return platform_position;
}

long SpinningPlatformController::getPlatformTargetPosition()
{
  long platform_position = getTargetPosition(constants::platform_channel);
  platform_position = positionToPlatformPosition(platform_position);

  return platform_position;
}

bool SpinningPlatformController::platformAtTargetPosition()
{
  return atTargetPosition(constants::platform_channel);
}

long SpinningPlatformController::incrementPlatformTargetPosition()
{
  long target_position = getPlatformTargetPosition();
  ++target_position;
  movePlatformSoftlyTo(target_position);
  return target_position;
}

long SpinningPlatformController::decrementPlatformTargetPosition()
{
  long target_position = getPlatformTargetPosition();
  --target_position;
  movePlatformSoftlyTo(target_position);
  return target_position;
}

long SpinningPlatformController::platformPositionToPosition(const long position)
{
  return position*constants::microsteps_per_platform_rev;
}

long SpinningPlatformController::positionToPlatformPosition(const long position)
{
  return position/constants::microsteps_per_platform_rev;
}

long SpinningPlatformController::limitedPlatformPosition(const long absolute_platform_position)
{
  long platform_position_min;
  modular_server_.property(constants::platform_position_min_property_name).getValue(platform_position_min);

  long platform_position_max;
  modular_server_.property(constants::platform_position_max_property_name).getValue(platform_position_max);

  long new_position = absolute_platform_position;

  if (new_position < platform_position_min)
  {
    new_position = platform_position_min;
  }
  else if (new_position > platform_position_max)
  {
    new_position = platform_position_max;
  }
  return new_position;
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
// const ConstantString *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void SpinningPlatformController::movePlatformSoftlyToHandler()
{
  long platform_position;
  modular_server_.parameter(constants::platform_position_parameter_name).getValue(platform_position);

  bool moving = movePlatformSoftlyTo(platform_position);
  modular_server_.response().returnResult(moving);
}

void SpinningPlatformController::getPlatformPositionHandler()
{
  long platform_position = getPlatformPosition();
  modular_server_.response().returnResult(platform_position);
}

void SpinningPlatformController::getPlatformTargetPositionHandler()
{
  long target_position = getPlatformTargetPosition();
  modular_server_.response().returnResult(target_position);
}

void SpinningPlatformController::platformAtTargetPositionHandler()
{
  bool platform_at_target_position = platformAtTargetPosition();
  modular_server_.response().returnResult(platform_at_target_position);
}

void SpinningPlatformController::incrementPlatformTargetPositionHandler(modular_server::Pin * pin_ptr)
{
  incrementPlatformTargetPosition();
}

void SpinningPlatformController::decrementPlatformTargetPositionHandler(modular_server::Pin * pin_ptr)
{
  decrementPlatformTargetPosition();
}
