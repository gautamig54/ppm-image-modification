#ifndef Image_h
#define Image_h

#include "Pixel.h"
#include <iostream>

class Image {
protected:
  int width, height, max;
  std::string magicNumber;
  Pixel** pixel;
  void label();

public:
  Image();
  Image(char* fileName);
  Image(int width, int height, int max);
  virtual ~Image();
  Image(Image const &image);
  int getWidth();
  int getHeight();
  int getMax();
  std::string getMagicNumber();
  Pixel** getPixels();
  Color getColor(int i, int j);
  void setWidth(int width);
  void setHeight(int height);
  void setMax(int max);
  void setMagicNumber(std::string magicNumber);
  void setPixelColor(int x, int y, Color c);
  void filter(Color c, float alpha);
  void printLocationOfSameColor(Image image);
  Image ReflectionaboutY();
  Image ReflectionaboutX();
  Image ClipImage(Image X);
  Image StencilImage(Image X);
  Image& operator=(Image const &image);
  std::ostream& print(std::ostream& os);
  friend Image operator*(Image const &image, float const alpha);
  friend Image operator+(Image const &image1, Image const &image2);
  friend std::istream& operator>>(std::istream& is, Image& i);
};

#endif
