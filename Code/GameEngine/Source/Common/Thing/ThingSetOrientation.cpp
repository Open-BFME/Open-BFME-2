// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// ?setOrientation@Thing@@QAEXM@Z 0x0030AB9D 480B evidence: BFME1 donor Code/GameEngine/Source/Common/Thing/Thing.cpp Thing::setOrientation; 40+ callers; vtable reactToTransformChange slot 0x14 alignOnTerrain slot 0x48; KINDOF offset 0x108
#include "../../../../../reference/shims/bfme_matrix3d_link/vector4.h"
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/PerfTimer.h"
#include "Common/Thing.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/GlobalData.h"
#include "Common/NameKeyGenerator.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/Team.h"
#include "Lib/Trig.h"
#include "GameLogic/TerrainLogic.h"

class BFMERetailThingVTable
{
public:
	virtual Real calculateHeightAboveTerrain() const = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void reactToTransformChange(const Matrix3D *oldMtx, const Coord3D *oldPos, Real oldAngle) = 0;
};

class BFMERetailTerrainLogicVTable
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	// ZH's TerrainLogic.h puts getGroundHeight at slot 5; retail calls
	// [vtable+0x18], one slot further out.
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = NULL) const = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual PathfindLayerEnum alignOnTerrain(Real angle, const Coord3D& pos, Bool stickToGround, Matrix3D& mtx) = 0;
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ, Real *terrainZ) = 0;
};

void Thing::setOrientation( Real angle )
{
	//USE_PERF_TIMER(ThingMatrixStuff)
	Coord3D u, x, y, z, pos;

	// setOrientation always forces us straight up in the Z axis,
	// or aligned with the terrain if we have the magic flag set.
	// don't want this? call setTransformMatrix instead.

	Real oldAngle = m_cachedAngle;
	const Coord3D &cachedPos = m_cachedPos;
	Coord3D oldPos;
	oldPos.x = cachedPos.x;
	oldPos.y = cachedPos.y;
	oldPos.z = cachedPos.z;
	float oldMtx[12];
	{
		const float *srcMtx = (const float *)&m_transform;
		oldMtx[0] = srcMtx[0]; oldMtx[1] = srcMtx[1]; oldMtx[2] = srcMtx[2]; oldMtx[3] = srcMtx[3];
		oldMtx[4] = srcMtx[4]; oldMtx[5] = srcMtx[5]; oldMtx[6] = srcMtx[6]; oldMtx[7] = srcMtx[7];
		oldMtx[8] = srcMtx[8]; oldMtx[9] = srcMtx[9]; oldMtx[10] = srcMtx[10]; oldMtx[11] = srcMtx[11];
	}

	pos.x = m_transform.Get_X_Translation();
	pos.y = m_transform.Get_Y_Translation();
	pos.z = m_transform.Get_Z_Translation();
	if( reinterpret_cast<const unsigned char *>(m_template.getNonOverloadedPointer())[0x108] & 0x10 )
	{
		const Bool stickToGround = true;	// yes, set the "z" pos
		reinterpret_cast<BFMERetailTerrainLogicVTable *>(TheTerrainLogic)->alignOnTerrain(angle, pos, stickToGround, m_transform );
	}
	else
	{
		z.x = 0.0f;
		z.y = 0.0f;
		z.z = 1.0f;

		u.x = Cos(angle);
		u.y = Sin(angle);
		u.z = 0.0f;

		y.crossProduct( &z, &u, &y );
		x.crossProduct( &y, &z, &x );

		m_transform.Set(  x.x, y.x, z.x, pos.x,
											x.y, y.y, z.y, pos.y,
											x.z, y.z, z.z, pos.z );
	}

	//DEBUG_ASSERTCRASH(-PI <= angle && angle <= PI, ("Please pass only normalized (-PI..PI) angles to setOrientation (%f).\n", angle));
	m_cachedAngle = normalizeAngle(angle);
	m_cachedPos = pos;
	m_cacheFlags &= ~VALID_DIRVECTOR;	// but don't clear the altitude flags.

	reinterpret_cast<BFMERetailThingVTable *>(this)->reactToTransformChange((const Matrix3D *)oldMtx, &oldPos, oldAngle);
	DEBUG_ASSERTCRASH(!(_isnan(getPosition()->x) || _isnan(getPosition()->y) || _isnan(getPosition()->z)), ("Drawable/Object position NAN! '%s'\n", m_template->getName().str() ));
}
