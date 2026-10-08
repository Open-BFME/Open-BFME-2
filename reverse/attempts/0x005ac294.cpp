// ?rva005AC294@Rva005AB7E5@@QAE_NXZ
// partial score=0.85 date=2026-10-09
// ?rva005AC294@Rva005AB7E5@@QAE_NXZ
// partial score=0.85 date=2026-10-04
// cl: /O1 /G7 /MD /GX /DNDEBUG /arch:SSE /Ireference/shims/bfme2_ascii
//
// The "StructureCreep" skirmish-AI tactic (vtable 0x008722EC; ctor 0x005AB91D
// in Rva004ECECDTacticCtors.cpp, slot 9 0x005AB9AF in
// Rva004ECECDTacticCreate.cpp). Base chain, all address-derived: Rva005DCC24
// (ctor 0x005DCC0A, dtor 0x005DCC24) over Rva005DC73C over the AITactic.cpp
// object Rva004ECECD. Layout: +0x58 an ObjectID, +0x5C, +0x64, +0x68
// counters, +0x60 the owned build order (Rva00573B23, 0x40 bytes), +0x6C the
// index of the structure name last picked from the owner's list.
//
//   0x005AB7E5  dtor: abandon (0x0055ADBA) and ::delete the build order
//   0x005AB993  scalar deleting dtor (slot 0)
//   0x005ABC81  slot 2: clear the running key and schedule the next run
//               5 * frames on; hand the built structure (+0x58) to the
//               controller's default team and the owner's list
//   0x005AB843  slot 5: xfer: the AITactic's, the id, the counters, whether
//               there is an order and the order itself (restarted on load
//               when it had not begun)
//   0x005AB9EE  (not here yet) whether the object's template name is one of the owner's
//               creep structure names (record +0x160, +0x98 vector)
//   0x005ABA59  the next creep structure name: a random one first, then
//               round-robin
#include "ascii_string.h"

extern int g_Va00DBA4E4;

// This unit's statics (0x00E06418..0x00E06428, built in this order by
// 0x007B458D, 0x007B45A8, 0x007B45C1, 0x007B45CE and 0x007B45D9).
AsciiString AIStructureCreep_IsRunning("AIStructureCreep_IsRunning");
float g_00E0641C = g_Va00DBA4E4 * 30.0f;
int g_00E06420 = g_Va00DBA4E4 * 2;
int g_00E06424 = g_Va00DBA4E4;
int g_00E06428 = g_Va00DBA4E4 * 5;

// BFME2's Xfer: operator== overloads, grouped by cl at the first overload
// slot in reverse declaration order (Rva004E0513Xfer.cpp has the same view).
class UnicodeString;
class PooledString;
struct XferUnknown11;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
struct Coord3DBase;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

enum ObjectID
{
	INVALID_ID = 0
};
void XferObjectID(Xfer *xfer, ObjectID *id);

struct Rva005AB7E5Template
{
	char m_pad00[0x64];
	AsciiString m_name;	// +0x64
};

class Player;
class Team;

class Object
{
public:
	Player *getControllingPlayer() const;
	void rva00298AE4(Team *team);
	char m_pad000[4];
	Rva005AB7E5Template *m_04;	// +0x04
	char m_pad008[0x438 - 8];
	unsigned char m_438;		// +0x438
};

class Player
{
public:
	char m_pad000[0x2EC];
	Team *m_defaultTeam;		// +0x2EC
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	unsigned int getFrame() const { return m_40; }
	char m_pad000[0x40];
	unsigned int m_40;		// +0x40
};
extern GameLogic *TheGameLogic;

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord3D : public Coord3DBase
{
	~Coord3D() {}
};

class Rva004EBF4B
{
public:
	Coord3D rva004EBF4B();
};

class Rva00599825
{
public:
	void rva00599825(int id);
	void *rva00599870(const Coord3D &point, int a);
};

class Rva00596389
{
public:
	int rva00596394() const;
};

struct Rva005AB7E5Objects
{
	char m_pad00[0x0C];
	Rva00596389 *m_0C;		// +0x0C
};

struct Rva005AB7E5NameList
{
	unsigned int size() const { return m_end - m_begin; }
	bool empty() const { return m_begin == m_end; }
	AsciiString &operator[](unsigned int i) { return m_begin[i]; }
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_capacity;
};

struct Rva005AB7E5Names
{
	char m_pad00[0x98];
	Rva005AB7E5NameList m_names;	// +0x98
};

struct Rva002A8AB1Record
{
	void rva002C717E(const AsciiString &key, int value);
	int rva002C7196(const AsciiString &key);
	char m_pad000[0x140];
	Rva00599825 m_140;		// +0x140
	char m_pad141[0x160 - 0x141];
	Rva005AB7E5Names *m_160;	// +0x160
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
	void *rva002A8F24(Player *player);
};
extern Rva002A8F24 *g_00DFEEF8;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class Rva00506FE9Hit
{
public:
	void rva0055ADBA(void *owner);
};

class Rva00573B23
{
public:
	Rva00573B23();
	virtual ~Rva00573B23();
	virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
	virtual void v5();
	virtual void start(void *owner, int a);
	virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
	virtual void v11();
	virtual void xfer(Xfer *xfer, void *owner);
	float m_radius;		// +0x04
	ObjectID m_08;		// +0x08
	AsciiString m_name;	// +0x0C
	int m_status;		// +0x10
	char m_pad14[0x20 - 0x14];
	bool m_20;		// +0x20
	bool m_21;		// +0x21
	char m_pad22[0x28 - 0x22];
	bool m_28;		// +0x28
	char m_pad29[0x40 - 0x29];
};

struct Rva00573A00
{
	void rva00573A00(const Coord3D *p);
};

class Rva004ECECD
{
public:
	virtual ~Rva004ECECD();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void xfer(Xfer *xfer);
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual Rva004ECECD *create();
};

class Rva005DC73C : public Rva004ECECD
{
public:
	virtual ~Rva005DC73C();
	char m_pad04[0x24 - 4];
	Player *m_owner;		// +0x24
	char m_pad28[0x58 - 0x28];
};

class Rva005DCC24 : public Rva005DC73C
{
public:
	virtual ~Rva005DCC24();
};

class Rva005AB7E5 : public Rva005DCC24
{
public:
	virtual ~Rva005AB7E5();
	virtual void v2();
	virtual void xfer(Xfer *xfer);
	bool rva005ABEA2();
	AsciiString rva005ABA59();
	bool rva005ABCFE(Coord3DBase *out, const AsciiString &name);
	bool rva005AC0B5(const AsciiString &name);
	bool rva005AC294();
private:
	ObjectID m_58;		// +0x58
	unsigned int m_5C;	// +0x5C
	Rva00573B23 *m_order;	// +0x60
	unsigned int m_64;	// +0x64
	unsigned int m_68;	// +0x68
	int m_next;		// +0x6C
	int m_70;
	int m_74;
	bool m_78;
	bool m_running;		// +0x79
	unsigned int m_nextRun;	// +0x7C
};

Rva005AB7E5::~Rva005AB7E5()
{
	if (m_order) {
		((Rva00506FE9Hit *)m_order)->rva0055ADBA(m_owner);
		::delete m_order;
		m_order = 0;
	}
}

void Rva005AB7E5::xfer(Xfer *xfer)
{
	Rva004ECECD::xfer(xfer);
	XferObjectID(xfer, &m_58);
	*xfer == m_5C;
	*xfer == m_64;
	*xfer == m_68;
	bool hasOrder = m_order != 0;
	*xfer == hasOrder;
	if (hasOrder) {
		if (xfer->IsStoring()) {
			m_order->xfer(xfer, m_owner);
		} else if (xfer->IsLoading()) {
			m_order = new Rva00573B23;
			m_order->xfer(xfer, m_owner);
			if (m_order->m_status == 0)
				m_order->start(m_owner, 1);
		}
	}
}

AsciiString Rva005AB7E5::rva005ABA59()
{
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	if (m_next == -1) {
		m_next = GetGameLogicRandomValue(0, record->m_160->m_names.size() - 1,
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\TargetlessTactics\\AIStructureCreepTactic.cpp",
			368);
	} else if ((unsigned int)++m_next >= record->m_160->m_names.size()) {
		m_next = 0;
	}
	return record->m_160->m_names[m_next];
}

void Rva005AB7E5::v2()
{
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	if (m_running) {
		record->rva002C717E(AIStructureCreep_IsRunning, 0);
		m_nextRun = TheGameLogic->getFrame() + g_00E06428;
	}
	Object *obj = TheGameLogic->findObjectByID(m_58);
	if (obj && !(obj->m_438 & 1)) {
		obj->rva00298AE4(obj->getControllingPlayer()->m_defaultTeam);
		record->m_140.rva00599825(m_58);
	}
}

bool Rva005AB7E5::rva005AC294()
{
	AsciiString name(AsciiString::TheEmptyString);
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	for (unsigned int i = 0; i < record->m_160->m_names.size(); ++i) {
		if (name != AsciiString::TheEmptyString)
			break;
		AsciiString candidate = rva005ABA59();
		if (rva005AC0B5(candidate))
			name = candidate;
	}
	if (m_order != 0 || name == AsciiString::TheEmptyString)
		return false;
	Coord3DBase pos;
	if (!rva005ABCFE(&pos, name))
		return false;
	m_order = new Rva00573B23;
	m_order->m_radius = -1.0f;
	m_order->m_21 = true;
	m_order->m_20 = false;
	m_order->m_name = name;
	m_order->m_08 = m_58;
	m_order->m_28 = false;
	((Rva00573A00 *)m_order)->rva00573A00((const Coord3D *)&pos);
	m_order->start(m_owner, 0);
	return true;
}
