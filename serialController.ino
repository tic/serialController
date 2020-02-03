#define BTN_PIN 2
#define LED_PIN 1
#define JOYSTICK_X A0
#define JOYSTICK_Y A1

#define MIDDLE 512
#define THRESHOLD 100


#define BTN_A_DOWN "\x20"
#define BTN_A_UP "\x21"
#define JOYSTICK_GO_LF "\x24"
#define JOYSTICK_LV_LF "\x25"
#define JOYSTICK_GO_UP "\x26"
#define JOYSTICK_LV_UP "\x27"
#define JOYSTICK_GO_RT "\x28"
#define JOYSTICK_LV_RT "\x29"
#define JOYSTICK_GO_DN "\x2A"
#define JOYSTICK_LV_DN "\x2B"

void setup()
{
    pinMode(BTN_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(JOYSTICK_X, INPUT);
    pinMode(JOYSTICK_Y, INPUT);
    Serial.begin(9600);
}

bool button = false;
int xpos = 0;
int ypos = 0;

int beyondThreshold(int reading) {
  if(reading > MIDDLE + THRESHOLD) return 1;
  if(reading < MIDDLE + THRESHOLD) return -1;
  return 0;
}

void loop()
{
    bool btnA = digitalRead(BTN_PIN);
    if(btnA != button) { // If they disagree, there will be an update.
        button = btnA;
        Serial.write(btnA ? BTN_A_DOWN : BTN_A_UP);
    }



    // the 8 different joystick axis changes
    // this uses -1 as left, but -1 would be up on the y axis

    // -1 -1 --> -1, send "" (nothing)

    // -1  0 -->  0, send "\x25" (leave left)
    // -1  1 -->  1, send "\x25\x28" (leave left, enter right)
    //  0 -1 --> -1, send "\x24" (enter left)
    //  0  0 -->  0, send "" (nothing)
    //  0  1 -->  1, send "\x28" (enter right)
    //  1 -1 --> -1, send "\x29\x24" (leave right, enter left)
    //  1  0 -->  0, send "\x29" (leave right)
    //  1  1 -->  1, send "" (nothing)

    int joystickX = beyondThreshold(analogRead(JOYSTICK_X));
    int joystickY = beyondThreshold(analogRead(JOYSTICK_Y));
    String jsBytes = "";
    if(xpos != joystickX) { // If they disagree, there will be an update.
      // Resolve "leaving" bytes
      if(xpos == -1) jsBytes = JOYSTICK_LV_LF;
      else if(xpos == 1) jsBytes = JOYSTICK_LV_RT;

      // Resolve "entering" bytes
      if(joystickX == -1) jsBytes += JOYSTICK_GO_LF;
      else if(joystickX == 1) jsBytes += JOYSTICK_GO_RT;

      xpos = joystickX;
    }

    if(joystickY != ypos) { // If they disagree, there will be an update.
      // Resolve "leaving" bytes
      if(ypos == -1) jsBytes += JOYSTICK_LV_UP;
      else if(ypos == 1) jsBytes += JOYSTICK_LV_DN;

      // Resolve "entering" bytes
      if(joystickY == -1) jsBytes += JOYSTICK_GO_UP;
      else if(joystickY == 1) jsBytes += JOYSTICK_GO_DN;

      ypos = joystickY;
    }

    if(jsBytes =! "") Serial.write(jsBytes); // Send joystick commands, if they exist.

    digitalWrite(LED_PIN, button ? HIGH : LOW);
    delay(10);
}
