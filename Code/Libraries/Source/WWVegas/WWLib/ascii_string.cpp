// cl: /O1
// Upstream implementation and layout: Open-BFME-1 ascii_string.h.

class AsciiString;
class PooledString;
class UnicodeString;

typedef unsigned short wchar_t;

template <typename T>
class StringBase
{
public:
    void set(const StringBase<T> &that);
    void set(const T *text);
    void set(const T *text, int length);
    void concat(const StringBase<T> &that);
    void concat(const T *text);
    void concat(const T *text, int length);

private:
    friend class AsciiString;

    StringBase(const StringBase<T> &that);
    StringBase(T character);
    StringBase(const T *text);
    StringBase(const T *text, int length);
    StringBase(const T *text, int start, int length);
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
    AsciiString &operator+=(const PooledString &that);
    AsciiString(const AsciiString &that);
    AsciiString(char character);
    AsciiString(const char *text);
    AsciiString(const char *text, int length);
    AsciiString(const char *text, int start, int length);
    AsciiString(const AsciiString &that, int start, int length);
    AsciiString &operator=(const AsciiString &that);
    AsciiString &operator=(char character);
    AsciiString &operator=(const char *text);
    AsciiString &operator+=(const AsciiString &that);
    AsciiString &operator+=(char character);
    AsciiString &operator+=(const char *text);

private:
    char *m_text;
};

// A PooledString is one pointer to a shared entry whose text starts at +8, and
// the entry is never null, so there is no empty-string fallback here.
struct PooledStringEntry
{
    void *m_unknown0;
    PooledStringEntry *m_noCase;
    char m_text[1];
};

AsciiString &AsciiString::operator+=(const PooledString &that)
{
    const PooledStringEntry *entry = *(const PooledStringEntry *const *)&that;

    ((StringBase<char> *)this)->concat(entry->m_text);

    return *this;
}

AsciiString::AsciiString(const AsciiString &that)
{
    ((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
}

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

AsciiString::AsciiString(const char *text, int start, int length)
{
    ((StringBase<char> *)this)->StringBase<char>::StringBase(text, start, length);
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

AsciiString &AsciiString::operator=(const char *text)
{
    ((StringBase<char> *)this)->set(text);
    return *this;
}

AsciiString &AsciiString::operator+=(const AsciiString &that)
{
    ((StringBase<char> *)this)->concat(*(const StringBase<char> *)&that);
    return *this;
}

AsciiString &AsciiString::operator+=(char character)
{
    char text = character;
    ((StringBase<char> *)this)->concat(&text, 1);
    return *this;
}

AsciiString &AsciiString::operator+=(const char *text)
{
    ((StringBase<char> *)this)->concat(text);
    return *this;
}
