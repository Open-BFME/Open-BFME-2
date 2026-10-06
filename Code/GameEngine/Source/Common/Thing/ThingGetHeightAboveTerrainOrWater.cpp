// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// ?getHeightAboveTerrainOrWater@Thing@@QBEMXZ 0x0030A4D0 88B evidence: ZH donor Thing OrWater via isUnderwater; callers at 0x000854F9 and 0x001E551C; prev calculateHeightAboveTerrain 0x0030A4AC
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
	// Retail at 0x0030A4D0 pushes 0,0,&waterZ,x,y (5 args) for slot 0x4c; ZH donor has 4-arg isUnderwater.
	// Model the trailing extra 0 to match bytes; slot identity from vtable offset and isUnderwater use.
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ, Real *terrainZ, int unused) = 0;
};

Real Thing::getHeightAboveTerrainOrWater() const
{
	if (!(m_cacheFlags & VALID_ALTITUDE_SEALEVEL))
	{
		const Coord3D* pos = getPosition();
		Real waterZ;
		if (reinterpret_cast<BFMERetailTerrainLogicVTable *>(TheTerrainLogic)->isUnderwater(pos->x, pos->y, &waterZ, 0, 0))
		{
			m_cachedAltitudeAboveTerrainOrWater = pos->z - waterZ;
		}
		else
		{
			m_cachedAltitudeAboveTerrainOrWater = getHeightAboveTerrain();
		}
		m_cacheFlags |= VALID_ALTITUDE_SEALEVEL;
	}
	return m_cachedAltitudeAboveTerrainOrWater;
}
