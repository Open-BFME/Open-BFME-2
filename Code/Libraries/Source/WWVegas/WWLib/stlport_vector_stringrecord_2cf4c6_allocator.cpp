// cl: /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's shared 20-byte vector allocator at RVA 0x395960.
// Retail keeps the imul; the home TU (stlport_vector_stringrecord_2cf4c6_allocate_copy.cpp)
// strength-reduces it to lea+shl under /O1. /G7 P4 tuning emits the imul
// (probe-proven on the 24-byte sibling at 0x395944), so the allocator lives in
// this shard; flipping the home TU would break its landed /O1 bodies. Called
// by the rowed 2CF4C6/3B3F78/568CE0/SaveMapPreview allocate_and_copy bodies;
// rowed under the 2CF4C6 spelling by caller evidence with the image-wide fold
// documented, sibling 3B3F78/568CE0 pins standing as fold candidates.
class AsciiString { public: AsciiString(const AsciiString &); __forceinline ~AsciiString() { releaseBuffer(); } protected: void releaseBuffer(); private: void *m_data; };
struct BfmeStringRecord002CF4C6 {
    AsciiString text0, text1;
    unsigned int word0, word1;
    unsigned char flag0, flag1;
    BfmeStringRecord002CF4C6();
    BfmeStringRecord002CF4C6(const BfmeStringRecord002CF4C6 &);
};
#include <memory>
template class _STL::allocator<BfmeStringRecord002CF4C6>;
