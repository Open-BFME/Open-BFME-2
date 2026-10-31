// cl: /DNDEBUG /MD
//
// ?deselectObject@GameLogic@@QAEXPAVObject@@IH@Z retail 0x0023C9F8, 171 bytes.
// Zero Hour GameLogic::deselectObject (no CRC log) with one BFME 2 addition:
// after each player the object gets 0x00290496 (unnamed: when that player
// controls it, clears flag +0x121 bit 2 and notifies its contain) - called
// whether or not a group was made. Player::getCurrentSelectionAsAIGroup is
// 0x002AA164 (forwards to the +0x730 selection), setCurrentlySelectedAIGroup
// 0x002ACC53; TheAI->destroyGroup is the rowed AI::destroyGroup;
// InGameUI::deselectDrawable is InGameUI slot 67 (0x10C).
//
// ?selectObject@GameLogic@@QAEXPAVObject@@_NI1@Z retail 0x0023C924, 212
// bytes, directly before it: Zero Hour GameLogic::selectObject (no CRC log)
// with two BFME 2 additions per player: when the player controls the object
// the first non-null 0x0028BD3A behavior interface gets its slot 1, then the
// object gets 0x0029041B (the select twin of 0x00290496). Object's
// isSelectable is 0x00292FAC, addAIGroupToCurrentSelection 0x002ACCA3 and
// InGameUI::selectDrawable slot 66 (0x108).

#include <stddef.h>

typedef bool Bool;
typedef int Int;
typedef unsigned int PlayerMaskType;

#include "../../Common/GameLogicObjectLookupView.h"
#include "../../Common/Thing/thing.h"
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ObjectStatusTypes { OBJECT_STATUS_0x37 = 0x37 };
class Module;
class Drawable;
class Player;
class AIGroup;
class Pathfinder;
class Rva005CB260;
class SystemBase
{
public:
	virtual ~SystemBase();
private:
	char m_pad[8];
};

class Object : public Thing, public Snapshot
{
public:
	void rva0028ACEE(int a, int b);
protected: Module *findModule(NameKeyType) const;
public: Module *lookupModule(NameKeyType key) const {return findModule(key);}
	bool isMassSelectable() const;
	Drawable *getDrawable() const;
	Player *getControllingPlayer() const;
	void *rva0028BD3A() const;
	void rva0029041B(Player *player);
	void rva00290496(Player *player);
	void friend_bindToDrawable( Drawable *draw );
	void rva0028B31A(int val);
	bool testStatus(ObjectStatusTypes status) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	Object *getNextObject() const { return m_next; }

	char m_pad64[0x74 - 0x64];
	ObjectID m_id; // +0x74
	char m_pad78[0x8C - 0x78];
	Object *m_next; // +0x8C
};

class Rva0028BD3AInterface
{
public:
	virtual void v00();
	virtual void v01();
};

class Rva0039B795
{
public:
	void rva0039B795(int delta);
	void rva0039B7CB(int delta);
	void rva0039B7E3(int delta);
};
class Rva0039B7AD
{
public:
	void rva0039B7AD(int delta);
};
class Rva003B0D7C
{
public:
	unsigned int withdraw(unsigned int amount, Rva0039B795 *arg2, bool flag);
	void rva003B0D7C(int amount, Rva0039B7AD *arg2, bool flag);
public:
	char m_pad00[4];
	unsigned int m_val04;
	int m_val08;
};
class Player
{
public:
	void onStructureCreated(Object*,Object*);
	void onUnitCreated(Object*,Object*);
	void onStructureConstructionComplete(Object*,Object*,bool);
	void getCurrentSelectionAsAIGroup(AIGroup *group);
	void setCurrentlySelectedAIGroup(AIGroup *group);
	void addAIGroupToCurrentSelection(AIGroup *group);

	char m_pad[0x54];
	int m_playerIndex; // +0x54
	char m_pad58[0x90 - 0x58];
	Rva003B0D7C m_money; // +0x90
	char m_pad9C[0x2EC - 0x9C];
	Team *m_team; // +0x2EC
	char pad2F0[0x3AC-0x2F0];
	int livingId; // +0x3AC
	char m_pad3B0[0x3BC - 0x3B0];
	char m_track[0x14]; // +0x3BC
};

class PlayerList : public SystemBase, public Snapshot
{
public:
	Player *Rva002A7A6F(int index);
	Player *getEachPlayerFromMask(int &mask);
	Player *getNthPlayer(int i);
};

class AIGroup
{
public:
	void add(Object *obj);
	Bool remove(Object *obj);
};

class AI : public SystemBase, public Snapshot
{
public:
	AIGroup *createGroup(void);
	void destroyGroup(AIGroup *group); // destroyGroup
	Pathfinder *m_pf; // +0x10
};

class InGameUISlots
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65();
};

class InGameUI : public InGameUISlots
{
public:
	Rva005CB260 *rva000CF155();
	virtual void selectDrawable(Drawable *draw); // slot 66
	virtual void deselectDrawable(Drawable *draw); // slot 67
};

extern PlayerList *ThePlayerList;
extern AI *TheAI;
extern InGameUI *TheInGameUI;

void GameLogic::selectObject(Object *obj, Bool createNewSelection, PlayerMaskType playerMask, Bool affectClient)
{
	if (!obj) {
		return;
	}

	if (!obj->isMassSelectable() && !createNewSelection) {
		return;
	}

	while (playerMask) {
		Player *player = ThePlayerList->getEachPlayerFromMask((Int &)playerMask);
		if (!player) {
			return;
		}

		AIGroup *group = TheAI->createGroup();
		group->add(obj);

		if (createNewSelection) {
			player->setCurrentlySelectedAIGroup(group);
		} else {
			player->addAIGroupToCurrentSelection(group);
		}

		TheAI->destroyGroup(group);

		if (affectClient) {
			Drawable *draw = obj->getDrawable();
			if (draw) {
				TheInGameUI->selectDrawable(draw);
			}
		}

		if (player == obj->getControllingPlayer()) {
			Rva0028BD3AInterface *iface = (Rva0028BD3AInterface *)obj->rva0028BD3A();
			if (iface) {
				iface->v01();
			}
		}

		obj->rva0029041B(player);
	}
}

void GameLogic::deselectObject(Object *obj, PlayerMaskType playerMask, Bool affectClient)
{
	if (!obj) {
		return;
	}

	while (playerMask) {
		Player *player = ThePlayerList->getEachPlayerFromMask((Int &)playerMask);
		if (!player) {
			return;
		}

		AIGroup *group = NULL;
		group = TheAI->createGroup();
		player->getCurrentSelectionAsAIGroup(group);

		Bool deleted = false;
		Bool actuallyRemoved = false;

		if (group) {
			deleted = group->remove(obj);
			actuallyRemoved = true;
		}

		if (actuallyRemoved) {
			if (!deleted) {
				player->setCurrentlySelectedAIGroup(group);
				TheAI->destroyGroup(group);
			} else {
				player->setCurrentlySelectedAIGroup(NULL);
			}

			if (affectClient) {
				Drawable *draw = obj->getDrawable();
				if (draw) {
					TheInGameUI->deselectDrawable(draw);
				}
			}
		}

		obj->rva00290496(player);
	}
}
