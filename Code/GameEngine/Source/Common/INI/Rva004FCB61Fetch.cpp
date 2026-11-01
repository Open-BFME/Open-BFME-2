// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// Target evidence: 0x004FCB61, 0x004FCB85 and 0x004FCBA9 are 36-byte copies
// of the 0x001EB382 fetch wrapper. Each reads TheGameText at VA 0x00DFF0BC,
// passes its member AsciiString label (this+0x10, +0x14 and +0x1C) to virtual
// slot +0x38 with a null exists pointer, and returns the hidden UnicodeString
// result pointer. The containing class identities remain unproven.
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

class Rva004FCB61
{
public:
	UnicodeString rva004fcb61();

private:
	unsigned int m_unknown00[4];
	AsciiString m_label;
};

UnicodeString Rva004FCB61::rva004fcb61()
{
	return TheGameText->fetch(m_label);
}

class Rva004FCB85
{
public:
	UnicodeString rva004fcb85();

private:
	unsigned int m_unknown00[5];
	AsciiString m_label;
};

UnicodeString Rva004FCB85::rva004fcb85()
{
	return TheGameText->fetch(m_label);
}

class Rva004FCBA9
{
public:
	UnicodeString rva004fcba9();

private:
	unsigned int m_unknown00[7];
	AsciiString m_label;
};

UnicodeString Rva004FCBA9::rva004fcba9()
{
	return TheGameText->fetch(m_label);
}
