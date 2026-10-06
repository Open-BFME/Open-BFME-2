// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// ?setTransformMatrix@Thing@@QAEXPBVMatrix3D@@@Z 0x0030A2B7 301B evidence: ZH donor GeneralsMD Thing.cpp Thing::setTransformMatrix; Thing layout +8 m_transform +38 cachedPos +44 angle +5c flags; vtable react slot 0x14 Get_Z_Rotation rowed; 35 callers
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

void Thing::setTransformMatrix( const Matrix3D *mx )
{
	//USE_PERF_TIMER(ThingMatrixStuff)
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

	m_transform = *mx;
	m_cachedPos.x = m_transform.Get_X_Translation();
	m_cachedPos.y = m_transform.Get_Y_Translation();
	m_cachedPos.z = m_transform.Get_Z_Translation();
	m_cachedAngle = m_transform.Get_Z_Rotation();
	m_cacheFlags = 0;

	reinterpret_cast<BFMERetailThingVTable *>(this)->reactToTransformChange((const Matrix3D *)oldMtx, &oldPos, oldAngle);
	DEBUG_ASSERTCRASH(!(_isnan(getPosition()->x) || _isnan(getPosition()->y) || _isnan(getPosition()->z)), ("Drawable/Object position NAN! '%s'\n", m_template->getName().str() ));
}
