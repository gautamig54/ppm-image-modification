#ifndef Segmentation_h
#define Segmentation_h

#include "Image.h"
#include <vector>

class Segmentation : public Image {
public:
  Segmentation();
  Segmentation(Image &image, std::vector<int> thresholds);
  void label();
  void color();
  std::ostream& print(std::ostream& os);
};

#endif