#ifndef GenerateCircle_h
#define GenerateCircle_h

#include "Image.h"
#include "math.h"
class GenerateCircle : public Image {
public:
  GenerateCircle();
  GenerateCircle(int width, int height,int m);
  ~GenerateCircle(){
  	
  }
};

#endif