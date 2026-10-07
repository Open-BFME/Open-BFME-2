// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva00360F55@@QAE@XZ, retail 0x00360FDB (128B): the implicit destructor of
// the 0x94-byte ObjectFilter record whose constructor is Rva00360F55Ctor.cpp.
// Read from this body: the first two of its six vectors hold AsciiStrings
// (destroyed through the rowed vector<AsciiString> destructor 0x0002CC70), the
// other four hold plain elements whose storage is freed directly; the two
// 0x1C-byte members and the trailing words need no teardown. Element types of
// the plain vectors stay size-only, as in the constructor's unit. /EHs, not
// /EHsc: STLport frees through a C++-linkage free that may throw, which is what
// gives retail one unwind state per vector.

#include <vector>

#include "ascii_string.h"

struct Rva00360F55Pod
{
	int m_value;
};

class Rva00360F55
{
public:
	~Rva00360F55();

private:
	_STL::vector<AsciiString> m_00;
	_STL::vector<AsciiString> m_0C;
	_STL::vector<Rva00360F55Pod> m_18;
	_STL::vector<Rva00360F55Pod> m_24;
	_STL::vector<Rva00360F55Pod> m_30;
	_STL::vector<Rva00360F55Pod> m_3C;
	unsigned char m_48[0x94 - 0x48];
};

Rva00360F55::~Rva00360F55()
{
}
