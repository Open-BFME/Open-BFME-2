// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/GameClient/GUI/Gadget/Rva004BE120TextEntryInput.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?input@Rva004BE120Input@@QAEHIII@Z 0x003206A4 (55B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// Retail 0x004BE120, 66 bytes. The callback table at 0x00D051F0
// identifies this input route, but no owner name is established.
// GWM_IME_CHAR is filtered through the landed character policy; all other
// messages and accepted characters forward through ILT 0x00003DF0.
//
// ?system@Rva004BE120Input@@QAEHIII@Z 0x003206DB (56B) is the next slot (4)
// of the same vtable 0x00867840, after input at slot 3. Target facts: window
// message 27 with a non-zero first datum hands the window at +0x08 to
// TheWindowManager slot 49 (winSetFocus, see GameWindowManager_winSetFocus.cpp);
// every message then forwards to the rowed base dispatch 0x003145B1 and its
// result is returned. Donor shape: Open-BFME-1 BfmeConv983.cpp
// BfmeG983::bfmeGo983 (retail 0x004BE180), whose manager slot is 44 there.
typedef unsigned short WideChar;

class GameWindow;

#include "../../../../Include/GameLogic/Rva003145B1.h"

#include "../../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

class Rva004BE120Input
{
public:
    int input(unsigned int msg, unsigned int data1, unsigned int data2);
    int system(unsigned int msg, unsigned int data1, unsigned int data2);

private:
    char m_unreconstructed00[8];
    GameWindow *m_window;
    int m_characterFlags;
};

extern bool __cdecl GadgetTextEntryValidateCharacter(
    WideChar character, signed char flags);

int Rva004BE120Input::input(unsigned int msg, unsigned int data1,
                           unsigned int data2)
{
    // The caller passes the full +0x0C dword. The policy consumes its low
    // byte, so retain the retail stack argument without narrowing it here.
    typedef bool (__cdecl *RawCharacterPolicy)(WideChar, int);
    RawCharacterPolicy policy = reinterpret_cast<RawCharacterPolicy>(
        &GadgetTextEntryValidateCharacter);
    if (msg == 0x19 && !policy((WideChar)data1, m_characterFlags))
        return 1;

    // The fallback is the rowed Rva003145B1::rva00314596 dispatch, a thiscall
    // that tails through a virtual slot and removes all three arguments.
    return ((Rva003145B1 *)this)->rva00314596(msg, data1, data2);
}

int Rva004BE120Input::system(unsigned int msg, unsigned int data1,
                            unsigned int data2)
{
    if (msg == 0x1b && data1)
        TheWindowManager->winSetFocus(m_window);

    return ((Rva003145B1 *)this)->Rva003145B1Dispatch(msg, data1, data2);
}
