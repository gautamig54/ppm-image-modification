#include "Gaussian.h"
#include<iostream>

int const Gaussian::gauss_array[5][5] = {{1,4,7,4,1},{4,16,26,16,4},{7,26,41,26,7},{4,16,26,16,4},{1,4,7,4,1}};
Gaussian::Gaussian(){

}

Gaussian::Gaussian(Image& a):
  Image(a) {
    (*this).apply_gaussian();
  }

Gaussian::Gaussian(int w,int h,int m):Image(w,h,m) {
    (*this).apply_gaussian();
  }

Gaussian::~Gaussian() {

}

float get_saturation(Pixel& p){
  Color c;
  c = p.getColor();
  int M,m;
  M = std::max(std::max(c.getRed(),c.getGreen()),c.getBlue());
  m = std::min(std::min(c.getRed(),c.getGreen()),c.getBlue());
  if(M == 0)
    return 0;
  return (M-m)/M;
}

std::vector<Pixel*> Gaussian::local_maxima() {
  std::vector<Pixel*> pix;
  for(int i=0;i<height;i++) {
    for(int j=0;j<width;j++) {
      if(is_max(i,j)) {
        pix.push_back(&pixel[i][j]);
      }
    }
  }
  return pix;
}

bool Gaussian::is_max(int y,int x) {
  for(int i=-1;i<=1;i++) {
    for(int j=-1;j<=1;j++) {
      if(!(i==0 && j==0)){
        if(is_valid_coor(x+j,y+i)) {
          if(get_saturation(pixel[y+i][x+j])>=get_saturation(pixel[y][x]))
            return false;
          }
        }
      }
    }
  return true;
}

std::vector<Pixel*> Gaussian::neighbourhood_24_color() {
  int x,y;
  Color w(255,255,255);
  Color b(0,0,0);
  std::vector<Pixel*> max = local_maxima();
  for(int i=0;i<height;i++) {
    for(int j=0;j<width;j++) {
      this->setPixelColor(i,j,b);
    }
  }
  for(int k=0;k<max.size();k++) {
    std::vector<Pixel*> pixels = neighbourhood_24(max[k]);
    for(int i=0;i<pixels.size();i++) {
      x = pixels[i]->getX();
      y = pixels[i]->getY();
      this->setPixelColor(y,x,w);
    }
    pixels.clear();
  }
  return max;
}

std::vector<Pixel*> Gaussian::neighbourhood_24(Pixel* p) {
  int x = p->getX();
  int y = p->getY();
  std::vector<Pixel*> pix;
  for(int i=-2;i<=2;i++) {
    for(int j=-2;j<=2;j++) {
      if(is_valid_coor(x+j,y+i))
        pix.push_back(&pixel[y+i][x+j]);
    }
  }
  return pix;
}

bool Gaussian::is_valid_coor(int x,int y)
{
  if(x>=0 && x<width) {
    if(y>=0 && y<height)
      return true;
    return false;
  }
  return false;
}

bool is_in_24_neighbourhood(Pixel* p1,Pixel* p2) {
  int p1_x=p1->getX();
  int p1_y=p1->getY();
  int p2_x=p2->getX();
  int p2_y=p2->getY();
  int x=p2_x-p1_x;
  int y=p2_y-p1_y;
  if(x<=2 && x>=-2) {
    if(y<=2 && y>=-2) {
      return true;
    }
    return false;
  }
  return false;
}
void Gaussian::apply_gaussian() {
  Color w(255,255,255);
  Color& w_ref=w;
  int x1,x2,y1,y2;
  std::vector<float> color;
  float col = 0;
  std::vector<Pixel*> max = neighbourhood_24_color();
  for(int k=0;k<max.size();k++) {
    std::vector<Pixel*> pixels = neighbourhood_24(max[k]);
    for(int i=0;i<pixels.size();i++) {
      int x = pixels[i]->getX();
      int y = pixels[i]->getY();
      Color c;
      c=pixel[y][x].getColor();
      Color& c_ref=c;
      if(c_ref == w_ref) {
        for(int j=k;j<max.size();j++) {
          if(is_in_24_neighbourhood(max[j],pixels[i])) {
            x1=max[j]->getX();x2=pixels[i]->getX();
            y1=max[j]->getY();y2=pixels[i]->getY();
            color.push_back(gauss_array[x2-x1+2][y2-y1+2]);
          }
        }
        col=0;
        for(int l=0;l<color.size();l++) {
          col+=color[l];
        }
        col/=color.size();
        col*=255;
        col/=273;
        Color c(col,col,col);
        this->setPixelColor(y,x,c);
        color.clear();
      }
    }
    pixels.clear();
  }
}

std::ostream& Gaussian::print(std::ostream& os) {
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
