#ifndef Melody_h
#define Melody_h

#include "Arduino.h"

/**
 *
 */
class Melody {
protected:
  int pin;
  
  char* melody;
  
  int index = 0;
  
  const float MidC = 261.6;
  const float LowC = 130.8;
  const float s12 = 1.059463094359295;
  float dt = 500;
  float key = 5;

  float noteDomain[36] = {
    1, 1.5, 2, 2.5, 3, 4, 4.5, 5, 5.5, 6, 6.5,  7,
    8, 8.5, 9, 9.5, 10, 11, 11.5, 12, 12.5, 13, 13.5, 14,
    15, 15.5, 16, 16.5, 17, 18, 18.5, 19, 19.5, 20, 20.5, 21
  };

public:
  Melody(int);
  
  void setMelody(char* m);
  
  int note2Index(float n);
  float note2Freq(float n);
  void playNote(float n, float d);
  void noteLed(float n);

  void indicatorLed(boolean b);
  void playMelody(char* s);
  void play();
  void next();

  boolean isDuration(char ch);

  boolean isNote(char ch);

  boolean isMod(char ch);
  boolean isOctave(char ch);

  float char2Note(char ch);

  int note2Bin(float n, float key);

};

#endif
