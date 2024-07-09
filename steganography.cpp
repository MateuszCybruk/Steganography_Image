#include "steganography.h"
#include <fmt/core.h>
#include <bitset>
#include <sstream>
#include "image_utils.h"

void checkMessageFit(const std::string &filePath, const std::string &message) {
    sf::Image image;
    if (!image.loadFromFile(filePath)) {
        fmt::println("Error: Could not load image {}", filePath);
        return;
    }

    std::istringstream messageStream(message);
    std::vector<std::bitset<8>> bitsets;
    for (std::string line; std::getline(messageStream, line);) {
        for (char c: line) {
            bitsets.emplace_back(static_cast<int>(c));
        }
    }
    bitsets.emplace_back(static_cast<int>(0x03)); // terminator

    size_t messageSize = bitsets.size();
    if (isImageLargeEnough(image, messageSize)) {
        fmt::println("The image is large enough to store the message.");
    } else {
        fmt::println("The image is not large enough to store the message.");
    }
}

void printDecrypted(const std::string &message) {
    // Print the result ensuring valid UTF-8 output
    fmt::print("Decoded message: ");
    for (char c: message) {
        if ((c >= 32 && c <= 126) || c == '\n' || c == '\r' || c == '\t') {
            fmt::print("{}", c);
        }
    }
}

void encrypt(sf::Image &image, std::istream &message) {
    std::vector<std::bitset<8>> bitsets;
    for (std::string line; std::getline(message, line);) {
        for (char c: line) {
            bitsets.emplace_back(static_cast<int>(c));
        }
    }


    size_t messageSize = bitsets.size();
    if (!isImageLargeEnough(image, messageSize)) {
        fmt::println("Error: The image is not large enough to store the message.");
        return;
    }

    bitsets.emplace_back(static_cast<int>(0x03)); //terminator

    size_t bitIndex = 0;
    for (unsigned int x = 0; x < image.getSize().x; ++x) {
        for (unsigned int y = 0; y < image.getSize().y; ++y) {
            if (bitIndex >= bitsets.size()) {
                return; // All bits have been encoded
            }
            sf::Color pixelColor = image.getPixel(x, y);
            auto bits = bitsets[bitIndex];

            std::bitset<2> twobits;

            //red
            twobits.set(0, bits[0]);
            twobits.set(1, bits[1]);
            pixelColor.r = (pixelColor.r & 0xFC) | twobits.to_ullong();

            //green
            twobits.set(0, bits[2]);
            twobits.set(1, bits[3]);
            pixelColor.g = (pixelColor.g & 0xFC) | twobits.to_ullong();

            //blue
            twobits.set(0, bits[4]);
            twobits.set(1, bits[5]);
            pixelColor.b = (pixelColor.b & 0xFC) | twobits.to_ullong();

            //alpha
            twobits.set(0, bits[6]);
            twobits.set(1, bits[7]);
            pixelColor.a = (pixelColor.a & 0xFC) | twobits.to_ullong();

            image.setPixel(x, y, pixelColor);
            ++bitIndex;
        }
    }
}

std::string decrypt(sf::Image &image) {
    //DO NOT print decrypted string directly from this method.
    //Returned string can contain all ASCI characters including NULL.
    std::vector<std::bitset<8>> bitsets;
    bool terminatorFound = false;

    for (unsigned int x = 0; x < image.getSize().x; ++x) {
        for (unsigned int y = 0; y < image.getSize().y; ++y) {


            sf::Color pixelColor = image.getPixel(x, y);
            std::bitset<8> sign;
            std::bitset<8> rchanel = static_cast<int>(pixelColor.r);
            std::bitset<8> gchanel = static_cast<int>(pixelColor.g);
            std::bitset<8> bchanel = static_cast<int>(pixelColor.b);
            std::bitset<8> achanel = static_cast<int>(pixelColor.a);


            //red
            sign.set(0, rchanel[0]);
            sign.set(1, rchanel[1]);

            //green
            sign.set(2, gchanel[0]);
            sign.set(3, gchanel[1]);

            //blue
            sign.set(4, bchanel[0]);
            sign.set(5, bchanel[1]);

            //alpha
            sign.set(6, achanel[0]);
            sign.set(7, achanel[1]);



            if (sign.to_ulong() == 0x03) {
                terminatorFound = true;
                break;
            }
            bitsets.push_back(sign);
        }
        if (terminatorFound) {
            break;
        }
    }


    std::string res;
    for (const auto &bits: bitsets) {
        res.push_back(static_cast<char>(bits.to_ulong()));
    }
    return res;


}
