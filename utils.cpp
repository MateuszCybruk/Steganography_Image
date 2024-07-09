#include "utils.h"
#include <fmt/core.h>
#include <chrono>
void printUsage() {
    fmt::println("Usage: [flag] [arguments]");
    fmt::println("Supported file extensions for images are .bmp and .png");
    fmt::println("Flags:");
    fmt::println("-i, --info       Display information about the image file");
    fmt::println("-e, --encrypt    Encrypt a message into the image file");
    fmt::println("-d, --decrypt    Decrypt a message from the image file");
    fmt::println("-c, --check      Check if a message can be stored in the image file");
    fmt::println("-h, --help       Display this help message");
}

bool isValidFormat(const std::string &filepath) {
    return filepath.ends_with(".png") || filepath.ends_with(".bmp");
}



