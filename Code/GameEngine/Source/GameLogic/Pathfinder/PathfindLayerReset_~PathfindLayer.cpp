// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Split from PathfindLayerReset.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Reference: Open-BFME-1 968ca36c3265b295297e6aed45a6bd89ffe59c40,
// game/GameEngine/Source/GameLogic/AI/PathfindLayerResetFull.cpp.
// Target identity: the adjacent verified PathfindLayer::getCell and
// DoBoundsOverlap bodies share cells +4, dimensions +8/+C and triggers +38.
// Target adaptation: bridge +34, triggers +38, trigger ID +3C; +2C becomes
// -1 and +30 is retained. The original name of this 66-byte wrapper and its
// 105-byte allocation-clear helper remain unknown.

#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Region2D.h"
#include <math.h>

inline float Coord3D::length() const { return (float)sqrt(x*x+y*y+z*z); }
inline void Coord3D::normalize() { float len=length(); if(len!=0.0f){float scale=1.0f/len;x*=scale;y*=scale;z*=scale;} }
inline float Coord3D::GetLengthSqrd() const { float x_value=x,y_value=y,z_value=z; return x_value*x_value+y_value*y_value+z_value*z_value; }

template<class T> inline volatile T &__vref(T &x){return *(volatile T *)&x;}

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#include <new>

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

// The primitive virtual order is measured by the rowed Common/System/Xfer.cpp
// providers: ICoord2D slot 19, int slot 31, bool slot 36. Version1 is the
// existing 23-byte provider at 0x000053EE. Other entries are ABI placeholders.
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
#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/GameLogic/PathfindCell.h"

// Native vslot zero is called with flags zero; its returned pointer is
// passed to the rowed global operator delete. Only that ABI is asserted.
class Rva00366DECVirtual
{
public:
	virtual void *slot0(unsigned int flags);
};

#include "../../../Include/GameLogic/PathfindLayer.h"

// Native 0x00366DEC..0x00366E2E, RET 0.
void PathfindLayer::rva00366DEC()
{
	m_bridge = 0;
	rva003667D4();
	m_layer = 1;
	if (m_triggers)
		::operator delete(((Rva00366DECVirtual *)m_triggers)->slot0(0));
	m_triggers = 0;
	m_startCell.x = -1;
	m_startCell.y = -1;
	m_endCell.x = -1;
	m_endCell.y = -1;
	m_zone = -1;
	height = -1;
}

// Native 0x003667D4..0x0036683D, RET 0. Reference algorithm:
// game/GameEngine/Source/GameLogic/AI/PathfindLayerApplyZone.cpp bfmeReset
// at the same donor revision. Target adds the zone reset at +0x2C.
void PathfindLayer::rva003667D4()
{
	if (m_layerCells)
	{
		for (int i = 0; i < m_width; ++i)
		{
			for (int j = 0; j < m_height; ++j)
			{
				PathfindCell *cell = &m_layerCells[i][j];
				cell->rva0052DED3();
			}
		}
		delete[] m_layerCells;
		m_layerCells = 0;
	}
	if (m_blockOfMapCells)
		delete[] m_blockOfMapCells;
	m_zone = -1;
	m_blockOfMapCells = 0;
	m_width = 0;
	m_height = 0;
	m_xOrigin = 0;
	m_yOrigin = 0;
}


// Native 0x00366B77..0x00366CEA, RET0. WB F29A70 names
// PathfindLayer::ClassifyWallCells and carries the same corner tests and
// reset/type classification. Target cell zone +8 and layer/zone flags +C
// are read from native stores and the already verified setter providers.
// Native tests nonzero in the branch reached when the count is not positive.
// Bitfield setter providers are already verified under their ledger owner.
// Native array cleanup callback367369 in Pathfinder destructor2F213F;
// target tail-jumps the already verified66B layer release wrapper.
PathfindLayer::~PathfindLayer(){rva00366DEC();}


// Native 00366CEA..00366DEC RET16; WB F29DE0 names ConnectsZones.
// BFME1 clean source supplies the zone-walk semantics. Native accesses prove
// cells4, dimensions8/C, destroyed30, zone flags10..15, and LocomotorSet10/15.
// The scheduling fence preserves the native loop-index load before cell-base load.
enum PathfindLayerEnum{LAYER_INVALID=-1,LAYER_GROUND=1,LAYER_FIRST_BRIDGE=16};
int isGroundOrBridgeLayer(int);
#include "../../../Include/GameLogic/LocomotorSet.h"
#include "../../../Include/GameLogic/PathfindZoneManager.h"
#include "../../../Include/GameLogic/AIPathfind.h"
#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;


// Native 0x00366E2E..0x00367369, RET 0. ZH AIPathfind.cpp PathfindLayer::classifyCells
// with classifyLayerMapCell inlined; the endpoint conversions are ZH's
// REAL_TO_INT_FLOOR spelled with the CRT floorf (BFME uses the floor import).
class Rva0027C36A 
{
 public: Rva0027C36A();
 Rva0027C36A &operator=(const Rva0027C36A&);
 Coord3D from,to;
 unsigned char rest[0xa8-24];
 
}
;
class Bridge 
{
 public: bool isPointOnBridge(const Coord3D*);
 bool isCellOnSide(const Region2D*);
 bool isCellOnEnd(const Region2D*);
 bool isCellEntryPoint(const Region2D*,float*);
 float getBridgeHeight(const Coord3D*,Coord3D*);
 unsigned char prefix[12];
 Rva0027C36A info;
 
}
;
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;
// ZH BaseType.h fast_float2long_round, preserved for the proven x87
// conversion blocker: C++ casts call _ftol2 and /QIfist rejects /arch:SSE.
// Native endpoint conversions use this exact fld/fistp rounding primitive.
__forceinline long fast_float2long_round(float f)

{
 long i;
 __asm 
 {
  fld [f]
  fistp [i]
  
 }
 return i;
 
}

