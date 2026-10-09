// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva0028449F@TerrainLogic@@QAEXPBUCoord3D@@ABVGeometryInfo@@M@Z retail
// 0x0028449F..0x0028458F (240 bytes) RET 0xC. Called from DozerAIUpdate
// 0x0048A15A. Builds a local cylinder GeometryInfo (rowed ctor 0x00050B74:
// height 35 and radii 14) then walks the record pointers at +0x578/+0x57C
// (same range as the rowed TerrainLogic::rva00283CE7). Every record with a
// key at +0xC whose position the argument shape overlaps (pinned
// GeometryInfo::bfmeIntersects 0x006BEB80 against the local shape at the
// record with angle 0) is reported to TheTriggerManager (rowed 0x0028641F)
// then reset (rowed 0x0027D098) and its key passed to g_00DFF080 slot +0x58
// while +0x1910 takes TheGameLogic's frame. Finally g_00DFF080 slot +0x48
// gets the position shape and angle. The local shape dies through the rowed
// GeometryInfo destructor 0x00050B2A. WB twin 0x00C483E0 (callgraph 3.1)
// has the same order with GeometryInfo::CollidesWith.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef float Real;

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

class GeometryInfo
{
public:
	GeometryInfo(GeometryType type, bool isSmall, Real height, Real majorRadius, Real minorRadius);
	virtual ~GeometryInfo();
	bool bfmeIntersects(const Coord3D &pos, Real angle, const GeometryInfo &other,
		const Coord3D &otherPos, Real otherAngle) const;

private:
	char m_data[0x5C - 4];
};

class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva0028449FFrameView
{
	char unknown00[0x40];
	unsigned int frame;
};

class Rva0027D098
{
public:
	void rva0027D098();
};

struct Rva0028449FRecordView
{
	Coord3D pos;
	unsigned int key;
};

class Rva002872BA
{
public:
	void rva0028641F(unsigned int key, Rva0027D098 *record);
};
extern Rva002872BA *TheTriggerManager;

class G00DFF080Obj;
extern G00DFF080Obj *g_00DFF080;

template<int N> class Rva0028449FSlots : public Rva0028449FSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};
template<> class Rva0028449FSlots<0> {};

class Rva0028449FGlobalView : public Rva0028449FSlots<18>
{
public:
	virtual void slot48(const Coord3D *pos, const GeometryInfo &geom, Real angle) = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58(unsigned int key) = 0;
};

class TerrainLogic
{
public:
	virtual void reset();
	void rva0028449F(const Coord3D *pos, const GeometryInfo &geom, Real angle);

private:
	char unknown04[0x578 - 4];
	Rva0027D098 **first;
	Rva0027D098 **last;
	char unknown580[0x1910 - 0x580];
	unsigned int stamp;
};

void TerrainLogic::rva0028449F(const Coord3D *pos, const GeometryInfo &geom, Real angle)
{
	GeometryInfo shape(GEOMETRY_CYLINDER, false, 35.0f, 14.0f, 14.0f);
	for (Rva0027D098 **i = first; i != last; ++i)
	{
		Rva0028449FRecordView *record = reinterpret_cast<Rva0028449FRecordView *>(*i);
		if (record->key == 0)
			continue;
		if (geom.bfmeIntersects(*pos, angle, shape, record->pos, 0.0f))
		{
			unsigned int key = reinterpret_cast<Rva0028449FRecordView *>(*i)->key;
			if (TheTriggerManager)
				TheTriggerManager->rva0028641F(key, *i);
			(*i)->rva0027D098();
			reinterpret_cast<Rva0028449FGlobalView *>(g_00DFF080)->slot58(key);
			stamp = reinterpret_cast<Rva0028449FFrameView *>(TheGameLogic)->frame;
		}
	}
	reinterpret_cast<Rva0028449FGlobalView *>(g_00DFF080)->slot48(pos, geom, angle);
}
