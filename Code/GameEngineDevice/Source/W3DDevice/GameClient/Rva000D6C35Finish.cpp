// ?rva000D6C35@RoadSegment@@QAEPAV1@XZ @ 0x000D6C35 (173B)
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/w3droadbuffer /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// RoadSegment full-init: zeroes both TRoadPt blocks and the scalar block,
// default-constructs the TRoadSegInfo at +0x68 via placement new, then zeroes
// the SphereClass bounds at +0xAC and returns this (layout ends at 0xBC).
// Evidence: sits between the rowed TRoadPt copy 0x000D6A72 and
// ??4RoadSegment 0x000D6DB1; caller 0x000DD47D builds a stack RoadSegment with
// it then calls rowed ??1RoadSegment 0x000D44B4; the m_info construction calls
// pinned ??0TRoadSegInfo 0x000D4ED0; member offsets match the rowed copy-assign
// 0x000D50CE. A ReadWriteBarrier before the scalar block is the proven codegen
// lever that keeps the ctor-address lea scheduled after the two TRoadPt blocks,
// exactly as retail orders it (same idiom as Rva001DCD3C).
#include <new>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef float Real;
typedef int Int;

struct Vector2
{
	float X;
	float Y;
};

struct TRoadPt
{
	Vector2 loc;
	Vector2 top;
	Vector2 bottom;
	Int count;
	bool last;
	bool multi;
	bool isAngled;
	bool isJoin;
};

struct TRoadSegInfo
{
	Vector2 loc;
	Vector2 roadNormal;
	Vector2 roadVector;
	Vector2 corners[4];
	Real uOffset;
	Real vOffset;
	Real scale;
	TRoadSegInfo() throw();
};

struct RoadBounds
{
	float X;
	float Y;
	float Z;
	float Radius;
};

class RoadSegment
{
public:
	TRoadPt m_pt1;
	TRoadPt m_pt2;
	Real m_curveRadius;
	int m_type;
	Real m_scale;
	Real m_widthInTexture;
	Int m_uniqueID;
	bool m_visible;
	Int m_numVertex;
	void *m_vb;
	Int m_numIndex;
	void *m_ib;
	TRoadSegInfo m_info;
	RoadBounds m_bounds;
public:
	RoadSegment *rva000D6C35();
};

RoadSegment *RoadSegment::rva000D6C35()
{
	m_pt1.loc.X = 0.0f;
	m_pt1.loc.Y = 0.0f;
	m_pt1.top.X = 0.0f;
	m_pt1.top.Y = 0.0f;
	m_pt1.bottom.X = 0.0f;
	m_pt1.bottom.Y = 0.0f;
	m_pt1.count = 0;
	m_pt1.last = false;
	m_pt1.multi = false;
	m_pt1.isAngled = false;
	m_pt1.isJoin = false;
	m_pt2.loc.X = 0.0f;
	m_pt2.loc.Y = 0.0f;
	m_pt2.top.X = 0.0f;
	m_pt2.top.Y = 0.0f;
	m_pt2.bottom.X = 0.0f;
	m_pt2.bottom.Y = 0.0f;
	m_pt2.count = 0;
	m_pt2.last = false;
	m_pt2.multi = false;
	m_pt2.isAngled = false;
	m_pt2.isJoin = false;
	_ReadWriteBarrier();
	m_curveRadius = 0.0f;
	m_type = 0;
	m_scale = 0.0f;
	m_widthInTexture = 0.0f;
	m_uniqueID = 0;
	m_visible = false;
	m_numVertex = 0;
	m_vb = 0;
	m_numIndex = 0;
	m_ib = 0;
	TRoadSegInfo *p = (TRoadSegInfo *)((char *)this + 0x68);
	__assume(p != 0);
	new (p) TRoadSegInfo();
	float *pb = (float *)&m_bounds;
	pb[0] = 0.0f;
	pb[1] = 0.0f;
	pb[2] = 0.0f;
	pb[3] = 0.0f;
	return this;
}
