#include "Image.h"
#include "NoiseImage.h"
#include "CompositeImage.h"
#include "Histogram.h"
#include "BinaryImage.h"
#include "LabeledImage.h"
#include "GenerateCircle.h"
#include "Gaussian.h"
#include "Segmentation.h"
#include "ScaledImage.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

int Max(int a, int b) {
  return a > b ? a : b;
}

int Min(int a, int b) {
  return a < b ? a : b;
}

std::ostream& operator<<(std::ostream& os, Image& image){
  return image.print(os);
}

int main(int argc, char* argv[]) {
  if(argc > 1){
    Image image(argv[1]);
    Histogram histogram(image);
    int tasks[] = {3, 1, 7, 4, 6, 8};
    std::cout << "Our group task ID combination is : ";
    for(int i = 0; i < (sizeof(tasks) / sizeof(int)) - 1; i++) {
      std::cout << tasks[i] << ", ";
    }
    std::cout << tasks[(sizeof(tasks) / sizeof(int)) - 1] << std::endl;
    for(int i = 0; i < sizeof(tasks) / sizeof(int); i++) {
      if(tasks[i] == 3) {

        Image ref = image.ReflectionaboutX();
        Gaussian *g = new Gaussian(ref);
        CompositeImage compImage(*g,ref,0.6);
        std::ofstream fout("output_task3_imt2016018.ppm");
        fout<<compImage;
        fout.close();

      } else if(tasks[i] == 1) {

        GenerateCircle G(image.getWidth(),image.getHeight(),image.getMax());
        Image C(image.ClipImage(G));
        Image R(image.ReflectionaboutY());
        Image S(R.StencilImage(G));
        CompositeImage I(C,S,0.5);
        std::ofstream fout("output_task1_imt2016045.ppm");
        fout << I;
        fout.close();

      } else if(tasks[i] == 7) {

          ScaledImage sc;
          sc.Scaling_reflect(image);
          Image img(sc);
          std::ofstream fout;
          fout.open("output_task7_imt2016069.ppm");
          fout << img;
          fout.close();

      } else if(tasks[i] == 4) {

        Histogram histogram(image);
        Segmentation segmentation(image, histogram.getThresholds());
        CompositeImage compositeImage(image, segmentation, 0.4);
        std::ofstream fout;
        fout.open("output_task4_imt2016090.ppm");
        fout << compositeImage;
        fout.close();

      } else if(tasks[i] == 6) {

        BinaryImage binaryImage(image, histogram.getThreshold());
        LabeledImage labeledImage(binaryImage);
        std::ofstream fout("output_task6_imt2016110.ppm");
        labeledImage.print(fout);
        fout.close();

      } else if(tasks[i] == 8) {

        NoiseImage noise(image.getWidth(), image.getHeight(), image.getMax());
        CompositeImage compositeImage(image, noise, 0.5);
        Histogram histogram8(compositeImage);
        BinaryImage binaryImage(compositeImage, histogram8.getThreshold());
        binaryImage.deNoise();
        LabeledImage labeledImage(binaryImage);
        std::ofstream fout("output_task8_imt2016129.ppm");
        fout << labeledImage;
        fout.close();

      }
    }
  } else {
    std::cout << "Please enter a file name in the command line." << std::endl;
  }
}
