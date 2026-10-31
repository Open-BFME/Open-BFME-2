// cl: /DNDEBUG /MD
// ?getVelocity@CylindricalEmissionVelocityModule@FXParticleSystem@@UAE?AUCoord3D@2@HH@Z
// retail 0x0055EB84, 118 bytes.
//
// Ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameClient/System/FXParticleSystem/CylindricalEmissionVelocityModuleSample.cpp
// (reference/open-bfme-1 @ 6583b3c1). Compiled at /O1, the donor body is a
// unique masked placement on unclaimed .text. Target facts: the two random
// variables at +0x1C and +0x28 go through the rowed
// GameClientRandomVariable::getValue (0x002341A1). The angle comes from the
// rowed GetGameClientRandomValueReal (0x00234111) with BFME 2's own source
// path literal and line 59. cos and sin are the CRT imports. The donor's
// name and layout are carried, not independently re-derived.

// Retail keeps the CRT float wrappers from other units: import them here so
// this unit inlines them without emitting its own competing out-of-line copies.
#pragma push_macro("inline")
#define inline __declspec(dllimport) __forceinline
#include <math.h>
#pragma pop_macro("inline")
#include <math.h>

extern float GetGameClientRandomValueReal( float low, float high,
	char *file, int line );

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"
class GameClientRandomVariable;
Xfer &xferRandomVariable( Xfer &xfer, GameClientRandomVariable &var );

class GameClientRandomVariable
{
public:
	float getValue() const;

	int distribution;
	float minimum;
	float maximum;
};

namespace FXParticleSystem
{

// Coord3D: shared header/view; no private copy.
#include "../../../../../Libraries/Include/Lib/Coord3DCtorView.h"

class CylindricalEmissionVelocityModule
{
public:
	virtual Coord3D getVelocity( int, int );

protected:
	virtual void xfer( Xfer *xfer );

private:
	char m_base[0x1c - 4];
	GameClientRandomVariable m_radial;		///< +0x1C
	GameClientRandomVariable m_normal;		///< +0x28
};

// ?xfer@CylindricalEmissionVelocityModule@FXParticleSystem@@MAEXPAVXfer@@@Z
// retail 0x0055ED34, 43 bytes: slot 3 (offset 0x0C) of the class's vtable
// 0x0081C8B8 (ICF-shared with five more slot-3 entries): Version1, then
// both variables through the rowed xferRandomVariable 0x00306183.
void CylindricalEmissionVelocityModule::xfer( Xfer *xfer )
{
	xfer->Version1();
	xferRandomVariable( *xfer, m_radial );
	xferRandomVariable( *xfer, m_normal );
}

}
