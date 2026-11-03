// cl: /MD /O2 /arch:SSE
// Native 0x006E4480 (98B). The same receiver calls rowed Rva006E34D0::rva006E34D0; retail writes records at +0x7C/+0x8C for IDs 0x1F5/0x1F6.
// The complete caller6CC9F0 copies a sixteen-byte aggregate to this method.
// Its first two words and byte8 feed the native records; word12 is the ID.
// Grouping the parameters correctly preserves this whole98B callee.
struct Rva006CC9F0Input { int first,second; unsigned char flag; char pad09[3]; int eventId; };
#include "Rva006E34D0.h"

void Rva006E34D0::rva006E4480(Rva006CC9F0Input input)
{
	if (input.eventId == 0x1f5)
	{
		m_field7C = input.first;
		m_field80 = input.second;
		m_field84 = input.flag;
	}
	else if (input.eventId == 0x1f6)
	{
		m_field8C = input.first;
		m_field90 = input.second;
		m_field94 = input.flag;
	}
	int packed = input.eventId;
	packed <<= 15;
	packed |= input.flag;
	packed <<= 2;
	packed |= 1;
	rva006E34D0(packed);
}
