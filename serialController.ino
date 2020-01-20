#define BTN_PIN 2
#define LED_PIN 1

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
      Serial.write("button pressed\n");
    }

    if(button && digitalRead(BTN_PIN) == LOW) {
      button = false;
      Serial.write("button released\n");
    }

    digitalWrite(LED_PIN, button ? HIGH : LOW);
    delay(10);
}
