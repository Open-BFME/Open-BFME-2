// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// platformsdk
// ?dumpWindow@GameWindowManager@@IAEXPAVGameWindow@@@Z @0x002C1148 43B
// GameWindowManager::dumpWindow; FINAL build strips DEBUG_LOG leaving only
// the child/sibling walk (m_child +0x204 m_next +0x1F8) with self recursion;
// donor Code/GameEngine/Source/GameClient/GUI/GameWindowManager.cpp.
//
// GameWindowManager::winCreate @0x002C2533 263B, the record-based window create, after the
// BFME1 donor (game/GameEngine/Source/GameClient/GUI/GameWindowManager.cpp,
// winCreate): allocate through the record's allocator (or the manager
// fallback, dumping the window list when that fails), parent into the caller
// list or link it, copy instance data, order pairs, send the create message,
// then set the font from the global language data (falling back to 14pt
// Times New Roman), as Zero Hour does. BFME2 facts, all read off retail:
// - The record is Rva0047EDE0CreateInfo (parent@0, stdcall allocator@0x18,
//   instance data@0x30).
// - Manager slots: +0x38 the window id getter, +0x3C the record allocator
//   fallback, +0xE0 addWindowToParent, +0xE8 winSendSystemMsg, +0x130
//   winFindFont(name, size, bold) with the name passed by value.
// - Window slot +0x28 is a boolean gate; Rva00477DF0::orderPairs reaches the
//   rowed body through the TU-local view; GameWindow::winSetFont is called
//   qualified (direct call, no vtable).
// - Callees rowed: dumpWindow 0x002C1148 (defined above, as in retail's unit),
//   linkWindow 0x002C0A89, winSetInstanceData 0x0031495C, orderPairs
//   0x0031394A, winSetFont 0x00313D73, the StringBase constructors 0x000365F0
//   and 0x00037BA0, and StringBase<char>::isEmpty 0x00001E2F.
// Codegen: retail keeps TheGlobalLanguageData in ESI across the isEmpty call
// (Zero Hour reads the global at every use). VC7.1 does that only when it can
// see the callee's body, so this unit carries a noinline copy of the rowed
// isEmpty (byte-identical to 0x00001E2F); with it the register roles of
// `this` (EDI) and the record (ESI) and dumpWindow's EDX-preserving walk come
// out as retail's.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
#include <windows.h>
class AsciiString;
class UnicodeString;
class GameFont;
class GameWindow;
class WinInstanceData;

#include <stddef.h>
#include "ascii_string.h"

// The out-of-line emptiness test (0x00001E2F, AsciiString.cpp), visible here.
template <> inline __declspec(noinline) bool StringBase<char>::isEmpty() const throw()
{
	return m_data == 0 || m_data->length == 0;
}

struct Rva0047EDE0CreateInfo
{
	GameWindow *m_parent;
	UnsignedInt m_field04;
	Int m_field08, m_field0C, m_field10, m_field14;
	GameWindow *(__stdcall *m_allocator)(Rva0047EDE0CreateInfo *);
	void *m_field1C;
	Int m_field20, m_field24, m_field28, m_field2C;
	WinInstanceData *m_field30;
};

struct Rva00477DF0
{
	void orderPairs();
};

struct Rva0047EDE0FontDesc
{
	AsciiString name;
	Int size;
	bool bold;
};

struct Rva0047EDE0GlobalLanguage
{
	unsigned char m_pad00[0xA4];
	Rva0047EDE0FontDesc m_defaultWindowFont;
};

class GlobalLanguage;
extern GlobalLanguage *TheGlobalLanguageData;
static inline Rva0047EDE0GlobalLanguage *theGlobalLanguage()
{
	return (Rva0047EDE0GlobalLanguage *)TheGlobalLanguageData;
}

class GameWindowManager
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
	virtual int slot14();
	virtual GameWindow *slot15(Rva0047EDE0CreateInfo *info);
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
	virtual void addWindowToParent(GameWindow *window, GameWindow *parent);
	virtual void slot57();
	virtual int winSendSystemMsg(GameWindow *window, UnsignedInt msg, int mData1, int mData2);
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
	virtual GameFont *winFindFont(AsciiString name, Int size, bool bold);
	GameWindow *winCreate(Rva0047EDE0CreateInfo *info);
private:
	unsigned char m_pad04[0x0C - 0x04];
	GameWindow *m_windowList;
protected:
	void dumpWindow(GameWindow *window);
public:
	void linkWindow(GameWindow *win);
};

class GameWindow
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
	virtual Bool windowSlot10();
	void winSetFont(GameFont *font);
	Int winSetInstanceData(WinInstanceData *data);
	int m_field04;
	UnsignedInt m_status;
	unsigned char m_padC[0x1F8 - 0x0C];
	GameWindow *m_next;
	unsigned char m_pad1FC[8];
	GameWindow *m_child;
};

void GameWindowManager::dumpWindow(GameWindow *window)
{
	if (!window)
		return;

	for (GameWindow *child = window->m_child; child; child = child->m_next)
		dumpWindow(child);
}


// ?winCreate@GameWindowManager@@QAEPAVGameWindow@@PAURva0047EDE0CreateInfo@@@Z
// ?winCreate@GameWindowManager@@QAEPAVGameWindow@@PAURva0047EDE0CreateInfo@@@Z
GameWindow *GameWindowManager::winCreate(Rva0047EDE0CreateInfo *info)
{
	GameWindow *window;

	if (info->m_allocator)
	{
		window = info->m_allocator(info);
		if (window->m_field04 == 0 && window->windowSlot10())
			window->m_field04 = slot14();
	}
	else
	{
		window = slot15(info);
		if (window == NULL)
		{
			GameWindow *win;
			for (win = m_windowList; win; win = win->m_next)
				dumpWindow(win);
			return NULL;
		}
	}

	if (info->m_parent)
		addWindowToParent(window, info->m_parent);
	else
		linkWindow(window);

	if (info->m_field30)
		window->winSetInstanceData(info->m_field30);

	((Rva00477DF0 *)window)->orderPairs();

	winSendSystemMsg(window, 1, 0, 0);

	if (theGlobalLanguage() && !((const StringBase<char> *)&theGlobalLanguage()->m_defaultWindowFont.name)->isEmpty())
		window->GameWindow::winSetFont(winFindFont(theGlobalLanguage()->m_defaultWindowFont.name,
			theGlobalLanguage()->m_defaultWindowFont.size, theGlobalLanguage()->m_defaultWindowFont.bold));
	else
		window->GameWindow::winSetFont(winFindFont("Times New Roman", 14, FALSE));

	return window;
}
