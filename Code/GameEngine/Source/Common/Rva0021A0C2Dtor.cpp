// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0021A0C2@@QAE@XZ @0x0021A0C2 (68B):
// Honest-address destructor: three narrow StringBase members at +0/+4/+8,
// each released via rowed StringBase<D>::releaseBuffer at 0x36410.
// Evidence: retail calls releaseBuffer thrice (esi+8 then esi+4 then esi),
// EH prolog with funclet, caller 0x0021AC81 is 28B deleting dtor shape.
// No donor; layout proven by the three immediates.

// The canonical AsciiString owns the same one-pointer narrow string
// and calls its retail releaseBuffer directly. This removes the private
// StringBase view and its linker alias while preserving all three releases.
#include "ascii_string.h"

class Rva0021A0C2
{
public:
	~Rva0021A0C2();

private:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
};

Rva0021A0C2::~Rva0021A0C2()
{
}
