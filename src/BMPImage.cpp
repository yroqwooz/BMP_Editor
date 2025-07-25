//
// Created by yronwooz on 7/25/2025.
//

#include <fstream>
#include <iostream>

#include "BMPImage.h"

bool BMPImage::load(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return false;

    file.read(reinterpret_cast<char *>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char *>(&infoHeader), sizeof(infoHeader));

    if (fileHeader.bfType != 0x4D42) {
        std::cerr << "BMPImage::load: Not a BMP 1.\n";
        return false;
    }
    if (infoHeader.biBitCount != 24 && infoHeader.biBitCount != 32) {
        std::cerr << "BMPImage::load: Not a BMP 2.\n";
        return false;
    }

    width = infoHeader.biWidth;
    height = infoHeader.biHeight;
    bitDepth = infoHeader.biBitCount;
    rowSize = ((bitDepth * width + 31) / 32) * 4;
    size_t dataSize = rowSize * abs(height);

    data = new uint8_t[dataSize];
    file.seekg(fileHeader.bfOffBits, std::ios::beg);
    file.read(reinterpret_cast<char *>(data), dataSize);
    file.close();

    return true;
}

void BMPImage::display() const {
    std::cout << "\n";
    for (int y = 0; y < height; ++y) {
        const uint8_t* row = data + rowSize * (height - 1 - y);
        for (int x = 0; x < width; ++x) {
            uint8_t b = row[x * (bitDepth / 8) + 0];
            uint8_t g = row[x * (bitDepth / 8) + 1];
            uint8_t r = row[x * (bitDepth / 8) + 2];

            if (r == 0 && g == 0 && b == 0) std::cout << "#";
            else if (r == 255 && g == 255 && b == 255) std::cout << " ";
            else std::cout << "?";
        }
        std::cout << '\n';
    }
}

void BMPImage::drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        setPixel(x1, y1, 0, 0, 0); // чёрный
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}

void BMPImage::drawCross() {
    drawLine(0, 0, width - 1, height - 1);
    drawLine(width - 1, 0, 0, height - 1);
}

bool BMPImage::save(const std::string& filename) const {
    std::ofstream out(filename, std::ios::binary);
    if (!out) return false;

    out.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    out.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));
    out.write(reinterpret_cast<const char*>(data), rowSize * abs(height));

    out.close();
    return true;
}

BMPImage::~BMPImage() {
    delete[] data;
}

void BMPImage::setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    if (x < 0 || y < 0 || x >= width || y >= height) return;
    uint8_t* row = data + rowSize * (height - 1 - y);
    uint8_t* pixel = row + x * (bitDepth / 8);
    pixel[0] = b;
    pixel[1] = g;
    pixel[2] = r;
    if (bitDepth == 32) pixel[3] = 255;
}