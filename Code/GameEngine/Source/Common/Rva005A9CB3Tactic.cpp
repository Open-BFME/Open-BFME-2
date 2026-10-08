// cl: /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
//
// The "SimpleSiege" skirmish-AI tactic (vtable 0x00871E6C; ctor 0x005A9D33 in
// Rva004ECECDTacticCtors.cpp, dtor 0x005A9CB3 and ??_G in
// Rva005DC87BDerived.cpp, slot 9 in Rva004ECECDTacticCreate.cpp). Base chain,
// all address-derived: AITacticSiege (ctor 0x005DC85F) over AITacticOffensive over
// the AITactic.cpp object AITactic. +0x5C is the siege stage (0..3).
//
//   0x005A9CBE  slot 1: the owner's TheSkirmishAIManager record answers
//               0x002C6ACB, the base test passes, the request carries no
//               +0x04, and the 0x005DC8A2 search finds a gate
//   0x005A9F70  slot 3 (not here yet): unless told otherwise, queue one order per gate
//               object (kind 7) the owner holds on the given order list
//   0x005A9D06  slot 5: xfer: the base's, then the stage
//   0x005A9EC9  slot 7: while running, step the stage machine
//   0x005A9DD4  attack the base's target and move the team 500 units short
//               of it on the leader's side
#include "ascii_string.h"

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord3D : public Coord3DBase
{
	float Normalize();
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

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[4];
	void *m_04;		// +0x04, its template
	char m_pad008[0x38 - 8];
	Coord3D m_pos;		// +0x38
	char m_pad044[0x304 - 0x44];
	int m_304;		// +0x304
};

struct Rva005A9CB3Template
{
	char m_pad000[0x64];
	AsciiString m_name;	// +0x64
	char m_pad068[0x520 - 0x68];
	int m_520;		// +0x520
};

class Player
{
public:
	char m_pad000[0x2EC];
	int m_2EC;		// +0x2EC
};

class Team
{
public:
	Object *rva0039E8EB();
};

struct Rva005A9CB3Record
{
	char m_pad00[0x0C];
	Coord3D m_point0C;	// +0x0C
	bool m_18;		// +0x18
};

struct Rva002A8AB1Record
{
	void *rva002C6ACB();
};

class Rva0025BFF8
{
public:
	Object *rva0025BFF8(int index);
};

namespace _STL
{
template <class T1, class T2> struct pair
{
	T1 first;
	T2 second;
};
template <class T> struct hash
{
};
template <class T> struct equal_to
{
};
template <class T> class allocator
{
};
template <class K, class V, class H, class E, class A> class hash_map
{
public:
	unsigned int bucket_count() const;
};
}

typedef _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, int> > > IntMap;

class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;

// The 0x18-byte order record (ctor 0x0039EA9C, dtor 0x0039EAB7) and its
// copy-assigned view (0x0039D769) that 0x003A0D62 appends.
class Rva0039D769;

class Rva0039EA9C
{
public:
	Rva0039EA9C();
	~Rva0039EA9C();
	int m_00;
	int m_04;
	int m_08;
	AsciiString m_0C;
	AsciiString m_10;
	int m_14;
};

class TeamPrototype
{
public:
	void addUnitInfo(const Rva0039D769 &order);
};

struct Rva005A9CB3Request
{
	char m_pad00[4];
	void *m_04;		// +0x04
};

class AITactic
{
public:
	virtual ~AITactic();
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual bool initializeTeamTemplate(TeamPrototype *orders, int skip);
	virtual void v4();
	virtual void xfer(Xfer *xfer);
	virtual void run();
	virtual void update();
	virtual void v8();
	virtual AITactic *create();
	Team *rva004ECECD(int index);
	bool isTeamIdle(int index);
	void teamAttackObject(int a, Object *target);
	void teamAttackMove(int a, const Coord3D *point);
	void end(bool a, bool b);
};

class AITacticOffensive : public AITactic
{
public:
	virtual ~AITacticOffensive();
	unsigned char checkTarget(void *request);
	char m_pad04[0x10 - 4];
	bool m_running;			// +0x10
	char m_pad11[0x20 - 0x11];
	Rva005A9CB3Record *m_record;	// +0x20
	Player *m_owner;		// +0x24
	char m_pad28[0x58 - 0x28];
};

class AITacticSiege : public AITacticOffensive
{
public:
	virtual ~AITacticSiege();
	virtual void xfer(Xfer *xfer);
	bool sideHasIdleSiegeWeapons();
	bool isWallBreached();
	bool findWallTarget();
	Object *rva005DCAE5();
	int m_58;
};

class AISimpleSiegeTactic : public AITacticSiege
{
public:
	virtual ~AISimpleSiegeTactic();
	virtual bool canRun(void *request);
	virtual void xfer(Xfer *xfer);
	virtual void update();
	bool rva005A9DD4();
private:
	unsigned int m_stage;	// +0x5C
};

bool AISimpleSiegeTactic::canRun(void *request)
{
	if (g_00DFEEF8->rva002A8AB1(m_owner)->rva002C6ACB()
		&& checkTarget(request)
		&& !((Rva005A9CB3Request *)request)->m_04)
		return sideHasIdleSiegeWeapons();
	return false;
}

void AISimpleSiegeTactic::xfer(Xfer *xfer)
{
	AITacticSiege::xfer(xfer);
	unsigned int stage = m_stage;
	*xfer == stage;
	m_stage = stage;
}

bool AISimpleSiegeTactic::rva005A9DD4()
{
	if (findWallTarget()) {
		Object *target = rva005DCAE5();
		teamAttackObject(0, target);
		const Coord3D *from = rva004ECECD(0)->rva0039E8EB()->getPosition();
		Coord3D dest;
		dest.x = from->x;
		dest.y = from->y;
		dest.z = from->z;
		dest.x -= target->getPosition()->x;
		dest.y -= target->getPosition()->y;
		dest.z -= target->getPosition()->z;
		dest.Normalize();
		dest.x *= 500.0f;
		dest.y *= 500.0f;
		dest.z *= 500.0f;
		dest.x = target->getPosition()->x + dest.x;
		dest.y = target->getPosition()->y + dest.y;
		dest.z = target->getPosition()->z + dest.z;
		teamAttackMove(1, &dest);
		return true;
	}
	return false;
}

void AISimpleSiegeTactic::update()
{
	if (!m_running)
		return;
	if (m_record->m_18) {
		end(1, 0);
		return;
	}
	if (!rva004ECECD(1) || !rva004ECECD(0)) {
		end(0, 0);
		return;
	}
	switch (m_stage) {
	case 0:
		if (rva005A9DD4())
			m_stage = 1;
		else
			end(0, 0);
		break;
	case 1:
		if (isWallBreached())
			m_stage = 2;
		break;
	case 2:
		teamAttackMove(1, &m_record->m_point0C);
		m_stage = 3;
		break;
	case 3:
		if (isTeamIdle(1))
			end(1, 0);
		break;
	}
}
