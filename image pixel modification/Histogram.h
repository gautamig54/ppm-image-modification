#ifndef Histogram_h
#define Histogram_h

#include "Image.h"
#include <vector>

class Histogram {
private:
  int numberOfPixels[256];

public:
  Histogram(Image &image);
  int* getHistogram();
  double getThreshold();
  std::vector<int> getThresholds();
  void print();
};

#endif
