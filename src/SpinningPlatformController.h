// ----------------------------------------------------------------------------
// SpinningPlatformController.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef SPINNING_PLATFORM_CONTROLLER_H
#define SPINNING_PLATFORM_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <StepDirController.h>
#include <StepperController.h>

#include "SpinningPlatformController/Constants.h"


class SpinningPlatformController : public StepperController
{
public:
  SpinningPlatformController();
  virtual void setup();

  bool movePlatformSoftlyTo(long absolute_platform_position);
  long getPlatformPosition();
  long getPlatformTargetPosition();
  bool platformAtTargetPosition();

  long incrementPlatformTargetPosition();
  long decrementPlatformTargetPosition();

  long platformPositionToPosition(long platform_position);
  long positionToPlatformPosition(long position);
  long limitedPlatformPosition(long absolute_platform_position);

private:
  modular_server::Property properties_[spinning_platform_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[spinning_platform_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[spinning_platform_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[spinning_platform_controller::constants::CALLBACK_COUNT_MAX];

  // Handlers
  void movePlatformSoftlyToHandler();
  void getPlatformPositionHandler();
  void getPlatformTargetPositionHandler();
  void platformAtTargetPositionHandler();
  void incrementPlatformTargetPositionHandler(modular_server::Pin * pin_ptr);
  void decrementPlatformTargetPositionHandler(modular_server::Pin * pin_ptr);

};

#endif
