// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target 0x2CC70 destroys four-byte strings, then frees the vector storage.
// The element cleanup is StringBase<char>::releaseBuffer at 0x36410.
#include <vector>

template <typename T> class StringBase {
    void *m_data;
    void releaseBuffer();
protected:
    ~StringBase() { releaseBuffer(); }
};

class AsciiString : private StringBase<char> {
public:
    ~AsciiString() {}
};

typedef char AsciiStringExtent[sizeof(AsciiString) == 4 ? 1 : -1];
template _STL::vector<AsciiString>::~vector();
