// ----------------------------------------------------------------------------
// SpinningPlatform.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef SPINNING_PLATFORM_H
#define SPINNING_PLATFORM_H
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

#include "SpinningPlatform/Constants.h"


class SpinningPlatform : public StepperController
{
public:
  SpinningPlatform();
  virtual void setup();

private:
  modular_server::Property properties_[spinning_platform::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[spinning_platform::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[spinning_platform::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[spinning_platform::constants::CALLBACK_COUNT_MAX];

  // Handlers

};

#endif
