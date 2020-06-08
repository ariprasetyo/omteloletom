#include "Arduino.h"
#include "Melody.h"

/**
 *
 */
Melody::Melody(int p) {
  pin = p;

  pinMode(pin, OUTPUT);
}

/**
 *
 */
void Melody::setMelody(char* m) {
  melody = m;
}

/**
 *
 */
int Melody::note2Index(float n) {
  int noteDomainCount = sizeof(noteDomain) / sizeof(float);
  
  for (int i = 0; i < noteDomainCount; i++) {
    if (n == noteDomain[i]) {
      return i;
    }
  }
  
  return -1;
}

/**
 *
 */
float Melody::note2Freq(float n) {
  return MidC * pow(s12, note2Index(n));
}

/**
 *
 */
void Melody::playNote(float n, float d) {
  float duration = d * dt;
  
  if (n > 0) {    
    float freq = note2Freq(n);

    tone(pin, freq);
    noteLed(n);
    indicatorLed(true);    
    delay(duration - 10);
    
    noteLed(0);
    indicatorLed(false);
    delay(10);
    
  }
  else {
    noTone(pin);
    noteLed(0);
    delay(duration);
  }
}

/**
 *
 */
void Melody::noteLed(float n) {
  /*digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, note2Bin(n, key));
  digitalWrite(latchPin, HIGH);*/
}

/**
 *
 */
void Melody::indicatorLed(boolean b) {
  /*int hilo = (b)? HIGH: LOW;

  digitalWrite(led, hilo);
  digitalWrite(iled, hilo);*/
}

/**
 *
 */
void Melody::playMelody(char* s) {
  String noteStr = "";
  String durStr = "";
  int octave = 0;
  float note = 0;
  float dur = 0;
  
  boolean play = false;
  
  char state = 'b';
  char prevState = 'b';
  String prevAtom = "";
  String atom = "";
  
  int i = 0;
  int len = strlen(s);
  
  while (i < len) {
    char ch = s[i];
    play = false;
    
    if (isNote(ch)) state = 'n';
    else if (isMod(ch)) state = 'm';
    else if (isOctave(ch)) state = 'o';
    else if (isDuration(ch)) state = 'd';
    else state = 'b';
    
    if (prevState != state) {
      if (prevState == 'd') {
        dur = 0;
        if (durStr.length() > 0) {
          char buffer[10];
          durStr.toCharArray(buffer, 10);
          dur = atof(buffer);
        }
        
        playNote(note, dur);
      }
    }
    
    if (state == 'b') {  // Blank
      note = 0;
      octave = 0;
      dur = 0;
      durStr = "";
      play = false;
    }
    else if (state == 'n') {  // Note
      note = char2Note(ch);
    }
    else if (state == 'm') {  // Mod
      if (ch == '/') note += 0.5;
      else if (ch == '\\') note -= 0.5;        
    }
    else if (state == 'o') {  // Octave
      if (ch == '+') note += 7;
      else if (ch == '-') note -= 7;
    }
    else if (state == 'd') {  // Duration
      durStr += ch;
    }
    
    prevState = state;
    
    i ++;
  }
}

/**
 *
 */
void Melody::play() {
  playMelody(melody);
}

/**
 *
 */
void Melody::next() {
  String noteStr = "";
  String durStr = "";
  int octave = 0;
  float note = 0;
  float dur = 0;
  
  boolean play = false;
  
  char state = 'b';
  char prevState = 'b';
  String prevAtom = "";
  String atom = "";
  
  int i = index;
  int len = strlen(melody);
  
  while (i < len) {
    char ch = melody[i];
    play = false;
    
    if (isNote(ch)) state = 'n';
    else if (isMod(ch)) state = 'm';
    else if (isOctave(ch)) state = 'o';
    else if (isDuration(ch)) state = 'd';
    else state = 'b';
    
    if (prevState != state) {
      if (prevState == 'd') {
        dur = 0;
        if (durStr.length() > 0) {
          char buffer[10];
          durStr.toCharArray(buffer, 10);
          dur = atof(buffer);
        }
        
        playNote(note, dur);
      }
    }
    
    if (state == 'b') {  // Blank
      note = 0;
      octave = 0;
      dur = 0;
      durStr = "";
      play = false;
      
      index = i + 1;
      break;
    }
    else if (state == 'n') {  // Note
      note = char2Note(ch);
    }
    else if (state == 'm') {  // Mod
      if (ch == '/') note += 0.5;
      else if (ch == '\\') note -= 0.5;        
    }
    else if (state == 'o') {  // Octave
      if (ch == '+') note += 7;
      else if (ch == '-') note -= 7;
    }
    else if (state == 'd') {  // Duration
      durStr += ch;
    }
    
    prevState = state;
    
    i ++;
  }

}

/**
 *
 */
boolean Melody::isDuration(char ch) {
  return (ch >= '0' && ch <= '9') || (ch == '.');
}

/**
 *
 */
boolean Melody::isNote(char ch) {
  return (ch >= 'a' && ch <= 'g')
    || (ch >= 'A' && ch <= 'G');
}

/**
 *
 */
boolean Melody::isMod(char ch) {
  return (ch == '/') || (ch == '\\');
}

/**
 *
 */
boolean Melody::isOctave(char ch) {
  return (ch == '+') || (ch == '-');
}

/**
 *
 */
float Melody::char2Note(char ch) {
  String notes = "cdefgab";
  
  for (int i = 0; i < notes.length(); i++) {
    if (ch == notes[i]) {
      return (int)(i + 1) + 7;
    }
  }
  
  return 0;
}

/**
 *
 */
int Melody::note2Bin(float n, float key) {
  int i = note2Index(n);
  int k = note2Index(key);
  
  int d = (i - k) + 1;
  
  if (d == 1) return 1;
  else if (d == 3) return 2;
  else if (d == 5) return 4;
  else if (d == 6) return 8;
  else if (d == 8) return 16;
  else if (d == 10) return 32;
  else if (d == 12) return 64;
  else if (d == 13) return 128;
  
  else if (d == 2) return 3;
  else if (d == 4) return 6;
  else if (d == 7) return 24;
  else if (d == 9) return 48;
  else if (d == 11) return 96;
  //else if (d == 7.5) return 192;
  
  return 0;
}


