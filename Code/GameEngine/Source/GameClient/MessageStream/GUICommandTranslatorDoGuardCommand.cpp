// cl: /O1 /MD /DNDEBUG
// ?doGuardCommand@@YAHPAXHPAUICoord2D@@@Z @0x00431362 335B
// Zero Hour GUICommandTranslator doGuardCommand (GameClient/MessageStream/
// GUICommandTranslator.cpp), BFME2 variant: the object-target branch also
// hands the PickAndPlayInfo the picked object's drawable (info+4); the
// position branch passes the world point in info+0x14 (rowed ctor 0x004D92FE).
// Message types read from retail: 0x434 guard object, 0x433 guard position.
// Evidence: retail bytes; callers 0x00431797/0x0043178F/0x00431787 (modes 0,1,2);
// validUnderCursor = rowed 0x00431012; rowed appendObjectID/Integer/Location.
struct ICoord2D
{
	int m_x;
	int m_y;
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Drawable;

enum ObjectID
{
	OBJECTID_NONE = 0
};

class GameMessage
{
public:
	enum Type
	{
		TYPE_433 = 0x433,
		TYPE_434 = 0x434
	};
	void appendIntegerArgument(int v);
	void appendObjectIDArgument(ObjectID id);
	void appendLocationArgument(const Coord3D &pos);
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
	char m_pad00[0x38 - sizeof(Thing)];
	Coord3D m_position;
	char m_pad44[0x74 - 0x44];
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
	Drawable *m_drawTarget;
	int m_08;
	int m_0c;
	int m_10;
	Coord3D m_14;
	int m_20;
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

class Rva0035AFE4;
Object *__cdecl Rva00431012PickObject(ICoord2D *pixel, Rva0035AFE4 *mask, int pickType);
void __cdecl pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type type, PickAndPlayInfo *info);

class GuardCommandButton
{
public:
	char m_pad[0x1C];
	unsigned int m_options;
};

int __cdecl doGuardCommand(void *command, int guardMode, ICoord2D *mouse)
{
	GuardCommandButton *cmd = (GuardCommandButton *)command;
	if (cmd == 0 || mouse == 0)
		return 1;
	if (TheInGameUI->getSelectCount() == 0)
		return 1;

	GameMessage *msg = 0;
	if (cmd->m_options & 7)
	{
		Object *target = Rva00431012PickObject(mouse, (Rva0035AFE4 *)cmd, 4);
		if (target)
		{
			msg = TheMessageStream->createMessage(0x434);
			msg->appendObjectIDArgument(target->m_id);
			msg->appendIntegerArgument(guardMode);
			Rva004D92FE info;
			info.m_drawTarget = target->getDrawable();
			pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), GameMessage::TYPE_434, (PickAndPlayInfo *)&info);
		}
	}

	if (msg == 0)
	{
		Coord3D world;
		if (cmd->m_options & 0x20)
		{
			TheTacticalView->screenToTerrain(mouse, &world, false);
		}
		else
		{
			Drawable *draw = TheInGameUI->getFirstSelectedDrawable();
			if (draw == 0 || draw->m_object == 0)
				return 1;
			world = draw->m_object->m_position;
		}
		msg = TheMessageStream->createMessage(0x433);
		msg->appendLocationArgument(world);
		msg->appendIntegerArgument(guardMode);
		Rva004D92FE info;
		info.m_14 = world;
		pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), GameMessage::TYPE_433, (PickAndPlayInfo *)&info);
	}
	return 1;
}
