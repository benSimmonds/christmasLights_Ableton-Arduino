#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();
//**** BANK ONE ****
#define iciclePin 6
#define treeBGPin 2
#define treeRYPin 4
#define treeControlPin 5
//**** BANK TWO ****
#define colour1Pin 9
#define starPin 10
#define nativityPin 11

int note=0;
int velo=0;
int chan=0;

//---------------------------------------------------------------------------
void lightOn(byte channel, byte pitch, byte velocity)
{
  note=(int) pitch;
  velo=(int) velocity *2;
  chan=(int) channel;
  if(note == 24){
    analogWrite(iciclePin, velo);
  }
  else if(note == 27){
    analogWrite(colour1Pin, velo);
  }
  else if(note == 34){
    analogWrite(starPin, velo);
  }
  else if(note == 35){
    analogWrite(nativityPin, velo);
  }
  else if(note == 36){
    digitalWrite(treeBGPin, HIGH);
    digitalWrite(treeRYPin, LOW);
    analogWrite(treeControlPin, velo);
  }
  else if(note == 37){
    digitalWrite(treeBGPin, LOW);
    digitalWrite(treeRYPin, HIGH);
    analogWrite(treeControlPin, velo);
  }
}

void lightOff(byte channel, byte pitch, byte velocity)
{
  note =(int) pitch;
  velo =(int) velocity;
  if(note == 24){
    digitalWrite(iciclePin, LOW);
  }
  else if(note == 27){
    digitalWrite(colour1Pin, LOW);
  }
  else if(note == 34){
    digitalWrite(starPin, LOW);
  }
  else if(note == 35){
    digitalWrite(nativityPin, LOW);
  }
  else if(note == 36){
    digitalWrite(treeRYPin, LOW);
    digitalWrite(treeControlPin, LOW);
  }
  else if(note == 37){
    digitalWrite(treeBGPin, LOW);
    digitalWrite(treeControlPin, LOW);
  }
}

//---------------------------------------------------------------------------

void setup() {
  //****BANK ONE****
  pinMode(iciclePin, OUTPUT);
  pinMode(treeRYPin, OUTPUT);
  pinMode(treeBGPin, OUTPUT);
  pinMode(treeControlPin, OUTPUT);
  digitalWrite(treeRYPin, LOW);
  digitalWrite(treeBGPin, LOW);
  //****BANK TWO****
  pinMode(colour1Pin, OUTPUT);
  pinMode(starPin, OUTPUT);
  pinMode(nativityPin, OUTPUT);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(lightOn);
  MIDI.setHandleNoteOff(lightOff);
  Serial.begin(115200); //COM5 linked to Hairless MIDI ***REMEMBER THIS MUST FOLLOW MIDI.begin()*** (Don't know why)
}

void loop() {
  MIDI.read();
}
