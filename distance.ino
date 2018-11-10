
#define DISTANCE_PIN SPI_CLOCK

void initDistance() {
  pinMode(DISTANCE_PIN, INPUT);
}

bool getDistance() {
   return !digitalRead(DISTANCE_PIN);
}
