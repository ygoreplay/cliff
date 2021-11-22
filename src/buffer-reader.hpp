#ifndef CLIFF_BUFFER_READER_HPP
#define CLIFF_BUFFER_READER_HPP

class BufferReader {
public:
    BufferReader(const byte* data, size_t size);
    ~BufferReader();

private:
    void _read(void* dest, size_t length);

    template <typename T1, typename T2>
    int copyString(T1* src, T2* pstr, int bufsize) {
        int l = 0;
        while(src[l] && l < bufsize - 1) {
            pstr[l] = src[l];
            l++;
        }
        pstr[l] = 0;
        return l;
    }

public:
    [[nodiscard]] size_t position() const {
        return this->cursor;
    }
    [[nodiscard]] size_t size() const {
        return this->dataSize;
    }
    [[nodiscard]] byte* current() const {
        return this->dataBuffer + this->cursor;
    }

    size_t moveCursorForward(size_t count = 1) {
        return (this->cursor += count);
    }

    size_t readBytes(byte* dest, size_t length) {
        if (this->cursor + length > this->dataSize) {
            length = std::min(length, this->dataSize - this->cursor);
        }

        this->_read(dest, length);
        return length;
    }
    void readName(wchar_t* dest) {
        unsigned short buffer[20];
        this->readBytes(reinterpret_cast<byte*>(buffer), 40);
        this->copyString(buffer, dest, 20);
    }

    template <typename T>
    T read() {
        T result;
        this->_read(&result, sizeof(T));
        return result;
    }

    template <typename T>
    size_t read(T& result) {
        this->_read(&result, sizeof(T));
        return sizeof(T);
    }

public:
    [[nodiscard]] const byte* data() const {
        return this->dataBuffer;
    }

private:
    byte* dataBuffer;
    size_t cursor;
    size_t dataSize;
};

#endif // CLIFF_BUFFER_READER_HPP
