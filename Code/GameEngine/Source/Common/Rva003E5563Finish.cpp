// ??0Rva003E5563@@QAE@XZ
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// retail 0x003E5563, 36 bytes.
// Evidence: default constructor of an address-derived class. It zeroes the int
// at +0x10, the four floats at +0..+0xc, then stores the 0x7ffffffe sentinel at
// +0x14. The `mov eax, ecx` prologue and eax-based stores are MSVC's constructor
// shape -- a plain void method with the same body compiles to 34 bytes -- and
// the sole caller 0x3E60BD (`lea ecx,[ebp-0x18]; call`) constructs a local.
// The banked attempt named this void; the constructor signature is what the
// bytes prove.

#include "../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef float Real;

class Rva003E5563
{
public:
	// Retail calls this out of line from 0x003E60BD, after the body in address order.
	__declspec(noinline) Rva003E5563();

	Coord3D m_pos;				// +0x00
	Real m_distSqr;				// +0x0C
	Int m_count;				// +0x10
	Int m_max;				// +0x14
};

Rva003E5563::Rva003E5563()
{
	m_count = 0;
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_pos.z = 0.0f;
	m_distSqr = 0.0f;
	m_max = 0x7ffffffe;
}
