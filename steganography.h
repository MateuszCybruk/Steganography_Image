
#ifndef INC_2324L_22_S30765_SZ_STEGANOGRAPHY_H
#define INC_2324L_22_S30765_SZ_STEGANOGRAPHY_H


#include <SFML/Graphics.hpp>
#include <string>
#include <istream>

void encrypt(sf::Image &image, std::istream &message);
std::string decrypt(sf::Image &image);
void checkMessageFit(const std::string &filePath, const std::string &message);
void printDecrypted(const std::string &message);

#endif //INC_2324L_22_S30765_SZ_STEGANOGRAPHY_H
