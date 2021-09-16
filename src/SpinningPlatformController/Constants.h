// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef SPINNING_PLATFORM_CONTROLLER_CONSTANTS_H
#define SPINNING_PLATFORM_CONTROLLER_CONSTANTS_H
#include <ConstantVariable.h>
#include <StepDirController.h>
#include <StepperController.h>


namespace spinning_platform_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=2};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=4};
enum{CALLBACK_COUNT_MAX=2};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

enum{CHANNEL_COUNT=1};
extern const long channel_count;
extern const long platform_channel;

extern const long full_steps_per_motor_rev;
extern const long motor_revs_per_shaft_rev;
extern const long steps_per_position_units;
extern const long microsteps_per_step;
extern const long shaft_revs_per_platform_rev;
extern const long microsteps_per_platform_rev;

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long steps_per_position_units_default[CHANNEL_COUNT];

extern const long microsteps_per_step_default[CHANNEL_COUNT];

extern ConstantString platform_position_min_property_name;
extern const long platform_position_min_default;

extern ConstantString platform_position_max_property_name;
extern const long platform_position_max_default;

// Parameters
extern ConstantString platform_position_parameter_name;

// Functions
extern ConstantString move_platform_softly_to_function_name;
extern ConstantString get_platform_position_function_name;
extern ConstantString get_platform_target_position_function_name;
extern ConstantString platform_at_target_position_function_name;

// Callbacks
extern ConstantString increment_platform_target_position_callback_name;
extern ConstantString decrement_platform_target_position_callback_name;

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
