#include "Pixel.h"
#include "Color.h"
#include <iostream>

Pixel::Pixel() {
  x = 0;
  y = 0;
  color = Color(0, 0, 0);
}

Pixel::Pixel(int a, int b, Color c) {
  x = a;
  y = b;
  color = c;
}

Pixel::~Pixel() {}

Pixel::Pixel(Pixel const &p) {
  x = p.x;
  y = p.y;
  color = p.color;
}

void Pixel::setX(int a) {
  x = a;
}

void Pixel::setY(int b) {
  y = b;
}
int Pixel::getX(){
  return x;
}

int Pixel::getY(){
  return y;
}

void Pixel::setColor(Color c) {
  color = c;
}

Color Pixel::getColor() {
  return color;
}

Pixel& Pixel::operator=(Pixel const &p) {
  x = p.x;
  y = p.y;
  color = p.color;
  return (*this);
}

std::istream& operator>>(std::istream& is, Pixel& p) {
  is >> p.color;
  return is;
}

std::ostream& operator<<(std::ostream& os, Pixel& p) {
  os << p.color;
  return os;
}
