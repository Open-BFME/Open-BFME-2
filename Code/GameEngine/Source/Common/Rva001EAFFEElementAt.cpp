// ?rva001EAFFE@Rva001EAFFE@@QAEAAVAsciiString@@H@Z
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// Retail 0x001EAFFE, 37 bytes: bounds-checked AsciiString element access of
// the array whose begin/end sit at +0xC/+0x10; out of range returns
// AsciiString::TheEmptyString (retail 0x009E0878). Owner address-derived.
#include "ascii_string.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva001EAFFE
{
public:
	AsciiString &rva001EAFFE(int index);
	char m_pad[0x0C];
	AsciiString *m_begin;
	AsciiString *m_end;
};

AsciiString &Rva001EAFFE::rva001EAFFE(int index)
{
	if (index >= 0 && (unsigned int)index < (unsigned int)(m_end - m_begin))
	{
		_ReadWriteBarrier();
		return m_begin[index];
	}
	return (AsciiString &)AsciiString::TheEmptyString;
}
