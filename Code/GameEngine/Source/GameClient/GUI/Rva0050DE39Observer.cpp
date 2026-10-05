// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?Rva0050DE39Init@@YAXXZ @0x0050DE39 597B: observer ControlBar cache init.
// Evidence: caller 0x0031D201; callees rowed nameToKey 0x00148E1A plus nameToKey_ascii 0x0009FA65 plus format 0x00038150 plus releaseBuffer 0x00036410 plus winGetWindowFromId slot 0xF0; strings ControlBar.wnd Observer/Player/Button/StaticText/WinFlag/Portrait/Cancel; globals g_00E0460C g_00E0462C g_00E0464C g_00E04650 g_00E04654 g_00E04674 g_00E04694 g_00E04698 g_00E0469C g_00E046A0 g_00E046A4 g_00E046A8 g_00E046AC g_00E046B0; neighbour Rva0050E776Send.cpp layout.
#include "ascii_string.h"

typedef int Int;

#ifndef NULL
#define NULL 0
#endif

class GameWindow
{
public:
	unsigned char m_pad[8];
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *nameString);
	NameKeyType nameToKey(const AsciiString &nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindowManager
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void pad15();
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual void pad21();
	virtual void pad22();
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual void pad27();
	virtual void pad28();
	virtual void pad29();
	virtual void pad30();
	virtual void pad31();
	virtual void pad32();
	virtual void pad33();
	virtual void pad34();
	virtual void pad35();
	virtual void pad36();
	virtual void pad37();
	virtual void pad38();
	virtual void pad39();
	virtual void pad40();
	virtual void pad41();
	virtual void pad42();
	virtual void pad43();
	virtual void pad44();
	virtual void pad45();
	virtual void pad46();
	virtual void pad47();
	virtual void pad48();
	virtual void pad49();
	virtual void pad50();
	virtual void pad51();
	virtual void pad52();
	virtual void pad53();
	virtual void pad54();
	virtual void pad55();
	virtual void pad56();
	virtual void pad57();
	virtual void pad58();
	virtual void pad59();
	virtual GameWindow *winGetWindowFromId(GameWindow *window, Int id);
};

extern GameWindowManager *TheWindowManager;

extern Int g_00E0460C[8];
extern Int g_00E0462C[8];
extern GameWindow *g_00E0464C;
extern GameWindow *g_00E04650;
extern GameWindow *g_00E04654[8];
extern GameWindow *g_00E04674[8];
extern Int g_00E04694;
extern GameWindow *g_00E04698;
extern GameWindow *g_00E0469C;
extern GameWindow *g_00E046A0;
extern GameWindow *g_00E046A4;
extern GameWindow *g_00E046A8;
extern GameWindow *g_00E046AC;
extern GameWindow *g_00E046B0;

void __cdecl Rva0050DE39Init()
{
	g_00E0464C = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ObserverPlayerInfoWindow"));
	g_00E04650 = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ObserverPlayerListWindow"));
	for (Int i = 0; i < 8; ++i) {
		AsciiString tmp;
		tmp.format("ControlBar.wnd:ButtonPlayer%d", i);
		Int key = TheNameKeyGenerator->nameToKey(tmp);
		g_00E0460C[i] = key;
		g_00E04654[i] = TheWindowManager->winGetWindowFromId(g_00E04650, key);
		tmp.format("ControlBar.wnd:StaticTextPlayer%d", i);
		Int key2 = TheNameKeyGenerator->nameToKey(tmp);
		g_00E0462C[i] = key2;
		g_00E04674[i] = TheWindowManager->winGetWindowFromId(g_00E04650, key2);
	}
	g_00E046A0 = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:StaticTextNumberOfUnits"));
	g_00E046A4 = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:StaticTextNumberOfBuildings"));
	g_00E046A8 = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:StaticTextNumberOfUnitsKilled"));
	g_00E046AC = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:StaticTextNumberOfUnitsLost"));
	g_00E046B0 = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:StaticTextPlayerName"));
	g_00E04698 = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:WinFlag"));
	g_00E0469C = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:WinGeneralPortrait"));
	g_00E04694 = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonCancel");
}
