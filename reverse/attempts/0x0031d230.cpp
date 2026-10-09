// ?rva0031D230@ControlBar@@QAEXXZ
// partial score=0.95 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva0031D230@ControlBar@@QAEXXZ -- retail 0x0031D230..0x0031D5F8 (968 bytes).
// ControlBar context evaluation (Zero Hour ControlBar::evaluateContextUI): clears
// the dirty byte at +0x28 / refreshes the purchase science window / reads the
// selection through TheInGameUI slots 0x118 0x124 0x130 and the controllable
// check 0x0029C752 / uncontrolled selections pick the beacon (5) structure
// inventory (4) or 3 contexts from the contain interface at Object +0x250
// (slots 0x70 0xD8 0xE0 0x4C) / multi-select through TheGameClient slot 0x40 /
// then the object context: status 0x13 / OCLUpdate module key / kind bit 150
// with 0x0028C15E / kind 0xDB / status 2 with the 0x0028BD17 interface slots
// 0x38 and 0x2C / garrison inventory (2) / OCL timer (10) / command (1) /
// beacon (5) / none (0). Identity: Zero Hour evaluateContextUI and the
// WorldBuilder twin at 0x00C2C270 share this call graph and order; the beacon
// test compares PlayerTemplate +0x17C with the template name at +0x64.
#include "ascii_string.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
enum KindOfType { KINDOF_INVALID = -1 };
enum Relationship { REL_ENEMIES = 0, REL_NEUTRAL = 1, REL_ALLIES = 2 };

class Object;
class Team;
class Module;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class PlayerTemplate
{
public:
	char pad000[0x17C];
	AsciiString m_beaconTemplate;	// +0x17C
	const AsciiString &getBeaconTemplate() const { return m_beaconTemplate; }
};

class Player
{
public:
	Relationship getRelationship(const Team *that) const;

	char pad00[0x34];
	PlayerTemplate *m_playerTemplate;	// +0x34
	const PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }
};

class PlayerList
{
public:
	char pad00[0x10];
	Player *m_local;	// +0x10
};

class ThingTemplate
{
public:
	__forceinline unsigned int isKindOf(int bit) const { return m_kindOf[bit >> 5] & (1u << (bit & 31)); }

	char pad000[0x64];
	AsciiString m_name;	// +0x64
	const AsciiString &getName() const { return m_name; }
	char pad068[0x108 - 0x68];
	unsigned int m_kindOf[7];	// +0x108
};

class ContainModuleInterface
{
public:
	virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
	virtual bool isGarrisonable() const;	// +0x10
	virtual void vf14(); virtual void vf18(); virtual void vf1C();
	virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C();
	virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3C();
	virtual void vf40(); virtual void vf44(); virtual void vf48();
	virtual const Player *getApparentControllingPlayer(const Player *observingPlayer) const;	// +0x4C
	virtual void vf50(); virtual void vf54(); virtual void vf58(); virtual void vf5C();
	virtual void vf60(); virtual void vf64(); virtual void vf68(); virtual void vf6C();
	virtual int getContainMax() const;	// +0x70
	virtual void vf74(); virtual void vf78(); virtual void vf7C();
	virtual void vf80(); virtual void vf84(); virtual void vf88(); virtual void vf8C();
	virtual void vf90(); virtual void vf94(); virtual void vf98(); virtual void vf9C();
	virtual void vfA0(); virtual void vfA4(); virtual void vfA8(); virtual void vfAC();
	virtual void vfB0(); virtual void vfB4(); virtual void vfB8(); virtual void vfBC();
	virtual void vfC0(); virtual void vfC4(); virtual void vfC8(); virtual void vfCC();
	virtual void vfD0(); virtual void vfD4();
	virtual bool vfD8() const;	// +0xD8
	virtual void vfDC();
	virtual const Player *vfE0() const;	// +0xE0
};

class Rva0028BD17Interface
{
public:
	virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
	virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C();
	virtual void vf20(); virtual void vf24(); virtual void vf28();
	virtual bool vf2C() const;	// +0x2C
	virtual void vf30(); virtual void vf34();
	virtual bool vf38() const;	// +0x38
};

class Object
{
	friend class ControlBar;

public:
	bool testStatus(ObjectStatusTypes status) const;
	Player *getControllingPlayer() const;
	bool isKindOf(KindOfType kind) const;
	bool rva0028C15E(int a1, float *value, int a3, int a4);
	void *rva0028BD17() const;
	const AsciiString *rva00290E67() const;
	bool isLocallyControlled() const;
	const ThingTemplate *getTemplate() const { return m_template; }

protected:
	Module *findModule(NameKeyType key) const;

public:
	void *m_vtbl;	// +0x00
	const ThingTemplate *m_template;	// +0x04
	char pad008[0x250 - 0x08];
	ContainModuleInterface *m_contain;	// +0x250
	char pad254[0x304 - 0x254];
	Team *m_team;	// +0x304
};

class Drawable
{
public:
	char pad000[0xFC];
	Object *m_object;	// +0xFC
};

struct DrawableListNode
{
	DrawableListNode *m_next;
	DrawableListNode *m_prev;
	Drawable *m_data;
};

struct DrawableList
{
	DrawableListNode *m_node;
	bool empty() const { return m_node->m_next == m_node; }
	Drawable *front() const { return m_node->m_next->m_data; }
};

class InGameUI
{
public:
	virtual void vf000(); virtual void vf004(); virtual void vf008(); virtual void vf00C();
	virtual void vf010(); virtual void vf014(); virtual void vf018(); virtual void vf01C();
	virtual void vf020(); virtual void vf024(); virtual void vf028(); virtual void vf02C();
	virtual void vf030(); virtual void vf034(); virtual void vf038(); virtual void vf03C();
	virtual void vf040(); virtual void vf044(); virtual void vf048(); virtual void vf04C();
	virtual void vf050(); virtual void vf054(); virtual void vf058(); virtual void vf05C();
	virtual void vf060(); virtual void vf064(); virtual void vf068(); virtual void vf06C();
	virtual void vf070(); virtual void vf074(); virtual void vf078(); virtual void vf07C();
	virtual void vf080(); virtual void vf084(); virtual void vf088(); virtual void vf08C();
	virtual void vf090(); virtual void vf094(); virtual void vf098(); virtual void vf09C();
	virtual void vf0A0(); virtual void vf0A4(); virtual void vf0A8(); virtual void vf0AC();
	virtual void vf0B0(); virtual void vf0B4(); virtual void vf0B8(); virtual void vf0BC();
	virtual void vf0C0(); virtual void vf0C4(); virtual void vf0C8(); virtual void vf0CC();
	virtual void vf0D0(); virtual void vf0D4(); virtual void vf0D8(); virtual void vf0DC();
	virtual void vf0E0(); virtual void vf0E4(); virtual void vf0E8(); virtual void vf0EC();
	virtual void vf0F0(); virtual void vf0F4(); virtual void vf0F8(); virtual void vf0FC();
	virtual void vf100(); virtual void vf104(); virtual void vf108(); virtual void vf10C();
	virtual void vf110(); virtual void vf114();
	virtual int getSelectCount();	// +0x118
	virtual void vf11C(); virtual void vf120();
	virtual const DrawableList *getAllSelectedDrawables() const;	// +0x124
	virtual void vf128(); virtual void vf12C();
	virtual int getSoloNexusSelectedDrawableID();	// +0x130

	bool areSelectedObjectsControllable() const;	// 0x0029C752
};

class GameClient
{
public:
	virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
	virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C();
	virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C();
	virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3C();
	virtual Drawable *findDrawableByID(int id);	// +0x40
};

extern InGameUI *TheInGameUI;
extern GameClient *TheGameClient;
extern PlayerList *ThePlayerList;
extern NameKeyGenerator *TheNameKeyGenerator;

int Rva0043C99AGet();

class ControlBar
{
public:
	void rva0031D230();
	void showPurchaseScience();
	void switchToContext(int context, void *draw);

	char pad00[0x28];
	bool m_UIDirty;	// +0x28
};

void ControlBar::rva0031D230()
{
	m_UIDirty = false;

	if ((unsigned char)Rva0043C99AGet())
		showPurchaseScience();

	if (TheInGameUI->getSelectCount() == 0)
	{
		switchToContext(0, 0);
		return;
	}

	const DrawableList *selectedDrawables = TheInGameUI->getAllSelectedDrawables();
	if (selectedDrawables->empty() == true)
	{
		switchToContext(0, 0);
		return;
	}

	if (!TheInGameUI->areSelectedObjectsControllable())
	{
		Drawable *draw = selectedDrawables->front();
		if (!draw)
		{
			switchToContext(0, 0);
			return;
		}
		Object *obj = draw->m_object;
		if (!obj)
		{
			switchToContext(0, 0);
			return;
		}

		if (obj->getControllingPlayer()
			&& obj->getControllingPlayer()->getPlayerTemplate()
			&& obj->getControllingPlayer()->getPlayerTemplate()->getBeaconTemplate().compare(obj->getTemplate()->getName()) == 0)
		{
			switchToContext(5, draw);
		}
		else
		{
			ContainModuleInterface *contain = obj->m_contain;
			if (contain && contain->getContainMax() > 0)
			{
				switchToContext(4, draw);
				Player *localPlayer = ThePlayerList->m_local;
				if (contain->vfD8() && contain->vfE0() == localPlayer)
				{
					switchToContext(3, draw);
					return;
				}
				const Player *otherPlayer = contain->getApparentControllingPlayer(localPlayer);
				if (!otherPlayer)
					otherPlayer = obj->getControllingPlayer();
				Player *player = ThePlayerList->m_local;
				if (!player || !otherPlayer)
				{
					switchToContext(0, 0);
					return;
				}
			}
		}
	}

	Drawable *drawToEvaluateFor = 0;
	bool multiSelect = false;
	if (TheInGameUI->getSelectCount() > 1)
	{
		drawToEvaluateFor = TheGameClient->findDrawableByID(TheInGameUI->getSoloNexusSelectedDrawableID());
		multiSelect = (drawToEvaluateFor == 0);
	}
	else
		drawToEvaluateFor = selectedDrawables->front();

	if (multiSelect)
	{
		switchToContext(7, 0);
	}
	else if (drawToEvaluateFor)
	{
		Object *obj = drawToEvaluateFor->m_object;
		if (!obj || obj->testStatus((ObjectStatusTypes)0x13)
			|| !obj->getControllingPlayer() || !obj->getControllingPlayer()->getPlayerTemplate())
		{
			switchToContext(0, 0);
			return;
		}

		static const NameKeyType key_OCLUpdate = TheNameKeyGenerator->nameToKey("OCLUpdate");
		Module *update = obj->findModule(key_OCLUpdate);

		bool emptyAmount = false;
		if (obj->getTemplate()->isKindOf(150))
		{
			float amount = 0.0f;
			if (obj->rva0028C15E(3, &amount, 0, 1))
				emptyAmount = (amount == 0.0f);
		}

		bool contextSelected = false;
		bool special = false;
		if (emptyAmount || obj->isKindOf((KindOfType)0xDB))
		{
			special = true;
		}
		else if (obj->testStatus((ObjectStatusTypes)2))
		{
			Rva0028BD17Interface *iface = (Rva0028BD17Interface *)obj->rva0028BD17();
			special = iface && (iface->vf38() || iface->vf2C());
		}
		else
		{
			Rva0028BD17Interface *iface = (Rva0028BD17Interface *)obj->rva0028BD17();
			special = iface && iface->vf2C();
		}
		if (special)
		{
			switchToContext(6, drawToEvaluateFor);
			contextSelected = true;
		}

		if (!contextSelected)
		{
			ContainModuleInterface *cmi = obj->m_contain;
			if (cmi && cmi->isGarrisonable() && ((const StringBase<char> *)obj->rva00290E67())->isEmpty())
			{
				Player *localPlayer = ThePlayerList->m_local;
				Relationship relationship = localPlayer->getRelationship(obj->m_team);
				if (obj->isLocallyControlled() == true || relationship == REL_NEUTRAL)
					switchToContext(2, drawToEvaluateFor);
			}
			else if (update)
			{
				switchToContext(10, drawToEvaluateFor);
			}
			else if (((const StringBase<char> *)obj->rva00290E67())->isEmpty() == false)
			{
				switchToContext(1, drawToEvaluateFor);
			}
			else if (obj->getControllingPlayer()
				&& obj->getControllingPlayer()->getPlayerTemplate()
				&& obj->getControllingPlayer()->getPlayerTemplate()->getBeaconTemplate().compare(obj->getTemplate()->getName()) == 0)
			{
				switchToContext(5, drawToEvaluateFor);
			}
			else
				switchToContext(0, drawToEvaluateFor);
		}
	}
	else
	{
		switchToContext(0, 0);
	}
}
