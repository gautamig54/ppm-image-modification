#include "Image.h"
#include "ScaledImage.h"
#include "Pixel.h"
#include "Color.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <cmath>
#include <cstdlib>
#include <algorithm>

ScaledImage::ScaledImage(): Image(){}


void ScaledImage:: Scaling_reflect(Image& img){
	int h=img.getHeight();
	int w= img.getWidth();
	this->setWidth(w);
	this->setHeight(h);
	this->setMax(img.getMax());
	this->setMagicNumber(img.getMagicNumber());
	
	pixel = new Pixel*[height];
  for(int i = 0; i < height; i++) {
    pixel[i] = new Pixel[width];
  }
   Pixel** pixels = img.getPixels();
	//Pixel** pix = image.getPixels();
	
	for(int i=0;i<h;i=i+2){
		for(int j=0;j<w;j=j+2){
			Color c;
			c=pixels[i][j].getColor();
			this->setPixelColor(i/2,j/2,c);
		}
	}

	int fh,fw;
	if(h%2==0)
		fh=0;
	else if(h%2!=0)
		fh=1;

	Pixel** pix = this->getPixels();
	
	if(w%2==0){
		for(int i=0;i<(h+fh)/2;i++){
			for(int j=w/2;j<w;j++){
				Color c;
				c=pix[i][w-j-1].getColor();
				this->setPixelColor(i,j,c);
			}
		}
	}
	else if(w%2!=0){
		for(int i=0;i<(h+fh)/2;i++){
			for(int j=(w/2)+1;j<w;j++){
				Color c;
				c=pix[i][w-j-1].getColor();
				
				this->setPixelColor(i,j,c);
			}
		}
	}

	if(h%2==0){
		for(int i=h/2;i<h;i++){
			for(int j=0;j<w;j++){
				Color c;
				c=pix[h-i-1][j].getColor();
				this->setPixelColor(i,j,c);
			}
		}
	}

	else if(h%2!=0){
		for(int i=(h/2)+1;i<h;i++){
			for(int j=0;j<w;j++){
				Color c;
				c=pix[h-i-1][j].getColor();
				this->setPixelColor(i,j,c);
			}
		}
	}

	Color cr(255,255,255);
	int a=(int)(std::min(floor(h/2),floor(w/2)));
	int midh=(int)h/2;
	int midw=(int)w/2;
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(j<midw-(a/2) || j>midw+(a/2) || i<midh-(a/2) || i>midh+(a/2))
				this->setPixelColor(i,j,cr);
		}
	}


}

std::ostream& ScaledImage::print(std::ostream& os) {
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



