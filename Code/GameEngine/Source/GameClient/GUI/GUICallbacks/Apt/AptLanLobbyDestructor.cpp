// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// AptLanLobby destructor: native 44455C..44467C, WB140D710,
// AptLanLobby.cpp:189. BFME1 donor9cbfb551fe20dae985f91f2319d8997287b6a705
// game/GameEngine/Source/GameClient/GUI/BfmeAptScreenLanLobbyDestructor.cpp
// supplied the lifetime structure; target evidence determines every receiver,
// state transition and call here. The complete BFME2 constructor445EE3 also
// proves the interfaces0/218/27C and members288/668/684/6A0/6AC.
// These are consumed class views, not a complete virtual-interface recovery.
// The base hierarchy and 27C extent follow the verified campaign review/base
// destructor sources. GameSorter stores game pointers: 580B40 adds LAN list
// entries and 58113D returns them after sorting through GameInfo virtuals;
// the same sorter serves the online lobby. GameSorterDestructor.cpp supplies
// the separate complete14B7FAB3 teardown, proven with all relocations.
// rva004443E7 is the existing37B cleanup member rehomed from
// AptLanLobbyGameCreate.cpp so teardown and its cleanup share this layout.
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>
class GameWindow { public: virtual ~GameWindow(); private: char storage[0x218-4]; };
class Rva005248D0 { public: virtual ~Rva005248D0(); private: char storage[0x58-4]; };
class _bfme_AptGameWindow : public GameWindow, public Rva005248D0 {
public: virtual ~_bfme_AptGameWindow();
private: AsciiString filename270; void *owner274; int tail278;
};
class Rva004444D2 { public: virtual ~Rva004444D2(); private: char storage[8]; };
class Rva004421E1 { public: virtual ~Rva004421E1(); private: char storage[0x3E0-4]; };
class LANPreferences { public: virtual ~LANPreferences(); private: char storage[0x1C-4]; };
class Rva0031455E { public: virtual ~Rva0031455E(); public: char storage[0xE-4]; unsigned char active; char tail[0x18-0xF]; };
// Game-sort entries are GameInfo pointers: LAN list append 580B40 and
// indexed result 58113D; shared sorter is used by the online screen too.
class GameInfo;
class Rva005248D0;
class GameSorter {
public:
 GameSorter(Rva005248D0 *registry);
 ~GameSorter();
private:
 _STL::vector<GameInfo*> m_games;
 int m_primarySort;
 int m_previousSort;
 bool m_changed;
 bool m_sorted;
 int m_cycle;
};
class LANAPI { public: virtual void *deleteObject(int); };
extern LANAPI *TheLAN;
extern int g_Va00A03354;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class WindowManagerView { public:
#define SLOT(N) virtual void slot##N();
 SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
 SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
 SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
 SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
 SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
 SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45)
#undef SLOT
};
class GameWindowManager;
extern GameWindowManager *TheWindowManager;
void _bfme_closeAptScreen(const AsciiString&);
void Rva00511F73Run();
void __cdecl operator delete(void*);
class Member004443E7
{
public:
	virtual void s0();
	virtual void s1();

	// Unrowed 0x0044303D (1040 bytes; registers the panel's Apt callbacks),
	// pinned by address.
	void rva0044303D();
};

class Global004443E7958View
{
public:
	virtual void g0();
	virtual void g1();
	virtual void g2();
	virtual void g3();
	virtual void g4();
	virtual void g5();
	virtual void g6();
	virtual void g7();
	virtual void g8();
	virtual void g9();
	virtual void g10();
	virtual void g11();
	virtual void g12();
	virtual void g13();
	virtual void g14();
	virtual void g15();
	virtual void g16();
	virtual void g17();
	virtual void g18();
};


class GameEngine { friend class AptLanLobby; void stopHeadlessClients(); };
extern GameEngine *TheGameEngine;

class AptLanLobby : public _bfme_AptGameWindow, public Rva004444D2 {
public: virtual ~AptLanLobby(); void rva004443E7();
private:
 Rva004421E1 panel;
 GameSorter sorter;
 LANPreferences preferences;
 UnicodeString name;
 int state; void *games;
 Rva0031455E entry;
};
typedef char CheckSize[(sizeof(AptLanLobby)==0x6C4)?1:-1];
AptLanLobby::~AptLanLobby() {
 if ((void*)g_Va00A03354 == this) {
  rva004443E7();
  void *dead=TheLAN ? TheLAN->deleteObject(0) : 0;
  ::operator delete(dead);
  TheLAN=0;
  entry.active=0;
  { AsciiString gadget("AptLanLobby::InitGadgets"); _bfme_closeAptScreen(gadget); }
  if (TheWindowManager) ((WindowManagerView*)TheWindowManager)->slot45();
  g_Va00A03354=0;
  Rva00511F73Run();
 }
}

void AptLanLobby::rva004443E7() {
 ((Member004443E7*)&panel)->s1();
 Global004443E7958View *g=(Global004443E7958View*)TheLAN;
 if (g) g->g18();
 TheGameEngine->stopHeadlessClients();
}
