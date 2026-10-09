// ??0AptWindowLayout@@QAE@PAX@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /GX /MD /arch:SSE /DNDEBUG /Ireference/shims/bfme2_ascii
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
class GameWindowManager {
public:
#define SLOT(n) virtual void slot##n();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7)
 SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
 SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
 SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
 SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
 SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
 SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
 SLOT(56) SLOT(57)
#undef SLOT
 virtual void getWindow(GameWindow *,unsigned,unsigned,GameWindow **);
};
extern GameWindowManager *TheWindowManager;
class AptPlayer {
public:
#define SLOT(n) virtual void slot##n();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7)
 SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
 SLOT(16) SLOT(17) SLOT(18) SLOT(19)
#undef SLOT
 virtual int AddLevel(AsciiString,AsciiString,bool,int);
};
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
 TheWindowManager->getWindow(window,29,2000,&m_gameWindow);
 if(m_gameWindow!=window) return;
 const AsciiString &filename=*reinterpret_cast<AsciiString *>(reinterpret_cast<char *>(m_gameWindow)+0x270);
 int level=reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager)->AddLevel(AsciiString("Apt\\"),filename,false,reinterpret_cast<int>(m_gameWindow));
 if(static_cast<unsigned>(level)>=14) return;
 *reinterpret_cast<int *>(reinterpret_cast<char *>(m_gameWindow)+0x274)=level;
}
