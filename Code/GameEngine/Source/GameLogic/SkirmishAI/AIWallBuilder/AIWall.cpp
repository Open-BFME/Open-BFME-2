// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// AIWall.cpp (the unit 0x004EAFBD's asserts name). The wall planner class is
// not established, hence the address name after that asserting member.
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

struct Coord3D
{
	float x;
	float y;
	float z;
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

class Rva004EAFBD
{
public:
	Coord3D rva004EAFBD();	// 0x004EAFBD (asserts in AIWall.cpp)
	void rva004EB902();
private:
	char m_pad00[0x14];
	Rva004EB902Plan *m_14;	// +0x14
	Player *m_18;		// +0x18
};

void Rva004EAFBD::rva004EB902()
{
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&rva004EAFBD(), 25.0f, 0,
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
