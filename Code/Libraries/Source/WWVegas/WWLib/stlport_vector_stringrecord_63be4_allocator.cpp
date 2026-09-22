// cl: /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's shared 36-byte vector allocator at RVA 0x5DFB2C.
// Retail keeps the imul; the home TU (stlport_vector_stringrecord_allocate_copy.cpp)
// strength-reduces it to lea+shl under /O1. /G7 P4 tuning emits the imul
// (probe-proven on the 24-byte sibling at 0x395944), so the allocator lives in
// this shard; flipping the home TU would break its landed /O1 bodies. Called
// by the rowed 63BE4 allocate_and_copy at 0x64405; rowed under that spelling
// with the image-wide fold documented.
class AsciiString { public: AsciiString(const AsciiString &); __forceinline ~AsciiString() { releaseBuffer(); } protected: void releaseBuffer(); private: void *m_data; };
struct BfmeStringRecord00063BE4 {
    unsigned int word0, word1, word2, word3, word4, word5, word6;
    AsciiString text;
    unsigned char tail0, tail1;
    BfmeStringRecord00063BE4();
    BfmeStringRecord00063BE4(const BfmeStringRecord00063BE4 &);
};
#include <memory>
template class _STL::allocator<BfmeStringRecord00063BE4>;
