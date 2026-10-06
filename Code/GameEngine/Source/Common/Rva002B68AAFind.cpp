// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva002B68AA@Rva002B68AA@@QAEPAUFindElem002B68AA@@ABVAsciiString@@@Z @0x002B68AA 86B
// Linear find over pointer vector at +0xBC/+0xC0 with key StringBase at +0x10
// via rowed compare 0x000069D6; caller at 0x002B7791.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "ascii_string.h"


struct FindElem002B68AA
{
	char m_pad[0x10];
	AsciiString m_key10;
};

class Rva002B68AA
{
public:
	FindElem002B68AA *rva002B68AA(const AsciiString &name);
private:
	char m_pad[0xBC];
	FindElem002B68AA **m_beginBC;
	FindElem002B68AA **m_endC0;
};

FindElem002B68AA *Rva002B68AA::rva002B68AA(const AsciiString &name)
{
	for (unsigned int i = 0; i < (unsigned int)(m_endC0 - m_beginBC); ++i)
	{
		_ReadWriteBarrier();
		if (((const StringBase<char> *)&m_beginBC[i]->m_key10)->compare(*(const StringBase<char> *)&name) == 0)
			return m_beginBC[i];
	}
	return 0;
}
