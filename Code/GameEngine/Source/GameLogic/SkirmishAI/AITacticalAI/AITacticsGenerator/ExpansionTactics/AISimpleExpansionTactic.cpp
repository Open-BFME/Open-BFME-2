// cl: /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
//
// The "SimpleExpansion" skirmish-AI tactic (vtable 0x00871FF4; ctor 0x005AA9DB
// in Rva004ECECDTacticCtors.cpp, dtor 0x005AA860 and ??_G, slot 9 in
// Rva004ECECDTacticCreate.cpp). Base chain, all address-derived: Rva005DCBE3
// over AITacticOffensive over the AITactic.cpp object AITactic. +0x58 owns the
// build order (Rva00573B23, 0x40 bytes: ctor 0x00573A9B, its +0x10 status),
// +0x5C is the stage (0..4).
//
//   0x005AAA34  stage 0: order a "MenFortress" at the +0x20 record's point
//               (radius 3000) and start it for the owner
//   0x005AA86B  stage 3: point this owner's base layout (record +0x04,
//               0x0050722A) at the record's point
//   0x005AA88D  slot 2: abandon the order (0x0055ADBA unless 0x004E9378
//               says it is done) and free it
//   0x005AA8CC  slot 3: give the unit a random count of 2
//   0x005AA90D  slot 5: xfer, version 1: the AITactic's, whether there is
//               an order and the order itself, then the stage
//   0x005AAB08  slot 7: step the stage machine; a failed order (status 3)
//               stops the tactic
#include "ascii_string.h"

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord3D : public Coord3DBase
{
};

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

class AIBaseBuilder
{
public:
	void rva0050722A(Coord3D *point);
};

struct Rva002A8AB1Record
{
	char m_pad00[4];
	AIBaseBuilder m_layout;	// +0x04
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;

// The build order's other address-named views (its base Rva0055B0CC).
class Rva004E9378
{
public:
	bool rva004E9378();
};

class Rva00506FE9Hit
{
public:
	void rva0055ADBA(void *owner);
};

class Rva00573A00
{
public:
	void rva00573A00(const Coord3D *point);
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
	void setName(const AsciiString &name) { m_name = name; }
	float m_radius;		// +0x04
	char m_pad08[0x0C - 8];
	AsciiString m_name;	// +0x0C
	int m_status;		// +0x10
	char m_pad14[0x20 - 0x14];
	bool m_20;		// +0x20
	char m_pad21[0x40 - 0x21];
};

struct Rva005AA860Record
{
	char m_pad00[0x0C];
	Coord3D m_point0C;	// +0x0C
};

struct Rva005AA860Unit
{
	char m_pad000[0x2D0];
	int m_2D0;		// +0x2D0
};

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class AITactic
{
public:
	virtual ~AITactic();
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual bool initializeTeamTemplate(Rva005AA860Unit *unit, void *unused);
	virtual void v4();
	virtual void xfer(Xfer *xfer);
	virtual void run();
	virtual void update();
	virtual void v8();
	virtual AITactic *create();
	unsigned char rva004ED169();
	void end(bool a, bool b);
};

class AITacticOffensive : public AITactic
{
public:
	virtual ~AITacticOffensive();
	char m_pad04[0x20 - 4];
	Rva005AA860Record *m_record;	// +0x20
	void *m_owner;			// +0x24
	char m_pad28[0x58 - 0x28];
};

class AISimpleExpansionTactic : public AITacticOffensive
{
public:
	virtual ~AISimpleExpansionTactic();
	virtual void cleanUp();
	virtual bool initializeTeamTemplate(Rva005AA860Unit *unit, void *unused);
	virtual void xfer(Xfer *xfer);
	virtual void update();
	void rva005AA663();
	void startCreateNewBase();
	void startConstruction();
private:
	Rva00573B23 *m_order;	// +0x58
	int m_stage;		// +0x5C
};

void AISimpleExpansionTactic::startCreateNewBase()
{
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	record->m_layout.rva0050722A(&m_record->m_point0C);
}

void AISimpleExpansionTactic::cleanUp()
{
	Rva00573B23 *order = m_order;
	if (order) {
		if (!((Rva004E9378 *)order)->rva004E9378())
			((Rva00506FE9Hit *)order)->rva0055ADBA(m_owner);
		::delete m_order;
		m_order = 0;
	}
}

bool AISimpleExpansionTactic::initializeTeamTemplate(Rva005AA860Unit *unit, void *)
{
	unit->m_2D0 = GetGameLogicRandomValue(2, 2,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\ExpansionTactics\\AISimpleExpansionTactic.cpp",
		160);
	return true;
}

void AISimpleExpansionTactic::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	AITactic::xfer(xfer);
	bool hasOrder = m_order != 0;
	*xfer == hasOrder;
	if (xfer->IsStoring() && hasOrder) {
		m_order->xfer(xfer, m_owner);
	} else if (xfer->IsLoading() && hasOrder) {
		m_order = new Rva00573B23;
		m_order->xfer(xfer, m_owner);
	}
	unsigned int stage = m_stage;
	*xfer == stage;
	m_stage = stage;
}

void AISimpleExpansionTactic::startConstruction()
{
	m_order = new Rva00573B23;
	m_order->setName(AsciiString("MenFortress"));
	((Rva00573A00 *)m_order)->rva00573A00(&m_record->m_point0C);
	m_order->m_radius = 3000.0f;
	m_order->m_20 = false;
	m_order->start(m_owner, 0);
}

void AISimpleExpansionTactic::update()
{
	if (m_stage > 0 && m_order->m_status == 3) {
		end(0, 0);
		return;
	}
	switch (m_stage) {
	case 0:
		startConstruction();
		m_stage = 1;
		break;
	case 1:
		if (m_order->m_status == 1) {
			rva005AA663();
			m_stage = 2;
		}
		break;
	case 2:
		if (rva004ED169())
			m_stage = 3;
	case 3:
		if (m_order->m_status == 2) {
			startCreateNewBase();
			m_stage = 4;
		}
		break;
	case 4:
		end(1, 0);
		break;
	}
}
