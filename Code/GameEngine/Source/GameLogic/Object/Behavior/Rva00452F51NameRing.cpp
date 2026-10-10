// cl: /O1 /G7 /DNDEBUG /MD /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB
// ?rva00452F51@Rva00452F51@@QBEABVAsciiString@@I@Z @0x00452F51 43B
// Evidence: Native452F51..452F7C RET4. Empty path returns independently identified AsciiString::TheEmptyString atVADE0878; nonempty path start8/finishC arithmetic>>2 and unsigned division identify4B name entries. Normal STLport vector<AsciiString> at+8 reproduces native shrink-wrapped ESI save and full43B. Complete owner/method original names unknown; address label retained.
// stlport
#include <vector>
#include "ascii_string.h"
class Rva00452F51 {public:const AsciiString&rva00452F51(unsigned)const;char pad[8];_STL::vector<AsciiString> names;};
const AsciiString&Rva00452F51::rva00452F51(unsigned index)const {if(names.empty())return AsciiString::TheEmptyString;return names[index%names.size()];}
