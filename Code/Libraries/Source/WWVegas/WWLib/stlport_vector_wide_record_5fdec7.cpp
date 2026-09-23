// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport donor: reference/open-bfme-1/vendor/stlport/stl/_vector.h.
// Target assignment 0x5FDEC7 copies words +0/+4 and sets the wide string at +8.
// The destroy loop confirms a 12-byte stride; application identity is unknown.
template<class T> class StringBase {
    void *m_data;
    void releaseBuffer();
public:
    void set(const StringBase<T> &other);
    StringBase(const StringBase<T> &other);
protected:
    __forceinline ~StringBase() { releaseBuffer(); }
};
class UnicodeString : private StringBase<unsigned short> {
public:
    __declspec(nothrow) __forceinline UnicodeString &operator=(const UnicodeString &other) {
        StringBase<unsigned short>::set(other);
        return *this;
    }
    __forceinline ~UnicodeString() {}
};
struct BfmeContainerRecord005FDEC7 {
    unsigned int word0;
    unsigned int word4;
    UnicodeString text08;
    BfmeContainerRecord005FDEC7();
    __declspec(nothrow) BfmeContainerRecord005FDEC7 &operator=(const BfmeContainerRecord005FDEC7 &other);
};
__declspec(nothrow) BfmeContainerRecord005FDEC7 &BfmeContainerRecord005FDEC7::operator=(const BfmeContainerRecord005FDEC7 &other) {
    word0 = other.word0;
    word4 = other.word4;
    text08 = other.text08;
    return *this;
}
#include <vector>
template class _STL::vector<BfmeContainerRecord005FDEC7, _STL::allocator<BfmeContainerRecord005FDEC7> >;
