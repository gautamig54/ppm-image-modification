#ifndef LabeledImage_h_
#define LabeledImage_h_

#include "BinaryImage.h"
#include "Image.h"

class LabeledImage : public Image{
  public:
    LabeledImage();
    LabeledImage(BinaryImage &image);
    ~LabeledImage();
    LabeledImage(LabeledImage &lim);
    void generateConnectedComponents();
    void set_label(int label,int x,int y);
    int get_label(int x,int y);
    int getLabelNumber();
    void setLabelNumber(int ln);
    int getNewLabel();
    void assignLabelColors();
    LabeledImage& operator=(LabeledImage const &i);
    std::ostream& print(std::ostream& os);
  private:
    bool inbounds(int x,int y);
    void changeLabel(int labelTrackarray[],int curLabel,int newLabel,int labelNumber);
    int **_labels;
    int labelNumber;
};

#endif
