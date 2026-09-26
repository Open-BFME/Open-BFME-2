// cl: /O1 /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ??0ProductionUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x0049E03A 258B
// ProductionUpdate behavior ctor over rowed UpdateModule base 0x253390 with two
// extra interface bases at +0x20/+0x24 (implicit vtables give early c513f0/
// c1c780 plus real five before members, Bezier double-store shape with members
// present so body stores cannot precede member ctors). Doors array at +0x3c
// (4x0x10 Rva0029BC80 zeroing ctor via rowed vector_constructor_iterator
// 0x1423), Rva members at +0x7c/+0xc8 via rowed memset ctor 0x42526, list<int>
// at +0x124 via rowed List_base 0x4EC36C, vector<BfmeE16> at +0x130 via rowed
// Vector_base 0x211E58 (16B stand-in, no erase so size unproven), trivial
// zeros/ones in init-list in declaration order (0 via ebx, 1 via edi juggled
// once and preserved callee-saved across member ctors), redundant doors zero
// loop in body (BFME1 donor for-loop kept after adding ctors, push-4/pop-ecx
// size idiom with +0x13c store hoisted between push and pop). No setWakeFrame
// (donor has none). Evidence: pin name, friend factory 0x24E87E news 0x140,
// BFME1 donor ProductionUpdate.cpp:197 (queue NULLs, uniqueID 1, doors loop,
// clear/setFlags, flagsDirty FALSE).
#include <list>
#include <vector>

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

class Thing;
class ModuleData;

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	void *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class Rva0049E03AIface20
{
public:
	Rva0049E03AIface20() {}
	virtual void rva0049E03ASlot20() = 0;
};

class Rva0049E03AIface24
{
public:
	Rva0049E03AIface24() {}
	virtual void rva0049E03ASlot24() = 0;
};

class Rva0029BC80
{
public:
	Rva0029BC80();
	int m_at00;
	int m_at04;
	int m_at08;
	unsigned char m_at0C;
};

class Rva0042526Member
{
public:
	Rva0042526Member();
private:
	unsigned char m_pad[0x4C];
};

class ProductionUpdate : public UpdateModule, public Rva0049E03AIface20, public Rva0049E03AIface24
{
public:
	ProductionUpdate(Thing *thing, const ModuleData *moduleData);

private:
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	Rva0029BC80 m_doors[4];
	Rva0042526Member m_7C;
	Rva0042526Member m_C8;
	unsigned char m_114;
	unsigned char m_pad115[3];
	int m_118;
	unsigned char m_11C;
	unsigned char m_11D;
	unsigned char m_pad11E[2];
	int m_120;
	_STL::list<int> m_list124;
	int m_128;
	int m_12C;
	_STL::vector<BfmeE16> m_vec130;
	unsigned char m_13C;
};

ProductionUpdate::ProductionUpdate(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData),
	m_28(0),
	m_2C(0),
	m_30(1),
	m_34(0),
	m_38(0),
	m_114(0),
	m_118(0),
	m_11C(0),
	m_11D(0),
	m_120(0),
	m_128(0),
	m_12C(1),
	m_13C(0)
{
	for (int i = 0; i < 4; ++i)
	{
		m_doors[i].m_at00 = 0;
		m_doors[i].m_at04 = 0;
		m_doors[i].m_at08 = 0;
		m_doors[i].m_at0C = 0;
	}
}
