#include "Image.hpp"
#include <stdexcept>
#include <cstring>

using namespace std;

inline unsigned char *BlackGen(unsigned int, unsigned int);
inline unsigned char *WhiteGen(unsigned int, unsigned int);

Image::Image(unsigned int width, unsigned int height, TEMPLATE type) :
    width(width), height(height) {
    switch (type) {
        case TEMPLATE::BLACK:
            this->data = BlackGen(this->width, this->height);
            return;
        case TEMPLATE::WHITE:
            this->data = WhiteGen(this->width, this->height);
            return;
    }
}

Image::~Image() {
    delete[] this->data;
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
        fwrite(this->data + (this->width * (this->height - index - 1) * 3), 3, this->width, fileHanle);
        fwrite(bmppad , 1, padSize, fileHanle);
    }

    fflush(fileHanle);
    fclose(fileHanle);
}

unsigned char *BlackGen(unsigned int width, unsigned int height) {
    size_t size = width * height * 3;
    auto data = new unsigned char[size];
    memset(data, 0x00, sizeof(char) * size);
    return data;
}

unsigned char *WhiteGen(unsigned int width, unsigned int height) {
    size_t size = width * height * 3;
    auto data = new unsigned char[size];
    memset(data, 0xff, sizeof(char) * size);
    return data;
}