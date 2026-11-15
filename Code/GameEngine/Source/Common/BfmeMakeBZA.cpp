// ?bfmeMakeBZA@@YAPAVBfmeCacheBZA@@PAVBfmeThingBZA@@@Z, retail 0x006612C0, 59 bytes.
// Dedicated TU (bfmeGetBZA in BfmeConv556.cpp calls this through the pin;
// a same-TU definition would capture its REL32 locally).
//
// Bfme zone-cache factory: allocates the 0x70-byte cache through the shared
// allocator at 0x0065D010 (the matched Gen007F0130 operator new provider) and constructs
// the multi-inheritance cache in place. Retail's store order proves the
// layout: the owner-carrying middle base (+0x04 vptr, +0x08 owner) and the
// trailing base (+0x0C vptr) install first, then the derived reinstalls all
// three vptrs (+0x00 primary, +0x04 folded secondary, +0x0C tertiary).
#include <new>

#include "../../Include/GameNetwork/Gen007F0130.h"

class BfmeThingBZA;

class BfmeCacheBZALeadingBase
{
public:
	BfmeCacheBZALeadingBase() {}
	virtual ~BfmeCacheBZALeadingBase() {}
};

// Q3MakeBaseB: definition as Code/GameEngine/Source/Common/Q3MakeDerivedFamily.cpp holds it
class Q3MakeBaseB
{
public:
	// No family member overrides this slot: every +4 vftable (retail 0x008E0FB4)
	// holds 0x007244B0, `mov eax,[ecx+4]; ret`, the payload getter that ICF
	// folded with CullSystemClass::Get_First_Collected_Object_Internal.
	virtual void *secondary() { return m_payload; }
	void *m_payload;
	Q3MakeBaseB( void *payload ) { m_payload = payload; }
};
typedef Q3MakeBaseB BfmeCacheBZAMiddleBase;

// Pure destructor: the trailing base's one-slot table 0x00C1C780, which the
// constructor installs at +0x0C first, holds __purecall.
class BfmeCacheBZATrailingBase
{
public:
	BfmeCacheBZATrailingBase() {}
	virtual ~BfmeCacheBZATrailingBase() = 0;
};
inline BfmeCacheBZATrailingBase::~BfmeCacheBZATrailingBase() {}

class BfmeCacheBZA
	: public BfmeCacheBZALeadingBase
	, public BfmeCacheBZAMiddleBase
	, public BfmeCacheBZATrailingBase
{
public:
	BfmeCacheBZA(BfmeThingBZA *owner) : BfmeCacheBZAMiddleBase(owner) {}
	virtual ~BfmeCacheBZA() {}

private:
	char m_tail[0x70 - 0x10];
};

// ?bfmeMakeBZA@@YAPAVBfmeCacheBZA@@PAVBfmeThingBZA@@@Z
BfmeCacheBZA *bfmeMakeBZA(BfmeThingBZA *owner)
{
	void *rawMemory = Gen007F0130::operator new(0x70);
	if (rawMemory != 0)
		return new (rawMemory) BfmeCacheBZA(owner);
	return 0;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfme5MakeObj70@@YAPAUBfme5Obj70@@H@Z=?bfmeMakeBZA@@YAPAVBfmeCacheBZA@@PAVBfmeThingBZA@@@Z")
