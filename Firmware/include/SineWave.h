#include <Arduino.h>

#include "SD.h"
#include "midiusb.h"

#define FREQUENCY 40
#define AMPLITUDE_DIVIDER 1
#define DEFINITION 12

MIDIusb MidiDevice;
const int btn = 0;
int previousBtnState = HIGH, iteration = 0;
boolean btnState, state = false;

void startMIDI(){
    MidiDevice.setBaseEP(3);
    MidiDevice.begin("MidiWaver");
    delay(1000);
}

void SetfixedPosition(int pos){
  for(int index = 1; index<=16; index++){
      MidiDevice.controlChange(index,pos);
      delay(10);
    }
}

double CalculateWavePosition(int index){
  return((sin(index * (3.1415/DEFINITION))+1)*64/(AMPLITUDE_DIVIDER >= 1 ? AMPLITUDE_DIVIDER : AMPLITUDE_DIVIDER + 1));
}

void SetWavePosition(int iteration){
  for(int index = 0; index < (DEFINITION*2); index++){
    if(index+iteration > -(DEFINITION*4) && index+iteration < (DEFINITION*4)){
      MidiDevice.controlChange(index+1,CalculateWavePosition(index+iteration));
    }else{
      MidiDevice.controlChange(index+1,64);
    }
  }
}

void StartAnimation(){
    iteration = 0;
    for(int index=(DEFINITION*4); index>=0; index--){
    SetWavePosition(index);
    delay(1000/FREQUENCY);
    }
}
void StopAnimation(){
    for(int index=-(DEFINITION*4)+iteration; index>=-((DEFINITION*4)+16); index--){
        SetWavePosition(index);
        delay(1000/FREQUENCY);
      }
}
void AnimationStep(){
    SetWavePosition(iteration);
    if(iteration > 0){
      iteration--;
    }else{
      iteration = (DEFINITION*2);
    }
    delay(1000/FREQUENCY);
}