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
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
// Use the same witnessed retail allocator cleanup as the matched builder.
namespace _STL { void __cdecl free(void *); }
#define free _STL::free
#include <vector>
#undef free
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Object;
class Player {
public:
    void rva002AF614(void *);
    unsigned char unknown00[0x54];
    int index54;
};

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
    WallPositionValue(const Coord3D &other) {
        x=other.x; y=other.y; z=other.z;
    }
    WallPositionValue(const WallPositionValue &other) {
        x=other.x; y=other.y; z=other.z;
    }
    WallPositionValue &operator+=(const WallPositionValue &other) {
        x+=other.x; y+=other.y; z+=other.z; return *this;
    }
    WallPositionValue &operator-=(const WallPositionValue &other) {
        x-=other.x; y-=other.y; z-=other.z; return *this;
    }
    float squaredLength() const { return x*x + y*y + z*z; }
    WallPositionValue &operator*=(float scale) {
        x=x*scale; y=y*scale; z=z*scale; return *this;
    }
};
class WallPositionOrderView {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(Player *, int); virtual void slot07(int); virtual void slot08();
    virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12();
    virtual WallPositionValue position();
    unsigned char unknown04[0x8];
    AsciiString name0c;
    int state10;
    unsigned char unknown14[0x10];
    ObjectID produced24;
    unsigned char unknown28[0x24];
    int startNode4c;
    unsigned key50;
    unsigned getKey() const { return key50; }
    int getState() const { return state10; }
    void setName(const AsciiString &name) { name0c = name; }
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
    Player *getControllingPlayer() const;
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

class Rva00506FE9Hit { public: void rva0055ADBA(void *); };

// Existing owned predicate4E9378 tests order state10 for 2 or 3.
class Rva004E9378 { public: bool rva004E9378(); };
// Existing pin5975C0: complete native23B caller checks helper5973D8's bool,
// then dispatches slot7(2); member receiver and no stack arguments are proved.
class Rva005975C0 { public: void rva005975C0(); };

class Rva004EAC8C { public: void rva004EAC8C(float); };
// Matched constructor5970ED and complete activate body establish allocation44
// and the timer at04. This allocation view declares the existing constructor
// without defining a private vtable or guessing unobserved members.
class Rva005970ED {
public:
    Rva005970ED();
    unsigned char unknown00[4];
    float delay04;
    unsigned char unknown08[0x44-8];
};

// The callback's native stride8 and WB two-word record constructor prove
// player-index/count storage. Reuse the established structural BfmeE8
// specialization; this does not assert the original record type spelling.
struct BfmeE8 {
    int a, b;
    // Retail initializes count; the index is assigned before any read.
    // WB137B560's redundant default index(-1) store is not in this body.
    BfmeE8() : b(0) {}
    void setPlayerIndex(int index) { a = index; }
};
namespace _STL {
template <> void vector<BfmeE8, allocator<BfmeE8> >::push_back(const BfmeE8 &);
}

class AIWall
{
public:
	WallPositionValue calcGatePosition();	// 0x004EAFBD: WB names calcGatePosition; hidden value result
	void buildGate();
	void updateState(bool left);
	void update();
	void activate(void *owner, float delay, const void *orderName);
	bool rva004EB7CC(void *owner);
    static void __cdecl informInstanceOnTriggerEntered(Object *, void *, bool);
private:
	void *unknown00;
	WallPositionOrderView *selected04;
	_STL::vector<WallPositionOrderView *> orders08;
	Rva004EB902Plan *m_14;	// +0x14
	Player *m_18;		// +0x18
	unsigned char unknown1c[0x0c];
    _STL::vector<BfmeE8> triggerCounts28;
	int state34, index38, state3c, index40;
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

// Native4EB405..4EB51C and named WB137BFD0/988 establish both directional
// state machines, the current/completed order checks and the next-node handoff.
// Native object offsets (+0x74 ID and +0x280 completion) differ from the WB
// layout and are proved by the complete target body. Only accessed order fields
// and virtual slots6/7 are specified; no vtable definition is emitted.
void AIWall::updateState(bool left)
{
    int &state = left ? state34 : state3c;
    int &index = left ? index38 : index40;
    switch (state) {
    case 1:
        if (selected04->getState() == 1)
            state = 2;
        else if (selected04->getState() == 3)
            state = 4;
        break;
    case 2: {
        WallPositionOrderView *current = index < 0 ? selected04 : orders08[index];
        if (current->getState() == 3)
            state = 4;
        else if (current->getState() != 0) {
            Object *built = TheGameLogic->findObjectByID(current->produced24);
            if (built) {
                if (built->m_280 == -1.0f) {
                    current->slot07(2);
                    if (left) --index; else ++index;
                    if (index >= 0 && (unsigned)index < orders08.size()) {
                        WallPositionOrderView *next = orders08[index];
                        next->startNode4c = built->getID();
                        next->slot06(m_18, 0);
                    } else {
                        state = 4;
                    }
                }
            } else {
                reinterpret_cast<Rva00506FE9Hit *>(current)->rva0055ADBA(m_18);
                current->slot06(m_18, 0);
            }
        }
        break;
    }
    }
}

// Named WB137BCE0/312 and complete native4EBA96..4EBAF7 prove the two
// directional updates, unsigned endpoint comparisons and plan dispatch.
// The native compiler calls the already-owned state predicate out of line.
void AIWall::update()
{
    updateState(true);
    updateState(false);
    if (m_14->m_08 == 0 &&
        ((unsigned)index38 < selected04->getKey() - 1 || state34 == 4) &&
        ((unsigned)index40 > selected04->getKey() + 1 || state3c == 4))
        buildGate();
    Rva004EB902Plan *plan = m_14;
    if (plan->m_08 != 0 &&
        !reinterpret_cast<Rva004E9378 *>(plan)->rva004E9378())
        reinterpret_cast<Rva005975C0 *>(plan)->rva005975C0();
}

// Named WB137BB30/420 and complete native4EAF18..4EAFBD prove owner18,
// state34/3C initialization, order float/name updates, slot6 registration,
// the owned timer constructor and the delay-plus-ten store. Opaque argument
// spellings retain the independently admitted caller ABI; name is a canonical
// one-word string reference, not a position argument.
void AIWall::activate(void *owner, float delay, const void *orderName)
{
    m_18 = static_cast<Player *>(owner);
    state34 = 1;
    state3c = 1;
    reinterpret_cast<Rva004EAC8C *>(this)->rva004EAC8C(delay);
    const AsciiString &name = *static_cast<const AsciiString *>(orderName);
    selected04->setName(name);
    _STL::vector<WallPositionOrderView *>::iterator end = orders08.end();
    for (_STL::vector<WallPositionOrderView *>::iterator p = orders08.begin(); p != end; ++p)
        (*p)->setName(name);
    selected04->slot06(m_18, 0);
    Rva005970ED *plan = new Rva005970ED;
    m_14 = reinterpret_cast<Rva004EB902Plan *>(plan);
    plan->delay04 = delay + 10.0f;
}

// Full native4EB7CC..4EB902 and WB137BE20/419 establish a bool predicate
// with one owner argument. Owned Player2AF614 and its callback2AF5EF prove
// vector<Coord3D> input (twelve-byte positions); canonical storage replaces
// the older bank's mismatched sixteen-byte element reinterpretation.
// Every order must be within squared distance2250000 of some supplied point.
// The native sum order is z-square plus y-square plus x-square; all points
// are visited even after a nearby point is found. Original method name unknown.
bool AIWall::rva004EB7CC(void *owner)
{
    _STL::vector<Coord3D> points;
    static_cast<Player *>(owner)->rva002AF614(&points);
    if (points.empty())
        return false;
    _STL::vector<WallPositionOrderView *>::iterator end = orders08.end();
    for (_STL::vector<WallPositionOrderView *>::iterator order = orders08.begin(); order != end; ++order) {
        bool far = true;
        _STL::vector<Coord3D>::iterator pointEnd = points.end();
        for (_STL::vector<Coord3D>::iterator point = points.begin(); point != pointEnd; ++point) {
            WallPositionValue local(*point);
            local -= (*order)->position();
            if (local.squaredLength() < 2250000.0f)
                far = false;
        }
        if (far)
            return false;
    }
    return true;
}

// WB137C410 names this static callback and its AIWall.cpp assertion329;
// native4EBAF7..4EBB58 proves cdecl Object/opaque-wall/bool arguments.
// Getter28AFA9 and player word54 identify each controlling player's counter.
void __cdecl AIWall::informInstanceOnTriggerEntered(Object *object, void *context, bool entered)
{
    AIWall *wall = static_cast<AIWall *>(context);
    if (entered) {
        BfmeE8 *found = 0;
        _STL::vector<BfmeE8>::iterator end = wall->triggerCounts28.end();
        for (_STL::vector<BfmeE8>::iterator entry = wall->triggerCounts28.begin(); entry != end; ++entry) {
            if (entry->a == object->getControllingPlayer()->index54) {
                found = entry;
                break;
            }
        }
        if (!found) {
            BfmeE8 entry;
            entry.setPlayerIndex(object->getControllingPlayer()->index54);
            wall->triggerCounts28.push_back(entry);
            found = &wall->triggerCounts28[wall->triggerCounts28.size()-1];
        }
        ++found->b;
    }
}
