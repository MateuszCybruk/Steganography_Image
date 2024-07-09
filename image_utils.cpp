#include "image_utils.h"
#include <fmt/core.h>
#include <filesystem>
#include <chrono>
#include <iostream>
#include "utils.h"

void displayImageInfo(const std::string &filePath) {
    sf::Image image;
    if (!image.loadFromFile(filePath)) {
        fmt::println("Error: Could not load image {}", filePath);
        return;
    }

    auto size = image.getSize();
    auto lastWriteTime = std::filesystem::last_write_time(filePath);
    std::cout << std::format("Last Modification Time: {}\n", lastWriteTime);
    fmt::println("Image Information:");
    fmt::println("File: {}", filePath);
    fmt::println("Size: {}x{}", size.x, size.y);
    fmt::println("Memory Usage: {} bytes", size.x * size.y * 4); // Assuming RGBA
}

bool isImageLargeEnough(const sf::Image &image, size_t messageSize) {
    size_t pixelsNeeded = messageSize; // 8 bits per character
    size_t imagePixels = image.getSize().x * image.getSize().y;
    return imagePixels >= pixelsNeeded;
}


