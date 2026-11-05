// cl: /O1 /MD /DNDEBUG
// ?translateGameMessage@GUICommandTranslator@@UAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z @0x004314B1 1008B
// plus file-static doFireWeaponCommand @0x00431057 336B (private register convention: command ESI,
// mouse EAX; from the same TU, defined before its caller).
// Zero Hour GUICommandTranslator (GameClient/MessageStream/GUICommandTranslator.cpp), BFME2 variant.
// The vtable at VA 0x0083C960 slot 2 holds this body. BFME2 deltas read from retail: the translator
// tracks mouse-down / mouse-up positions in +0x04..+0x38 (messages 3/4/6/0xE/0x10), a drag-distance test
// (rowed 0x001EDD80 on TheMouse) decides when the click arms the command, and the 0x0A command type
// swaps which of the two click kinds applies when TheWritableGlobalData+0x5C is set.
// Message types read from retail: 0x40D/0x40E/0x40F weapon (no target/at location/at object), 0x41A beacon
// voice, 0x41E/0x41F/0x455 location + voice, 0x433/0x434 guard (rowed 0x00431362).
// Evidence: retail bytes; WB lead 0x12C5760; rowed callees 0x0030F4EA getArgument, 0x00431012 pick,
// 0x00431362 doGuardCommand, 0x004311A7 attack-move, 0x00431241 rally, 0x004312E5 beacon emit.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../../Libraries/Include/Lib/IRegion2D.h"

struct Rva001EDD80Pair
{
	int x;
	int y;
};

enum ObjectID
{
	OBJECTID_NONE = 0
};

enum GameMessageDisposition
{
	KEEP_MESSAGE = 0,
	DESTROY_MESSAGE = 1
};

union GameMessageArgumentType
{
	int integer;
	ICoord2D pixel;
	IRegion2D pixelRegion;
};

class Drawable;

#include "../../../Include/Common/MessageStream.h"


extern MessageStream *TheMessageStream;

class TacticalView
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void screenToTerrain(const ICoord2D *pixel, Coord3D *world, bool clamp);
};

extern class View *TheTacticalView;

#include "../../Common/Thing/thing.h"

class Object : public Thing
{
public:
	char m_pad00[0x74 - sizeof(Thing)];
	ObjectID m_id;
};

#include "../../../Include/GameClient/Drawable.h"

class DrawableList;
class PickAndPlayInfo;

class PickAndPlayInfo
{
public:
	PickAndPlayInfo();
	bool m_00;
	Drawable *m_04;
	int m_08;
	int *m_weaponSlot;
	int m_10;
	Coord3D m_14;
	int m_20;
};

#include "../../../Include/GameClient/CommandButton.h"

#include "../../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

#include "../../../Include/Common/GlobalData.h"

extern GlobalData *TheWritableGlobalData;

#include "../../../Include/GameClient/Mouse.h"

extern Mouse *TheMouse;

class Rva005B5440
{
public:
	void clearFlags();
};

class BfmeOwnVVD;
class LookAtTranslator; extern LookAtTranslator *TheLookAtTranslator;

class Rva0035AFE4;
Object *__cdecl Rva00431012PickObject(ICoord2D *pixel, Rva0035AFE4 *mask, int pickType);
int __cdecl doGuardCommand(void *command, int guardMode, ICoord2D *mouse);
int __cdecl doAttackMoveCommand(void *command, ICoord2D *mouse);
int __cdecl doSetRallyPointCommand(void *command, ICoord2D *mouse);
int __cdecl Rva004312E5Emit(void *command, ICoord2D *mouse);
bool __cdecl pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type type, PickAndPlayInfo *info);

static int doFireWeaponCommand(const CommandButton *command, ICoord2D *mouse)
{
	if (command == 0 || mouse == 0)
		return 1;
	if (TheInGameUI->getSelectCount() == 1)
	{
		Drawable *draw = TheInGameUI->getFirstSelectedDrawable();
		if (draw == 0 || draw->m_object == 0)
			return 1;
	}

	if (command->m_options & 0x20)
	{
		Coord3D world;
		((TacticalView *)TheTacticalView)->screenToTerrain(mouse, &world, false);
		GameMessage *msg = TheMessageStream->appendMessage(GameMessage::MSG_DO_WEAPON_AT_LOCATION);
		msg->appendIntegerArgument(command->m_weaponSlot);
		msg->appendLocationArgument(world);
		msg->appendIntegerArgument(command->m_maxShotsToFire);
		Object *target = Rva00431012PickObject(mouse, (Rva0035AFE4 *)command, 4);
		ObjectID targetID = target ? target->m_id : OBJECTID_NONE;
		msg->appendObjectIDArgument(targetID);
	}
	else if (command->m_options & 7)
	{
		int pickType = 4;
		if (command->m_options & 0x10)
			pickType |= 8;
		if (command->m_options & 0x200000)
			pickType |= 0x200;
		Object *target = Rva00431012PickObject(mouse, (Rva0035AFE4 *)command, pickType);
		if (target)
		{
			GameMessage *msg = TheMessageStream->appendMessage(GameMessage::MSG_DO_WEAPON_AT_OBJECT);
			msg->appendIntegerArgument(command->m_weaponSlot);
			msg->appendObjectIDArgument(target->m_id);
			msg->appendIntegerArgument(command->m_maxShotsToFire);
		}
	}
	else
	{
		GameMessage *msg = TheMessageStream->appendMessage(GameMessage::MSG_DO_WEAPON);
		msg->appendIntegerArgument(command->m_weaponSlot);
		msg->appendIntegerArgument(command->m_maxShotsToFire);
	}
	return 1;
}

class GUICommandTranslator
{
public:
	virtual void v00();
	virtual void v01();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
private:
	Rva001EDD80Pair m_04;
	ICoord2D m_leftMouseUpPosition;
	bool m_14;
	int m_leftMouseDownTime;
	int m_leftMouseUpTime;
	Rva001EDD80Pair m_20;
	ICoord2D m_rightMouseUpPosition;
	bool m_rightMouseDragged;
	int m_rightMouseDownTime;
	int m_rightMouseUpTime;
};

GameMessageDisposition GUICommandTranslator::translateGameMessage(const GameMessage *msg)
{
	int disp = KEEP_MESSAGE;
	switch (msg->m_type)
	{
	case 3:
	{
		ICoord2D mousePosition = msg->getArgument(0)->pixel;
		if (TheMouse->rva001EDD80(&m_04, (const Rva001EDD80Pair *)&mousePosition))
			m_14 = true;
		if (TheMouse->rva001EDD80(&m_20, (const Rva001EDD80Pair *)&mousePosition))
			m_rightMouseDragged = true;
		break;
	}
	case 4:
	{
		const GameMessageArgumentType *gameMessageArgumentType = msg->getArgument(0);
		m_04.x = gameMessageArgumentType->pixel.x;
		m_04.y = gameMessageArgumentType->pixel.y;
		m_leftMouseDownTime = msg->getArgument(2)->integer;
		m_14 = false;
		break;
	}
	case 6:
	{
		const GameMessageArgumentType *gameMessageArgumentType = msg->getArgument(0);
		m_leftMouseUpPosition.x = gameMessageArgumentType->pixel.x;
		m_leftMouseUpPosition.y = gameMessageArgumentType->pixel.y;
		m_leftMouseUpTime = msg->getArgument(2)->integer;
		break;
	}
	case 0xE:
	{
		const GameMessageArgumentType *gameMessageArgumentType = msg->getArgument(0);
		m_20.x = gameMessageArgumentType->pixel.x;
		m_20.y = gameMessageArgumentType->pixel.y;
		m_rightMouseDownTime = msg->getArgument(2)->integer;
		m_rightMouseDragged = false;
		break;
	}
	case 0x10:
	{
		const GameMessageArgumentType *gameMessageArgumentType = msg->getArgument(0);
		m_rightMouseUpPosition.x = gameMessageArgumentType->pixel.x;
		m_rightMouseUpPosition.y = gameMessageArgumentType->pixel.y;
		m_rightMouseUpTime = msg->getArgument(2)->integer;
		break;
	}
	}

	const CommandButton *command = TheInGameUI->getGUICommand();
	if (command == 0)
		return KEEP_MESSAGE;

	bool gameMessageArgumentType = (msg->m_type == 0x18 || msg->m_type == 0x17) && !m_14;
	bool rightClick = (msg->m_type == 0x1C || msg->m_type == 0x1B) && !m_rightMouseDragged;
	bool isDown = msg->m_type == 4;
	bool cancelCommand;
	bool executeCommand;
	if (command->m_command == 0xA && TheWritableGlobalData->field005C)
	{
		cancelCommand = gameMessageArgumentType;
		executeCommand = rightClick;
	}
	else
	{
		cancelCommand = rightClick;
		executeCommand = gameMessageArgumentType;
	}

	if (!executeCommand && !cancelCommand && !isDown)
		return KEEP_MESSAGE;
	if (isDown)
		disp = DESTROY_MESSAGE;
	else if (cancelCommand)
	{
		disp = DESTROY_MESSAGE;
		TheInGameUI->setGUICommand(0);
	}
	else if (executeCommand)
	{
	int status = 1;
	const ICoord2D *hi = &msg->getArgument(0)->pixelRegion.hi;
	ICoord2D mouse = *hi;
	((Rva005B5440 *)((BfmeOwnVVD *)TheLookAtTranslator))->clearFlags();
	if (!command->isContextCommand())
	{
	switch (command->m_command)
	{
	case 0x17:
	{
		status = doFireWeaponCommand(command, &mouse);
		PickAndPlayInfo info;
		int slot = command->m_weaponSlot;
		info.m_weaponSlot = &slot;
		pickAndPlayUnitVoiceResponse((const DrawableList *)TheInGameUI->getAllSelectedDrawables(), GameMessage::MSG_DO_WEAPON_AT_LOCATION, (PickAndPlayInfo *)&info);
		break;
	}
	case 0x18:
	case 0x20:
	case 0x26:
		return KEEP_MESSAGE;
	case 0x28:
		if (command->m_options & 0x20)
		{
			Coord3D world;
			((TacticalView *)TheTacticalView)->screenToTerrain(&mouse, &world, false);
			GameMessage *gameMessage = TheMessageStream->appendMessage(GameMessage::MSG_CREW_EVACUATE);
			gameMessage->appendLocationArgument(world);
			PickAndPlayInfo info;
			info.m_14 = world;
			pickAndPlayUnitVoiceResponse((const DrawableList *)TheInGameUI->getAllSelectedDrawables(), GameMessage::MSG_CREW_EVACUATE, (PickAndPlayInfo *)&info);
			status = 1;
		}
		break;
	case 0x11:
		if (command->m_options & 0x20)
		{
			Coord3D world;
			((TacticalView *)TheTacticalView)->screenToTerrain(&mouse, &world, false);
			GameMessage *gameMessage = TheMessageStream->appendMessage(GameMessage::MSG_EVACUATE);
			gameMessage->appendLocationArgument(world);
			PickAndPlayInfo info;
			info.m_14 = world;
			pickAndPlayUnitVoiceResponse((const DrawableList *)TheInGameUI->getAllSelectedDrawables(), GameMessage::MSG_EVACUATE, (PickAndPlayInfo *)&info);
			status = 1;
		}
		break;
	case 0x12:
		if (command->m_options & 0x20)
		{
			Coord3D world;
			((TacticalView *)TheTacticalView)->screenToTerrain(&mouse, &world, false);
			GameMessage *gameMessage = TheMessageStream->appendMessage(GameMessage::MSG_EVACUATE_CONTESTERS);
			gameMessage->appendLocationArgument(world);
			PickAndPlayInfo info;
			info.m_14 = world;
			pickAndPlayUnitVoiceResponse((const DrawableList *)TheInGameUI->getAllSelectedDrawables(), GameMessage::MSG_EVACUATE_CONTESTERS, (PickAndPlayInfo *)&info);
			status = 1;
		}
		break;
	case 0xD:
		status = doGuardCommand((void *)command, 2, &mouse);
		break;
	case 0xC:
		status = doGuardCommand((void *)command, 1, &mouse);
		break;
	case 0xB:
		status = doGuardCommand((void *)command, 0, &mouse);
		break;
	case 0xA:
		status = doAttackMoveCommand((void *)command, &mouse);
		break;
	case 0x15:
		status = doSetRallyPointCommand((void *)command, &mouse);
		break;
	case 0x1F:
		status = Rva004312E5Emit((void *)command, &mouse);
		break;
	case 0x35:
	{
		PickAndPlayInfo info;
		pickAndPlayUnitVoiceResponse((const DrawableList *)TheInGameUI->getAllSelectedDrawables(), GameMessage::MSG_DOZER_CONSTRUCT, (PickAndPlayInfo *)&info);
		break;
	}
	}

	disp = DESTROY_MESSAGE;
	if (status == 1)
		TheInGameUI->setGUICommand(0);
	}
	}
	return (GameMessageDisposition)disp;
}