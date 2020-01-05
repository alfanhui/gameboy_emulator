#include "FileLoader.h"
#include <iostream>
#include <fstream>
#include <string>

char* FileLoader::ReadFile(std::string filePath) {

    std::ifstream inputFile(filePath, std::ifstream::binary);
    if (inputFile) {
        inputFile.seekg(0, inputFile.end);
        int bufferLength = inputFile.tellg();
        inputFile.seekg(0, inputFile.beg); //put seeker at beginning.

        char* buffer = new char[bufferLength];

        inputFile.read((char*)buffer, bufferLength);
        inputFile.close();
        return buffer;
    }
    return 0;
}

int FileLoader::sizeOfFile(std::string filePath) {
    std::ifstream inputFile(filePath, std::ifstream::binary);
    if (inputFile) {
        inputFile.seekg(0, inputFile.end);
        int length = inputFile.tellg();
        inputFile.close();
        return length;
    }
    else {
        return 0;
    }
}


void FileLoader::PrintPointerHex(char* buffer, int bufferLength, int location = -1) {
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
