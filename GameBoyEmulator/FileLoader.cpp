#include "FileLoader.h"
#include <iostream>
#include <fstream>
#include <string>

uint8_t* FileLoader::ReadFile(std::string filePath) {

    std::ifstream inputFile(filePath, std::ifstream::binary);
    if (inputFile) {
        inputFile.seekg(0, inputFile.end);
        signed int bufferLength = (int)inputFile.tellg();
        inputFile.seekg(0, inputFile.beg); //put seeker at beginning.

        uint8_t* buffer = new uint8_t[bufferLength];

        inputFile.read((char*)buffer, bufferLength);
        inputFile.close();
        return buffer;
    }
    inputFile.close();
    return 0;
}

int FileLoader::SizeOfFile(std::string filePath) {
    std::ifstream inputFile(filePath, std::ifstream::binary);
    if (inputFile) {
        inputFile.seekg(0, inputFile.end);
        signed int length = (int)inputFile.tellg();
        inputFile.close();
        return length;
    }
    else {
        inputFile.close();
        return 0;
    }
}


void FileLoader::PrintPointerHex(uint8_t* buffer, int bufferLength, int location = -1) {
    if (location != -1) {
        std::cout << std::hex << (int)buffer[location] << std::endl;
    }
    else {
        for (int i = 0; i < bufferLength; i++)
        {
            std::cout << std::hex << (int)buffer[i] << " ";
            if ((i + 1) % 16 == 0) {
                std::cout << std::endl;
            }
        }
    }
}
