#include "Color.h"
#include <iostream>

Color::Color(){
  red = 0;
  blue = 0;
  green = 0;
}

Color::Color(int x, int y, int z){
  red = x;
  green = y;
  blue = z;
}

Color::~Color(){}

Color::Color(Color const &c){
  red = c.red;
  blue = c.blue;
  green = c.green;
}

void Color::setRed(int f){
  red = f;
}

void Color::setGreen(int f){
  green = f;
}

void Color::setBlue(int f){
  blue = f;
}

int Color::getRed(){
  return red;
}

int Color::getGreen(){
  return green;
}

int Color::getBlue(){
  return blue;
}

Color& Color::operator=(Color const &c){
  red = c.red;
  blue = c.blue;
  green = c.green;
  return (*this);
}

bool operator==(Color& c1, Color& c2){
  return (c1.red == c2.red && c1.green == c2.green && c1.blue == c2.blue);
}

Color operator*(Color const &color, float const alpha) {
  Color c;
  c.red = (color.red * alpha);
  c.green = (color.green * alpha);
  c.blue = (color.blue * alpha);
  return c;
}

Color operator+(Color const &c1, Color const &c2) {
  Color c;
  c.red = (c1.red + c2.red);
  c.green = (c1.green + c2.green);
  c.blue = (c1.blue + c2.blue);
  return c;
}

std::istream& operator>>(std::istream& is, Color& c){
  is >> c.red >> c.green >> c.blue;
  return is;
}

std::ostream& operator<<(std::ostream& os, Color& c){
  os << (int)c.red << " " << (int)c.green << " " << (int)c.blue;
  return os;
}
