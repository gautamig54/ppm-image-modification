#ifndef Pixel_h
#define Pixel_h

#include "Color.h"
#include <iostream>

class Pixel {
private:
  int x, y;
  Color color;

public:
  Pixel();
  Pixel(int x, int y, Color c);
  ~Pixel();
  Pixel(Pixel const &p);
  void setX(int a);
  void setY(int b);
  int getX();
  int getY();
  void setColor(Color c);
  Color getColor();
  Pixel& operator=(Pixel const &p);
  friend std::ostream& operator<<(std::ostream& os, Pixel& p);
  friend std::istream& operator>>(std::istream& is, Pixel& p);
};

#endif
