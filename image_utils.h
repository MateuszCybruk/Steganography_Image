
#ifndef INC_2324L_22_S30765_SZ_IMAGE_UTILS_H
#define INC_2324L_22_S30765_SZ_IMAGE_UTILS_H


#include <SFML/Graphics.hpp>
#include <string>

void displayImageInfo(const std::string &filePath);
bool isImageLargeEnough(const sf::Image &image, size_t messageSize);


#endif //INC_2324L_22_S30765_SZ_IMAGE_UTILS_H
