// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// Native checklist constructor688 initializes the custom-render name list at18.
// This default vector<AsciiString> lifetime is a complete19-byte constructor
// and allocator-base relocation twin of ObjectCreationList; no unique-byte gain.
#include "ascii_string.h"
#include <vector>
class Rva00524265 { public: Rva00524265(); ~Rva00524265(); private: _STL::vector<AsciiString> names; };
Rva00524265::Rva00524265() {}
