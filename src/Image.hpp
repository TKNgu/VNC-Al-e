#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include <string>

enum TEMPLATE {BLACK, WHITE, CARO};

class Image {
public:
    Image(unsigned int, unsigned int, TEMPLATE = BLACK);
    ~Image();
    void save(std::string);
private:
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned char *data = nullptr;
};

#endif