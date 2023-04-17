#include <Arduino.h>
#if ARDUINO_USB_MODE
#warning This sketch should be used when USB is in OTG mode
void setup(){}
void loop(){}
#else

#include <SineWave.h>

#define FREQUENCY 45
#define AMPLITUDE_DIVIDER 1
#define DEFINITION 16

void setup() {
  pinMode(btn, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  startMIDI();
}

void loop() {
  btnState = digitalRead(btn);

  if((btnState != previousBtnState && btnState == LOW)){
    
    state = !state;
    digitalWrite(LED_BUILTIN, state);

    if(state){
      StartAnimation();
    }else{
      StopAnimation();
    }
  }
  previousBtnState = btnState;

  if(state){
    AnimationStep();
  }
}
#endif