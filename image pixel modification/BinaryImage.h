#ifndef BinaryImage_h
#define BinaryImage_h

#include "Image.h"

class BinaryImage : public Image {
private:
  int** foregroundOrBackground;

public:
  BinaryImage();
  BinaryImage(Image &image, int threshold);
  ~BinaryImage();
  void deNoise();
  void colorConnectedComponents();
  std::ostream& print(std::ostream& os);
};

#endif
