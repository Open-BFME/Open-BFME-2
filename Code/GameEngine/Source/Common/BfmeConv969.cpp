// Open-BFME5 conversions.

// Retail vtables 0x008E2C10, 0x008E2BCC and 0x008E2BE8 are emitted by
// Y2ScalarDeleters.cpp, InlineDtorDeletingDtors2.cpp and Rva00666BA0Derived.cpp;
// __identifier spells those symbols exactly.
extern "C" char __identifier("??_7Gen007F4D00@@6BGen007F4D00Listener@@@")[];
extern "C" char __identifier("??_7Rva006613E0@@6B@")[];
extern "C" char __identifier("??_7Rva00661350@@6B@")[];

// The base destructor is rowed as ??1Rva00666BA0 (DirtySock/Rva00666BA0Dtor.cpp).
#include "../../../Libraries/Source/DirtySock/Rva00666BA0.h"

class BfmeD969
{
public:
	void bfmeGo969D();

	char *volatile m_bfmeVft;
	char *volatile m_bfmeVft2;
	volatile int m_bfme08;
	volatile int m_bfme0c;
	volatile int m_bfme10;
	volatile int m_bfme14;
};

void BfmeD969::bfmeGo969D()
{
	m_bfmeVft2 = __identifier("??_7Gen007F4D00@@6BGen007F4D00Listener@@@");
	m_bfme08 = 0;
	m_bfme0c = 0;
	m_bfme10 = 0;
	m_bfme14 = 0;
	m_bfmeVft2 = __identifier("??_7Rva006613E0@@6B@");
	m_bfmeVft = __identifier("??_7Rva00661350@@6B@");
	((Rva00666BA0 *)this)->Rva00666BA0::~Rva00666BA0();
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Gen007F4D00@@UAE@XZ=?bfmeGo969D@BfmeD969@@QAEXXZ")
