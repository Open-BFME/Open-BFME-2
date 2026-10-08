// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /O1 /arch:SSE /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// AIWall.cpp. Named WB137E130/137E4D0 and the complete native bodies
// establish buildGate and calcGatePosition. The original coordinate-return
// and wall-order type spellings remain unknown; caller views are labeled below.
//
//   0x004EB902  among the alive objects the planner's player (+0x18) finds
//               allied (relationship flag 2) within 25 of 0x004EAFBD's
//               position, the first whose command set (ControlBar) has a
//               button with an upgrade whose button template has +0x120
//               bit 11, on an object with +0x280 at -1 and 0x0028BC58(0),
//               that the object accepts (0x002940B9): record its cost, the
//               object's ID, the button and the upgrade's name in the +0x14
//               plan and hand it on (slot 6). The scan is BFME2's partition
//               filter chain (the view AIStructureCreepTactic.cpp documents).
#include "ascii_string.h"
#include <vector>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

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

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags, +0x0C whether a hit allows.
class Rva00261409Filter : public Rva000421C8
{
public:
	Rva00261409Filter(Player *player, bool match, int flags)
		: m_player(player), m_match(match), m_flags(flags) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
	int m_flags;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

float __cdecl GetGameLogicRandomValueReal(float, float, char *, int);
// Native4EAFBD/213 and WB137E4D0/747 prove a hidden twelve-byte result,
// float addition/scaling and component-wise return copying. This value view
// reuses the canonical twelve-byte coordinate base. Its explicit copy and
// arithmetic follow WWMath vector3.h at BFME1 revision
// 9cbfb551fe20dae985f91f2319d8997287b6a705. That donor is the semantic/codegen
// guide, not proof of the original return-type spelling. The virtual slot13
// result and key50 are separately witnessed in the native/debug bodies and
// supported by the already-rowed wall-order constructor and transfer sibling.
// No vtable definition or assertion about unobserved slots is made here.
struct WallPositionValue : Coord3D {
    WallPositionValue() {}
    WallPositionValue(const WallPositionValue &other) {
        x=other.x; y=other.y; z=other.z;
    }
    WallPositionValue &operator+=(const WallPositionValue &other) {
        x+=other.x; y+=other.y; z+=other.z; return *this;
    }
    WallPositionValue &operator*=(float scale) {
        x=x*scale; y=y*scale; z=z*scale; return *this;
    }
};
class WallPositionOrderView {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12();
    virtual WallPositionValue position();
    unsigned char unknown04[0x4c];
    unsigned key50;
    unsigned getKey() const { return key50; }
};


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

class ThingTemplate
{
public:
	char m_pad000[0x120];
	unsigned m_120;		// +0x120 (bit 11 tested)
};

class UpgradeTemplate
{
public:
	unsigned rva0026EF50(Player *player, Object *obj) const;	// 0x0026EF50
	const AsciiString &getName() const { return m_08; }
	char m_pad00[0x08];
	AsciiString m_08;	// +0x08 the name
};

class CommandButton
{
public:
	const ThingTemplate *rva0035B570() const;	// 0x0035B570
	char m_pad00[0x24];
	const UpgradeTemplate *m_24;	// +0x24
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const;	// 0x00409EE8
};

class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);	// 0x0031D5F8
};
extern ControlBar *TheControlBar;

class Object
{
public:
	const AsciiString &getCommandSetString() const;	// 0x00290E67
	void *rva0028BC58(int arg);			// 0x0028BC58
	bool rva002940B9(const UpgradeTemplate *upgrade);	// 0x002940B9
	int getID() const { return m_74; }
	char m_pad000[0x74];
	int m_74;		// +0x74 the ID
	char m_pad078[0x280 - 0x78];
	float m_280;		// +0x280
};

// What the wall planner fills in at +0x14 (slot 6 hands it on).
class Rva004EB902Plan
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void rva004EB902Slot6(Player *player, int arg);
	void setName(const AsciiString &name) { m_0C = name; }
	int m_04;
	int m_08;		// +0x08 the object's ID
	AsciiString m_0C;	// +0x0C the upgrade's name
	char m_pad10[0x2C - 0x10];
	unsigned m_2C;		// +0x2C the cost
	const CommandButton *m_30;	// +0x30 the button
};

class AIWall
{
public:
	WallPositionValue calcGatePosition();	// 0x004EAFBD: WB names calcGatePosition; hidden value result
	void buildGate();
private:
	void *unknown00;
	WallPositionOrderView *selected04;
	_STL::vector<WallPositionOrderView *> orders08;
	Rva004EB902Plan *m_14;	// +0x14
	Player *m_18;		// +0x18
};

void AIWall::buildGate()
{
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&calcGatePosition(), 25.0f, 0,
		Rva0026119DFilter().link(&Rva00261409Filter(m_18, true, 2)), 1);
	Object *other;
	while ((other = hits.next()) != 0) {
		const CommandSet *set = TheControlBar->findCommandSet(other->getCommandSetString());
		if (!set)
			continue;
		if (other->m_280 != -1.0f)
			continue;
		if (!other->rva0028BC58(0))
			continue;
		for (int i = 0; i < 32; ++i) {
			const CommandButton *button = set->getCommandButton(i);
			if (!button)
				continue;
			const UpgradeTemplate *upgrade = button->m_24;
			if (!upgrade)
				continue;
			const ThingTemplate *tmpl = button->rva0035B570();
			if (!tmpl || !(tmpl->m_120 & 0x800))
				continue;
			if (other->rva002940B9(upgrade)) {
				m_14->m_2C = upgrade->rva0026EF50(m_18, other);
				m_14->m_08 = other->getID();
				m_14->m_30 = button;
				m_14->setName(upgrade->getName());
				m_14->rva004EB902Slot6(m_18, 0);
				return;
			}
		}
	}
}

// Native4EAFBD..4EB092 chooses the adjacent order, randomizing only an
// interior start key (full retail filename, line560), then returns the mean
// of both virtual slot13 positions. STLport's real size/index accessors are
// required for the observed repeated reads and virtual-call register flow.
WallPositionValue AIWall::calcGatePosition()
{
    unsigned startIndex = selected04->getKey();
    WallPositionValue position = selected04->position();
    unsigned otherIndex;
    if (startIndex == 0)
        otherIndex = 1;
    else if (startIndex == orders08.size() - 1)
        otherIndex = orders08.size() - 2;
    else
        otherIndex = GetGameLogicRandomValueReal(0.0f, 1.0f,
            "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIWallBuilder\\AIWall.cpp", 560) > 0.5f
            ? startIndex + 1 : startIndex - 1;
    position += orders08[otherIndex]->position();
    position *= 0.5f;
    return position;
}
