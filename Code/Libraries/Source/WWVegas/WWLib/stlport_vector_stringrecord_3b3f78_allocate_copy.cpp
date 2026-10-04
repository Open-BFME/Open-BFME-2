// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /G7
// stlport
// BFME2's 20-byte BfmeStringRecord003B3F78 vector allocation/copy helper at RVA 0x3B469A.
class AsciiString { public: AsciiString(const AsciiString &); __forceinline ~AsciiString(); protected: void releaseBuffer(); private: void *m_data; };
struct BfmeStringRecord003B3F78 {
    unsigned int word0, word1;
    AsciiString text;
    unsigned char flag;
    unsigned short short0;
    unsigned int word2;
    BfmeStringRecord003B3F78();
    BfmeStringRecord003B3F78(const BfmeStringRecord003B3F78 &o);
};
#include <memory>
template void _STL::_Construct<BfmeStringRecord003B3F78,BfmeStringRecord003B3F78>(BfmeStringRecord003B3F78*,const BfmeStringRecord003B3F78&);
#include <vector>
template class _STL::vector<BfmeStringRecord003B3F78, _STL::allocator<BfmeStringRecord003B3F78> >;
