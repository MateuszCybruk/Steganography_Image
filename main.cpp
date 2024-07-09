#include <iostream>
#include <fmt/core.h>
#include "image_utils.h"
#include "steganography.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printUsage();
        return 1;
    }

    std::string flag = argv[1];

    if (flag == "-i" or flag == "--info") {
        if (argc != 3) {
            fmt::println("Error: Incorrect number of arguments for info flag");
            fmt::println("Type -h or --help for more information");
            return 1;
        }
        std::string filePath = argv[2];
        if (!isValidFormat(filePath)) {
            fmt::println("Error: Incorrect file extension, use .bmp or .png");
            fmt::println("Type -h or --help for more information");
            return 1;
        }
        displayImageInfo(filePath);
    } else if (flag == "-e" or flag == "--encrypt") {
        if (argc != 4) {
            fmt::println("Error: Incorrect number of arguments for info flag");
            fmt::println("Type -h or --help for more information");
            return 1;
        }
        std::string filePath = argv[2];
        if (!isValidFormat(filePath)) {
            fmt::println("Error: Incorrect file extension, use .bmp or .png");
            fmt::println("Type -h or --help for more information");
            return 1;
        }
        std::string message = argv[3];

        sf::Image image;
        if (!image.loadFromFile(filePath)) {
            fmt::println("Error: Could not load image from path:{}", filePath);
            return 1;
        }
        std::istringstream messageStream(message);
        encrypt(image, messageStream);
        image.saveToFile(filePath);
        fmt::println("Message encrypted into image {}", filePath);
    } else if (flag == "-d" or flag == "--decrypt") {
        if (argc != 3) {
            fmt::println("Error: Incorrect number of arguments for info flag");
            fmt::println("Type -h or --help for more information");
            return 1;
        }
        std::string filePath = argv[2];
        if (!isValidFormat(filePath)) {
            fmt::println("Error: Incorrect file extension, use .bmp or .png");
            fmt::println("Type -h or --help for more information");
            return 1;
        }
        sf::Image image;
        if (!image.loadFromFile(filePath)) {
            fmt::println("Error: Could not load image from path:{}", filePath);
            return 1;
        }
        printDecrypted(decrypt(image));
    } else if (flag == "-c" or flag == "--check") {
        if (argc != 4) {
            fmt::println("Error: Incorrect number of arguments for info flag");
            fmt::println("Type -h or --help for more information");
            return 1;
        }
        std::string filePath = argv[2];
        if (!isValidFormat(filePath)) {
            fmt::println("Error: Incorrect file extension, use .bmp or .png");
            fmt::println("Type -h or --help for more information");
            return 1;
        }
        std::string message = argv[3];
        sf::Image image;
        if (!image.loadFromFile(filePath)) {
            fmt::println("Error: Could not load image {}", filePath);
            return 1;
        }
        checkMessageFit(filePath, message);
    } else if (flag == "-h" or flag == "--help") {
        printUsage();
    } else {
        fmt::println("Error: Unknown flag {}", flag);
        fmt::println("Type -h or --help for more information");
    }

    return 0;
}

