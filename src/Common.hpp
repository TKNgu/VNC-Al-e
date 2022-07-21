#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <memory>

std::unique_ptr<unsigned char[]> BlackGen(unsigned int, unsigned int);
std::unique_ptr<unsigned char[]> WhiteGen(unsigned int, unsigned int);
std::unique_ptr<unsigned char[]> CaroGen(unsigned int, unsigned int);

void ScaleNN(unsigned int, unsigned int, unsigned char *,
    unsigned int, unsigned int, unsigned char *);
void ScaleBiliner(unsigned int, unsigned int, unsigned char *,
    unsigned int, unsigned int, unsigned char *);

#endif