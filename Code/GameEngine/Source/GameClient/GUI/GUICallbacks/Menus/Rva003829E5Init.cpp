// cl: /DNDEBUG /MD
// ??0Rva003829E5@@QAE@PAXABUAsciiUnicodePair@@@Z 0x003829E5 29B
// Thiscall init: m0 = *a then placement copy-construct pair at +4.
// Evidence: calls 0x00382444 AsciiUnicodePair copy ctor; caller 0x00385EA0 passes (tmp, eax, ebx).
#include <new>

struct AsciiUnicodePair
{
	AsciiUnicodePair(const AsciiUnicodePair& other);
};

class Rva003829E5
{
	int m0;
	AsciiUnicodePair m4;
public:
	Rva003829E5(void* a, const AsciiUnicodePair& b);
	Rva003829E5(const Rva003829E5& other);
};

Rva003829E5::Rva003829E5(void* a, const AsciiUnicodePair& b)
	: m0(*(int*)a)
	, m4(b)
{
}

Rva003829E5::Rva003829E5(const Rva003829E5& other)
	: m0(other.m0)
	, m4(other.m4)
{
}
