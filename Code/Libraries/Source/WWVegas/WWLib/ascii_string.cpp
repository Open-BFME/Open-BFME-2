// cl: /O1
// Upstream implementation and layout: Open-BFME-1 ascii_string.h.

class AsciiString;

template <typename T>
class StringBase
{
public:
    void set(const StringBase<T> &that);
    void set(const T *text, int length);
    void concat(const T *text, int length);

private:
    friend class AsciiString;

    StringBase(T character);
    StringBase(const T *text);
    StringBase(const T *text, int length);
    StringBase(const StringBase<T> &that, int start, int length);

    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;
};

class AsciiString
{
public:
    AsciiString(char character);
    AsciiString(const char *text);
    AsciiString(const char *text, int length);
    AsciiString(const AsciiString &that, int start, int length);
    AsciiString &operator=(const AsciiString &that);
    AsciiString &operator=(char character);
    AsciiString &operator+=(char character);

private:
    char *m_text;
};

AsciiString::AsciiString(char character)
{
    ((StringBase<char> *)this)->StringBase<char>::StringBase(character);
}

AsciiString::AsciiString(const char *text)
{
    ((StringBase<char> *)this)->StringBase<char>::StringBase(text);
}

AsciiString::AsciiString(const char *text, int length)
{
    ((StringBase<char> *)this)->StringBase<char>::StringBase(text, length);
}

AsciiString::AsciiString(const AsciiString &that, int start, int length)
{
    ((StringBase<char> *)this)->StringBase<char>::StringBase(
        *(const StringBase<char> *)&that, start, length);
}

AsciiString &AsciiString::operator=(const AsciiString &that)
{
    ((StringBase<char> *)this)->set(*(const StringBase<char> *)&that);
    return *this;
}

AsciiString &AsciiString::operator=(char character)
{
    char text = character;
    ((StringBase<char> *)this)->set(&text, 1);
    return *this;
}

AsciiString &AsciiString::operator+=(char character)
{
    char text = character;
    ((StringBase<char> *)this)->concat(&text, 1);
    return *this;
}
