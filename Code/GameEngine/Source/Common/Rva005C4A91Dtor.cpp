// cl: /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// Native005C4A91..005C4ACD (60B): same verified Rva004FA830 base
// vptr C633A0 after vector cleanup; member vector<AsciiString> at+C calls
// complete63B row2CC70. Original derived class name/word8 meaning unknown.
// Body and sibling004FADB8 prove the destructor pattern; this is not a
// no-argument vector push_back candidate as the structural queue suggests.
#include "ascii_string.h"
#include <vector>
class Rva004FA830 {
public: virtual ~Rva004FA830();
private: AsciiString m_s;
};
inline Rva004FA830::~Rva004FA830() {}
class __declspec(novtable) Rva005C4A91:public Rva004FA830 {
public: virtual ~Rva005C4A91(); void *rva005C4A75(unsigned int);
private: unsigned int unknown08; _STL::vector<AsciiString> member0C;
};
Rva005C4A91::~Rva005C4A91() {}

// Native scalar deleting wrapper005C4A75..005C4A91: invoke the verified
// destructor, delete storage when flags bit0 is set, and return this pointer.
// The ordinary opaque member spelling avoids asserting a compiler symbol
// that this focused novtable view does not emit.
void *Rva005C4A91::rva005C4A75(unsigned int flags) {
 this->Rva005C4A91::~Rva005C4A91();
 if (flags&1) operator delete(this);
 return this;
}
