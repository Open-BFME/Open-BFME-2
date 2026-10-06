// ?rva00396F2C@Rva003962E7@@QAEXXZ
// partial score=0.7 date=2026-10-06
// cl: /O1 /Oy- /EHsc /MD
//
// ?rva00396F2C@Rva003962E7@@QAEXXZ @0x00396F2C 443B: Eva event for the
// owner's object, range-17 dump lane.
//
// The +0x08 Object's team (rowed Object+0x304 layout per
// EvaEventFXNuggetDoFXObj) must have a controlling player (rowed Team
// 0x0039D7CF); a Rva00395561 counter (pinned ctor 0x00395534, rowed drain
// 0x00395561) spans the rest. With a local player (PlayerList+0x10) the
// +0x38 ObjectID resolves through TheGameLogic (rowed 0x00049DC5); when
// found its module key (same static NameKey wrapper and 0xBF5CCC slot as
// Rva00395C80Check, rowed Object::findModule 0x0028B6D6) selects the event:
// the controlling player itself, an ALLIES team (rowed Player
// 0x002AD0C6), or an ENEMIES team via the +0xA0 int tree (rowed _M_find
// 0x00388F63 with range check) run the rowed 0x003962E7 tree predicate,
// then the event (module face +8/+C/+10, else 9/0xA/8) plays through the
// rowed Eva 0x001DE2DA on TheEva with the target-or-owner +0x38 position.
// /O1 keeps the frame in the shared __EH_prolog helper (0x629188).

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

enum NameKeyType
{
	NK_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern const char Rva00BF5CCC[];

struct Rva00396F2CKey
{
	NameKeyType key;
	__forceinline Rva00396F2CKey(const char *name) { key = TheNameKeyGenerator->nameToKey(name); }
};

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object;
class Player;
class Module;
class Rva003962E7;

class Team
{
public:
	Player *getControllingPlayer() const;
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

class Player
{
public:
	Relationship getRelationship(const Team *that) const;

public:
	char m_pad00[0x54];
	int m_playerIndex; // +0x54
};

class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_local; }

private:
	unsigned char m_pad[0x10];
	Player *m_local; // +0x10
};

extern PlayerList *ThePlayerList;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);

public:
	char m_pad00[0x40];
	int m_cmp40; // +0x40
};

extern GameLogic *TheGameLogic;

class Eva
{
public:
	void rva001DE2DA(int event, const Coord3D *position, int unused);

public:
	char m_pad00[0x84];
	int m_84; // +0x84
	int m_88; // +0x88
};

extern Eva *TheEva;

class Rva00395561
{
	int m_00;

public:
	Rva00395561();
	void rva00395561();
};

namespace _STL
{

template <class T1, class T2>
struct pair
{
	T1 first;
	T2 second;
	pair(const pair &);
};

template <class P>
struct _Select1st
{
};

template <class T>
struct less
{
};

template <class T>
class allocator
{
};

struct _Rb_tree_node_base
{
	bool _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};

template <class V>
struct _Rb_tree_node : public _Rb_tree_node_base
{
	V _M_value_field;
};

template <class K, class V, class KoV, class Cmp, class Al>
class _Rb_tree
{
public:
	_Rb_tree_node_base *m_header;

private:
	template <class Q>
	_Rb_tree_node<V> *_M_find(const Q &) const;
	friend class ::Rva003962E7;
};

}

typedef _STL::pair<const int, int> Rva00396F2CPair;
typedef _STL::_Rb_tree<int, Rva00396F2CPair, _STL::_Select1st<Rva00396F2CPair>, _STL::less<int>, _STL::allocator<Rva00396F2CPair> > Rva00396F2CTree;
typedef _STL::_Rb_tree_node<Rva00396F2CPair> Rva00396F2CNode;

struct Rva00396F2CFace
{
	int m_00;
	int m_04;
	int m_08; // +0x08
	int m_0C; // +0x0C
	int m_10; // +0x10
};

class Rva003962E7
{
public:
	bool rva003962E7(int key, int dummy);
	void rva00396F2C();

private:
	char m_pad00[8];
	Object *m_object08; // +0x08
	char m_pad0C[0x38 - 0x0C];
	ObjectID m_id38; // +0x38
	char m_pad3C[0xA0 - 0x3C];
	Rva00396F2CTree m_treeA0; // +0xA0
};

class Object
{
public:
	virtual ~Object();
	const Coord3D *getPosition() const { return &m_position; }
	Player *getControllingPlayer() const;
	Team *getTeam() const { return m_team; }

protected:
	Module *findModule(NameKeyType key) const;
	friend void Rva003962E7::rva00396F2C();

private:
	unsigned char m_pad04[0x38 - 4];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x304 - 0x44];
	Team *m_team; // +0x304
};

// ?rva00396F2C@Rva003962E7@@QAEXXZ
void Rva003962E7::rva00396F2C()
{
	Object *obj = m_object08;
	Team *team = obj->getTeam();
	if (team == 0)
		return;
	Player *player = team->getControllingPlayer();
	if (player == 0)
		return;
	Rva00395561 counter;
	Module *mod = 0;
	Player *local;
	Object *target;
	local = ThePlayerList->getLocalPlayer();
	if (local != 0) {
		target = TheGameLogic->findObjectByID(m_id38);
		if (target != 0) {
			static Rva00396F2CKey s_key(Rva00BF5CCC);
			mod = target->findModule(s_key.key);
		}
		if (player == local) {
			if (rva003962E7(TheEva->m_88, player->m_playerIndex)) {
				int ev = (mod != 0) ? (*(Rva00396F2CFace **)((char *)mod + 4))->m_08 : 9;
				const Coord3D *pos = (target != 0 ? target : obj)->getPosition();
				TheEva->rva001DE2DA(ev, pos, 0);
			}
		}
		else {
			Relationship rel = local->getRelationship(team);
			if (rel == ALLIES) {
				if (rva003962E7(TheEva->m_88, player->m_playerIndex)) {
					int ev = (mod != 0) ? (*(Rva00396F2CFace **)((char *)mod + 4))->m_0C : 0xA;
					const Coord3D *pos = (target != 0 ? target : obj)->getPosition();
					TheEva->rva001DE2DA(ev, pos, 0);
				}
			}
			else if (rel == ENEMIES) {
				int index = local->m_playerIndex;
				Rva00396F2CNode *found = m_treeA0._M_find(index);
				if (found != (Rva00396F2CNode *)m_treeA0.m_header) {
					int lim = TheEva->m_84 + found->_M_value_field.second;
					if (lim >= TheGameLogic->m_cmp40) {
						int ev = (mod != 0) ? (*(Rva00396F2CFace **)((char *)mod + 4))->m_10 : 8;
						const Coord3D *pos = (target != 0 ? target : obj)->getPosition();
						TheEva->rva001DE2DA(ev, pos, 0);
					}
				}
			}
		}
	}
	counter.rva00395561();
}
