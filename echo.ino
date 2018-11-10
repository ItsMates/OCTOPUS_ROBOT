//echo
const int TRIG_PIN = PIN_PWM1;
const int ECHO_PIN = PIN_PWM2;

// interrupt handling variables
volatile long _start_micros = 0;
volatile long _lenght = 0;
volatile bool _finished = false;

//last read echo distance
int _distance = 0;

unsigned long _millis_last = 0;

//trigger the echo (sends the sound pulse)
void _pulse(int interval) {
  if (millis() < _millis_last + interval) {
    return;
  }

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  _millis_last = millis();
}

// Handle interrupt - read pulse length
void _handleEcho() {  
  if (digitalRead(ECHO_PIN) == HIGH) {
    _start_micros = micros();
  } else {
    _lenght = micros() - _start_micros;
    _finished = true;
  }
}

//echo setup
void initEcho() {
  pinMode(ECHO_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), _handleEcho, CHANGE);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
}

//needs to be periodically updated in loop
int updateEcho() {
  if (_finished) {
    _distance = _lenght * 0.17;
    _finished = false;
  }
  _pulse(50);
  return _distance;
}
