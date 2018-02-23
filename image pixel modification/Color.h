#ifndef Color_h
#define Color_h

#include <iostream>

class Color {
private:
  int red, green, blue;

public:
  Color();
  Color(int x, int y, int z);
  ~Color();
  Color(Color const &c);
  void setRed(int f);
  void setGreen(int f);
  void setBlue(int f);
  int getRed();
  int getGreen();
  int getBlue();
  Color& operator=(Color const &c);
  friend bool operator==(Color& c1, Color& c2);
  friend Color operator*(Color const &c, float const alpha);
  friend Color operator+(Color const &c1, Color const &c2);
  friend std::ostream& operator<<(std::ostream& os, Color& c);
  friend std::istream& operator>>(std::istream& is, Color& c);
};

#endif
