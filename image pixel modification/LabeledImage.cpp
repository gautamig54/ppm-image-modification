#include<iostream>
#include<cstdlib>
#include<cmath>
#include<map>
#include<stack>
#include<fstream>

#include "LabeledImage.h"
#include "Image.h"

using namespace std;

LabeledImage::LabeledImage() : Image(){
  labelNumber = 0;
}

LabeledImage::LabeledImage( BinaryImage &image) : Image(image){
  labelNumber = 0;
  _labels = new int*[getHeight()];

  for(int i=0;i<getHeight();i++){
    _labels[i] = new int[getWidth()];
  }

  generateConnectedComponents();
  assignLabelColors();
}

LabeledImage::~LabeledImage() {

  for(int i=0;i<getHeight();i++) delete []_labels[i];
  if(getHeight()!=0) delete []_labels;

}

LabeledImage::LabeledImage(LabeledImage &lim) : Image(lim) {

  _labels = new int*[getHeight()];
  for(int i=0;i<getHeight();i++){
    _labels[i] = new int[getWidth()];
  }
  labelNumber = 0;

}

void LabeledImage::set_label(int label,int x,int y) {
  _labels[x][y] = label;
}

int LabeledImage::get_label(int x,int y) {
  return _labels[x][y];
}

int LabeledImage::getLabelNumber() {
  return labelNumber;
}

void LabeledImage::setLabelNumber(int ln) {
  labelNumber = ln;
}

int LabeledImage::getNewLabel() {
  return ++labelNumber;
}

void LabeledImage::assignLabelColors() {
  map<int,int> colorMapRed,colorMapBlue,colorMapGreen;
  for(int i=0;i<getHeight();i++) {
    for(int j=0;j<getWidth();j++) {
        if(colorMapRed.find(get_label(i,j)) == colorMapRed.end()) {
          //IF A COLOR WAS ASSIGNED TO THIS LABEL PREVIOUSLY, FIND IT FROM COLORMAPS
          //AND ASSIGN THE CURRENT PIXEL THAT COLOR
          int r = rand() % 256, g = rand() % 256, b = rand() % 256;
          colorMapRed[get_label(i,j)] = r;
          colorMapGreen[get_label(i,j)] = g;
          colorMapBlue[get_label(i,j)] = b;
          Color c(r, g, b);
          setPixelColor(i, j, c);
        }
        else{
          //IF NO COLOR WAS ASSIGNED TO THIS LABEL PREVIOUSLY, ASSIGN A NEW ONE
          int r = colorMapRed[get_label(i,j)],g = colorMapGreen[get_label(i,j)],b = colorMapBlue[get_label(i,j)];
          Color c(r,g,b);
          setPixelColor(i,j,c);
        }
    }
  }
}

void LabeledImage::generateConnectedComponents() {

    //THIS IS THE FIRST STEP IN CREATING THE CONNECTED COMPONENTS

    stack <pair<int,int> > equivalentPairs;
    set_label(getNewLabel(),0,0);

    for(int i=0;i<getHeight();i++){
      for(int j=0;j<getWidth();j++){

          //COUNT THE PNUMBER OF PIXELS THAT HAVE SAME COLOR AS CURRUNT ONE
          //IN LEFT,TOP AND TWO TOP DIAGONAL PIXELS
          int sameColorCount = 0;

          //IF THERE IS ONE PIXEL WITH THE SAME COULOR AS THE CURRENT PIXEL,
          //ASSIGN THE LABEL OF THET PIXEL TO THE CURRENT ONE
          for(int k1=-1;k1<1;k1++){
            for(int k2=-1;k2<=abs(k1);k2++){

                if(inbounds(i+k1,j+k2) && (k1!=0 || k2!=0)){
                  //SINCE THE GIVEN IMAGE IS BINARY, ALL R,G,B VALUES AR SAME
                  //SO IT'S ENOUGH TO CHECK IF R VALUES ARE SAME
                  if(getColor(i+k1,j+k2).getRed() == getColor(i,j).getRed()){
                    sameColorCount++;
                    set_label(get_label(i+k1,j+k2),i,j);
                  }
                }
            }
          }

      //IF NO PIXEL ROUND HAS SAME COLOR, GIVE THE CURRENT PIXEL A NEW LABEL.
      if(sameColorCount==0) set_label(getNewLabel(),i,j);
      else if(sameColorCount>1){
      //IF MORE THAN ONE PIXELS AROUND HAVE THE SAME COLOR AS THE CURRENT ONE,
      //ASSIGN ONE OF THEIR LABELS TO THE CURRENT PIXEL AND
      //ADD THE CURRENT PIXEL TO THE EQUIVALANCIES STACK
        pair<int,int> p(i,j);
        equivalentPairs.push(p);
        }
      }
    }


    //SECOND STEP IN GENERATING CONNECTED COMPONENTS

    //CREATE AN ARRAY OF THE SIZE THE CURRENT NUMBER OF COMPONENTS IN THE IMAGE
    //WHICH IS GIVEN BY THE CURRENT NUMBER OF LABELS USED
    int labelNumber = getLabelNumber();
    int labelTrackarray[labelNumber];

    //NOW AT EACH EQUIVALANCY POINT, WE NEED TO SEE IF WE CAN MERGE TWO COMPONENTS INTO ONE
    //THIS ARRAY WILL BE USED TO KEEP TRACK OF WHICH LABEL HAS BEEN CHANGES TO WHAT
    //SO INITIALLY EACH ELEMENT OF THIS ARRAY HAS ITS OWN LABEL
    for(int i=0;i<getLabelNumber();i++) labelTrackarray[i] = i+1;

    //GO THROUGH EACH EQUIVALANCY POINT
    while(!equivalentPairs.empty()){
      pair<int,int> &p = equivalentPairs.top();
      int i = p.first,j=p.second;

      //NOW AT EACH PIXEL(EQUIVALANT ONES) CHECK IF TWO COMPONENTS CAN BE MERGED
      //IF YES, GENERATE A NEW LABEL NUMBER AND ASSIGN BOTH THE COMPONENTS THIS LABEL
      for(int k1=-1;k1<1;k1++){
        for(int k2=-1;k2<=abs(k1);k2++){

          if(inbounds(i+k1,j+k2)){
            if(getColor(i+k1,j+k2).getRed()==getColor(i,j).getRed()){

                //CHANGIND THE LABELS
                if(labelTrackarray[get_label(i+k1,j+k2)] != labelTrackarray[get_label(i,j)]){
                  int newLabel = getNewLabel();
                  changeLabel(labelTrackarray,labelTrackarray[get_label(i+k1,j+k2)],newLabel,labelNumber);
                  changeLabel(labelTrackarray,labelTrackarray[get_label(i,j)],newLabel,labelNumber);
                      }

              }
            }
          }
        }

        equivalentPairs.pop();
      }


    //THIRD STEP IN GENERATING CONNECTED ConnectedComponents

    //AFTER THE COMPONENTS ARE MERGED, GO THROUGH ALL THE PIXELS AND ASSIGN THEM THE NEW LABEL
    //THIS NEW LABEL CAN BE TRACKED FROM THE labelTrackarray THAT WE HAVE CREATED IN THE STEP TWO
    for(int i=0;i<getHeight();i++){
      for(int j=0;j<getWidth();j++){

        set_label(labelTrackarray[get_label(i,j)],i,j);

      }
    }

}

LabeledImage& LabeledImage::operator=(LabeledImage const &image) {

    width = image.width;
    height = image.height;
    max = image.max;
    magicNumber = image.magicNumber;
    pixel = new Pixel*[height];
    _labels = new int*[height];

    for(int i = 0; i < height; i++) {
      pixel[i] = new Pixel[width];
      _labels[i] = new int[width];
    }

    for(int i = 0; i < height; i++) {
      for(int j = 0; j < width; j++) {
        pixel[i][j] = image.pixel[i][j];
        _labels[i][j] = image._labels[i][j];
      }
    }

    return (*this);
}

std::ostream& LabeledImage::print(std::ostream& os) {
  os << "P3" << std::endl;
  os << width << " " << height << std::endl;
  os << max << std::endl;
  for(int i = 0; i <height; i++) {
    for(int j = 0; j < width; j++) {
      os << pixel[i][j] << " ";
    }
    os << std::endl;
  }
  return os;
}

//UTILITY FUNCTIONS

//CHECKS IF THE GIVEN COORDINATES ARE INBOUNDS OF THE IMAGE
bool LabeledImage::inbounds(int x,int y) {
  if(x>=0 && x<getHeight() && y>=0 && y<getWidth()) return true;
  return false;
}
//CHANGES ASSIGNS THE NEW LABE TO ALL THE GIVEN OLD LABELS
void LabeledImage::changeLabel(int labelTrackarray[],int curLabel,int newLabel,int labelNumber) {
  for(int i=0;i<labelNumber;i++){
    if(labelTrackarray[i]==curLabel) labelTrackarray[i] = newLabel;
  }
}
