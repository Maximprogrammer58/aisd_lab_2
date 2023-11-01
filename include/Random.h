#ifndef LAB_2_INCLUDE_RANDOM_H
#define LAB_2_INCLUDE_RANDOM_H

#include <string>
#include <random>

std::string disks[3] = {"D", "C", "E"};
std::string file_extensions[16] = { ".jpg", ".png", ".bmp", ".gif", ".tif", ".doc", ".xls", ".pdf", ".txt", ".mp3", ".mp4", ".ppt", ".html", ".py", ".cc", ".h"};

int generateRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(mt);
}

std::string generateRandomString(int length) {
    std::random_device rd;
    std::uniform_int_distribution<int> distribution(97, 122);
    std::string randomString;
    for (int i = 0; i < length; i++) {
        randomString += static_cast<char>(distribution(rd));
    }
    return randomString;
}

std::string randomSelectionFromArray(std::string* array, int size) {
    return array[generateRandomNumber(0, size - 1)];
}

#endif