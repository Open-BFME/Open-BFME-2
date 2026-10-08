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

class Drawable;
class Player;
class AIGroup;

class Object
{
public:
	Bool rva00292FAC() const;
	Drawable *getDrawable() const;
	Player *getControllingPlayer() const;
	void *rva0028BD3A() const;
	void rva0029041B(Player *player);
	void rva00290496(Player *player);
};

class Rva0028BD3AInterface
{
public:
	virtual void v00();
	virtual void v01();
};

class Player
{
public:
	void getCurrentSelectionAsAIGroup(AIGroup *group);
	void setCurrentlySelectedAIGroup(AIGroup *group);
	void rva002ACCA3(AIGroup *group);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(Int &mask);
};

class AIGroup
{
public:
	void add(Object *obj);
	Bool remove(Object *obj);
};

class AI
{
public:
	AIGroup *createGroup(void);
	void destroyGroup(AIGroup *group); // destroyGroup
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
	virtual void selectDrawable(Drawable *draw); // slot 66
	virtual void deselectDrawable(Drawable *draw); // slot 67
};

extern PlayerList *ThePlayerList;
extern AI *TheAI;
extern InGameUI *TheInGameUI;

class GameLogic
{
public:
	void selectObject(Object *obj, Bool createNewSelection, PlayerMaskType playerMask, Bool affectClient);
	void deselectObject(Object *obj, PlayerMaskType playerMask, Bool affectClient);
};

void GameLogic::selectObject(Object *obj, Bool createNewSelection, PlayerMaskType playerMask, Bool affectClient)
{
	if (!obj) {
		return;
	}

	if (!obj->rva00292FAC() && !createNewSelection) {
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
			player->rva002ACCA3(group);
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
