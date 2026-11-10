// cl: /DNDEBUG /MD /EHsc
// The two concrete slots of the FXNugget-family base vftable 0x00BDC940
// (tools/vftable_map.py: ~dtor, purecall, 0x001DFF1F, purecall, 0x001DFF5D),
// inherited unchanged by the nugget vftables (EvaEvent 0x00BDD754, Sound
// 0x00BDD768, ...), so no derived table can be defined until both have names.
//
// ?doFXObj@Rva001DFEAABase@@UBEXPBVObject@@0@Z @0x001DFF1F 62B: ZH
// FXNugget::doFXObj's shape - forwards to slot 1 (doFXPos) with the
// primary's position (+0x38) and transform (+0x08), speed 0 and the
// secondary's position; BFME2's doFXPos has no overrideRadius.
// ?rva001DFF5D@Rva001DFEAABase@@UAE_NPAVObject@@0@Z @0x001DFF5D 157B: the
// nugget's fire gate. Primary: filter +0x08 (0x00362437), model-condition
// masks +0x10/+0x5C against Object+0x10C (0x001DFE56), no drawable in state
// 5; secondary: filter +0x0C and masks +0xA8/+0xF4; then +0x140 (2 = any)
// against TheWritableGlobalData+0x138. Identity of the gate unproven, so it
// keeps the address name; the base class keeps its do-not-name token.
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"
class Drawable;
class Player;

#include "../../Include/Common/Rva001DFE56.h"

class Object
{
public:
	const Coord3D *getPosition() const { return &m_cachedPos; }
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
	virtual ~Object();
	Drawable *getDrawable() const;
	int m_04;
	Matrix3D m_transform;		// +0x08
	Coord3D m_cachedPos;		// +0x38
	unsigned char m_pad44[0x10C - 0x44];
	Rva001DFE56 m_modelConditions;	// +0x10C
};

#include "../../Include/GameClient/Drawable.h"

class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
	int m_index;
};

#include "../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;

#include "../../Include/GameClient/Rva001DFEAABase.h"

void Rva001DFEAABase::doFXObj(const Object *primary, const Object *secondary) const
{
	const Coord3D *primaryPos = primary ? primary->getPosition() : 0;
	const Matrix3D *primaryMtx = primary ? primary->getTransformMatrix() : 0;
	const Coord3D *secondaryPos = secondary ? secondary->getPosition() : 0;
	doFXPos(primaryPos, primaryMtx, 0.0f, secondaryPos);
}

bool Rva001DFEAABase::rva001DFF5D(Object *primary, Object *secondary)
{
	if (primary)
	{
		if (!reinterpret_cast<Rva2225E0Filter &>(m_08).accepts(primary, 0))
			return false;
		if (!primary->m_modelConditions.rva001DFE56(&m_10, &m_5C))
			return false;
		Drawable *draw = primary->getDrawable();
		if (draw && draw->m_stealthLook == 5)
			return false;
	}
	if (secondary)
	{
		if (!reinterpret_cast<Rva2225E0Filter &>(m_0C).accepts(secondary, 0))
			return false;
		if (!secondary->m_modelConditions.rva001DFE56(&m_A8, &m_F4))
			return false;
	}
	if (m_140 != 2 && TheWritableGlobalData->m_weather != m_140)
		return false;
	return true;
}
