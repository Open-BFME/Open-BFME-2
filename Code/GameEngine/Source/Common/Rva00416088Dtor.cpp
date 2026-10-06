// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ??1Rva00416088@@QAE@XZ @0x00416088 (54B): string record dtor.
// Releases AsciiStrings at +8/+0xC via rowed releaseBuffer at 0x00036410
// (+0xC first with EH state 0 then +8). Ints at +0/+4 trivial. Same shape
// as BfmeStringRecord family in StringRecordInlineCopyBFME2. Callers at
// 0x00417786 0x0051748B 0x0059FD1F 0x005A5B20 0x005AE872. Prev _Construct
// next list _M_create_node.
#include "ascii_string.h"

struct Rva00416088
{
	unsigned int m_00;
	unsigned int m_04;
	AsciiString m_08;
	AsciiString m_0C;
	~Rva00416088();
};

Rva00416088::~Rva00416088()
{
}
