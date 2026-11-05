// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?rva0006B76C@BaseHeightMapRenderObjClass@@QAEXPBVRva0055A88BDwordField@@VAsciiString@@@Z @0x0006B76C 83B
// Wrapper over 0x000E5EE5: loads Rva000E5EE5* from this+0x3860 and forwards
// (id, by-value AsciiString name) if non-null. Same shape as sibling 0x0006B7BF
// (Rva0006B7BFMethod.cpp) but callee takes the name by value so retail emits
// the copy-ctor call. Shape-lever order: StringBase-direct by-value copy
// transposes mov ecx esp and mov ebp-0x10 esp on every flag; AsciiString with
// inline forwarding copy/dtor to the base restores retail order. Row 0x000E5EE5
// spells the callee with StringBase but the bytes use AsciiString so this TU
// declares the AsciiString spelling with a twin pin; same 4B by-value slot.
// Callers at 0x000CF1EE 0x000CF30A. Scope table shared with sibling at 0x0075E7A1.
#include "ascii_string.h"


class Rva0055A88BDwordField;

class Rva000E5EE5
{
public:
	void rva000E5EE5(const Rva0055A88BDwordField *idSrc, AsciiString name);
};

#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h"

// Use the canonical RefCountClass instead of the donor refcount.h.
#define REFCOUNT_H

#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h"

void BaseHeightMapRenderObjClass::rva0006B76C(const Rva0055A88BDwordField *id, AsciiString name)
{
	if (field3860 != 0)
		static_cast<Rva000E5EE5 *>(field3860)->rva000E5EE5(id, name);
}
