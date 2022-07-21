#include <iostream>
#include "Image.hpp"
#include "Common.hpp"
#include "Pixel.hpp"

using namespace std;

int main(int, char *[]) {
    cout << "Hello" << endl;
    Image image(100, 100, CaroGen);
    image.save("data/sample.bmp");
    Image scale = image.scale(75, 75, ScaleBiliner);
    scale.save("data/scale.bmp");
    // Image scaleSmall = image.scale(75, 75, ScaleBilinerSmall);
    // scaleSmall.save("data/scaleSmall.bmp");
    return 0;
}