#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include <string>
#include <memory>
#include <functional>

class Image {
public:
    Image(unsigned int, unsigned int);
    Image(unsigned int, unsigned int, std::unique_ptr<unsigned char[]>);
    Image(unsigned int, unsigned int, std::function<std::unique_ptr<unsigned char[]>(unsigned int, unsigned int)>);
    void save(std::string);
    Image scale(unsigned int, unsigned int,
        std::function<void(unsigned int, unsigned int, unsigned char*,
            unsigned int, unsigned int, unsigned char*)>);
private:
    unsigned int width = 0;
    unsigned int height = 0;
    std::unique_ptr<unsigned char[]> data;
};

#endif