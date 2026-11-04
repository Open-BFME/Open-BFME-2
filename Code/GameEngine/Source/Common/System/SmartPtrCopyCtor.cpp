// cl: /DNDEBUG /MD
//
// ??0RvaSmartPtr12@@QAE@ABV0@@Z, retail 0x0004CC19 (36 bytes).
// ??4RvaSmartPtr12@@QAEAAV0@ABV0@@Z, retail 0x0004CC3D (44 bytes).
//
// Frameless copy over the 12-byte reference-counted smart pointer at +0x15C
// of Rva003FDA90SmartField (see SmartPtrRvoGetter.cpp, which carries the
// rowed RVO getter): copy the raw pointer, attach through the intrusive-list
// helper at 0x4CB9A when non-null, otherwise zero the +4/+8 pads. Lives in
// its own shard because the getter TU builds with /Oy- (framed) while this
// body is frameless.
// Assignment over the same 12-byte handle: self-check, conditional release
// via the rowed BfmeParticleSystemHandle dtor at 0x4CBC0, raw copy, then
// conditional attach via 0x4CB9A. Callers include 0x4CCE9 0x4D064 0xC7DC2.

#include "../../../Include/GameClient/BfmeParticleSystemHandle.h"

#include "../../../Include/Common/RvaSmartPtr12.h"

RvaSmartPtr12::RvaSmartPtr12(void *ptr) throw()
{
	field00 = ptr;
	if (field00 != 0)
		attach();
	else
	{
		field08 = 0;
		field04 = 0;
	}
}

RvaSmartPtr12::RvaSmartPtr12(const RvaSmartPtr12 &that) throw()
{
	field00 = that.field00;
	if (field00 != 0)
		attach();
	else
	{
		field08 = 0;
		field04 = 0;
	}
}

RvaSmartPtr12 &RvaSmartPtr12::operator=(const RvaSmartPtr12 &that) throw()
{
	if (this != &that)
	{
		if (field00 != 0)
			rva0004CBC0();
		field00 = that.field00;
		if (field00 != 0)
			attach();
	}
	return *this;
}
