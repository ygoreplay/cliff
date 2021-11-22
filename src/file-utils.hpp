#ifndef CLIFF_FILE_UTILS_HPP
#define CLIFF_FILE_UTILS_HPP

class FileUtils {
public:
    static size_t getFileSize(std::ifstream& file);
    static std::vector<uint8_t> readFile(const fs::path& filePath);
};

#endif // CLIFF_FILE_UTILS_HPP
