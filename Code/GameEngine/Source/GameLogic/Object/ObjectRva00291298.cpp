// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?rva00291298@Object@@QAEXVAsciiString@@H@Z @0x00291298 68B
// Object AsciiString member at +0x494 plus int at +0x498 with EH copy.
// Evidence: rowed set 0x000366F0 plus releaseBuffer 0x00036410 plus EH_prolog 0x00629188;
// ret 8 two args; caller 0x004F4B08; prev ObjectRva00290FBB.
#include "ascii_string.h"

class Object
{
public:
	void rva00291298(AsciiString a1, int a2);
private:
	char m_pad[0x494];
	AsciiString m_str494;
	int m_int498;
};

void Object::rva00291298(AsciiString a1, int a2)
{
	AsciiString *pm = &m_str494;
	const AsciiString *pa = &a1;
	((StringBase<char> *)pm)->set(*(const StringBase<char> *)pa);
	m_int498 = a2;
}
