// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// B4926..B493B returns first AsciiString from vector or canonical empty string.
// Native caller BEE25 passes selected 64-byte animation record beginning.
// Original record/method name unproven: retain address-derived owner.
#include <vector>
#include "ascii_string.h"
class Rva000B4926 { std::vector<AsciiString> names;public:const AsciiString &rva000B4926() const;};
const AsciiString &Rva000B4926::rva000B4926()const { if(names.size()!=0)return names[0];return AsciiString::TheEmptyString; }
