#include "Image.h"
#include "CompositeImage.h"

CompositeImage::CompositeImage(Image &image1, Image &image2, float alpha) {
  if((image1.getHeight() == image2.getHeight()) && (image1.getWidth() == image2.getWidth())){
    width = image1.getWidth();
    height = image1.getHeight();
    max = (image1.getMax() > image2.getMax()) ? image1.getMax() : image2.getMax();
    pixel = new Pixel*[height];
    for(int i = 0; i < height; i++) {
      pixel[i] = new Pixel[width];
    }
    Pixel** pixels1 = image1.getPixels();
    Pixel** pixels2 = image2.getPixels();
    int red, green, blue;
    for(int i = 0; i < height; i++){
      for(int j = 0; j < width; j++){
        Color c = pixels1[i][j].getColor() * (1 - alpha) + pixels2[i][j].getColor() * alpha;
        pixel[i][j].setColor(c);
      }
    }
  } else {
    std::cout << "Cannot compose images with different sizes." << std::endl;
  }
}

std::ostream& CompositeImage::print(std::ostream& os) {
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
