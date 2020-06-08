#ifndef Led8x8_h
#define Led8x8_h

#include "Arduino.h"

/**
 *
 */
class Led8x8 {
protected:
  int pinClk;
  int pinCs;
  int pinDin;

  unsigned char Disp[8] = {
    B10000000,
    B01000000,
    B00000001,
    B00000010,
    B00001000,
    B00001000,
    B00000000,
    B00000001,
  };
  
public:
  Led8x8(int, int, int);
  void writeByte(unsigned char data);
  void writeM(unsigned char address, unsigned char data);
  
  void pixel(int x, int y, boolean on);
  boolean getPixel(int x, int y);
  
  void rect(int x, int y, int w, int h, boolean on);
  
  void set();
  
  void invert();
  void fill(boolean on);
  void clear();
  
  void rotate90();
  
  void getMatrix(unsigned char*);
  void setMatrix(unsigned char*);
};

#endif
