#define BTN_PIN 2
#define LED_PIN 1

#define BTN_A_DOWN "\x20"
#define BTN_A_UP "\x21"


void setup()
{
    pinMode(BTN_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);
}

bool button = false;

void loop()
{
    //test comment
    if(!button && digitalRead(BTN_PIN) == HIGH) {
      button = true;
      Serial.write(BTN_A_DOWN);
    }

    if(button && digitalRead(BTN_PIN) == LOW) {
      button = false;
      Serial.write(BTN_A_UP);
    }

    digitalWrite(LED_PIN, button ? HIGH : LOW);
    delay(10);
}
