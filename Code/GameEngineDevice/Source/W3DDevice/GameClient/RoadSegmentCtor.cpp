// cl: /O1 /arch:SSE /DNDEBUG /DWIN32 /MD /EHsc
// ??0RoadSegment@@QAE@XZ @ 0x000D6C35 (173B)
//
// BFME 2's RoadSegment default constructor: both TRoadPt ends, every scalar
// and the bounds sphere start at zero (Zero Hour starts scale, width and the
// bound radius at 1.0), and m_info at +0x68 is built by the pinned
// TRoadSegInfo constructor 0x000D4ED0. Evidence: the body sits in the
// W3DRoadBuffer.cpp run between the TRoadPt copy 0x000D6A72 and
// ??4RoadSegment 0x000D6DB1; W3DRoadBuffer::addMapObjects (0x000DD47D)
// constructs its stack RoadSegment with it and destroys it with the rowed
// ??1RoadSegment 0x000D44B4; offsets agree with the rowed copy constructor
// 0x000D50CE. BFME 2's TRoadPt zeroes itself, which is what orders the two
// ends' stores ahead of the scalars. The Zero Hour W3DRoadBuffer.cpp header
// view keeps the older TRoadPt, so the constructor is compiled here.
typedef float Real;
typedef int Int;

struct Vector2
{
	float X;
	float Y;
};

struct Vector3
{
	Vector3(void) {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X;
	float Y;
	float Z;
};

struct TRoadPt
{
	TRoadPt()
	{
		loc.X = 0.0f; loc.Y = 0.0f;
		top.X = 0.0f; top.Y = 0.0f;
		bottom.X = 0.0f; bottom.Y = 0.0f;
		count = 0;
		last = false; multi = false; isAngled = false; isJoin = false;
	}
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
	TRoadSegInfo();
};

class SphereClass
{
public:
	SphereClass(void) { Center.X = 0.0f; Center.Y = 0.0f; Center.Z = 0.0f; Radius = 0.0f; }
	Vector3 Center;
	float Radius;
};

enum TRoadType { SEGMENT, CURVE, TEE, FOUR_WAY, THREE_WAY_Y, THREE_WAY_H, THREE_WAY_H_FLIP, ALPHA_JOIN };

class RoadSegment
{
public:
	TRoadPt m_pt1;
	TRoadPt m_pt2;
	Real m_curveRadius;
	TRoadType m_type;
	Real m_scale;
	Real m_widthInTexture;
	Int m_uniqueID;
	bool m_visible;
	Int m_numVertex;
	void *m_vb;
	Int m_numIndex;
	void *m_ib;
	TRoadSegInfo m_info;
	SphereClass m_bounds;
public:
	RoadSegment(void);
};

RoadSegment::RoadSegment(void) :
m_curveRadius(0.0f),
m_type(SEGMENT),
m_scale(0.0f),
m_widthInTexture(0.0f),
m_uniqueID(0),
m_visible(false),
m_numVertex(0),
m_vb(0),
m_numIndex(0),
m_ib(0)
{
}
