// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// ?rva0030A92C@Rva0030A92C@@QAEXM@Z 0x0030A92C 340B evidence: Thing layout +8 transform +38 cachedPos +44 angle +54 +58 altitudes +5c flags +4 template KINDOF 0x108 0x10; setTransformMatrix rowed; TerrainLogic alignOnTerrain slot 0x48; react slot 0x14; callers UNCLAIMED
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
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ, Real *terrainZ) = 0;
};

// Owner unknown: TU-local layout matching Thing offsets for setZ-like update.
class Rva0030A92C
{
public:
	void *m_vptr;
	void *m_template;
	Matrix3D m_transform;
	Coord3D m_cachedPos;
	Real m_cachedAngle;
	unsigned char m_pad48[0x54 - 0x48];
	Real m_54;
	Real m_58;
	int m_cacheFlags;
	void rva0030A92C(Real z);
};

void Rva0030A92C::rva0030A92C(Real z)
{
	if (!((reinterpret_cast<const unsigned char *>(m_template)[0x108]) & 0x10))
	{
		Real oldAngle = m_cachedAngle;
		const Coord3D &cachedPos = m_cachedPos;
		Coord3D oldPos;
		oldPos.x = cachedPos.x;
		oldPos.y = cachedPos.y;
		oldPos.z = cachedPos.z;
		unsigned char oldMtx_buf[sizeof(Matrix3D)];
		Matrix3D &oldMtx = reinterpret_cast<Matrix3D &>(oldMtx_buf);
		oldMtx = m_transform;

		m_transform.Set_Z_Translation(z);
		m_cachedPos.z = z;

		if (m_cacheFlags & 2)
			m_54 += (z - oldPos.z);
		if (m_cacheFlags & 4)
			m_58 += (z - oldPos.z);

		reinterpret_cast<BFMERetailThingVTable *>(this)->reactToTransformChange(&oldMtx, &oldPos, oldAngle);
	}
	else
	{
		unsigned char mtx_buf[sizeof(Matrix3D)];
		Matrix3D &mtx = reinterpret_cast<Matrix3D &>(mtx_buf);
		Coord3D pos;
		pos.x = m_cachedPos.x;
		pos.y = m_cachedPos.y;
		pos.z = z;
		const Bool stickToGround = true;
		reinterpret_cast<BFMERetailTerrainLogicVTable *>(TheTerrainLogic)->alignOnTerrain(m_cachedAngle, pos, stickToGround, mtx);
		reinterpret_cast<Thing *>(this)->setTransformMatrix(&mtx);
	}
}
