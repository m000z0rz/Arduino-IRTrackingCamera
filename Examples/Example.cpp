// https://www.dfrobot.com/wiki/index.php/Positioning_ir_camera

// This example simply prints the four sets of point coordinates detected
//    by the sensor to the Serial port (at 9600 baud)

#include "Arduino.h"
#include <Wire.h>  // For now with PlatformIO, we need to include Wire.h here too
#include "IRTrackingCamera.h"

IRTrackingCamera irCam;

void printPaddedInt(int i)
{
  if(i < 1000) Serial.print(" ");
  if(i < 100) Serial.print(" ");
  if(i < 10) Serial.print(" ");
  Serial.print(i);
}



void setup()
{
  Serial.begin(9600);

  irCam.initialize();
}
void loop()
{
  irCam.update();

  Vector2 v;
  for(int i = 0; i < 4; i++)
  {
    v = irCam.Points[i];

    printPaddedInt(v.x);
    Serial.print(",");

    printPaddedInt(v.y);
    Serial.print(v.y);

    Serial.print(" : ");
  }
  Serial.println();

  delay(100);
}
