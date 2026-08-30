// cl: /O1
// Upstream implementation and layout: Open-BFME-1 ascii_string.h.

template <typename T>
class StringBase
{
public:
    void set(const StringBase<T> &that);

private:
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
    AsciiString &operator=(const AsciiString &that);

private:
    char *m_text;
};

AsciiString &AsciiString::operator=(const AsciiString &that)
{
    ((StringBase<char> *)this)->set(*(const StringBase<char> *)&that);
    return *this;
}
