// cl: /O1 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// RVA2CD71 is a five-byte tail jump to the macro map lifetime provider2CCC3.
// Its owner remains unknown. Use the same nocase lookup view as INI.cpp;
// the mapped-record spelling remains address-derived, not an original name.
#include "ascii_string.h"
namespace rts {
template<class T> struct hash {};
template<> struct hash<AsciiString> { unsigned int operator()(const AsciiString &) const; };
template<class T> struct equal_to {};
template<> struct equal_to<AsciiString> { bool operator()(const AsciiString &,const AsciiString &) const; };
}
struct Rva0002C9E7Value { AsciiString m_text; };
#include <hash_map>
typedef _STL::hashtable<_STL::pair<const AsciiString,Rva0002C9E7Value>,AsciiString,rts::hash<AsciiString>,_STL::_Select1st<_STL::pair<const AsciiString,Rva0002C9E7Value> >,rts::equal_to<AsciiString>,_STL::allocator<_STL::pair<const AsciiString,Rva0002C9E7Value> > > IniMacroTableHash;
namespace _STL { template<> IniMacroTableHash::~hashtable(); }
class Rva0002CD71 {
public:
    ~Rva0002CD71();
private:
    IniMacroTableHash m_00;
};
Rva0002CD71::~Rva0002CD71() {}
