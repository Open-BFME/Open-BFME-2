// cl: /Ireference/shims/bfme2_ascii /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00288BBA@@QAE@ABVAsciiString@@@Z retail 0x00288BBA 58 bytes.
// Converting ctor over vector<BfmeE16> plus AsciiString at +0x0C via rowed StringBase copy.
// Evidence: rowed _Vector_base<BfmeE16> 0x00211E58 plus rowed StringBase copy 0x000365F0;
// callers at 0x002892AB and 0x00289B35; unblocks 0x00289ABD.
#include "ascii_string.h"
#include <vector>
struct BfmeE16 { float x, y, z, w; };
class Rva00288BBA {
public:
_STL::vector<BfmeE16> m_vec;
AsciiString m_str;
Rva00288BBA(const AsciiString &s);
};
Rva00288BBA::Rva00288BBA(const AsciiString &s) : m_str(s) {}
