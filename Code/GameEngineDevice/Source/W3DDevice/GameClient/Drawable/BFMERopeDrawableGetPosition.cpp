// cl: /DNDEBUG /MD /EHsc
// BFME1 donor: reference/open-bfme-1/game/GameEngine/Source/GameClient/BFMERopeDrawableInterpolatedPosition.cpp
// donor revision 10af19f44a89ab7ecc23195bb9a842ceafbc02c9. The retail
// getPosition body carries the same interpolation logic but uses BFME2 member
// offsets; the rebuild helper's target identity remains address-derived.

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

struct BfmeVector3
{
	float x;
	float y;
	float z;
};

class GameEngine
{
private:
	char m_unreconstructed_000[0x3c];

public:
	float m_interpolationFactor;
};

extern GameEngine *TheGameEngine;

extern "C" BfmeVector3 *__stdcall D3DXVec3CatmullRom(
	BfmeVector3 *result,
	const Coord3D *position0,
	const Coord3D *tangent0,
	const Coord3D *position1,
	const Coord3D *tangent1,
	float factor);

class Rva002747F9
{
public:
	void rva002747F9(int force);
};

class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;

private:
	char m_unreconstructed_000[0x38];
	Coord3D m_basePosition;
	char m_unreconstructed_044[0xfc - 0x44];
	void *m_object;
	char m_unreconstructed_100[0x238 - 0x100];
	Coord3D m_interpolatedPosition;
	char m_unreconstructed_244[0x40c - 0x244];
	Coord3D m_position0;
	Coord3D m_tangent0;
	Coord3D m_position1;
	Coord3D m_tangent1;
	char m_unreconstructed_43c[8];
	bool m_interpolationReady;
};

// ?getPosition@BFMERopeDrawable@@QBEPBUCoord3D@@XZ
const Coord3D *BFMERopeDrawable::getPosition() const
{
	if (!m_object)
		return &m_basePosition;

	BFMERopeDrawable *self = const_cast<BFMERopeDrawable *>(this);
	if (!m_interpolationReady)
		reinterpret_cast<Rva002747F9 *>(self)->rva002747F9(0);

	Coord3D interpolated;
	BfmeVector3 result;
	D3DXVec3CatmullRom(
		&result,
		&m_position0,
		&m_tangent0,
		&m_position1,
		&m_tangent1,
		TheGameEngine->m_interpolationFactor);

	interpolated.x = result.x;
	interpolated.y = result.y;
	interpolated.z = result.z;
	self->m_interpolatedPosition = interpolated;
	return &m_interpolatedPosition;
}

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:_D3DXVec3CatmullRom@24=_rva0062AFC8D3DXVec3CatmullRom@24")
