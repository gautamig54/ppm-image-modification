#include "NoiseImage.h"
#include "Image.h"
#include "Pixel.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

NoiseImage::NoiseImage() : Image() {}

NoiseImage::NoiseImage(int w, int h, int m) {
  magicNumber = "P3";
  width = w;
  height = h;
  max = m;
  pixel = new Pixel*[height];
  for(int i = 0; i < height; i++) {
    pixel[i] = new Pixel[width];
  }
  std::srand(std::time(0));
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      int c = rand() % 256;
      Color color(c, c, c);
      pixel[i][j].setColor(color);
    }
  }
}

std::ostream& NoiseImage::print(std::ostream& os) {
  os << magicNumber << std::endl;
  os << width << " " << height << std::endl;
  os << max << std::endl;
  for(int i = 0; i <height; i++) {
    for(int j = 0; j < height; j++) {
      os << pixel[i][j] << " ";
    }
    os << std::endl;
  }
  return os;
}
