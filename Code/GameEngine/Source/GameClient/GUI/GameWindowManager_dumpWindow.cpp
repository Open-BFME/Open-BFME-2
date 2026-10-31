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

#include "../../../Include/GameClient/GameWindowManager.h"

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
		window->GameWindow::winSetFont(slot76(theGlobalLanguage()->m_defaultWindowFont.name,
			theGlobalLanguage()->m_defaultWindowFont.size, theGlobalLanguage()->m_defaultWindowFont.bold));
	else
		window->GameWindow::winSetFont(slot76("Times New Roman", 14, FALSE));

	return window;
}
