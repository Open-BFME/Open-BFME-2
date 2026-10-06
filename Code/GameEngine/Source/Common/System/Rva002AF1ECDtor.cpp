// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1Rva002AF1EC@@QAE@XZ, retail 0x002AF1EC, 74 bytes.
// Non-virtual dtor: vector<AsciiString> at +0x14 (rowed 0x2CC70), raw pointer
// at +8 (free), AsciiString at +0 (releaseBuffer 0x36410). Order: vector,
// free, releaseBuffer via reverse destruction (m_14, m_08, m_00).
#include <vector>

extern "C" void __cdecl free(void *block);

#include "ascii_string.h"


struct FreePtr {
	~FreePtr() { if (m_ptr != 0) free(m_ptr); }
	void *m_ptr;
};

namespace _STL {
	template <> vector<AsciiString>::~vector();
}

class Rva002AF1EC
{
public:
	~Rva002AF1EC();

private:
	AsciiString m_00;
	int m_04;
	FreePtr m_08;
	unsigned char m_pad0C[8];
	_STL::vector<AsciiString> m_14;
};

Rva002AF1EC::~Rva002AF1EC()
{
}
