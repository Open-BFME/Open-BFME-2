// ?update@DamageFieldUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.6 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// ?update@DamageFieldUpdate@@UAE?AW4UpdateSleepTime@@XZ
// Retail 0x00491316..0x0049157D (615 bytes). BANKED ROUGH DRAFT (~0.6):
// semantics and callees are mapped, codegen is not converged (587 vs 615
// bytes). Open points:
//  - the four partition filters: retail constructs them in order (EH states
//    0..3), links them extra.link(alive.link(notMe.link(&relationship))) and
//    restores their base vftables right after iterateObjectsInRange, i.e.
//    before the two local lists are built; named locals (this draft) live too
//    long and an inline helper is refused by cl (EH), so they are probably
//    temporaries of the call expression in the original;
//  - the zero register (retail keeps ebx = 0 for the null tests and pushes);
//  - the list views: retail's local lists are the placeholder
//    Rva0029FB3BMember (ctor pin 0x0029FB3B, insert pin 0x002A1316, dtor pin
//    0x00268902); the member list at +0x2C goes through the push_back pin
//    0x002A1B6F (BridgeBehaviorObjectIDList) and list<BfmePod12>::remove
//    0x002ABFC3; finds use the list<int> find row 0x0029B694.
//
// DamageFieldUpdate::update (UpdateModuleInterface slot at vtable entry
// 0x0084D964, this = module + 0x10): with module data and an object, an
// unmet required upgrade (+0x18, findUpgrade / Object 0x00290D2B) sleeps
// none; otherwise gathers the objects within data +0x10 of the object
// through the relationship (+0x14 spec, controlling player) / not-self /
// alive / 0x00BFBC90 filters, fires (rowed 0x004911AE) at and remembers
// every new one in +0x2C, forgets the ones no longer in range, then returns
// FireWeaponUpdate's rowed update 0x0048BA3E.
#include "ascii_string.h"

typedef float Real;
typedef int Int;

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
enum ObjectID { INVALID_ID = 0 };

struct Coord3D { Real x, y, z; };

class Player;
class UpgradeTemplate;
class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;

class Object
{
public:
	Player *getControllingPlayer() const;
	bool rva00290D2B(const UpgradeTemplate *upgrade) const;	// has the upgrade
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }
	unsigned char m_pad00[0x38];
	Coord3D m_pos;			// +0x38
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id;			// +0x74
};

// Partition filters: vptr, +0x04 chain link, then each filter's members.
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};
class Rva00BCECF0Filter : public Rva000421C8
{
public:
	Rva00BCECF0Filter(const void *spec, Player *player, bool flag) : m_spec(spec), m_player(player), m_flag(flag) {}
	virtual bool allow(Object *obj);
	const void *m_spec;
	Player *m_player;
	bool m_flag;
};
class Rva00BF91BCFilter : public Rva000421C8
{
public:
	Rva00BF91BCFilter(Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	Object *m_obj;
};
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};
class Rva00BFBC90Filter : public Rva000421C8
{
public:
	Rva00BFBC90Filter(Object *obj, Int mode, bool flag) : m_obj(obj), m_mode(mode), m_flag(flag) {}
	virtual bool allow(Object *obj);
	Object *m_obj;
	Int m_mode;
	bool m_flag;
};

struct BfmeWideResult
{
	Object *next() throw();		// 0x00045623
	void *m_value;
	~BfmeWideResult();		// 0x0004AA28
};
class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc, Rva000421C8 *filters, int order);
};
extern PartitionManager *ThePartitionManager;

// list<int> views (STLport node: next, prev, value).
struct IDNode { IDNode *m_next; IDNode *m_prev; int m_value; };
namespace _STL
{
template <class T> struct _Nonconst_traits;
template <class T, class Traits> struct _List_iterator
{
	_List_iterator(IDNode *n) : m_node(n) {}
	IDNode *m_node;
};
template <class It, class T> It find(It first, It last, const T &value);
}
typedef _STL::_List_iterator<int, _STL::_Nonconst_traits<int> > IDIter;
template IDIter _STL::find<IDIter, int>(IDIter, IDIter, const int &);

struct Rva0029FB3BAlloc { Rva0029FB3BAlloc() {} ~Rva0029FB3BAlloc() {} };
struct Rva0029FB3BIter { IDNode *m_node; };
class Rva0029FB3BMember
{
public:
	Rva0029FB3BMember(const Rva0029FB3BAlloc &alloc);
	~Rva0029FB3BMember();
	Rva0029FB3BIter insert(Rva0029FB3BIter pos, const ObjectID &id);
	IDIter begin() { return IDIter(m_node->m_next); }
	IDIter end() { return IDIter(m_node); }
	__forceinline void push_back(ObjectID id) { Rva0029FB3BIter e; e.m_node = m_node; insert(e, id); }
	IDNode *m_node;
};
class BridgeBehaviorObjectIDList { public: void push_back(const ObjectID &id); };
struct BfmePod12 { int v[3]; };
namespace _STL
{
template <class T> class allocator;
template <class T, class A> class list { public: void remove(const T &value); };
}

struct DamageFieldUpdateModuleData
{
	unsigned char m_pad00[0x10];
	Int m_radius;			// +0x10
	unsigned char m_filterSpec[4];	// +0x14
	AsciiString m_requiredUpgrade;	// +0x18
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	const DamageFieldUpdateModuleData *m_moduleData;	// +0x04
	Object *m_object;					// +0x08
};
class BehaviorModuleInterface { public: virtual void behaviorSlot(); };
class UpdateModuleInterface { public: virtual UpdateSleepTime update() = 0; };
class UpdateModule : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	int m_14, m_18, m_1c;
};
class FireWeaponUpdate : public UpdateModule
{
protected:
	UpdateSleepTime rva0048BA3E();
	void *m_20, *m_24, *m_28;
};
class DamageFieldUpdate : public FireWeaponUpdate
{
public:
	virtual UpdateSleepTime update();
	void rva004911AE(Object *other);
private:
	IDNode *m_victims;	// +0x2C
};

UpdateSleepTime DamageFieldUpdate::update()
{
	const DamageFieldUpdateModuleData *data = m_moduleData;
	Object *me = m_object;
	if (data && me)
	{
		if (data->m_requiredUpgrade != AsciiString::TheEmptyString)
		{
			const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(data->m_requiredUpgrade);
			if (upgrade && !me->rva00290D2B(upgrade))
				return UPDATE_SLEEP_NONE;
		}

		Player *player = me->getControllingPlayer();
		Rva00BCECF0Filter relationship(data->m_filterSpec, player, true);
		Rva00BF91BCFilter notMe(me);
		Rva0026119DFilter alive;
		Rva00BFBC90Filter extra(me, 1, false);
		BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(me->getPosition(), (Real)data->m_radius, 0,
			extra.link(alive.link(notMe.link(&relationship))), 0);

		Rva0029FB3BMember inRange((Rva0029FB3BAlloc()));
		Rva0029FB3BMember gone((Rva0029FB3BAlloc()));
		IDIter victimsEnd(m_victims);
		for (Object *other = iter.next(); other; other = iter.next())
		{
			inRange.push_back(other->getID());
			IDIter end(m_victims);
			if (_STL::find(IDIter(m_victims->m_next), end, (int)other->getID()).m_node == end.m_node)
			{
				rva004911AE(other);
				((BridgeBehaviorObjectIDList *)&m_victims)->push_back(other->getID());
			}
		}
		for (IDNode *node = m_victims->m_next; node != m_victims; node = node->m_next)
		{
			IDIter end = inRange.end();
			if (_STL::find(inRange.begin(), end, node->m_value).m_node == end.m_node)
				gone.push_back((ObjectID)node->m_value);
		}
		for (IDNode *g = gone.m_node->m_next; g != gone.m_node; g = g->m_next)
		{
			BfmePod12 value;
			value.v[0] = g->m_value;
			((_STL::list<BfmePod12, _STL::allocator<BfmePod12> > *)&m_victims)->remove(value);
		}
	}
	return FireWeaponUpdate::rva0048BA3E();
}
