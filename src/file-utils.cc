#include "common.hpp"
#include "file-utils.hpp"


std::vector<uint8_t> FileUtils::readFile(const fs::path &filePath) {
    std::ifstream file(filePath, std::ios::binary);
    std::streampos fileSize;

    // prevent eating new lines in binary mode
    file.unsetf(std::ios::skipws);

    // get file size
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // reserve capacity
    std::vector<uint8_t> data;
    data.reserve((size_t)fileSize);

    // copy it into vector
    data.insert(data.begin(), std::istream_iterator<uint8_t>(file), std::istream_iterator<uint8_t>());

    return data;
}

size_t FileUtils::getFileSize(std::ifstream& file) {
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    return fileSize;
}

