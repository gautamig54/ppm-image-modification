#ifndef Gaussian_H_
#define Gaussian_H_

#include<vector>
#include "Image.h"
class Gaussian : public Image {
public:
    Gaussian();
    Gaussian(Image& a);
    Gaussian(int w,int h,int max);
    ~Gaussian();
    void apply_gaussian();
    friend float get_saturation(Pixel& p);
    std::vector<Pixel*> local_maxima();
    bool is_max(int i,int j);
    friend bool is_in_24_neighbourhood(Pixel* p1,Pixel* p2);
    std::vector<Pixel*> neighbourhood_24_color();
    std::vector<Pixel*> neighbourhood_24(Pixel* p);
    bool is_valid_coor(int x,int y);
    std::ostream& print(std::ostream& os);
private:
    static int const gauss_array[5][5];
};

#endif