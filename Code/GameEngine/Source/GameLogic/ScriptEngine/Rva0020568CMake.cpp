// cl: /EHsc
// ?Rva0020568CMake@@YA?AURva0020561C@@ABU?$pair@VAsciiString@@V1@@_STL@@ABV?$StringBase@D@@@Z @0x0020568B 27B
// Hidden-dest forwarder over rowed Rva0020561C pair-plus-StringBase ctor 0x0020561C.
// Same 27B shape as rowed make_pair 0x0032ACCF and siblings 0x002056A6 0x00205655 0x00205670.
// Caller at 0x00208E0E.
template <typename T> class StringBase
{
    friend class AsciiString;
    friend struct Rva0020561C;
    StringBase(const StringBase<T> &other);
    void releaseBuffer();
    void *m_data;
public:
    ~StringBase() { releaseBuffer(); }
};

class AsciiString
{
public:
    AsciiString(const AsciiString &other);
    ~AsciiString();
private:
    void *m_data;
};

namespace _STL {
template <class T1, class T2> struct pair
{
    T1 first;
    T2 second;
    pair(const pair<T1, T2> &other);
    pair(const T1 &a, const T2 &b);
};
}

struct Rva0020561C
{
    _STL::pair<AsciiString, AsciiString> m_pair;
    StringBase<char> m_str;
    Rva0020561C(const _STL::pair<AsciiString, AsciiString> &p, const StringBase<char> &s);
    ~Rva0020561C();
};

Rva0020561C Rva0020568CMake(const _STL::pair<AsciiString, AsciiString> &p, const StringBase<char> &s);

Rva0020561C Rva0020568CMake(const _STL::pair<AsciiString, AsciiString> &p, const StringBase<char> &s)
{
    return Rva0020561C(p, s);
}
