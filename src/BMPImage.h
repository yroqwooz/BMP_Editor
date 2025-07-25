//
// Created by yronwooz on 7/25/2025.
//

#ifndef BMPIMAGE_H
#define BMPIMAGE_H
#include <cstdint>
#include <string>
#include <windows.h>

class BMPImage {
public:
    BMPImage() = default;
    ~BMPImage();
    bool load(const std::string& filename);
    void display() const;
    void drawLine(int x1, int y1, int x2, int y2);
    void drawCross();
    bool save(const std::string& filename) const;

private:
    uint8_t* data;
    int width, height;
    int bitDepth;
    int rowSize;
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    void setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
    void getPixel(int x, int y, uint8_t& r, uint8_t& g, uint8_t& b) const;
};



#endif //BMPIMAGE_H
