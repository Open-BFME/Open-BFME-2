// cl: /O1 /MD /DNDEBUG
//
// Zero Hour's MetaEventTranslator::translateGameMessage (GameEngine/Source/
// GameClient/MessageStream/MetaEvent.cpp), the body just before the rowed
// MetaMap::findGameMessageMetaType 0x001DB3FE. Native [1DB0B5,1DB3CB),790B,
// thiscall ret 4, with its two-level case table at 0x001DB3CB.
//
// BFME2 deltas read from retail: with OurLanguage 2 the Y and Z scancodes
// (0x15/0x2C) swap; a map entry is usable when its usable-in bits meet the
// shell bit (1) while the shell is active, else the game bit (2), plus 4 when
// the local player's +0x750 is 2; an auto-repeated key is still consumed
// unless the +0x18 flag of the object at VA 0x00DFEF18 is set; ZH's
// fast-forward-replay special case is gone. The mouse half is ZH's.

typedef int Int;
typedef unsigned int UnsignedInt;

extern "C" int __cdecl abs(int);

struct ICoord2D
{
	Int x, y;
};
struct IRegion2D
{
	ICoord2D lo, hi;
};
void buildRegion(const ICoord2D *anchor, const ICoord2D *dest, IRegion2D *region);

union GameMessageArgumentType
{
	Int integer;
	ICoord2D pixel;
};

class GameMessage
{
public:
	enum Type
	{
		MSG_RAW_MOUSE_BEGIN = 2,
		MSG_RAW_MOUSE_LEFT_BUTTON_DOWN = 4,
		MSG_RAW_MOUSE_LEFT_DOUBLE_CLICK = 5,
		MSG_RAW_MOUSE_LEFT_BUTTON_UP = 6,
		MSG_RAW_MOUSE_MIDDLE_BUTTON_DOWN = 10,
		MSG_RAW_MOUSE_MIDDLE_DOUBLE_CLICK = 11,
		MSG_RAW_MOUSE_MIDDLE_BUTTON_UP = 12,
		MSG_RAW_MOUSE_RIGHT_BUTTON_DOWN = 14,
		MSG_RAW_MOUSE_RIGHT_DOUBLE_CLICK = 15,
		MSG_RAW_MOUSE_RIGHT_BUTTON_UP = 16,
		MSG_RAW_MOUSE_END = 20,
		MSG_RAW_KEY_DOWN = 21,
		MSG_RAW_KEY_UP = 22,
		MSG_MOUSE_LEFT_CLICK = 23,
		MSG_MOUSE_LEFT_DOUBLE_CLICK = 24,
		MSG_MOUSE_MIDDLE_CLICK = 25,
		MSG_MOUSE_MIDDLE_DOUBLE_CLICK = 26,
		MSG_MOUSE_RIGHT_CLICK = 27,
		MSG_MOUSE_RIGHT_DOUBLE_CLICK = 28
	};
	Type getType() const { return m_type; }
	const GameMessageArgumentType *getArgument(Int argIndex) const;
	void appendIntegerArgument(Int arg);
	void appendPixelRegionArgument(const IRegion2D &dragRegion);
private:
	unsigned char m_00[0x10];
	Type m_type;	// +0x10
};

class MessageStream
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage(GameMessage::Type type);
	virtual GameMessage *insertMessage(GameMessage::Type type, GameMessage *messageToInsertAfter);
};
extern MessageStream *TheMessageStream;

enum MappableKeyType { MK_NONE = 0, MK_Y = 0x15, MK_Z = 0x2C };
enum MappableKeyTransition { DOWN = 0, UP = 1 };
enum
{
	KEY_STATE_UP = 0x0001,
	KEY_STATE_DOWN = 0x0002,
	KEY_STATE_CONTROL = 0x000C,
	KEY_STATE_SHIFT = 0x0430,
	KEY_STATE_ALT = 0x00C0,
	KEY_STATE_AUTOREPEAT = 0x0100
};
enum MappableKeyModState { NONE = 0, CTRL = 4, SHIFT = 16, ALT = 64 };
enum CommandUsableInType { COMMANDUSABLE_SHELL = 1, COMMANDUSABLE_GAME = 2 };

class MetaMapRec
{
public:
	MetaMapRec *m_next;
	GameMessage::Type m_meta;
	MappableKeyType m_key;
	MappableKeyTransition m_transition;
	Int m_modState;
	Int m_usableIn;
};

class MetaMap
{
public:
	const MetaMapRec *getFirstMetaMapRec() const { return m_metaMaps; }
private:
	unsigned char m_00[0x0C];
	MetaMapRec *m_metaMaps;	// +0x0C
};
extern MetaMap *TheMetaMap;

class GameClient
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30();
	virtual UnsignedInt getFrame();
};
extern GameClient *TheGameClient;

class Shell
{
public:
	bool isShellActive() const { return m_isShellActive; }
private:
	unsigned char m_00[0x5C];
	bool m_isShellActive;	// +0x5C
};
extern Shell *TheShell;

class Player
{
public:
	unsigned char m_00[0x750];
	Int m_750;
};
class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
private:
	unsigned char m_00[0x10];
	Player *m_local;	// +0x10
};
extern PlayerList *ThePlayerList;

class Mouse
{
public:
	unsigned char m_00[0x12E8];
	UnsignedInt m_dragTolerance;	// +0x12E8
};
extern Mouse *TheMouse;

enum LanguageID { LANGUAGE_ID_2 = 2 };
extern LanguageID OurLanguage;

class Rva002D3627Host
{
public:
	unsigned char m_00[0x18];
	bool m_18;
};
extern Rva002D3627Host *g_00DFEF18;

enum GameMessageDisposition { KEEP_MESSAGE, DESTROY_MESSAGE };

class GameMessageTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg) = 0;
};

class MetaEventTranslator : public GameMessageTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
private:
	MappableKeyType m_lastKeyDown;			// +0x04
	Int m_lastModState;						// +0x08
	ICoord2D m_mouseDownPosition[3];		// +0x0C
	bool m_nextUpShouldCreateDoubleClick[3];	// +0x24
};

GameMessageDisposition MetaEventTranslator::translateGameMessage(const GameMessage *msg)
{
	GameMessageDisposition disp = KEEP_MESSAGE;
	GameMessage::Type t = msg->getType();

	if (t == GameMessage::MSG_RAW_KEY_DOWN || t == GameMessage::MSG_RAW_KEY_UP)
	{
		MappableKeyType key = (MappableKeyType)msg->getArgument(0)->integer;
		if (OurLanguage == LANGUAGE_ID_2)
		{
			if (key == MK_Z)
				key = MK_Y;
			else if (key == MK_Y)
				key = MK_Z;
		}
		Int keyState = msg->getArgument(1)->integer;

		Int newModState = 0;
		if (keyState & KEY_STATE_CONTROL)
			newModState |= CTRL;
		if (keyState & KEY_STATE_SHIFT)
			newModState |= SHIFT;
		if (keyState & KEY_STATE_ALT)
			newModState |= ALT;

		Int usable;
		if (TheShell && TheShell->isShellActive())
			usable = COMMANDUSABLE_SHELL;
		else
		{
			usable = COMMANDUSABLE_GAME;
			if (ThePlayerList && ThePlayerList->getLocalPlayer() && ThePlayerList->getLocalPlayer()->m_750 == 2)
				usable = 6;
		}

		for (const MetaMapRec *map = TheMetaMap->getFirstMetaMapRec(); map; map = map->m_next)
		{
			if (map->m_usableIn == COMMANDUSABLE_GAME && TheGameClient->getFrame() < 1)
				continue;
			if (!(map->m_usableIn & usable))
				continue;

			if (map->m_key == MK_NONE &&
				newModState != m_lastModState &&
				((map->m_transition == UP && map->m_modState == m_lastModState) ||
				 (map->m_transition == DOWN && map->m_modState == newModState)))
			{
				TheMessageStream->appendMessage(map->m_meta);
				disp = DESTROY_MESSAGE;
				break;
			}

			if (map->m_key == key &&
				map->m_modState == newModState &&
				((map->m_transition == UP && (keyState & KEY_STATE_UP)) ||
				 (map->m_transition == DOWN && (keyState & KEY_STATE_DOWN))))
			{
				if (!(keyState & KEY_STATE_AUTOREPEAT))
					TheMessageStream->appendMessage(map->m_meta);
				if (!g_00DFEF18->m_18)
					disp = DESTROY_MESSAGE;
				break;
			}
		}

		if (t == GameMessage::MSG_RAW_KEY_DOWN)
			m_lastKeyDown = key;
		m_lastModState = newModState;
	}

	if (t > GameMessage::MSG_RAW_MOUSE_BEGIN && t < GameMessage::MSG_RAW_MOUSE_END)
	{
		Int index = 0;
		switch (t)
		{
			case GameMessage::MSG_RAW_MOUSE_LEFT_BUTTON_DOWN:
			case GameMessage::MSG_RAW_MOUSE_MIDDLE_BUTTON_DOWN:
			case GameMessage::MSG_RAW_MOUSE_RIGHT_BUTTON_DOWN:
			{
				if (t == GameMessage::MSG_RAW_MOUSE_MIDDLE_BUTTON_DOWN)
					index = 1;
				else if (t == GameMessage::MSG_RAW_MOUSE_RIGHT_BUTTON_DOWN)
					index = 2;
				m_mouseDownPosition[index] = msg->getArgument(0)->pixel;
				m_nextUpShouldCreateDoubleClick[index] = false;
				break;
			}

			case GameMessage::MSG_RAW_MOUSE_LEFT_DOUBLE_CLICK:
			case GameMessage::MSG_RAW_MOUSE_MIDDLE_DOUBLE_CLICK:
			case GameMessage::MSG_RAW_MOUSE_RIGHT_DOUBLE_CLICK:
			{
				if (t == GameMessage::MSG_RAW_MOUSE_MIDDLE_DOUBLE_CLICK)
					index = 1;
				else if (t == GameMessage::MSG_RAW_MOUSE_RIGHT_DOUBLE_CLICK)
					index = 2;
				m_nextUpShouldCreateDoubleClick[index] = true;
				break;
			}

			case GameMessage::MSG_RAW_MOUSE_LEFT_BUTTON_UP:
			case GameMessage::MSG_RAW_MOUSE_MIDDLE_BUTTON_UP:
			case GameMessage::MSG_RAW_MOUSE_RIGHT_BUTTON_UP:
			{
				ICoord2D location = msg->getArgument(0)->pixel;

				if (t == GameMessage::MSG_RAW_MOUSE_MIDDLE_BUTTON_UP)
					index = 1;
				else if (t == GameMessage::MSG_RAW_MOUSE_RIGHT_BUTTON_UP)
					index = 2;

				GameMessage *newMessage = 0;
				if (t == GameMessage::MSG_RAW_MOUSE_LEFT_BUTTON_UP)
				{
					if (m_nextUpShouldCreateDoubleClick[index])
						newMessage = TheMessageStream->insertMessage(GameMessage::MSG_MOUSE_LEFT_DOUBLE_CLICK, const_cast<GameMessage *>(msg));
					else
						newMessage = TheMessageStream->insertMessage(GameMessage::MSG_MOUSE_LEFT_CLICK, const_cast<GameMessage *>(msg));
					m_nextUpShouldCreateDoubleClick[index] = false;
				}
				else if (t == GameMessage::MSG_RAW_MOUSE_MIDDLE_BUTTON_UP)
				{
					if (m_nextUpShouldCreateDoubleClick[index])
						newMessage = TheMessageStream->insertMessage(GameMessage::MSG_MOUSE_MIDDLE_DOUBLE_CLICK, const_cast<GameMessage *>(msg));
					else
						newMessage = TheMessageStream->insertMessage(GameMessage::MSG_MOUSE_MIDDLE_CLICK, const_cast<GameMessage *>(msg));
					m_nextUpShouldCreateDoubleClick[index] = false;
				}
				else if (t == GameMessage::MSG_RAW_MOUSE_RIGHT_BUTTON_UP)
				{
					if (m_nextUpShouldCreateDoubleClick[index])
						newMessage = TheMessageStream->insertMessage(GameMessage::MSG_MOUSE_RIGHT_DOUBLE_CLICK, const_cast<GameMessage *>(msg));
					else
						newMessage = TheMessageStream->insertMessage(GameMessage::MSG_MOUSE_RIGHT_CLICK, const_cast<GameMessage *>(msg));
					m_nextUpShouldCreateDoubleClick[index] = false;
				}

				IRegion2D pixelRegion;
				buildRegion(&m_mouseDownPosition[index], &location, &pixelRegion);
				if (abs(pixelRegion.hi.x - pixelRegion.lo.x) < TheMouse->m_dragTolerance &&
					abs(pixelRegion.hi.y - pixelRegion.lo.y) < TheMouse->m_dragTolerance)
				{
					pixelRegion.hi.x = pixelRegion.lo.x;
					pixelRegion.hi.y = pixelRegion.lo.y;
				}

				newMessage->appendPixelRegionArgument(pixelRegion);
				newMessage->appendIntegerArgument(msg->getArgument(1)->integer);
				break;
			}
		}
	}

	return disp;
}
