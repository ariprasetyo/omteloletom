#include <Melody.h>
#include <Led8x8.h>

Led8x8* disp;
Melody* melody;

unsigned char __[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
};

unsigned char _O[8] = {
  B00000000,
  B00111100,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B00111100,
  B00000000,
};

unsigned char _E[8] = {
  B00000000,
  B01111110,
  B01100000,
  B01111100,
  B01111100,
  B01100000,
  B01111110,
  B00000000,
};

unsigned char _M[8] = {
  B00000000,
  B01000010,
  B01100110,
  B01011010,
  B01000010,
  B01000010,
  B01000010,
  B00000000,
};

unsigned char _T[8] = {
  B00000000,
  B01111110,
  B01111110,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00000000,
};

unsigned char _L[8] = {
  B00000000,
  B01100000,
  B01100000,
  B01100000,
  B01100000,
  B01111110,
  B01111110,
  B00000000,
};

unsigned char _horn[8] = {
  B00000000,
  B00000010,
  B00000110,
  B00111110,
  B00111110,
  B00000110,
  B00000010,
  B00000000,
};

unsigned char _smile[8] = {
  B00000000,
  B01100110,
  B01100110,
  B00000000,
  B01000010,
  B01000010,
  B00111100,
  B00000000,
};

#define LENGTH 16

unsigned char* text[LENGTH] = {
  __,
  _O, _M,
  __,
  _T, _E, _L, _O, _L, _E, _T,
  __,
  _O, _M,
  __,
  _horn
};

char* mels = 
  "c0.25 d0.25 e0.25 "
  "c0.25 d0.25 e0.25 "
  "c0.25 d0.25 e0.25 "
  "c0.25 d0.25 e0.25 "
  " 1 1"
  ;

int k = 0;
boolean invert = false;

/**
 *
 */
void setup() {
  delay(50);
  
  disp = new Led8x8(10, 9, 8);
  disp->clear();
  
  melody = new Melody(3);
  melody->setMelody(mels);
}

/**
 *
 */
void loop() {
  disp->clear();
  
  scroll(
    text[k], text[k + 1],
    (invert)? 30: 50
  );
  
  k++;
  if (k >= LENGTH - 1) {
    k = 0;
    invert = ! invert;
    
    melody->play();  
  }
  
  if (! invert) delay (50);  
  //delay(20);

}

/**
 *
 */
void scroll(unsigned char* A, unsigned char* B, int d) {
  unsigned char M[8];
  
  for (int k = 0; k < 8; k++) {  
    for (int y = 0; y < 8; y++) {
      M[y] = A[y] << k | B[y] >> (7 - k);
    }
    
    disp->setMatrix(M);
    disp->rotate90();
    if (invert) disp->invert();
    disp->set();
    
    delay(d);
  }
}
