// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1BfmeStringRecord002199C8@@QAE@XZ @0x0021A0C2 (68B):
// The16B record is independently proven by ctor21997A, copy2199C8
// and vector stride16. Reconcile this cleanup owner with that neutral
// record name instead of keeping a second destructor spelling.
// Destructor: three narrow StringBase members at +0/+4/+8,
// each released via rowed StringBase<D>::releaseBuffer at 0x36410.
// Evidence: retail calls releaseBuffer thrice (esi+8 then esi+4 then esi),
// EH prolog with funclet, caller 0x0021AC81 is 28B deleting dtor shape.
// No donor; layout proven by the three immediates.

// The canonical AsciiString owns the same one-pointer narrow string
// and calls its retail releaseBuffer directly. This removes the private
// StringBase view and its linker alias while preserving all three releases.
#include "ascii_string.h"

struct BfmeStringRecord002199C8
{
public:
	~BfmeStringRecord002199C8();

private:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	unsigned int m_word0C;
};

BfmeStringRecord002199C8::~BfmeStringRecord002199C8()
{
}
