#include "common.hpp"

BufferReader::BufferReader(const byte *data, size_t size) :
    cursor(0), dataSize(size), dataBuffer(nullptr) {
    this->dataBuffer = new byte[size];
    memcpy(this->dataBuffer, data, size);
}
BufferReader::~BufferReader() {
    delete[] this->dataBuffer;
}

void BufferReader::_read(void *dest, size_t length) {
    if (this->cursor + length > this->dataSize) {
        throw std::out_of_range("Tried to read outside of buffer.");
    }

    memcpy(dest, this->dataBuffer + this->cursor, length);
    this->cursor += length;
}
