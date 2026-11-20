// cl: /MD
// Each destructor rowed in another unit is only declared here: the inline
// constructor references the vtable, which brings the compiler's deleting
// destructor into this unit without a second definition of the destructor;
// its int tag keeps it from spelling a real default constructor.
// ??_GRva006FBA10@@UAEPAXI@Z, retail 0x006FB9E0, 35 bytes.
// Scalar deleting destructor for Rva006FBA10 (vtable 0x008ED844, slot 14
// offset 0x38 per tf.py vslot). Calls the rowed complete dtor at 0x006FBA10
// (11B vptr store + tail-jmp to the base at 0x006DE350, now the rowed
// ??1AptValue@@MAE@XZ rather than a pin), then sized release
// through the pinned pool deallocator 0x006DB270 with the pool object at
// 0x00E176E8 and class size 0xC. Same sized-pool-free recipe as the sibling
// ??_GRva006FB9B00 at 0x006FB980; the dtor stays empty so the local ??1 copy
// remains 11B.

// Rva006FBA10 is an AptValue (retail table 0x008ED844 carries AptValue's own
// fifteen slots); Rva006DE350Derived.cpp carries the same declaration and the
// two overrides. Both units must agree on the base or the two ??_G copies
// diverge.
#include "../../../Libraries/Source/Apt/AptValue.h"

// The protected base constructor takes this enum, which the tree defines per
// TU (AptScriptFunction.h precedent). Retail's constructor view at 0x006FB9C0
// passes type 8.
enum AptVirtualFunctionTable_Indices { AptVFT_Rva006FBA10 = 8 };

#include "../../Include/Common/Rva006DB270.h"

extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8

class Rva006FBA10 : public AptValue
{
public:
	explicit Rva006FBA10(int) : AptValue(AptVFT_Rva006FBA10) {}
	virtual ~Rva006FBA10();
	virtual bool IsGarbageCollected() const;
	virtual void RegisterReferences() const;
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
	char m_pad[4]; // AptValue is 8 bytes: +0x08..0x0B keeps sizeof 0xC
};

Rva006FBA10 *famgenNew_Rva006FBA10() { return new Rva006FBA10(0); }

void deleteRva006FBA10(Rva006FBA10 *p)
{
	delete p;
}
