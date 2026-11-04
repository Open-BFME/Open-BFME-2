// cl: /O1 /G7 /GX /MD /arch:SSE /DNDEBUG /Ireference/shims/bfme2_ascii
// AptWindowLayout::AptWindowLayout(void *), retail 0x0040FDD1..0x0040FE7A
// (169 bytes). Over the 0x24-byte window-list base it clears the owned game
// window and the +0x28 flag, asks TheWindowManager (slot 58) for the layout
// window of the base list, and when that is the list head registers its
// +0x270 filename as an Apt level under "Apt\\" (AptPlayer slot 20); a
// level below 14 is stored at window +0x274. The init callback at
// 0x0040FB9C (AptWindowLayout.cpp) is the same owner's slot 0.
#include "ascii_string.h"
class GameWindow;
// This trial retains the existing base constructor's ABI name. Its original
// class spelling is not established by that old donor name. Retail proves
// a 0x24-byte base with a window-list pointer at +8 and seven virtual slots.
class BfmeQuickMatchScreenBase {
public:
 BfmeQuickMatchScreenBase(void *);
 ~BfmeQuickMatchScreenBase();
 virtual void bfmeSlot0(); virtual void bfmeSlot1();
 virtual void bfmeSlot2(); virtual void bfmeSlot3();
 virtual void rva00538AB0(bool); virtual void bringForward();
 virtual void addWindow(GameWindow *);
protected:
 unsigned char pad04[4];
 GameWindow *m_windows;
 unsigned char pad0c[0x24-0x0c];
};
#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Include/GameClient/GameWindowManager.h"
extern GameWindowManager *TheWindowManager;
#include "../../../../Libraries/Source/Apt/AptPlayerClass.h"
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class AptWindowLayout : public BfmeQuickMatchScreenBase {
public:
 AptWindowLayout(void *info);
 virtual void bfmeSlot0(); virtual void bfmeSlot1();
 virtual void bfmeSlot2(); virtual void bfmeSlot3();
private:
 GameWindow *m_gameWindow;
 bool m_flag28;
};
AptWindowLayout::AptWindowLayout(void *info) : BfmeQuickMatchScreenBase(info)
{
 m_gameWindow=0;
 m_flag28=false;
 GameWindow *window=m_windows;
 TheWindowManager->winSendSystemMsg(window,29,2000,(unsigned int)&m_gameWindow);
 if(m_gameWindow!=window) return;
 const AsciiString &filename=*reinterpret_cast<AsciiString *>(reinterpret_cast<char *>(m_gameWindow)+0x270);
 int level=reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager)->AddLevel(AsciiString("Apt\\"),filename,false,reinterpret_cast<int>(m_gameWindow));
 if(static_cast<unsigned>(level)>=14) return;
 *reinterpret_cast<int *>(reinterpret_cast<char *>(m_gameWindow)+0x274)=level;
}

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:??1BfmeQuickMatchScreenBase@@QAE@XZ=??3@YAXPAX@Z")
#pragma comment(linker, "/alternatename:?addWindow@BfmeQuickMatchScreenBase@@UAEXPAVGameWindow@@@Z=?addWindow@WindowLayout@@UAEXPAVGameWindow@@@Z")
#pragma comment(linker, "/alternatename:?bfmeSlot0@AptWindowLayout@@UAEXXZ=?rva0040FB9C@AptWindowLayout@@UAEXPAX@Z")
#pragma comment(linker, "/alternatename:?bfmeSlot1@AptWindowLayout@@UAEXXZ=??_GRva0040FB4A@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?bfmeSlot2@AptWindowLayout@@UAEXXZ=?guard@Rva0040FC79Host@@QAEXH@Z")
#pragma comment(linker, "/alternatename:?bfmeSlot3@AptWindowLayout@@UAEXXZ=?rva0040FCC0@Rva0040FCC0@@QAEXH@Z")
#pragma comment(linker, "/alternatename:?bringForward@BfmeQuickMatchScreenBase@@UAEXXZ=?bringForward@WindowLayout@@UAEXXZ")
