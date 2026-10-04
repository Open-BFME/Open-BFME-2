// cl: /O1 /DNDEBUG /MD
//
// ?deselectObject@GameLogic@@QAEXPAVObject@@IH@Z retail 0x0023C9F8, 171 bytes.
// Zero Hour GameLogic::deselectObject (no CRC log) with one BFME 2 addition:
// after each player the object gets 0x00290496 (unnamed: when that player
// controls it, clears flag +0x121 bit 2 and notifies its contain) - called
// whether or not a group was made. Player::getCurrentSelectionAsAIGroup is
// 0x002AA164 (forwards to the +0x730 selection), setCurrentlySelectedAIGroup
// 0x002ACC53; TheAI->destroyGroup is the rowed AI::rva002FE712;
// InGameUI::deselectDrawable is InGameUI slot 67 (0x10C).

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
	Drawable *getDrawable() const;
	void rva00290496(Player *player);
};

class Player
{
public:
	void getCurrentSelectionAsAIGroup(AIGroup *group);
	void setCurrentlySelectedAIGroup(AIGroup *group);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(Int &mask);
};

class AIGroup
{
public:
	Bool remove(Object *obj);
};

class AI
{
public:
	AIGroup *createGroup(void);
	void rva002FE712(AIGroup *group); // destroyGroup
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
	virtual void s64(); virtual void s65(); virtual void s66();
};

class InGameUI : public InGameUISlots
{
public:
	virtual void deselectDrawable(Drawable *draw); // slot 67
};

extern PlayerList *ThePlayerList;
extern AI *TheAI;
extern InGameUI *TheInGameUI;

class GameLogic
{
public:
	void deselectObject(Object *obj, PlayerMaskType playerMask, Bool affectClient);
};

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
				TheAI->rva002FE712(group);
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
