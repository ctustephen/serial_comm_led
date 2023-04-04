#define LED1 3

byte option = 0;
bool blink = 0;
int brightness = 0;
int fadeAmount = 5;
long millis1 = 0;

void setup() {
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, HIGH);

  Serial.println("Ready...");
}

void loop() {

  if (Serial.available() > 0)
  {
    String data = Serial.readStringUntil('\n');
    Serial.println(data);

    if (data == "on")
    {
      Serial.println("reply: on");
      option = 1;
    }
    else if (data == "off")
    {
      Serial.println("reply: off");
      option = 2;
    }
    else if (data == "blink") {
      long millis1 = 0;
      Serial.println("reply: blink");
      option = 3;
    }
    else if (data == "fade")
    {
      Serial.println("reply: fade");
      option = 4;
    }
  }

  if (option == 1)
  {
    digitalWrite(LED1, LOW);
  }
  else if (option == 2)
  {
    digitalWrite(LED1, HIGH);
  }
  else if (option == 3) {
    if (blink && millis() - millis1 > 1000) {
      digitalWrite(LED1, LOW);
      millis1 = millis();
    } else if (millis() - millis1 > 1000) {
      digitalWrite(LED1, HIGH);
      millis1 = millis();
    }
    blink = !blink;
  }
  else if (option == 4)
  {
    digitalWrite(LED1, HIGH);
    analogWrite(LED1, brightness);
    brightness = brightness + fadeAmount;
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
    delay(30);
  }
}
