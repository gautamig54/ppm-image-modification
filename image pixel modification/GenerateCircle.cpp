#include "Image.h"
#include "GenerateCircle.h"
GenerateCircle::GenerateCircle(){
}
GenerateCircle::GenerateCircle(int w,int h,int m){
	magicNumber="P3";
	width = w;
  height = h;
  max = m;
  int x=floor(width/2);
  int y=floor(height/2);
  int r=std::min((int)width*0.125,(int)height*0.125);
  pixel = new Pixel*[height];
  for(int i = 0; i < height; i++) {
    pixel[i] = new Pixel[width];
  }
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      pixel[i][j].setX(j);
      pixel[i][j].setY(i);
  		if(sqrt((j-x)*(j-x)+(i-y)*(i-y))<=r){
    		Color color(255, 255, 255);
    		pixel[i][j].setColor(color);
    	}
    	else{
    		Color color(0,0,0);
      	pixel[i][j].setColor(color);
      }
    }
  }
  x=floor(width/4);
  y=floor(3*height/4);
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      pixel[i][j].setX(j);
      pixel[i][j].setY(i);
    	if(pixel[i][j].getColor().getRed()==0){
  			if(sqrt((j-x)*(j-x)+(i-y)*(i-y))<=r){
    			Color color(255, 255, 255);
    			pixel[i][j].setColor(color);
    		}
      }
    }
  }
  x=floor(3*width/4);
  y=floor(3*height/4);
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      pixel[i][j].setX(j);
      pixel[i][j].setY(i);
    	if(pixel[i][j].getColor().getRed()==0){
  			if(sqrt((j-x)*(j-x)+(i-y)*(i-y))<=r){
    			Color color(255, 255, 255);
    			pixel[i][j].setColor(color);
    		}
      }
    }
  }
  x=floor(width/4);
  y=floor(height/4);
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      pixel[i][j].setX(j);
      pixel[i][j].setY(i);
    	if(pixel[i][j].getColor().getRed()==0){
  			if(sqrt((j-x)*(j-x)+(i-y)*(i-y))<=r){
    			Color color(255, 255, 255);
    			pixel[i][j].setColor(color);
    		}
      }
    }
  }
  x=floor(3*width/4);
  y=floor(height/4);
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      pixel[i][j].setX(j);
      pixel[i][j].setY(i);
    	if(pixel[i][j].getColor().getRed()==0){
  			if(sqrt((j-x)*(j-x)+(i-y)*(i-y))<=r){
    			Color color(255, 255, 255);
    			pixel[i][j].setColor(color);
    		}
      }
    }
  }
  x=floor(width/4);
  y=floor(3*height/4);
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      pixel[i][j].setX(j);
      pixel[i][j].setY(i);
    	if(pixel[i][j].getColor().getRed()==0){
  			if(sqrt((j-x)*(j-x)+(i-y)*(i-y))<=r){
    			Color color(255, 255, 255);
    			pixel[i][j].setColor(color);
    		}
      }
    }
  }
}
