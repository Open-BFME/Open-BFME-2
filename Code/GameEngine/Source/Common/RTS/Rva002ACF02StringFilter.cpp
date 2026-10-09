// cl: /O1 /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// Native2ACF02..2ACF5179B and WBc234F0165B prove this string-list filter.
// Target fields: twelve-byte vector14 with four-byte AsciiString elements;
// configured float20; empty name or list returns that float; absent name0.
// Player.cpp production modifiers supply a subsystem lead only; neither the
// original record type nor its original method name is established.
// Actual STLport vector methods and separate early cases reproduce native
// loop entry and its fresh start-pointer load. No private STL observer view.
#include "ascii_string.h"
#include <vector>
class Rva002ACF02 {
public: float rva002ACF02(const AsciiString &);
private: char unknown[0x14]; _STL::vector<AsciiString> names; float value;
};
float Rva002ACF02::rva002ACF02(const AsciiString &name) {
 if(name==AsciiString::TheEmptyString) return value;
 if(names.empty()) return value;
 for(_STL::vector<AsciiString>::const_iterator it=names.begin();it!=names.end();++it)
  if(*it==name) return value;
 return 0.0f;
}
