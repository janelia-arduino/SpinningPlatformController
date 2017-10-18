// ----------------------------------------------------------------------------
// SpinningPlatformController.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef SPINNING_PLATFORM_CONTROLLER_H
#define SPINNING_PLATFORM_CONTROLLER_H
#include <Flash.h>
#include <EEPROM.h>
#include <Streaming.h>
#include <ArduinoJson.h>
#include <JsonSanitizer.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <MemoryFree.h>
#include <ConstantVariable.h>
#include <SavedVariable.h>
#include <Functor.h>
#include <IndexedContainer.h>
#include <FunctorCallbacks.h>

#include <ModularClient.h>

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

  bool movePlatformSoftlyTo(const long absolute_platform_position);
  long getPlatformPosition();
  long getPlatformTargetPosition();
  bool platformAtTargetPosition();

  long incrementPlatformTargetPosition();
  long decrementPlatformTargetPosition();

  long platformPositionToPosition(const long platform_position);
  long positionToPlatformPosition(const long position);
  long limitedPlatformPosition(const long absolute_platform_position);

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
  void incrementPlatformTargetPositionHandler(modular_server::Interrupt * interrupt_ptr);
  void decrementPlatformTargetPositionHandler(modular_server::Interrupt * interrupt_ptr);

};

#endif
