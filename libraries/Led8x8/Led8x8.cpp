#include "Arduino.h"
#include "Led8x8.h"

/**
 *
 */
Led8x8::Led8x8(int pclk = 10, int pcs = 9, int pdin = 8) {
  pinClk = pclk;
  pinCs = pcs;
  pinDin = pdin;
  
  pinMode(pinClk, OUTPUT);
  pinMode(pinCs, OUTPUT);
  pinMode(pinDin, OUTPUT);
  
  writeM(0x09, 0x00);
  writeM(0x0a, 0x03);
  writeM(0x0b, 0x07);
  writeM(0x0c, 0x01);
  writeM(0x0f, 0x00);
}

/**
 *
 */
void Led8x8::writeByte(unsigned char data) {
  digitalWrite(pinCs, LOW);
  
  for (int i = 0; i< 8; i++) {
    digitalWrite(pinClk, LOW);
    digitalWrite(pinDin, data & 0x80);
    data = data << 1;
    digitalWrite(pinClk, HIGH);
  }
}

/**
 *
 */
void Led8x8::writeM(unsigned char address, unsigned char data) {
  digitalWrite(pinCs, LOW);
  writeByte(address);
  writeByte(data);
  digitalWrite(pinCs, HIGH);
}

/**
 *
 */
void Led8x8::pixel(int x, int y, boolean on = true) {
  if (x >= 0 && x < 8 && y >= 0 && y < 8) {
    unsigned char b = 128 >> x;//1 << (7 - x);
    
    if (! on) {
      Disp[y] &= ~ b;
    }
    else {    
      Disp[y] |= b;
    }
  }
}

/**
 *
 */
boolean Led8x8::getPixel(int x, int y) {
  if (x >= 0 && x < 8 && y >= 0 && y < 8) {
    unsigned char row = Disp[y];
    
    unsigned char mask = 128 >> x;// << (7 - x);
    
    unsigned char b = row && mask;
    
    return (b > 0);
  };  
  
  return false;  
}

/**
 *
 */
void Led8x8::rect(int x, int y, int w, int h, boolean on = true) {
  for (int px = x; px < x + w; px ++) {
    for (int py = y; py < y + h; py ++) {
      pixel(px, py, on);
    }
  }
}

/**
 *
 */
void Led8x8::set() {
  for (int x = 0; x < 8; x++) {
    writeM(x + 1, Disp[x]);
  }
}

/**
 *
 */
void Led8x8::invert() {
  for (int x = 0; x < 8; x++) {
    Disp[x] = ~ Disp[x];
  }
}

/**
 *
 */
void Led8x8::rotate90() {
  unsigned char matrix[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  for (int x = 0; x < 8; x++) {
    unsigned char mask = 128 >> x;
  
    for (int y = 0; y < 8; y++) {
      if ((Disp[y] & mask) > 0) {
        unsigned char masky = 1 << y;
      
        matrix[x] = matrix[x] | masky;
      }
    }
  }
  
  setMatrix(matrix);
}

/**
 *
 */
void Led8x8::fill(boolean on) {
  unsigned char b = on? 255: 0;
  
  for (int y = 0; y < 8; y++) {
    Disp[y] = b;
  }
}

/**
 *
 */
void Led8x8::clear() {
  fill(false);
}

/**
 *
 */
void Led8x8::getMatrix(unsigned char* matrix) {
  for (int i = 0; i < 8; i++) {
    matrix[i] = Disp[i];
  }
}

/**
 *
 */
void Led8x8::setMatrix(unsigned char* matrix) {
  for (int i = 0; i < 8; i++) {
    Disp[i] = matrix[i];
  }
}

