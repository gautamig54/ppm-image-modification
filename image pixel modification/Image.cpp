#include "Image.h"
#include "Pixel.h"
#include "Color.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <map>

extern int Max(int a, int b);

Image::Image() {
  width = 0;
  height = 0;
  int max = 255;
  magicNumber = "P3";
  pixel = NULL;
}

Image::Image(char* fileName) {
  std::ifstream fin;
  fin.open(fileName);
  fin >> magicNumber >> width >> height >> max;
  pixel = new Pixel*[height];
  for(int i = 0; i < height; i++) {
    pixel[i] = new Pixel[width];
  }
  int red, green, blue;
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      fin >> red >> green >> blue;
      Color c(red, green, blue);
      pixel[i][j].setColor(c);
    }
  }
}

Image::Image(int w, int h, int m) {
  magicNumber = "P3";
  width = w;
  height = h;
  max = m;
  pixel = new Pixel*[height];
  for(int i = 0; i < height; i++) {
    pixel[i] = new Pixel[width];
  }
}

Image::~Image() {
  if(pixel != NULL) {
    for(int i = 0; i < height; i++) {
      delete [] pixel[i];
    }
    delete [] pixel;
  }
}

Image::Image(Image const &image) {
  width = image.width;
  height = image.height;
  max = image.max;
  magicNumber = "P3";
  pixel = new Pixel*[height];
  for(int i = 0; i < height; i++) {
    pixel[i] = new Pixel[width];
  }
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      pixel[i][j] = image.pixel[i][j];
    }
  }
}

int Image::getWidth() {
  return width;
}

int Image::getHeight() {
  return height;
}

int Image::getMax() {
  return max;
}

std::string Image::getMagicNumber() {
  return magicNumber;
}

Pixel** Image::getPixels() {
  return pixel;
}

Color Image::getColor(int i, int j) {
  Color c;
  c = pixel[i][j].getColor();
  return c;
}

void Image::setWidth(int w) {
  width = w;
}

void Image::setHeight(int h) {
  height = h;
}

void Image::setMax(int m) {
  max = m;
}

void Image::setMagicNumber(std::string magicNum) {
  magicNumber = magicNum;
}

void Image::setPixelColor(int x, int y, Color c) {
  pixel[x][y].setColor(c);
}

void Image::filter(Color color, float alpha) {
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      Color c = pixel[i][j].getColor();
      c = c * (1 - alpha) + color * alpha;
      pixel[i][j].setColor(c);
    }
  }
}

void Image::printLocationOfSameColor(Image image) {
  int minx = height + 1, miny = width + 1;
  Color sameColor;
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      Color c1, c2;
      c1 = pixel[i][j].getColor();
      c2 = image.pixel[i][j].getColor();
      if(c1 == c2){
        if((i * i + j * j) < (minx * minx + miny * miny)) {
          minx = i;
          miny = j;
          sameColor = c1;
        }
      }
    }
  }
  if(minx > width && miny > height) {
    std::cout << "No pixel of the same color as the original exists!!!" << std::endl;
  } else {
    std::cout << "RGB = (" << sameColor.getRed() << "," << sameColor.getGreen() << "," << sameColor.getBlue() << ")" << std::endl;
    std::cout << minx << " " << miny << std::endl;
  }
}

Image Image::ReflectionaboutY(){
  Image temp(this->getWidth(),this->getHeight(),this->getMax());
  Pixel ** p =this->getPixels();
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      temp.getPixels()[i][j].setX(j);
      temp.getPixels()[i][j].setY(i);
      Color color;
      color=p[i][width-j-1].getColor();
      temp.setPixelColor(i,j,color);
    }
  }
  return temp;
}

Image Image::ReflectionaboutX(){
  Image temp(this->getWidth(),this->getHeight(),this->getMax());
  Pixel ** p =this->getPixels();
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      temp.getPixels()[i][j].setX(j);
      temp.getPixels()[i][j].setY(i);
      Color color;
      color=p[height-i-1][j].getColor();
      temp.setPixelColor(i,j,color);
    }
  }
  return temp;
}

Image Image::ClipImage(Image X){
  Image temp(this->getWidth(),this->getHeight(),this->getMax());
  Color color(0,0,0);
  Pixel ** p =X.getPixels();
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      temp.getPixels()[i][j].setX(j);
      temp.getPixels()[i][j].setY(i);
      if(p[i][j].getColor().getRed()==255){
        Color color;
        color=pixel[i][j].getColor();
        temp.setPixelColor(i,j,color);
      }
      else{
        Color color(255,255,255);
        temp.setPixelColor(i,j,color);
      }
    }
  }
  return temp;
}

Image Image::StencilImage(Image X){
  Image temp(this->getWidth(),this->getHeight(),this->getMax());
  Pixel ** p =X.getPixels();
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      temp.getPixels()[i][j].setX(j);
      temp.getPixels()[i][j].setY(i);
      if(p[i][j].getColor().getRed()==0){
        Color color;
        color=pixel[i][j].getColor();
        temp.setPixelColor(i,j,color);
      }
      else{
        Color color(255,255,255);
        temp.setPixelColor(i,j,color);
      }
    }
  }
  return temp;
}

Image& Image::operator=(Image const &image) {
  width = image.width;
  height = image.height;
  max = image.max;
  magicNumber = image.magicNumber;
  pixel = new Pixel*[height];
  for(int i = 0; i < height; i++) {
    pixel[i] = new Pixel[width];
  }
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      pixel[i][j] = image.pixel[i][j];
    }
  }
  return (*this);
}

Image operator*(Image const &image, float const alpha) {
  Image newImage(image.width, image.height, image.max);
  for(int i = 0; i < image.height; i++) {
    for(int j = 0; j < image.width; j++) {
      newImage.setPixelColor(i, j, image.pixel[i][j].getColor() * alpha);
    }
  }
  return newImage;
}

Image operator+(Image const &image1, Image const &image2) {
  Image newImage(image1.width, image1.height, Max(image1.max, image2.max));
  for(int i = 0; i < image1.height; i++) {
    for(int j = 0; j < image1.width; j++) {
      newImage.setPixelColor(i, j, image1.pixel[i][j].getColor() + image2.pixel[i][j].getColor());
    }
  }
  return newImage;
}

std::ostream& Image::print(std::ostream& os) {
  os << magicNumber << std::endl;
  os << width << " " << height << std::endl;
  os << max << std::endl;
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      os << pixel[i][j] << " ";
    }
    os << std::endl;
  }
  return os;
}

std::istream& operator>>(std::istream& is, Image& image) {
  int red, green, blue;
  for(int i = 0; i < image.height; i++) {
    for(int j = 0; j < image.width; j++) {
      is >> red >> green >> blue;
      Color c(red, green, blue);
      image.pixel[i][j].setColor(c);
    }
  }
  return is;
}
