#include "config.h"

#define MQ_PIN A0

int current = 0;
int mapped = 0;
int last = -1;

AdafruitIO_Feed *mq = io.feed("mq");

void setup() {

  Serial.begin(115200);

  while(! Serial);

  Serial.print("Connecting to Adafruit IO");
  io.connect();

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  io.run();

  current = analogRead(MQ_PIN);

  mapped = map(current, 150, 430, 0, 100);

  if(current == last)
    return;

  Serial.print("Serial -> ");
  Serial.println(current);
  Serial.print("Sending -> ");
  Serial.println(mapped);
  mq->save(mapped);

  last = mapped;

  delay(3000);
}
