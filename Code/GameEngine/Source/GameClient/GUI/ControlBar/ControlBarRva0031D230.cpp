// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/subsystem_bfme2
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
// The selection is Zero Hour's STLport std::list<Drawable *> (DrawableList).
// stlport
typedef bool Bool;
#ifndef BFME_SUBSYSTEM_SLOTS
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "ascii_string.h"
#include <list>

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
enum KindOfType { KINDOF_INVALID = -1 };
enum Relationship { REL_ENEMIES = 0, REL_NEUTRAL = 1, REL_ALLIES = 2 };

class Object;
class Team;
class Module;

class AsciiString;
#include "../../../../Include/Common/NameKeyGenerator.h"

#include "../../../../Include/Common/PlayerTemplate.h"

#include "../../../../Include/Common/Player.h"

#include "../../../../Include/Common/PlayerList.h"

class Image;
#include "../../../../Include/Common/ThingTemplate.h"

#include "../../../../Include/GameLogic/Module/ContainModule.h"

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

struct Coord3D;
#include "../../../../Include/GameClient/Drawable.h"

class Drawable;
class UnicodeString;
typedef std::list<Drawable *> DrawableList;
class InGameUI
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void __cdecl message(UnicodeString format, ...);	// +0x40
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void notify();	// +0x110
	virtual void v69();
	virtual int getSelectCount();	// +0x118
	virtual void v71();
	virtual void v72();
	virtual const DrawableList *getAllSelectedDrawables() const;	// +0x124
	virtual void v74();
	virtual void v75();
	virtual int getSoloNexusSelectedDrawableID();	// +0x130
	bool areSelectedObjectsControllable() const;	// 0x0029C752
	char m_pad04[0x11];
	unsigned char m_15;
	unsigned char m_16;
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

#include "ControlBarMemberTypes.h"
enum CommandButtonMappedBorderType
{
    COMMAND_BUTTON_BORDER_NONE,
    COMMAND_BUTTON_BORDER_BUILD,
    COMMAND_BUTTON_BORDER_UPGRADE,
    COMMAND_BUTTON_BORDER_ACTION,
    COMMAND_BUTTON_BORDER_SYSTEM,
    COMMAND_BUTTON_BORDER_BFME5
};
enum CommandAvailability
{
	COMMAND_RESTRICTED = 0,
	COMMAND_AVAILABLE = 1,
	COMMAND_ACTIVE = 2,
	COMMAND_HIDDEN = 3,
	COMMAND_NOT_ALLOWED = 4,
	COMMAND_NOT_READY = 5,
	COMMAND_CANT_AFFORD = 6,
	COMMAND_LIMITED = 7,
	COMMAND_DONE = 8
};
class CommandButton;
class GameWindow;
class Image;
class CommandSet;
class INI;
class WindowVideoManager;
class AnimateWindowManager;
struct ICoord2D;
struct Rva0031DBFCElement;
class ControlBarSchemeManager;
class WindowLayout;
class vector;
struct PlayerAITypeEntry;
class Rva000AD6F4;
#include "../../../../Include/GameClient/ControlBar.h"

void ControlBar::rva0031D230()
{

	//
	// the UI has been "evaluated" and is now displaying the most current and correct
	// information to the player
	//
	field28 = false;

	// if our purchase science window is up, we will want to update it by repopulating it.
	if ((unsigned char)Rva0043C99AGet())
		showPurchaseScience();

	// sanity, nothing selected
	if (TheInGameUI->getSelectCount() == 0)
	{
		switchToContext(0, 0);
		return;
	}

	// get the list of drawable IDs from the in game UI
	const DrawableList *selectedDrawables = TheInGameUI->getAllSelectedDrawables();

	// sanity
	if (selectedDrawables->empty() == true)
	{
		switchToContext(0, 0);
		return;
	}

	//Make sure the selected objects are in fact, controllable! If not, then
	//we don't show any GUI commands for them!!!
	//This is used when we select enemy objects or objects on another team.
	//@todo we may want to show their portrait
	if (!TheInGameUI->areSelectedObjectsControllable())
	{
		//Also make sure the unit isn't a garrisonable neutral civ team building!
		Drawable *draw = selectedDrawables->front();

		//sanity
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
			//Check for a contain interface and a enemy relationship and reject that!
			ContainModuleInterface *contain = obj->m_contain;
			if (contain && contain->getContainMax() > 0)
			{
				switchToContext(4, draw);
				Player *localPlayer = ThePlayerList->m_local;
				if (contain && contain->slot54() && contain->slot56() == localPlayer)
				{
					switchToContext(3, draw);
					return;
				}
				const Player *otherPlayer = contain->getApparentControllingPlayer(localPlayer);
				if (!otherPlayer)
					otherPlayer = obj->getControllingPlayer();
				Player *player = ThePlayerList->m_local;
				bool playersKnown = player && otherPlayer;
				if (!playersKnown)
				{
					//Sanity.
					switchToContext(0, 0);
					return;
				}
			}
		}
	}

	//
	// when we have multiple things selected, we will only display the common commands
	// in the center command bar that can be displayed with multi-units selected
	//

	Drawable *drawToEvaluateFor = 0;
	bool multiSelect = false;
	if (TheInGameUI->getSelectCount() > 1)
	{
		// Attempt to isolate a Drawable here to evaluate
		// The need arises when selected is an AngryMob,
		// whose selection actually consists of varied units
		// but is represented in the UI as a single unit,
		// so we must isolate and evaluate only the Nexus
		drawToEvaluateFor = TheGameClient->findDrawableByID(TheInGameUI->getSoloNexusSelectedDrawableID());
		multiSelect = (drawToEvaluateFor == 0);
	}
	else // get the first and only drawble in the selection list
		drawToEvaluateFor = selectedDrawables->front();

	if (multiSelect)
	{
		switchToContext(7, 0);
	}
	else if (drawToEvaluateFor)// either we have exactly one drawable, or we have isolated one to evaluate for...
	{
		// get object
		Object *obj = drawToEvaluateFor->m_object;

		// we show no interface for objects being sold
		if (!obj || obj->testStatus((ObjectStatusTypes)0x13)
			|| !obj->getControllingPlayer() || !obj->getControllingPlayer()->getPlayerTemplate())
		{
			switchToContext(0, 0);
			return;
		}

		static const NameKeyType key_OCLUpdate = TheNameKeyGenerator->nameToKey("OCLUpdate");
		Module *update = obj->findModule(key_OCLUpdate);

		bool emptyAmount = false;
		if ((obj->getTemplate()->m_kindof[150 >> 5] & (1u << (150 & 31))))
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

		// check for a regular switch to the appropriate context
		if (!contextSelected)
		{
			ContainModuleInterface *cmi = obj->m_contain;
			if (cmi && cmi->isGarrisonable() && ((const StringBase<char> *)obj->rva00290E67())->isEmpty())
			{
				//Kris: This is a convenient section to graft an inventory commandset for
				//garrisoned troops. However, we only want to use this if we DON'T have
				//a commandset defined. If we do, then trust that the commandset will
				//handle it!

				Player *localPlayer = ThePlayerList->m_local;

				// we cannot select objects that are controlled by our enemies
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
