// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE /GX
//
// ??0RayEffectFXNugget@@QAE@XZ 123B @0x1E01B2: no-arg ctor called by
// RayEffectFXNugget::parse (0x001E13A5) for the RayEffect FXList keyword;
// class name from BFME1. Member names and offsets from the retail FieldParse
// table 0x00BDCB58 (Name@0x148, PrimaryOffset@0x14C, SecondaryOffset@0x158)
// and the BFME1 donor (FXNugget::m_nuggetType = 2, template clear, offsets
// zeroed). Base 0x001DFEAA is a shared FXNugget-family base ctor (16
// ctor-start callers with this undisplaced); pinned opaquely, do not name.

#include "../../Include/GameClient/Rva001DFEAABase.h"

#include "ascii_string.h"

#include "../../../Libraries/Include/Lib/Coord3D.h"

struct BEXPBUCoord3D;
class Matrix3D;
class RayEffectFXNugget : public Rva001DFEAABase
{
public:
	RayEffectFXNugget();
	// Compiler-generated destruction (members, then the rowed base dtor), the
	// body retail's vtable slot 0 reaches.
	virtual ~RayEffectFXNugget() {}
private:
	AsciiString m_templateName; // +0x148
	Coord3D m_primaryOffset; // +0x14C
	Coord3D m_secondaryOffset; // +0x158
public:
	virtual void doFXPos(const struct Coord3D *, const class Matrix3D *, float, const struct Coord3D *) const;
};

// ??0RayEffectFXNugget@@QAE@XZ
inline RayEffectFXNugget::RayEffectFXNugget()
{
	m_templateName.clear();
	m_primaryOffset.x = m_primaryOffset.y = m_primaryOffset.z = 0.0f;
	m_secondaryOffset.x = m_secondaryOffset.y = m_secondaryOffset.z = 0.0f;
	m_nuggetType = 2;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeRayEffectFXNuggetInlineAnchor@@YAXPAVRayEffectFXNugget@@@Z absent-from-retail
void _bfmeRayEffectFXNuggetInlineAnchor(RayEffectFXNugget *rayEffectFXNugget)
{
    rayEffectFXNugget->RayEffectFXNugget::RayEffectFXNugget();
}
#pragma inline_depth()
