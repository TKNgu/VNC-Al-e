#include "Common.hpp"
#include <cstring>
#include <cmath>
#include "Pixel.hpp"
#include <iostream>

using namespace std;

unique_ptr<unsigned char[]> BlackGen(unsigned int width, unsigned int height) {
    size_t size = width * height * 3;
    auto data = unique_ptr<unsigned char[]>(new unsigned char[size]);
    memset((void *)data.get(), 0x00, sizeof(char) * size);
    return data;
}

unique_ptr<unsigned char[]> WhiteGen(unsigned int width, unsigned int height) {
    size_t size = width * height * 3;
    auto data = unique_ptr<unsigned char[]>(new unsigned char[size]);
    memset((void *)data.get(), 0xff, sizeof(char) * size);
    return data;
}

unique_ptr<unsigned char[]> CaroGen(unsigned int width, unsigned int height) {
    auto data = WhiteGen(width, height);
    auto color = 0;
    auto size = 5;
    auto sizex2 = size << 1;
    for (int indexY = 0; indexY < height; indexY++) {
        auto offset = (indexY % sizex2 < size) ? size : 0;
        for (int indexX = 0; indexX < width; indexX++) {
            auto pixel = data.get() + (indexY * width + indexX) * 3;
            color = (indexX + offset) % sizex2 < size ? 0 : 255;
            pixel[0] = color;
            pixel[1] = color;
            pixel[2] = color;  
        }
    }
    return data;
}

void ScaleNN(unsigned int width, unsigned int height, unsigned char *data,
    unsigned int scaleWidth, unsigned int scaleHeight, unsigned char * scaleData) {
    float scaleWidthRatio = (float)width / (float)scaleWidth;
    float scaleHeightRatio = (float)height / (float)scaleHeight;
    unsigned int refWidth;
    unsigned int refHeight;
    unsigned char *refData;
    unsigned char *pixel;
    for (auto indexX = 0; indexX < scaleWidth; indexX++) {
        refWidth = round(indexX * scaleWidthRatio);
        for (auto indexY = 0; indexY < scaleHeight; indexY++) {
            refHeight = round(indexY * scaleHeightRatio);
            refData = data + ((refHeight * width) + refWidth) * 3;
            pixel = scaleData + ((indexY * scaleWidth) + indexX) * 3;
            pixel[0] =refData[0];
            pixel[1] = refData[1];
            pixel[2] = refData[2];
        }
    }
}

void ScaleBiliner(unsigned int width, unsigned int height, unsigned char *data,
    unsigned int scaleWidth, unsigned int scaleHeight, unsigned char *scaleData) {
    float scaleWidthRatio = (float)width / (float)scaleWidth;
    float scaleHeightRatio = (float)height / (float)scaleHeight;
    unsigned int refWidthFloor;
    unsigned int refWidthCeil;
    unsigned int refHeightFloor;
    unsigned int refHeightCeil;
    float tmp;
    float wRatio;
    float hRatio;
    size_t tmpHFW;
    size_t tmpHCW;
    size_t tmpWF;
    size_t tmpWC;
    float tmpWR;
    float tmpHR;
    for (auto indexX = 0; indexX < scaleWidth; indexX++) {
        tmp = indexX * scaleWidthRatio;
        refWidthFloor = floor(tmp);
        refWidthCeil = ceil(tmp);
        wRatio = tmp - refWidthFloor;
        tmpWF = refWidthFloor * 3;
        tmpWC = refWidthCeil * 3;
        tmpWR = 1 - wRatio;
        for (auto indexY = 0; indexY < scaleHeight; indexY++) {
            tmp = indexY * scaleHeightRatio;
            refHeightFloor = floor(tmp);
            refHeightCeil = ceil(tmp);
            hRatio = tmp - refHeightFloor;
            tmpHFW = refHeightFloor * width * 3;
            tmpHCW = refHeightCeil * width * 3;
            tmpHR = 1 - hRatio;
            Pixel A(data + tmpHFW + tmpWF);
            Pixel B(data + tmpHFW + tmpWC);
            Pixel C(data + tmpHCW + tmpWF);
            Pixel D(data + tmpHCW + tmpWC);
            auto Y = A * tmpWR * tmpHR + B * wRatio * tmpHR + C * hRatio * tmpWR + D * wRatio * hRatio;
            Y.copy(scaleData + ((indexY * scaleWidth) + indexX) * 3);
        }
    }
}