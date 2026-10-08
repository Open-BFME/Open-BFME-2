// ?Rva0039A270Move@@YGXPAVObject@@@Z
// partial score=0.92 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// ?Rva0039A270Move@@YGXPAVObject@@@Z @0x0039A270 542B
// Free helper moving blocking objects off a site: would-collide query around
// source pos with 1.1x bounding radius then pushes each hit outward along
// normalized delta by 1.5x radius. Evidence: callers 0x0039A64F 0x0039A970
// linkbody lane, callees GeometryInfo copy Filter WouldCollide
// iterateObjectsInRange BfmeWideResult next AI aiMove normalize GetLength
// slot114 rva0029439D, floats 1.1 1.5 1.0, kinds at template +0x108.
struct Coord3D
{
	float x;
	float y;
	float z;
	void normalize();
};

typedef bool Bool;
typedef float Real;

class Coord2D
{
public:
	float GetLength() const;
	float x;
	float y;
};

class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &that);
	virtual ~GeometryInfo();
	float getBoundingCircleRadius() const { return m_radius14; }
private:
	char m_pad00[0x10];
	float m_radius14;
	char m_pad18[0x5C - 0x18];
};

class Rva000421C8
{
public:
	virtual ~Rva000421C8() {}
	virtual Bool allow(void *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

class Rva00261603Filter : public Rva000421C8
{
public:
	Rva00261603Filter(const Coord3D &pos, const GeometryInfo &geom, Real angle, Bool desired);
	virtual Bool allow(void *obj);
private:
	Coord3D m_position;
	const GeometryInfo &m_geom;
	Real m_angle;
	Bool m_desired;
};

class Object;

struct BfmeWideResult
{
	Object *next();
	~BfmeWideResult();
	void *m_value;
};

class PartitionManager
{
	char m_pad[0x10];
	void *m_impl;
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distType, Rva000421C8 *filters, int order);
};
extern PartitionManager *ThePartitionManager;

class ThingTemplate
{
public:
	char m_pad[0x108];
	unsigned char m_kind00;
	unsigned char m_kind01;
	unsigned char m_kind02;
	unsigned char m_kind03;
	unsigned char m_kind04;
	unsigned char m_kind05;
	unsigned char m_kind06;
	unsigned char m_kind07;
	unsigned char m_kind08;
	unsigned char m_kind09;
	unsigned char m_kind0A;
	unsigned char m_kind0B;
	unsigned char m_kind0C;
	unsigned char m_kind0D;
	unsigned char m_kind0E;
	unsigned char m_kind0F;
	unsigned char m_kind10;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 1,
	CMD_FROM_DOZER = 2
};

class AICommandInterface
{
public:
	void aiMoveToPositionEvenIfSleeping(const Coord3D *pos, CommandSourceType src);
};

struct AIHolder
{
	char m_pad[0x20];
	AICommandInterface m_cmd;
};

class Slot114Module
{
public:
	virtual void slot000(); virtual void slot001(); virtual void slot002(); virtual void slot003();
	virtual void slot004(); virtual void slot005(); virtual void slot006(); virtual void slot007();
	virtual void slot008(); virtual void slot009(); virtual void slot010(); virtual void slot011();
	virtual void slot012(); virtual void slot013(); virtual void slot014(); virtual void slot015();
	virtual void slot016(); virtual void slot017(); virtual void slot018(); virtual void slot019();
	virtual void slot020(); virtual void slot021(); virtual void slot022(); virtual void slot023();
	virtual void slot024(); virtual void slot025(); virtual void slot026(); virtual void slot027();
	virtual void slot028(); virtual void slot029(); virtual void slot030(); virtual void slot031();
	virtual void slot032(); virtual void slot033(); virtual void slot034(); virtual void slot035();
	virtual void slot036(); virtual void slot037(); virtual void slot038(); virtual void slot039();
	virtual void slot040(); virtual void slot041(); virtual void slot042(); virtual void slot043();
	virtual void slot044(); virtual void slot045(); virtual void slot046(); virtual void slot047();
	virtual void slot048(); virtual void slot049(); virtual void slot050(); virtual void slot051();
	virtual void slot052(); virtual void slot053(); virtual void slot054(); virtual void slot055();
	virtual void slot056(); virtual void slot057(); virtual void slot058(); virtual void slot059();
	virtual void slot060(); virtual void slot061(); virtual void slot062(); virtual void slot063();
	virtual void slot064(); virtual void slot065(); virtual void slot066(); virtual void slot067();
	virtual void slot068(); virtual void slot069(); virtual void slot070(); virtual void slot071();
	virtual void slot072(); virtual void slot073(); virtual void slot074(); virtual void slot075();
	virtual void slot076(); virtual void slot077(); virtual void slot078(); virtual void slot079();
	virtual void slot080(); virtual void slot081(); virtual void slot082(); virtual void slot083();
	virtual void slot084(); virtual void slot085(); virtual void slot086(); virtual void slot087();
	virtual void slot088(); virtual void slot089(); virtual void slot090(); virtual void slot091();
	virtual void slot092(); virtual void slot093(); virtual void slot094(); virtual void slot095();
	virtual void slot096(); virtual void slot097(); virtual void slot098(); virtual void slot099();
	virtual void slot100(); virtual void slot101(); virtual void slot102(); virtual void slot103();
	virtual void slot104(); virtual void slot105(); virtual void slot106(); virtual void slot107();
	virtual void slot108(); virtual void slot109(); virtual void slot110(); virtual void slot111();
	virtual void slot112(); virtual void slot113();
	virtual bool slot114();
};

class Object
{
public:
	virtual ~Object();
	ThingTemplate *m_template04;
	char m_pad08[0x38 - 0x08];
	Coord3D m_pos38;
	float m_angle44;
	char m_pad48[0xA8 - 0x48];
	GeometryInfo m_geomA8;
	char m_padAfterGeom[0x258 - 0xA8 - 0x5C];
	AIHolder *m_ai258;
	void *rva0029439D();
};

void __stdcall Rva0039A270Move(Object *src)
{
	if (!src)
		return;
	Coord3D pos;
	pos.x = src->m_pos38.x;
	pos.y = src->m_pos38.y;
	pos.z = src->m_pos38.z;
	GeometryInfo gi(src->m_geomA8);
	Real radius = gi.getBoundingCircleRadius() * 1.1f;
	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(&pos, radius, 3,
		&Rva00261603Filter(pos, gi, src->m_angle44, true), 0);
	for (Object *them = iter.next(); them; them = iter.next()) {
		ThingTemplate *tmpl = them->m_template04;
		if (tmpl->m_kind0B & 2)
			continue;
		if (tmpl->m_kind10 & 0x40)
			continue;
		if (tmpl->m_kind0D & 1)
			continue;
		if (tmpl->m_kind07 & 0x10)
			continue;
		if (tmpl->m_kind00 & 4)
			continue;
		Slot114Module *mod = (Slot114Module *)them->rva0029439D();
		if (mod && mod->slot114())
			continue;
		AIHolder *holder = them->m_ai258;
		if (!holder)
			continue;
		Coord3D delta;
		delta.x = them->m_pos38.x - src->m_pos38.x;
		delta.y = them->m_pos38.y - src->m_pos38.y;
		delta.z = them->m_pos38.z - src->m_pos38.z;
		Real len = ((Coord2D *)&delta)->GetLength();
		delta.z = 0.0f;
		Real dirX;
		Real dirY;
		Real dirZ;
		if (len > 0.0f) {
			delta.normalize();
			dirX = delta.x;
			dirY = delta.y;
			dirZ = delta.z;
		} else {
			dirX = 1.0f;
			dirY = 0.0f;
			dirZ = 0.0f;
		}
		Real step = radius * 1.5f;
		Coord3D dest;
		dest.x = pos.x + step * dirX;
		dest.y = pos.y + step * dirY;
		dest.z = pos.z + step * dirZ;
		holder->m_cmd.aiMoveToPositionEvenIfSleeping(&dest, (CommandSourceType)2);
	}
}
