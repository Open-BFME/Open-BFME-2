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

class BfmeCacheBZAMiddleBase
{
public:
	BfmeCacheBZAMiddleBase(BfmeThingBZA *owner) : m_owner(owner) {}
	virtual ~BfmeCacheBZAMiddleBase() {}

	BfmeThingBZA *m_owner;
};

class BfmeCacheBZATrailingBase
{
public:
	BfmeCacheBZATrailingBase() {}
	virtual ~BfmeCacheBZATrailingBase() {}
};

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
