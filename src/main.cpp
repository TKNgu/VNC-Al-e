#include <iostream>
#include "Image.hpp"

using namespace std;

int main(int, char *[]) {
    cout << "Hello" << endl;
    Image image(100, 100, TEMPLATE::CARO);
    image.save("data/sample.bmp");
    return 0;
}