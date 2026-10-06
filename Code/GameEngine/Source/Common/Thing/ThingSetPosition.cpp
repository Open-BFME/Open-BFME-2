// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// ?setPosition@Thing@@QAEXPBUCoord3D@@@Z 0x0030AA80 285B evidence: ZH donor Thing setPosition; KINDOF 0x108 terrain branch via align slot 0x48 then setTransformMatrix rowed; 40 callers
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

void Thing::setPosition( const Coord3D *pos )
{
	//USE_PERF_TIMER(ThingMatrixStuff)
	if( !(reinterpret_cast<const unsigned char *>(m_template.getNonOverloadedPointer())[0x108] & 0x10) )
	{
		Real oldAngle = m_cachedAngle;
		const Coord3D &cachedPos = m_cachedPos;
		Coord3D oldPos;
		oldPos.x = cachedPos.x;
		oldPos.y = cachedPos.y;
		oldPos.z = cachedPos.z;
		Matrix3D oldMtx = m_transform;

		//DEBUG_ASSERTCRASH(!(_isnan(pos->x) || _isnan(pos->y) || _isnan(pos->z)), ("Drawable/Object position NAN! '%s'\n", m_template->getName().str() ));
		m_transform.Set_X_Translation( pos->x );
		m_transform.Set_Y_Translation( pos->y );
		m_transform.Set_Z_Translation( pos->z );
		m_cachedPos = *pos;
		m_cacheFlags &= ~(VALID_ALTITUDE_TERRAIN | VALID_ALTITUDE_SEALEVEL);	// but don't clear the dir flags.

		reinterpret_cast<BFMERetailThingVTable *>(this)->reactToTransformChange(&oldMtx, &oldPos, oldAngle);
	}
	else
	{
		Matrix3D mtx;
		const Bool stickToGround = true;	// yes, set the "z" pos
		reinterpret_cast<BFMERetailTerrainLogicVTable *>(TheTerrainLogic)->alignOnTerrain(getOrientation(), *pos, stickToGround, mtx );
		setTransformMatrix(&mtx);
	}
	DEBUG_ASSERTCRASH(!(_isnan(getPosition()->x) || _isnan(getPosition()->y) || _isnan(getPosition()->z)), ("Drawable/Object position NAN! '%s'\n", m_template->getName().str() ));
}
