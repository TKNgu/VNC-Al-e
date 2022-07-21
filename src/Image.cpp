#include "Image.hpp"
#include <stdexcept>
#include <cstring>
#include <cmath>
#include <iostream>

using namespace std;

Image::Image(unsigned int width, unsigned int height) : width(width), height(height),
    data(new unsigned char[width * height * 3]) {
    //TODO
}

Image::Image(unsigned int width, unsigned int height, unique_ptr<unsigned char[]> data) :
    width(width), height(height), data(move(data)) {
    //TODO
}

Image::Image(unsigned int width, unsigned int height,
    function<unique_ptr<unsigned char[]>(unsigned int, unsigned int)> dataGen):
    width(width), height(height) {
    this->data = dataGen(this->width, this->height);
}

void Image::save(string path) {
    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[3] = {0,0,0};

    int filesize = 54 + this->width * this->height * 3;
    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);

    bmpinfoheader[ 4] = (unsigned char)(       this->width     );
    bmpinfoheader[ 5] = (unsigned char)(       this->width>> 8 );
    bmpinfoheader[ 6] = (unsigned char)(       this->width>>16 );
    bmpinfoheader[ 7] = (unsigned char)(       this->width>>24 );
    bmpinfoheader[ 8] = (unsigned char)(       this->height    );
    bmpinfoheader[ 9] = (unsigned char)(       this->height>> 8);
    bmpinfoheader[10] = (unsigned char)(       this->height>>16);
    bmpinfoheader[11] = (unsigned char)(       this->height>>24);

    FILE *fileHanle = fopen(path.c_str(), "wb");
    if (fileHanle == nullptr) {
        throw runtime_error("Error open file " + path);
    }
    fwrite(bmpfileheader, 1, 14, fileHanle);
    fwrite(bmpinfoheader, 1, 40, fileHanle);
    auto padSize = (4 - (this->width * 3) % 4) % 4;
    for (int index = 0; index < this->height; index++) {
        fwrite(this->data.get() + (this->width * (this->height - index - 1) * 3), 3, this->width, fileHanle);
        fwrite(bmppad , 1, padSize, fileHanle);
    }
    fflush(fileHanle);
    fclose(fileHanle);
}

Image Image::scale(unsigned int scaleWidth, unsigned int scaleHeight,
    std::function<void(unsigned int, unsigned int, unsigned char*,
            unsigned int, unsigned int, unsigned char*)> scaleFunction) {
    Image tmp(scaleWidth, scaleHeight);
    scaleFunction(this->width, this->height, this->data.get(),
        tmp.width, tmp.height, tmp.data.get());
    return tmp;
}