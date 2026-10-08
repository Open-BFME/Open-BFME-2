// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport strstream constructors over the existing _strstream.h/_streambuf.h
// definitions. Header donor: Open-BFME-1 9cbfb551fe20dae985f91f2319d8997287b6a705.
// The donor headers establish the stream classes, embedded buffers, and buffer
// operations; the constructor bodies below are reconstructed from BFME2.
// Target boundaries 006028A0/198 and 00602AA0/163 prove the dynamic/constant
// bit settings, minimum allocation of 16, zero/negative length handling, and
// get/put area setup. The seven derived constructor boundaries 00603200,
// 006032C0, 006033A0, 00603470, 006035A0, 00603670, and 00603740 prove null
// base-stream initialization followed by init(&_M_buf). Existing destructor
// rows independently support the class layouts. Every body and callee is
// checked against its own target bytes; no new address pins are needed.
#include <strstream>
#include <cstring>

namespace _STL {

// Retail calls the already-matched char basic_ios::init at 000162F0 rather
// than inlining the header's init into the istream/ostream base construction.
template <> void basic_ios<char, char_traits<char> >::init(
    basic_streambuf<char, char_traits<char> > *);

strstreambuf::strstreambuf(streamsize initial)
{
    _M_alloc_fun = 0;
    _M_free_fun = 0;
    _M_dynamic = true;
    _M_frozen = false;
    _M_constant = false;
    streamsize n = (max)(initial, streamsize(16));
    char *buffer = new char[n];
    if (buffer) {
        setp(buffer, buffer + n);
        setg(buffer, buffer, buffer);
    }
}

strstreambuf::strstreambuf(const char *s, streamsize n)
{
    _M_alloc_fun = 0;
    _M_free_fun = 0;
    _M_dynamic = false;
    _M_frozen = false;
    _M_constant = true;
    if (s) {
        streamsize length = n > 0 ? n : n == 0 ? strlen(s) : 0x7fffffff;
        setg(const_cast<char *>(s), const_cast<char *>(s),
             const_cast<char *>(s) + length);
    }
}

ostrstream::ostrstream()
    : basic_ostream<char, char_traits<char> >(0), _M_buf()
{
    this->init(&_M_buf);
}

ostrstream::ostrstream(char *s, int n, ios_base::openmode mode)
    : basic_ostream<char, char_traits<char> >(0),
      _M_buf(s, n, mode & ios_base::app ? s + strlen(s) : s)
{
    this->init(&_M_buf);
}

istrstream::istrstream(char *s)
    : basic_istream<char, char_traits<char> >(0), _M_buf(s, 0)
{
    this->init(&_M_buf);
}

istrstream::istrstream(const char *s)
    : basic_istream<char, char_traits<char> >(0), _M_buf(s, 0)
{
    this->init(&_M_buf);
}

istrstream::istrstream(char *s, streamsize n)
    : basic_istream<char, char_traits<char> >(0), _M_buf(s, n)
{
    this->init(&_M_buf);
}

istrstream::istrstream(const char *s, streamsize n)
    : basic_istream<char, char_traits<char> >(0), _M_buf(s, n)
{
    this->init(&_M_buf);
}

strstream::strstream()
    : basic_iostream<char, char_traits<char> >(0), _M_buf()
{
    this->init(&_M_buf);
}

}
