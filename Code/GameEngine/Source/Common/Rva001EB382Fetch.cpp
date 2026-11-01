// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// Target evidence: 0x001EB382 reads TheGameText at VA 0x00DFF0BC, passes
// this+4 as the label to virtual slot +0x38 with a null exists pointer, and
// returns the hidden UnicodeString result pointer. The +4 AsciiString view is
// supported by the call; the containing class identity and first word remain
// unknown. TheGameText slot ABI follows the matched sibling fetch bodies.
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

class Rva001EB382
{
public:
	UnicodeString rva001eb382();

private:
	unsigned int m_unknown00;
	AsciiString m_label;
};

UnicodeString Rva001EB382::rva001eb382()
{
	return TheGameText->fetch(m_label);
}
