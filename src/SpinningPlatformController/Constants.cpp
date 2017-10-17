// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace spinning_platform_controller
{
namespace constants
{
CONSTANT_STRING(device_name,"spinning_platform_controller");

CONSTANT_STRING(firmware_name,"SpinningPlatformController");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
  {
    .name_ptr=&firmware_name,
    .version_major=1,
    .version_minor=0,
    .version_patch=0,
  };

const long channel_count = CHANNEL_COUNT;
const long platform_channel = 0;

const long full_steps_per_motor_rev = 200;
const long motor_revs_per_shaft_rev = 100;
const long steps_per_position_units = 1;
const long microsteps_per_step = 1;
const long shaft_revs_per_platform_rev = 1;
const long microsteps_per_platform_rev = (full_steps_per_motor_rev*motor_revs_per_shaft_rev*microsteps_per_step*shaft_revs_per_platform_rev)/steps_per_position_units;

// Interrupts

// Units

// Properties
const long steps_per_position_units_default[CHANNEL_COUNT] =
  {
   steps_per_position_units,
  };


const long microsteps_per_step_default[CHANNEL_COUNT] =
  {
   microsteps_per_step,
  };

// Parameters
CONSTANT_STRING(stage_position_parameter_name,"stage_position");

// Functions
CONSTANT_STRING(get_platform_position_function_name,"getPlatformPosition");
CONSTANT_STRING(get_platform_target_position_function_name,"getPlatformTargetPosition");
CONSTANT_STRING(platform_at_target_position_function_name,"platformAtTargetPosition");

// Callbacks

// Errors
}
}
