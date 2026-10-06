// cl: /Ireference/shims/bfme2_ascii /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??4AudioEventRTS@@QAEAAV0@ABV0@@Z @0x0009A41B (93B).
// BFME2 AudioEventRTS copy-assign matching the ctor TU layout: two
// AsciiStrings then one int six floats and three bytes. Donor is BFME1
// AudioEventRTS::operator= (AudioEventRTS.cpp:273) trimmed to BFME2 members.
// Evidence: caller 0x9A8D3 copies into a locally constructed AudioEventRTS;
// AsciiString op= pin @0x366F0; ctor layout @0x79514.

typedef int Int;

#include "ascii_string.h"

class AudioEventRTS
{
public:
	AudioEventRTS &operator=(const AudioEventRTS &right);
private:
	AsciiString m_first;
	AsciiString m_second;
	Int m_unknown8;
	float m_floatC;
	float m_float10;
	float m_float14;
	float m_float18;
	float m_float1C;
	float m_float20;
	unsigned char m_byte24;
	unsigned char m_byte25;
	unsigned char m_byte26;
};

AudioEventRTS &AudioEventRTS::operator=(const AudioEventRTS &right)
{
	m_first = right.m_first;
	m_second = right.m_second;
	m_unknown8 = right.m_unknown8;
	m_floatC = right.m_floatC;
	m_float10 = right.m_float10;
	m_float14 = right.m_float14;
	m_float18 = right.m_float18;
	m_float1C = right.m_float1C;
	m_float20 = right.m_float20;
	m_byte24 = right.m_byte24;
	m_byte25 = right.m_byte25;
	m_byte26 = right.m_byte26;
	return *this;
}
