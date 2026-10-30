// cl: /EHs /MD /Ireference/shims/bfme2_ascii
// ??1Rva0053FB33@@UAE@XZ, retail 0x0053FB33, 66 bytes.
// Virtual dtor: installs vtable 0x008694DC, destroys StringBase<char> at
// +0x18 via rowed releaseBuffer 0x00036410, frees heap pointer at +4 via
// rowed _free 0x00030830, with __EH_prolog frame 0x00629188. Same EH plus
// releaseBuffer shape as Rva003F0C6CDtor (53B, two StringBases). Evidence:
// vtable store plus lea ecx [esi+0x18] plus free branch; ctor sibling at
// 0x0053FAB7 installs same vtable; deleting-dtor candidate at 0x0053FB75
// calls here then operator delete.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

// The canonical frozen StringBase replaces the private copy; its switch makes
// the member dtor reachable and keeps the teardown an out-of-line call to the
// rowed releaseBuffer (0x00036410 narrow, 0x00036E70 wide).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"



// Native20B cleanup guards null before adjusting to the base at +4.
// Sibling constructor53FAB7 calls the16B storage constructor330757 before
// installing this same C694DC vptr; opaque words retain their measured extent.
struct Rva0053FB33Holder
{
	~Rva0053FB33Holder() { if (m_ptr != 0) free(m_ptr); }
	void *m_ptr;
	char m_opaque04[0xC];
};

class Rva0053FB33 : private Rva0053FB33Holder
{
public:
	virtual ~Rva0053FB33();
private:
	char m_pad14[0x18 - 0x14];
	StringBase<char> m_str18;
};

Rva0053FB33::~Rva0053FB33()
{
}
