// cl: /O1

typedef unsigned short wchar_t;
// Upstream implementation and layout: Open-BFME-1 unicode_string.h.

class UnicodeString;

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
    friend class UnicodeString;

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

class UnicodeString
{
public:
    UnicodeString(const UnicodeString &that);
    UnicodeString(wchar_t character);
    UnicodeString(const wchar_t *text);
    UnicodeString(const wchar_t *text, int length);
    UnicodeString(const wchar_t *text, int start, int length);
    UnicodeString(const UnicodeString &that, int start, int length);
    UnicodeString &operator=(const UnicodeString &that);
    UnicodeString &operator=(wchar_t character);
    UnicodeString &operator=(const wchar_t *text);
    UnicodeString &operator+=(const UnicodeString &that);
    UnicodeString &operator+=(wchar_t character);
    UnicodeString &operator+=(const wchar_t *text);

private:
    wchar_t *m_text;
};

UnicodeString::UnicodeString(const UnicodeString &that)
{
    ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
        *(const StringBase<wchar_t> *)&that);
}

UnicodeString::UnicodeString(wchar_t character)
{
    ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(character);
}

UnicodeString::UnicodeString(const wchar_t *text)
{
    ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(text);
}

UnicodeString::UnicodeString(const wchar_t *text, int length)
{
    ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(text, length);
}

UnicodeString::UnicodeString(const wchar_t *text, int start, int length)
{
    ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(text, start, length);
}

UnicodeString::UnicodeString(const UnicodeString &that, int start, int length)
{
    ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
        *(const StringBase<wchar_t> *)&that, start, length);
}

UnicodeString &UnicodeString::operator=(const UnicodeString &that)
{
    ((StringBase<wchar_t> *)this)->set(*(const StringBase<wchar_t> *)&that);
    return *this;
}

UnicodeString &UnicodeString::operator=(wchar_t character)
{
    wchar_t text = character;
    ((StringBase<wchar_t> *)this)->set(&text, 1);
    return *this;
}

UnicodeString &UnicodeString::operator=(const wchar_t *text)
{
    ((StringBase<wchar_t> *)this)->set(text);
    return *this;
}

UnicodeString &UnicodeString::operator+=(const UnicodeString &that)
{
    ((StringBase<wchar_t> *)this)->concat(*(const StringBase<wchar_t> *)&that);
    return *this;
}

UnicodeString &UnicodeString::operator+=(wchar_t character)
{
    wchar_t text = character;
    ((StringBase<wchar_t> *)this)->concat(&text, 1);
    return *this;
}

UnicodeString &UnicodeString::operator+=(const wchar_t *text)
{
    ((StringBase<wchar_t> *)this)->concat(text);
    return *this;
}
