#ifndef CompositeImage_h
#define CompositeImage_h

#include "Image.h"

class CompositeImage : public Image {
public:
  CompositeImage(Image &image1, Image &i2, float alpha);
  std::ostream& print(std::ostream& os);
};

#endif
