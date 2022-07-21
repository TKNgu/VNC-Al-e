#include "Pixel.hpp"
#include <cmath>
#include <iostream>

using namespace std;

Pixel::Pixel() {
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
}

Pixel::Pixel(const unsigned char *data) {
    this->data[0] = data[0];
    this->data[1] = data[1];
    this->data[2] = data[2];
}

Pixel Pixel::operator + (Pixel const &a) {
    Pixel tmp;
    tmp.data[0] = this->data[0] + a.data[0];
    tmp.data[1] = this->data[1] + a.data[1];
    tmp.data[2] = this->data[2] + a.data[2];
    return tmp;
}

Pixel Pixel::operator - (Pixel const &a) {
    Pixel tmp;
    tmp.data[0] = this->data[0] - a.data[0];
    tmp.data[1] = this->data[1] - a.data[1];
    tmp.data[2] = this->data[2] - a.data[2];
    return tmp;
}

Pixel Pixel::operator * (float value) {
    Pixel tmp;
    tmp.data[0] = this->data[0] * value;
    tmp.data[1] = this->data[1] * value;
    tmp.data[2] = this->data[2] * value;
    return tmp;
}

void Pixel::copy(unsigned char *data) {
    data[0] = round(this->data[0]);
    data[1] = round(this->data[1]);
    data[2] = round(this->data[2]);
}

void Pixel::show() {
    cout << data[0] << " " << data[1] << " " << data[2] << endl;    
}