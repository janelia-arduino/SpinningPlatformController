#include <SpinningPlatformController.h>


SpinningPlatformController dev;

void setup()
{
  dev.setup();
  dev.startServer();
}

void loop()
{
  dev.update();
}
