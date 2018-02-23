#include "Segmentation.h"
#include "CompositeImage.h"
#include "Image.h"
#include "Pixel.h"
#include <iostream>
#include <map>
#include <vector>

Segmentation::Segmentation() : Image() {}

Segmentation::Segmentation(Image& image, std::vector<int> thresholds) {
  magicNumber = "P3";
  width = image.getWidth();
  height = image.getHeight();
  max = image.getMax();
  pixel = new Pixel*[height];
  for(int i = 0; i < height; i++) {
    pixel[i] = new Pixel[width];
  }
  Color *col=new Color[2];
  col[0]=Color(0, 255, 0);
  col[1]=Color(0, 0, 255);
  // for(int i = 0; i < height; i++) {
  //   for(int j = 0; j < width; j++) {
  //     Color c;
  //     c = image.getColor(i, j);
  //     pixel[i][j].setColor(c);
  //   }
  // }
  int brightness;
  if(thresholds.size()==0) {
    Image reflection=this->ReflectionaboutY();
    for(int i = 0; i < height; i++) {
      for(int j = 0; j < width; j++) {
        pixel[i][j] = reflection.getPixels()[i][j];
	  }
    }
  }
  else {
    for(int i = 0; i < height; i++) {
      for(int j = 0; j < width; j++) {
        Color color;
        color = image.getColor(i, j);
        brightness = (color.getRed() + color.getGreen() + color.getBlue()) / 3;
        if(thresholds.size()==1) {
          if(brightness<thresholds[0])
          {
            Color c(255, 0, 0);
            pixel[i][j].setColor(c);
          }
          else
          {
            Color c(0, 255, 0);
            pixel[i][j].setColor(c);
          }
        }
        else if(thresholds.size()==2) {
          if(brightness<thresholds[0])
          {
            Color c(255, 0, 0);
            pixel[i][j].setColor(c);
          }
          else if(brightness>=thresholds[0] && brightness<thresholds[1])
          {
            Color c(0, 255, 0);
            pixel[i][j].setColor(c);
          }
          else
          {
            Color c(0, 0, 255);
            pixel[i][j].setColor(c);
          }
        }
        else if(thresholds.size()==3) {
          if(brightness<thresholds[0])
          {
            Color c(255, 0, 0);
            pixel[i][j].setColor(c);
          }
          else if(brightness>=thresholds[0] && brightness<thresholds[1])
          {
            Color c(0, 255, 0);
            pixel[i][j].setColor(c);
          }
          else if(brightness>=thresholds[1] && brightness<thresholds[2])
          {
            Color c(0, 0, 255);
            pixel[i][j].setColor(c);
          }
          else
          {
            Color c(255, 255, 0);
            pixel[i][j].setColor(c);
          }
        }
        else if(thresholds.size()==4) {
          if(brightness<thresholds[0])
          {
            Color c(255, 0, 0);
            pixel[i][j].setColor(c);
          }
          else if(brightness>=thresholds[0] && brightness<thresholds[1])
          {
            Color c(0, 255, 0);
            pixel[i][j].setColor(c);
          }
          else if(brightness>=thresholds[1] && brightness<thresholds[2])
          {
            Color c(0, 0, 255);
            pixel[i][j].setColor(c);
          }
          else if(brightness>=thresholds[2] && brightness<thresholds[3])
          {
            Color c(255, 255, 0);
            pixel[i][j].setColor(c);
          }
          else
          {
            Color c(255, 0, 255);
            pixel[i][j].setColor(c);
          }
        }
        else if(thresholds.size()==5) {
          if(brightness<thresholds[0])
          {
            Color c(255, 0, 0);
            pixel[i][j].setColor(c);
          }
          else if(brightness>=thresholds[0] && brightness<thresholds[1])
          {
            Color c(0, 255, 0);
            pixel[i][j].setColor(c);
          }
          else if(brightness>=thresholds[1] && brightness<thresholds[2])
          {
            Color c(0, 0, 255);
            pixel[i][j].setColor(c);
          }
          else if(brightness>=thresholds[2] && brightness<thresholds[3])
          {
            Color c(255, 255, 0);
            pixel[i][j].setColor(c);
          }
          else if(brightness>=thresholds[3] && brightness<thresholds[4])
          {
            Color c(255, 0, 255);
            pixel[i][j].setColor(c);
          }
          else
          {
            Color c(0, 255, 255);
            pixel[i][j].setColor(c);
          }
        }
        else if(thresholds.size()>=6) {
          if(brightness<thresholds[0])
          {
            Color c(255, 0, 0);
            pixel[i][j].setColor(c);
          }
          else if(brightness>=thresholds[0] && brightness<thresholds[1])
          {
            Color c(0, 255, 0);
            pixel[i][j].setColor(c);
          }
          else if(brightness>=thresholds[1] && brightness<thresholds[2])
          {
            Color c(0, 0, 255);
            pixel[i][j].setColor(c);
          }
          else if(brightness>=thresholds[2] && brightness<thresholds[3])
          {
            Color c(255, 255, 0);
            pixel[i][j].setColor(c);
          }
          else if(brightness>=thresholds[3] && brightness<thresholds[4])
          {
            Color c(255, 0, 255);
            pixel[i][j].setColor(c);
          }
          else if(brightness>=thresholds[4] && brightness<thresholds[5])
          {
            Color c(0, 255, 255);
            pixel[i][j].setColor(c);
          }
          else
          {
            Color c(0, 0, 0);
            pixel[i][j].setColor(c);
          }
        }
      }
    }
  }
}

// void Segmentation::label() {
//   std::map<int, int> labelMap;
//   int** label;
//   for(int i = 0; i < height; i++) {
//     for(int j = 0; j < width; j++) {
//       label[i][j] = 0;
//     }
//   }
//   int** foregroundOrBackground;
//   for(int i = 0; i < height; i++) {
//     for(int j = 0; j < width; j++) {
//       if(getColor(i, j).getRed() == 255) {
//         foregroundOrBackground[i][j] = 1;
//       } else {
//         foregroundOrBackground[i][j] = 0;
//       }
//     }
//   }
//   int currentLabel = 0;
//   for(int i = 0; i < height; i++) {
//     for(int j = 0; j < width; j++) {
//       if(i == 0 && j == 0) {
//         label[i][j] = 0;
//       } else if(i == 0) {
//         if(foregroundOrBackground[i][j - 1] == foregroundOrBackground[i][j]) {
//           label[i][j] = label[i][j - 1];
//         }
//       } else if(j == 0) {
//         if(foregroundOrBackground[i - 1][j] == foregroundOrBackground[i][j]
//         && foregroundOrBackground[i - 1][j + 1] == foregroundOrBackground[i][j]) {
//           int minimum = min(label[i - 1][j], label[i - 1][j + 1]);
//           int maximum = max(label[i - 1][j], label[i - 1][j + 1]);
//           label[i][j] = minimum;
//           labelMap.insert(std::pair<int, int>(maximum, minimum));
//         }
//       } else {}
//     }
//   }
// }

std::ostream& Segmentation::print(std::ostream& os) {
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