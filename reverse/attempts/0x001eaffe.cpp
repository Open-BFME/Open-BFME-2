// ?rva001EAFFE@Rva001EAFFE@@QAEABVAsciiString@@H@Z
// partial score=0.92 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva001EAFFE@Rva001EAFFE@@QAEAAVAsciiString@@H@Z @0x001EAFFE 37B: bounds-checked AsciiString vector access.
// Evidence: caller 0x001ECDF3; callee none (only AsciiString::TheEmptyString); members +0xC base +0x10 finish stride 4 via size shr 2 plus index jl plus jae; neighbours Rva001EAFC1Assign Rva001EB023Search same flags.
#include "ascii_string.h"

class Rva001EAFFE
{
public:
	const AsciiString &rva001EAFFE(int index);
private:
	unsigned char m_pad[0x0C];
	AsciiString *m_0C;
	AsciiString *m_10;
};

// ?rva001EAFFE@Rva001EAFFE@@QAEABVAsciiString@@H@Z present-unmatched
const AsciiString &Rva001EAFFE::rva001EAFFE(int index)
{
	if (index < 0)
		return AsciiString::TheEmptyString;
	int size = (((int)m_10 - (int)m_0C) >> 2);
	if (index >= size)
		return AsciiString::TheEmptyString;
	return m_0C[index];
}
