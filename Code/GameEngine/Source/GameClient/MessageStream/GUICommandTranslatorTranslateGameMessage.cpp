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

struct ICoord2D
{
	int m_x;
	int m_y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

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

class GameMessage
{
public:
	enum Type
	{
		TYPE_40E = 0x40E,
		TYPE_41A = 0x41A,
		TYPE_41E = 0x41E,
		TYPE_41F = 0x41F,
		TYPE_455 = 0x455
	};
	const GameMessageArgumentType *getArgument(int argIndex) const;
	void appendIntegerArgument(int v);
	void appendObjectIDArgument(ObjectID id);
	void appendLocationArgument(const Coord3D &pos);
	char m_pad[0x10];
	int m_type;
};

class MessageStream
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
	virtual void v16();
	virtual void v17();
	virtual GameMessage *createMessage(int type);
};

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

extern TacticalView *TheTacticalView;

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Object : public Thing
{
public:
	char m_pad00[0x74 - sizeof(Thing)];
	ObjectID m_id;
};

class Drawable
{
public:
	char m_pad[0xFC];
	Object *m_object;
};

class DrawableList;
class PickAndPlayInfo;

class Rva004D92FE
{
public:
	Rva004D92FE();
	bool m_00;
	Drawable *m_04;
	int m_08;
	int *m_weaponSlot;
	int m_10;
	Coord3D m_14;
	int m_20;
};

class CommandButton
{
public:
	bool isContextCommand() const;
	char m_pad00[0x14];
	int m_commandType;
	char m_pad18[4];
	unsigned int m_options;
	char m_pad20[0x80 - 0x20];
	int m_weaponSlot;
	char m_pad84[0xA0 - 0x84];
	int m_maxShots;
};

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
	virtual void v16();
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
	virtual void setGUICommand(const CommandButton *command);
	virtual const CommandButton *getGUICommand();
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
	virtual void v68();
	virtual void v69();
	virtual int getSelectCount();
	virtual void v71();
	virtual void v72();
	virtual const DrawableList *getAllSelectedDrawables();
	virtual void v74();
	virtual Drawable *getFirstSelectedDrawable();
};

extern InGameUI *TheInGameUI;

class GlobalData
{
public:
	char m_pad[0x5C];
	bool m_flag5C;
};

extern GlobalData *TheWritableGlobalData;

class Mouse;
class Rva001EDD80
{
public:
	bool rva001EDD80(const Rva001EDD80Pair *a, const Rva001EDD80Pair *b);
};

extern Mouse *TheMouse;

class Rva005B5440
{
public:
	void clearFlags();
};

class BfmeOwnVVD;
extern BfmeOwnVVD *g_bfmeSingletonVVD;

class Rva0035AFE4;
Object *__cdecl Rva00431012PickObject(ICoord2D *pixel, Rva0035AFE4 *mask, int pickType);
int __cdecl doGuardCommand(void *command, int guardMode, ICoord2D *mouse);
int __cdecl doAttackMoveCommand(void *command, ICoord2D *mouse);
int __cdecl doSetRallyPointCommand(void *command, ICoord2D *mouse);
int __cdecl Rva004312E5Emit(void *command, ICoord2D *mouse);
void __cdecl pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type type, PickAndPlayInfo *info);

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
		TheTacticalView->screenToTerrain(mouse, &world, false);
		GameMessage *msg = TheMessageStream->createMessage(0x40E);
		msg->appendIntegerArgument(command->m_weaponSlot);
		msg->appendLocationArgument(world);
		msg->appendIntegerArgument(command->m_maxShots);
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
			GameMessage *msg = TheMessageStream->createMessage(0x40F);
			msg->appendIntegerArgument(command->m_weaponSlot);
			msg->appendObjectIDArgument(target->m_id);
			msg->appendIntegerArgument(command->m_maxShots);
		}
	}
	else
	{
		GameMessage *msg = TheMessageStream->createMessage(0x40D);
		msg->appendIntegerArgument(command->m_weaponSlot);
		msg->appendIntegerArgument(command->m_maxShots);
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
	ICoord2D m_0c;
	bool m_14;
	int m_18;
	int m_1c;
	Rva001EDD80Pair m_20;
	ICoord2D m_28;
	bool m_30;
	int m_34;
	int m_38;
};

GameMessageDisposition GUICommandTranslator::translateGameMessage(const GameMessage *msg)
{
	int disp = KEEP_MESSAGE;
	switch (msg->m_type)
	{
	case 3:
	{
		ICoord2D p = msg->getArgument(0)->pixel;
		if (((Rva001EDD80 *)TheMouse)->rva001EDD80(&m_04, (const Rva001EDD80Pair *)&p))
			m_14 = true;
		if (((Rva001EDD80 *)TheMouse)->rva001EDD80(&m_20, (const Rva001EDD80Pair *)&p))
			m_30 = true;
		break;
	}
	case 4:
	{
		const GameMessageArgumentType *a = msg->getArgument(0);
		m_04.x = a->pixel.m_x;
		m_04.y = a->pixel.m_y;
		m_18 = msg->getArgument(2)->integer;
		m_14 = false;
		break;
	}
	case 6:
	{
		const GameMessageArgumentType *a = msg->getArgument(0);
		m_0c.m_x = a->pixel.m_x;
		m_0c.m_y = a->pixel.m_y;
		m_1c = msg->getArgument(2)->integer;
		break;
	}
	case 0xE:
	{
		const GameMessageArgumentType *a = msg->getArgument(0);
		m_20.x = a->pixel.m_x;
		m_20.y = a->pixel.m_y;
		m_34 = msg->getArgument(2)->integer;
		m_30 = false;
		break;
	}
	case 0x10:
	{
		const GameMessageArgumentType *a = msg->getArgument(0);
		m_28.m_x = a->pixel.m_x;
		m_28.m_y = a->pixel.m_y;
		m_38 = msg->getArgument(2)->integer;
		break;
	}
	}

	const CommandButton *command = TheInGameUI->getGUICommand();
	if (command == 0)
		return KEEP_MESSAGE;

	bool a = (msg->m_type == 0x18 || msg->m_type == 0x17) && !m_14;
	bool b = (msg->m_type == 0x1C || msg->m_type == 0x1B) && !m_30;
	bool isDown = msg->m_type == 4;
	bool x;
	bool y;
	if (command->m_commandType == 0xA && TheWritableGlobalData->m_flag5C)
	{
		x = a;
		y = b;
	}
	else
	{
		x = b;
		y = a;
	}

	if (!y && !x && !isDown)
		return KEEP_MESSAGE;
	if (isDown)
		disp = DESTROY_MESSAGE;
	else if (x)
	{
		disp = DESTROY_MESSAGE;
		TheInGameUI->setGUICommand(0);
	}
	else if (y)
	{
	int status = 1;
	const ICoord2D *hi = &msg->getArgument(0)->pixelRegion.hi;
	ICoord2D mouse = *hi;
	((Rva005B5440 *)g_bfmeSingletonVVD)->clearFlags();
	if (!command->isContextCommand())
	{
	switch (command->m_commandType)
	{
	case 0x17:
	{
		status = doFireWeaponCommand(command, &mouse);
		Rva004D92FE info;
		int slot = command->m_weaponSlot;
		info.m_weaponSlot = &slot;
		pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), GameMessage::TYPE_40E, (PickAndPlayInfo *)&info);
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
			TheTacticalView->screenToTerrain(&mouse, &world, false);
			GameMessage *m = TheMessageStream->createMessage(0x455);
			m->appendLocationArgument(world);
			Rva004D92FE info;
			info.m_14 = world;
			pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), GameMessage::TYPE_455, (PickAndPlayInfo *)&info);
			status = 1;
		}
		break;
	case 0x11:
		if (command->m_options & 0x20)
		{
			Coord3D world;
			TheTacticalView->screenToTerrain(&mouse, &world, false);
			GameMessage *m = TheMessageStream->createMessage(0x41E);
			m->appendLocationArgument(world);
			Rva004D92FE info;
			info.m_14 = world;
			pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), GameMessage::TYPE_41E, (PickAndPlayInfo *)&info);
			status = 1;
		}
		break;
	case 0x12:
		if (command->m_options & 0x20)
		{
			Coord3D world;
			TheTacticalView->screenToTerrain(&mouse, &world, false);
			GameMessage *m = TheMessageStream->createMessage(0x41F);
			m->appendLocationArgument(world);
			Rva004D92FE info;
			info.m_14 = world;
			pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), GameMessage::TYPE_41F, (PickAndPlayInfo *)&info);
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
		Rva004D92FE info;
		pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), GameMessage::TYPE_41A, (PickAndPlayInfo *)&info);
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