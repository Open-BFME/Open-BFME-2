// cl: /EHsc /MD /Ireference/shims/bfme2_ascii
//
// ??1Rva000B7539@@QAE@XZ retail 0x000B7539 68 bytes. Non-virtual dtor with
// EH destroying three StringBase char at +0 +4 +8 via rowed releaseBuffer.
// Evidence is triple lea plus EH states plus caller Unwind plus neighbour
// StringRecordCopy flags.

// The canonical frozen StringBase replaces the private copy; its switch makes
// the member dtor reachable and keeps the teardown an out-of-line call to the
// rowed releaseBuffer (0x00036410 narrow, 0x00036E70 wide).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"



class Rva000B7539
{
public:
	~Rva000B7539();
private:
	StringBase<char> m_00;
	StringBase<char> m_04;
	StringBase<char> m_08;
};

Rva000B7539::~Rva000B7539()
{
}
