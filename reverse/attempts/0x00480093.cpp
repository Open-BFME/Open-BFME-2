// ?rva00480093@ShareExperienceBehavior@@UAEXM@Z
// partial score=0.93 date=2026-10-04
// cl: /O1 /GX /arch:SSE /MD /DNDEBUG
// ?rva0047FFFE@ShareExperienceBehavior@@QAEMPAVCoord3D@@PAUPos0047FFFE@@@Z @ 0x0047FFFE 149B
// Unlock: ShareExperience distance falloff between ModuleData radii. Evidence:
// contiguous gap after ??1ShareExperienceBehaviorModuleData 0x0047FFCE and before
// caller 0x00480093; ecx+4 is ModuleData with floats +8/+0xC matching ctor TU
// 0x0047FE90 (m_r8/m_rC); second param carries pos at +0x38/+0x3C/+0x40;
// callees all rowed (Coord3D::GetLength 0x00005A26); float refs g_Va00BBB8D8 / BfmeZeroRange.
//
// ?rva00480093@ShareExperienceBehavior@@UAEXM@Z @ 0x00480093 467B
// Slot 11 of the +0x20 interface vftable 0x008485AC (the ctor 0x0047FEED stores
// it): unless the module data's +0x10 share is not positive or the object has
// status 0x41, every alive object other than this one, passing 0x002614DF,
// relationship 4 and the data's +0x14 object filter for the object's player
// within the data's +0x08 radius (BFME2's partition filter chain, the view
// AIStructureCreepTactic.cpp documents) with an experience tracker (+0x264)
// that 0x0039AE04 allows gets the amount, scaled by the share and by the
// falloff above, through 0x0039B315; when the object's template has +0x110
// bit 26 and TheGameLogic +0x9F is clear, objects whose template has that
// bit too are skipped. The amount argument keeps the running product.
extern float g_Va00BBB8D8;
extern const float BfmeZeroRange;

class Coord3D
{
public:
	float GetLength() const;
	float x;
	float y;
	float z;
};

struct Pos0047FFFE
{
	unsigned char pad[0x38];
	float x;
	float y;
	float z;
};

class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00C07190, allow 0x002614DF: +0x08 an object.
class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a
// player, +0x10 whether a hit allows.
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA00480093_65 = 0x41
};

class ExperienceTracker
{
public:
	bool rva0039AE04() const;	// 0x0039AE04
	void rva0039B315(float amount, bool a, bool b, bool c, int d);	// 0x0039B315
};

class ThingTemplate
{
public:
	char m_pad000[0x110];
	unsigned m_110;		// +0x110 (bit 26 tested)
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	bool testStatus(ObjectStatusTypes bit) const;	// 0x0004E536
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;				// +0x38
	char m_pad044[0x264 - 0x44];
	ExperienceTracker *m_264;		// +0x264
};

class GameLogic
{
public:
	char m_pad00[0x9F];
	bool m_9F;		// +0x9F
};
extern GameLogic *TheGameLogic;

class ShareExperienceBehaviorModuleData
{
public:
	unsigned char m_pad[8];
	float m_08;
	float m_0C;
	float m_10;		// +0x10 the share
	int m_14;		// +0x14 the object filter
};

class Module
{
public:
	virtual ~Module();
	const ShareExperienceBehaviorModuleData *m_moduleData;	// +0x04
	Object *m_object;					// +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
class Rva00480093Base10
{
public:
	virtual void rva00480093Base10Anchor();
private:
	char m_pad14[0x20 - 0x14];
};
class Rva00480093Iface20
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void rva00480093(float amount) = 0;
};

class ShareExperienceBehavior : public Module, public BehaviorModuleInterface, public Rva00480093Base10,
	public Rva00480093Iface20
{
public:
	float rva0047FFFE(Coord3D *a, Pos0047FFFE *b);
	virtual void rva00480093(float amount);
};

float ShareExperienceBehavior::rva0047FFFE(Coord3D *a, Pos0047FFFE *b)
{
	const ShareExperienceBehaviorModuleData *md = m_moduleData;
	if (md->m_0C == g_Va00BBB8D8)
	{
		Coord3D diff;
		diff.x = b->x;
		diff.y = b->y;
		diff.z = b->z;
		diff.x -= a->x;
		diff.y -= a->y;
		diff.z -= a->z;
		float len = diff.GetLength();
		float f = g_Va00BBB8D8 - len / md->m_08;
		if (f >= BfmeZeroRange)
			return f;
		return BfmeZeroRange;
	}
	return g_Va00BBB8D8;
}

void ShareExperienceBehavior::rva00480093(float amount)
{
	const ShareExperienceBehaviorModuleData *data = m_moduleData;
	Object *obj = m_object;
	if (!(data->m_10 > 0.0f))
		return;
	if (obj->testStatus(OBJECT_STATUS_RVA00480093_65))
		return;
	bool selfFlag = (obj->m_template->m_110 >> 26) & 1;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(obj->getPosition(), data->m_08, 0,
		Rva002614DFFilter(obj).link(&Rva0026119DFilter())->link(&Rva00260EB1Filter(obj, 4, false))
			->link(&Rva002611BFFilter(obj))
			->link(&Rva002614ECFilter(&data->m_14, obj->getControllingPlayer(), true)), 0);
	Coord3D center;
	center.x = obj->getPosition()->x;
	center.y = obj->getPosition()->y;
	center.z = obj->getPosition()->z;
	Object *other;
	while ((other = hits.next()) != 0) {
		if (selfFlag && !TheGameLogic->m_9F && (other->m_template->m_110 & 0x04000000))
			continue;
		ExperienceTracker *tracker = other->m_264;
		if (!tracker || !tracker->rva0039AE04())
			continue;
		amount *= data->m_10;
		amount *= rva0047FFFE(&center, (Pos0047FFFE *)other);
		if (amount > 0.0f)
			tracker->rva0039B315(amount, true, true, true, 0);
	}
}
