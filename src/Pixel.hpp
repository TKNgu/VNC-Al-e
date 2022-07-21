#ifndef __PIXEL_HPP__
#define __PIXEL_HPP__

class Pixel {
public:
    Pixel();
    Pixel(const unsigned char *);
    Pixel operator + (Pixel const &);
    Pixel operator - (Pixel const &);
    Pixel operator * (float);
    void copy(unsigned char *);
    void show();
private:
    float data[3];
};

#endif