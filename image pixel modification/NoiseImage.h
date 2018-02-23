#ifndef NoiseImage_h
#define NoiseImage_h

#include "Image.h"

class NoiseImage : public Image {
public:
  NoiseImage();
  NoiseImage(int width, int height, int max);
  std::ostream& print(std::ostream& os);
};

#endif
