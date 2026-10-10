// cl: /O1 /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Target 0x0023DC8E (64B) calls StringBase<char>::isEmpty at 0x00001E2F,
// tests the byte at TheWritableGlobalData+0x9AD, then writes byte +0x72 and either assigns
// or destroys the AsciiString-shaped field at +0x74. The offsets and callees
// are target evidence; this address-derived owner and operation remain
// unresolved.
#include "ascii_string.h"

class GlobalData;
extern GlobalData *TheWritableGlobalData;

class Rva0023DC8EOwner
{
public:
	void rva0023DC8E(const AsciiString &value);

private:
	char m_unknown00[0x72];
	unsigned char m_flag;
	char m_unknown73;
	AsciiString m_value;
};

void Rva0023DC8EOwner::rva0023DC8E(const AsciiString &value)
{
	const StringBase<char> &stringBase = *(const StringBase<char> *)&value;
	if (!stringBase.isEmpty() && ((unsigned char *)TheWritableGlobalData)[0x9AD] == 0)
	{
		m_flag = 1;
		m_value = value;
	}
	else
	{
		m_flag = 0;
		m_value.~AsciiString();
	}
}
