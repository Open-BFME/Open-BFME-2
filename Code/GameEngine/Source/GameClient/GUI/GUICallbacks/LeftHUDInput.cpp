// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// LeftHUDInput 0x004020CE (903B): Zero Hour ControlBarCallback.cpp's radar
// window input callback, through BFME1's ControlBarCallback.cpp donor.
//
// Target evidence: the FunctionLexicon entry at 0x009BCB80 pairs the literal
// "LeftHUDInput" (0x00C02528) with 0x004020CE. The body is ZH's: eat input
// when the radar is hidden or missing and not forced, then the cursor cases
// (none, mouse entering/leaving), the mouse-position cursor refresh, the eaten
// button-ups and the left/right down command through localPixelToRadar and
// radarToWorld. BFME2 drops ZH's middle-button early-out and eats middle
// down/up instead; its targeting test checks NEED_TARGET_POS (0x20) first and
// accepts command types 0x18, 0x20 and 0x26; attack move is type 0x0A and
// sends 0x430, move sends 0x42F, both with BFME's PickAndPlayInfo position.
// The ZH trailing clearAttackMoveToMode() is gone. Slot offsets are read from
// the retail calls.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef unsigned int WindowMsgData;

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };

enum GameWindowMessage
{
	GWM_NONE = 0,
	GWM_LEFT_DOWN = 5,
	GWM_LEFT_UP = 6,
	GWM_MIDDLE_DOWN = 9,
	GWM_MIDDLE_UP = 10,
	GWM_RIGHT_DOWN = 13,
	GWM_RIGHT_UP = 14,
	GWM_MOUSE_ENTERING = 17,
	GWM_MOUSE_LEAVING = 18,
	GWM_MOUSE_POS = 24
};

struct ICoord2D { Int x, y; };

#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Drawable;

struct DrawableListNode { DrawableListNode *m_next; };

class DrawableList
{
public:
	Bool empty() const { return m_node->m_next == m_node; }
	DrawableListNode *m_node;
};

class PickAndPlayInfo
{
public:
	PickAndPlayInfo();
	Bool m_air;
	Drawable *m_drawTarget;
	void *m_weaponSlot;
	Int m_specialPowerType;
	Int m_10;
	Coord3D m_position;             // +0x14
	Int m_20;
};

class GameMessage
{
public:
	enum Type { MSG_DO_MOVETO = 0x42F, MSG_DO_ATTACKMOVETO = 0x430 };
	void appendLocationArgument(const Coord3D &location);
};

void pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type msgType, PickAndPlayInfo *info);

enum NEED_TARGET_OPTION { NEED_TARGET_POS = 0x20 };

class CommandButton
{
public:
	char m_pad00[0x14];
	Int m_commandType;              // +0x14
	char m_pad18[4];
	UnsignedInt m_options;          // +0x1C
	char m_pad20[0x50 - 0x20];
	AsciiString m_cursorName;       // +0x50

	Int getCommandType() const { return m_commandType; }
	UnsignedInt getOptions() const { return m_options; }
	const AsciiString &getCursorName() const { return m_cursorName; }
};

class GameWindow
{
public:
	Int winGetSize(Int *width, Int *height);
	Int winGetScreenPosition(Int *x, Int *y);
};

class Player
{
public:
	Bool hasRadar() const;
};

class PlayerList
{
public:
	// Matched callers read the local player at +0x10 directly; do not emit
	// a shared getter from this partial target layout.
	char m_pad00[0x10];
	Player *m_local;                // +0x10
};

class Radar
{
public:
	char m_pad00[0x10];
	Bool m_radarHidden;             // +0x10
	Bool m_radarForceOn;            // +0x11
	Bool isRadarHidden() { return m_radarHidden; }
	Bool isRadarForced() { return m_radarForceOn; }
	Bool localPixelToRadar(const ICoord2D *pixel, ICoord2D *radar);
	Bool radarToWorld(const ICoord2D *radar, Coord3D *world);
};

class Mouse
{
public:
	enum MouseCursor { INVALID_MOUSE_CURSOR = -1, ARROW = 2, CROSS = 4, MOVETO = 5, ATTACKMOVETO = 6 };
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18();
	virtual void setCursor(MouseCursor cursor);                          // +0x4C
	Int getCursorIndex(const AsciiString &name);
};

class InGameUI
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46();
	virtual void setGUICommand(const CommandButton *command);            // +0xBC
	virtual const CommandButton *getGUICommand();                        // +0xC0
	virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72();
	virtual const DrawableList *getAllSelectedDrawables();               // +0x124
	virtual const DrawableList *getAllSelectedLocalDrawables();          // +0x128
};

enum CommandEvaluateType { DO_COMMAND, DO_HINT, DO_EVALUATE };

class GameClient
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual Int evaluateContextCommand(Drawable *draw, const Coord3D *pos, CommandEvaluateType type);   // +0x48
};

class MessageStream
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage(GameMessage::Type type);           // +0x48
};

class View
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20();
	virtual void lookAt(const Coord3D *o);                               // +0x54
};

struct GlobalData
{
	char m_pad00[0x5C];
	Bool m_useAlternateMouse;       // +0x5C
};

extern PlayerList *ThePlayerList;
extern Radar *TheRadar;
extern Mouse *TheMouse;
extern InGameUI *TheInGameUI;
extern GameClient *TheGameClient;
extern MessageStream *MessageStreamSubsystem;
extern View *TheTacticalView;
extern GlobalData *TheGlobalData;

WindowMsgHandledType LeftHUDInput( GameWindow *window, UnsignedInt msg,
																	 WindowMsgData mData1, WindowMsgData mData2 )
{
	Player *player = ThePlayerList->m_local;

	if( !TheRadar->isRadarForced() && (TheRadar->isRadarHidden() || !player->hasRadar()) )
		return MSG_HANDLED;

	switch( msg )
	{
		case GWM_NONE:
		case GWM_MOUSE_ENTERING:
		case GWM_MOUSE_LEAVING:
		{
			Bool targeting = false;
			const CommandButton *command = TheInGameUI->getGUICommand();
			if( command
					&& (command->getOptions() & NEED_TARGET_POS)
					&& (command->getCommandType() == 0x18 || command->getCommandType() == 0x20 || command->getCommandType() == 0x26) )
				targeting = true;

			if( targeting == false )
			{
				const DrawableList *drawableList = TheInGameUI->getAllSelectedLocalDrawables();
				Mouse::MouseCursor cur = Mouse::ARROW;

				if (!(drawableList->empty() || msg == GWM_MOUSE_LEAVING))
				{
					if (command && command->getCommandType() == 0x0A)
						cur = Mouse::ATTACKMOVETO;
					else
						cur = Mouse::MOVETO;
				}

				TheMouse->setCursor(cur);
			}

			return MSG_HANDLED;
		}

		case GWM_MOUSE_POS:
		{
			ICoord2D mouse;
			mouse.x = mData1 & 0xFFFF;
			mouse.y = mData1 >> 16;

			ICoord2D screenPos;
			window->winGetScreenPosition( &screenPos.x, &screenPos.y );

			mouse.x -= screenPos.x;
			mouse.y -= screenPos.y;

			ICoord2D radar;
			if( (TheRadar->isRadarHidden() == false || TheRadar->isRadarForced()) &&
					TheRadar->localPixelToRadar( &mouse, &radar ) )
			{
				const CommandButton *command = TheInGameUI->getGUICommand();
				if( command
					&& (command->getOptions() & NEED_TARGET_POS)
					&& (command->getCommandType() == 0x18 || command->getCommandType() == 0x20 || command->getCommandType() == 0x26) )
				{
					Int index = TheMouse->getCursorIndex( command->getCursorName() );

					if( index != Mouse::INVALID_MOUSE_CURSOR )
						TheMouse->setCursor( (Mouse::MouseCursor)index );
					else
						TheMouse->setCursor( Mouse::CROSS );
				}
				else
				{
					const DrawableList *drawableList = TheInGameUI->getAllSelectedLocalDrawables();
					Mouse::MouseCursor cur = Mouse::ARROW;

					if (!(drawableList->empty() || msg == GWM_MOUSE_LEAVING))
					{
						if (command && command->getCommandType() == 0x0A)
							cur = Mouse::ATTACKMOVETO;
						else
							cur = Mouse::MOVETO;
					}

					TheMouse->setCursor(cur);
				}
			}
			break;
		}

		case GWM_RIGHT_UP:
		case GWM_LEFT_UP:
		case GWM_MIDDLE_DOWN:
		case GWM_MIDDLE_UP:
			break;

		case GWM_RIGHT_DOWN:
		case GWM_LEFT_DOWN:
		{
			ICoord2D mouse;
			ICoord2D radar;
			ICoord2D size;
			ICoord2D screenPos;
			Coord3D world;

			window->winGetSize( &size.x, &size.y );

			mouse.x = mData1 & 0xFFFF;
			mouse.y = mData1 >> 16;

			window->winGetScreenPosition( &screenPos.x, &screenPos.y );

			mouse.x -= screenPos.x;
			mouse.y -= screenPos.y;

			if( (TheRadar->isRadarHidden() == false || TheRadar->isRadarForced()) &&
					TheRadar->localPixelToRadar( &mouse, &radar ) &&
					TheRadar->radarToWorld( &radar, &world ) )
			{
				const DrawableList *drawableList = TheInGameUI->getAllSelectedLocalDrawables();

				if (	drawableList->empty()
					||	msg == (TheGlobalData->m_useAlternateMouse ? GWM_LEFT_DOWN : GWM_RIGHT_DOWN)	)
				{
					TheTacticalView->lookAt( &world );
					break;
				}

				const CommandButton *command = TheInGameUI->getGUICommand();
				if( command
					&& (command->getOptions() & NEED_TARGET_POS)
					&& (command->getCommandType() == 0x18 || command->getCommandType() == 0x20 || command->getCommandType() == 0x26) )
				{
					TheGameClient->evaluateContextCommand( 0, &world, DO_COMMAND );
				}
				else if( command && command->getCommandType() == 0x0A )
				{
					GameMessage *msg = MessageStreamSubsystem->appendMessage( GameMessage::MSG_DO_ATTACKMOVETO );
					msg->appendLocationArgument( world );

					PickAndPlayInfo info;
					info.m_position = world;
					pickAndPlayUnitVoiceResponse( TheInGameUI->getAllSelectedDrawables(), GameMessage::MSG_DO_ATTACKMOVETO, &info );
					TheInGameUI->setGUICommand( 0 );
				}
				else
				{
					GameMessage *newMsg = MessageStreamSubsystem->appendMessage( GameMessage::MSG_DO_MOVETO );
					newMsg->appendLocationArgument( world );

					PickAndPlayInfo info;
					info.m_position = world;
					pickAndPlayUnitVoiceResponse( drawableList, GameMessage::MSG_DO_MOVETO, &info );
				}
			}
			break;
		}

		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
