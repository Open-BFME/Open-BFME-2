// Derived destructor at retail 0x006D6470 (82 bytes), owner unidentified.
//
// Formerly rowed as LadderPreferences::~LadderPreferences on byte evidence
// alone. BFME 2's real LadderPreferences destructor is 0x005DFF7B (its base
// is the recovered UserPreferences and its vtable's write slot is Zero
// Hour's ladder writer); this body's base is 0x006DE350 and its vtable is
// 0x00CEA264, so it keeps an address name. BFME1 near-miss donor:
// lotrbfme.exe 0x000ABB70 (82 bytes) is byte-identical except one immediate:
// BFME1 destroys its ladder map at [esi+0x14], BFME2 at [esi+0x08]
// (near-miss class immediate-only, 98.5% aligned). The vtable, the SEH
// cookie and both call displacements are relocation slots, so they match
// by construction. BFME1's member is LadderPrefMap m_ladders; the BFME2
// member body at 0x0070A840 is opaque (pinned Rva0070A840), as is the base
// at 0x006DE350 (pinned Rva006DE350), so both are declared here and never
// defined: a same-TU definition would capture the call locally instead of
// at the ledger address. The derived destructor itself is empty; the
// compiler emits the vtable store, the member call (EH state 0) and the
// base call (EH state -1) around the SEH registration.

// The scalar deleting destructor emitted here releases through the
// chain-block pool at 0x00E176F4 with the class size, as retail's does.
#include "../../../Libraries/Source/Apt/Rva006D2A60.h"

extern Rva006D2A60 *g_pChainBlockAllocatorF4;   // 0x00E176F4

// The AptValue root view the first-in-link-order vtable copy
// (Rva006D6360Ctor.cpp) declares: its private slot 0 precedes the destructor.
class AptValue
{
public:
    virtual void AddRef();
    virtual void Release();
};
// Retail vtable 0x008EA228 starts with the rowed AptValue::AddRef (0x006DCAC0) and Release.
class BfmeAptValue006DCD20 : public AptValue
{
protected:
    unsigned int m_flags04;
public:
    virtual ~BfmeAptValue006DCD20();
};
struct Rva006DE350 : public BfmeAptValue006DCD20
{
	virtual ~Rva006DE350();
};

struct Rva0070A840
{
	~Rva0070A840();
};

struct Rva006D6470Owner : public Rva006DE350
{
	Rva0070A840 m_ladders; // +0x08: BFME1 keeps this map at +0x14
	char m_rest[0x20 - 0x09]; // to the 0x20 bytes the pool release frees

	virtual ~Rva006D6470Owner();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
};

Rva006D6470Owner::~Rva006D6470Owner()
{
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1S4Base009A1A40@@UAE@XZ=??1Rva006D6470Owner@@UAE@XZ")
