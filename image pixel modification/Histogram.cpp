#include "Histogram.h"
#include "Image.h"
#include "Pixel.h"
#include <fstream>
#include <vector>

extern std::ostream& operator<<(std::ostream& os, Image& image);

Histogram::Histogram(Image &image) {
  for(int i = 0; i < 256; i++) {
    numberOfPixels[i] = 0;
  }
  int brightness;
  Pixel** pixels = image.getPixels();
  for(int i = 0; i < image.getHeight(); i++){
    for(int j = 0; j < image.getWidth(); j++){
      Color color;
      color = pixels[i][j].getColor();
      brightness = (color.getRed() + color.getGreen() + color.getBlue()) / 3;
      numberOfPixels[brightness]++;
    }
  }
}

int* Histogram::getHistogram() {
  return numberOfPixels;
}

double Histogram::getThreshold() {
  long int cumulativeFrequency[256];
  long int sum = numberOfPixels[0];
  cumulativeFrequency[0] = numberOfPixels[0];
  for(int i = 1; i < 256; i++) {
    cumulativeFrequency[i] = cumulativeFrequency[i - 1] + numberOfPixels[i];
    sum += numberOfPixels[i];
  }
  int i = 0;
  if(sum % 2 == 0) {
    int index = sum / 2;
    while(index > cumulativeFrequency[i]) {
      i++;
    }
    if(index + 1 > cumulativeFrequency[i]) {
      return (i + (i + 1)) / 2.0;
    } else {
      return i;
    }
  } else {
    int index = (sum + 1) / 2;
    while(index > cumulativeFrequency[i]) {
      i++;
    }
    return i;
  }
}

std::vector<int> Histogram::getThresholds()
{
  std::vector<int> thrs;
  for(int i=1;i<255;i++)
  {
    if(numberOfPixels[i]<numberOfPixels[i-1] && numberOfPixels[i]<numberOfPixels[i+1])
    {
      thrs.push_back(i);
    }
  }
  return thrs;
}

void Histogram::print() {
  int width = 256;
  int height = 0;
  for(int i = 0; i < width; i++) {
    if(height < numberOfPixels[i]) {
      height = numberOfPixels[i];
    }
  }
  Image image(width, height , 255);
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      if(numberOfPixels[j] >= height - i) {
        Color c;
        c = Color(0, 0, 0);
        image.setPixelColor(i, j, c);
      } else {
        Color c;
        c = Color(255, 255, 255);
        image.setPixelColor(i, j, c);
      }
    }
  }
  std::ofstream fout;
  fout.open("histogram.ppm");
  fout << image;
  fout.close();
}
