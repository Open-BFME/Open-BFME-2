// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// Target evidence: 0x005E755E is a 36-byte copy of the 0x001EB382 fetch
// wrapper. It reads TheGameText at VA 0x00DFF0BC, passes its member
// AsciiString label (this+0x0C) to virtual slot +0x38 with a null exists
// pointer, and returns the hidden UnicodeString result pointer. The containing
// class identity remains unproven.
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

class Rva005E755E
{
public:
	UnicodeString rva005e755e();

private:
	unsigned int m_unknown00[3];
	AsciiString m_label;
};

UnicodeString Rva005E755E::rva005e755e()
{
	return TheGameText->fetch(m_label);
}
