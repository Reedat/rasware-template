#include <raslib/inc/common.h>
#include <raslib/inc/servo.h>

#include "RASDemo.h"

static tServo *servo;
static tBoolean initialized = false;

void initServo(void) {
  // don't initialize this if we've already done so
  if (initialized) {
    return;
  }

  initialized = true;

  servo = InitializeServo(PIN_B0);
}

void servoDemo(void) {
  float position = 0;
  char newline = 13;
  char ch;

  Printf(
      "Press:\n"
      "  a-'up' 0.10\n"
      "  w-'up' 0.01\n"
      "  s-'down' 0.01\n"
      "  d-'down' 0.10\n"
      "  enter-quit\n");

  // wait for the user to enter a character
  ch = Getc();

  while (ch != newline) {
    switch (ch) {
      case 'w':
        position += 0.01F;
        break;
      case 's':
        position -= 0.01F;
        break;
      case 'a':
        position += 0.10F;
        break;
      case 'd':
        position -= 0.10F;
        break;
      default:
        position = position;
    }

    // bounds checking (done in SetServo, but also useful to bound it here for
    // the demo)
    if (position > 1.0F) {
      position = 1.0F;
    } else if (position < 0.0F) {
      position = 0.0F;
    }

    SetServo(servo, position);
    Printf("set servo to %1.2f\r", position);

    ch = Getc();
  }

  Printf("\n");
}
