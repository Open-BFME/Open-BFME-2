// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

#include <sstream>
#include <cstddef>

template <typename T>
struct BfmeStreambufHelper : public _STL::basic_streambuf<char, _STL::char_traits<char> > {
    void emit(char *b, char *n, char *e, int k) {
        setg(b, n, e);
        setp(b, e);
        pbump(k);
    }
};

template struct BfmeStreambufHelper<int>;

extern void (BfmeStreambufHelper<int>::*const g_streambufEmit)(char *, char *, char *, int);
void (BfmeStreambufHelper<int>::*const g_streambufEmit)(char *, char *, char *, int) = &BfmeStreambufHelper<int>::emit;

template <typename T>
void bfmeEmitFpos(_STL::fpos<int> &f, long off, int c) {
    f += off;
    f = f - off;
    (void)_STL::char_traits<char>::not_eof(c);
}
template void bfmeEmitFpos<int>(_STL::fpos<int> &, long, int);
