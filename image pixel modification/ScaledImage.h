#ifndef ScaledImage_h
#define ScaledImage_h

#include "Image.h"
#include "Pixel.h"
#include "Color.h"

class ScaledImage : public Image {
public:
	ScaledImage();
	
	void Scaling_reflect(Image &img);
	std::ostream& print(std::ostream& os);

};

#endif
