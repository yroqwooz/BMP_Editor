#include <iostream>
#include <string>
#include <filesystem>

#include "src/BMPImage.h"

int main() {
    std::string inputFile, outputFile;

    std::cout << ">> Enter input BMP file name: ";
    std::getline(std::cin, inputFile);

    BMPImage image;

    if (!image.load(inputFile)) {
        std::cerr << "Failed to load BMP.\n";
        return 1;
    }

    image.display();
    image.drawCross();
    std::cout << "\nAfter drawing cross:\n";
    image.display();

    std::cout << ">> Enter output BMP file name: ";
    std::getline(std::cin, outputFile);

    if (!image.save(outputFile)) {
        std::cerr << "Failed to save BMP.\n";
        return 1;
    }

    return 0;
}

