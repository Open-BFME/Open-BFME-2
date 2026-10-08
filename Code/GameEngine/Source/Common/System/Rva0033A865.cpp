// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
#include "ascii_string.h"

// ?rva0033A865@Rva0033A865@@QAEXXZ @0x0033A865 35B.
// Record-piece init: memset +0/4, set AsciiString at +4 from TheEmptyString,
// zero +8. Evidence: retail calls memset 0x6291ae with (this,0,4), then
// StringBase<char>::set 0x366F0 on +4 with AsciiString::TheEmptyString
// 0x9E0878, then ANDs +8 to 0; unblocks 0x0033B0EF MyRecord ctor; LINK BONUS
// via 0x0033B0EF. Layout {4, string, 4} matches MyRecord/BfmeContainerRecord.
extern "C" void *memset(void *dst, int val, unsigned int n);

class Rva0033A865
{
public:
	void rva0033A865();
private:
	int m00;
	AsciiString m04;
	int m08;
};

void Rva0033A865::rva0033A865()
{
	memset(this, 0, 4);
	m04.setCopyInline(AsciiString::TheEmptyString);
	m08 = 0;
}
