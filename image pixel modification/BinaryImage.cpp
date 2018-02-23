#include "BinaryImage.h"
#include "Image.h"
#include "Pixel.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

BinaryImage::BinaryImage() : Image() {}

BinaryImage::BinaryImage(Image& image, int threshold) {
  magicNumber = "P3";
  width = image.getWidth();
  height = image.getHeight();
  max = image.getMax();
  pixel = new Pixel*[height];
  for(int i = 0; i < height; i++) {
    pixel[i] = new Pixel[width];
  }
  int brightness;
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      Color color;
      color = image.getColor(i, j);
      brightness = (color.getRed() + color.getGreen() + color.getBlue()) / 3;
      if(brightness >= threshold){
        Color c(max, max, max);
        pixel[i][j].setColor(c);
      } else {
        Color c(0, 0, 0);
        pixel[i][j].setColor(c);
      }
    }
  }
  foregroundOrBackground = new int*[height];
  for(int i = 0; i < height; i++) {
    foregroundOrBackground[i] = new int[width];
  }
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      if(pixel[i][j].getColor().getRed() == max) {
        foregroundOrBackground[i][j] = 1;
      } else {
        foregroundOrBackground[i][j] = 0;
      }
    }
  }
}

BinaryImage::~BinaryImage() {
  if(foregroundOrBackground != NULL) {
    for(int i = 0; i < height; i++) {
      delete [] foregroundOrBackground[i];
    }
    delete [] foregroundOrBackground;
  }
}

void BinaryImage::deNoise() {
  int** count;
  count = new int*[height];
  for(int i = 0; i < height; i++) {
    count[i] = new int[width];
  }
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      if(i == 0 && j == 0) {
        count[i][j] = foregroundOrBackground[i + 1][j] + foregroundOrBackground[i][j + 1] + foregroundOrBackground[i + 1][j + 1];
      } else if(i == 0) {
        if(j == width - 1) {
          count[i][j] = foregroundOrBackground[i][j - 1] + foregroundOrBackground[i + 1][j - 1] + foregroundOrBackground[i + 1][j];
        } else {
          count[i][j] = foregroundOrBackground[i + 1][j] + foregroundOrBackground[i][j + 1] + foregroundOrBackground[i + 1][j + 1] + foregroundOrBackground[i][j - 1] + foregroundOrBackground[i + 1][j - 1];
        }
      } else if(j == 0) {
        if(i == height - 1) {
          count[i][j] = foregroundOrBackground[i - 1][j] + foregroundOrBackground[i - 1][j + 1] + foregroundOrBackground[i][j + 1];
        } else {
          count[i][j] = foregroundOrBackground[i - 1][j] + foregroundOrBackground[i - 1][j + 1] + foregroundOrBackground[i][j + 1] + foregroundOrBackground[i + 1][j + 1] + foregroundOrBackground[i + 1][j];
        }
      } else if(i == height - 1 && j == width - 1) {
        count[i][j] = foregroundOrBackground[i - 1][j] + foregroundOrBackground[i - 1][j - 1] + foregroundOrBackground[i][j - 1];
      } else if(i == height - 1) {
        if(j == 0) {
          count[i][j] = foregroundOrBackground[i - 1][j] + foregroundOrBackground[i - 1][j + 1] + foregroundOrBackground[i][j + 1];
        } else {
          count[i][j] = foregroundOrBackground[i][j - 1] + foregroundOrBackground[i - 1][j - 1] + foregroundOrBackground[i - 1][j] + foregroundOrBackground[i - 1][j + 1] + foregroundOrBackground[i][j + 1];
        }
      } else if(j == width - 1) {
        if(i == 0) {
          count[i][j] = foregroundOrBackground[i][j - 1] + foregroundOrBackground[i + 1][j - 1] + foregroundOrBackground[i + 1][j];
        } else {
          count[i][j] = foregroundOrBackground[i - 1][j] + foregroundOrBackground[i - 1][j - 1] + foregroundOrBackground[i][j - 1] + foregroundOrBackground[i + 1][j - 1] + foregroundOrBackground[i + 1][j];
        }
      } else {
        count[i][j] = foregroundOrBackground[i - 1][j - 1] + foregroundOrBackground[i][j - 1] + foregroundOrBackground[i + 1][j - 1] + foregroundOrBackground[i - 1][j] + foregroundOrBackground[i - 1][j + 1] + foregroundOrBackground[i][j + 1] + foregroundOrBackground[i + 1][j + 1] + foregroundOrBackground[i + 1][j];
      }
      // if(count[i][j] > 4) {
      //   foregroundOrBackground[i][j] = 1;
      //   pixel[i][j].setColor(Color(max, max, max));
      // } else if(count[i][j] < 4) {
      //   foregroundOrBackground[i][j] = 0;
      //   pixel[i][j].setColor(Color(0, 0, 0));
      // }
    }
  }
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      if(count[i][j] > 4) {
        foregroundOrBackground[i][j] = 1;
        pixel[i][j].setColor(Color(max, max, max));
      } else if(count[i][j] < 4) {
        foregroundOrBackground[i][j] = 0;
        pixel[i][j].setColor(Color(0, 0, 0));
      }
    }
  }
  for(int i = 0; i < height; i++) {
    delete [] count[i];
  }
  delete [] count;
}

std::ostream& BinaryImage::print(std::ostream& os) {
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
