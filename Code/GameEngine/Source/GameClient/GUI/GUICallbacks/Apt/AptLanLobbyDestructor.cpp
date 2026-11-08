// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// AptLanLobby lifetime recovery; destructor: native 44455C..44467C, WB140D710,
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
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

#include "../../../../../Include/GameClient/FunctorBinding.h"

class FunctorWrapperHead
{
public:
	void *m_vtbl;
	int m_refCount; // +0x04
};

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
	Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
	}

	FunctorWrapperHead *m_ptr;
};

__forceinline FunctorBinding MakeBinding(FunctorMethod method, FunctorTarget *target)
{
	FunctorBinding binding(method, target);
	return binding;
}

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

template <class T> class AptRef : public Rva0057BC63FunctorHolder
{
public:
	AptRef(const FunctorBinding &binding) : Rva0057BC63FunctorHolder(binding) {}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

class AptCommandMap;
class AptExternHandler;

#include "../../../../../../Libraries/Source/Apt/AptCommandMapAdder.h"

class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);


class GameWindow { public: virtual ~GameWindow(); private: char storage[0x218-4]; };
#include "../../../../../Include/GameClient/Rva005248D0.h"
class _bfme_AptGameWindow : public GameWindow, public Rva005248D0 {
public: _bfme_AptGameWindow(void *context); virtual ~_bfme_AptGameWindow();
private: AsciiString filename270; void *owner274; int tail278;
};
class Rva004444D2 { public: Rva004444D2(); virtual ~Rva004444D2(); private: char storage[8]; };
class MpGameSetupOwner;
class AptMpGameSetup { public: AptMpGameSetup(MpGameSetupOwner*,int); virtual ~AptMpGameSetup(); private: char storage[0x3E0-4]; };
class LANPreferences { public: LANPreferences(int); virtual ~LANPreferences(); private: char storage[0x1C-4]; };
class Rva0031455E { public: Rva0031455E(); virtual ~Rva0031455E(); private: char storage[8]; };
class AptLanLobbyNameEntry : public Rva0031455E {
public: AptLanLobbyNameEntry() {}
 unsigned char flag0,flag1,active,flag3; int kind; unsigned char flag4; char pad[3];
};
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
#include "../../../../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
#include "../../../../../Include/GameNetwork/LANAPI.h"
extern LANAPI *TheLAN;
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
#include <new>
class Member004443E7
{
public:
	virtual void s0();
	virtual void s1();
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


#include "../../../../../Include/Common/GameEngine.h"
extern GameEngine *TheGameEngine;

class AptLanLobby : public _bfme_AptGameWindow, public Rva004444D2 {
public: virtual ~AptLanLobby(); void rva004443E7();
 AptLanLobby(void*);
 void Cancel(int);
 void InitGadgets(const char*,void*,GameWindow*);
 void OnOptionsBttn(const char*);
 void OnExitBttn(const char*);
 void OnStartGameBttn(const char*);
 void OnLoadGameBttn(const char*);
 void OnLoadScreen(const char*);
 void OnCreateGameBttn(const char*);
 void OnInitialized(const char*);
 void OnJoinGameBttn(const char*);

private:
 AptMpGameSetup panel;
 GameSorter sorter;
 LANPreferences preferences;
 UnicodeString name;
 int state; void *games;
 AptLanLobbyNameEntry entry;
 static AptLanLobby *s_instance;
};
typedef char CheckSize[(sizeof(AptLanLobby)==0x6C4)?1:-1];
AptLanLobby::~AptLanLobby() {
 if (s_instance == this) {
  rva004443E7();
  ::delete TheLAN;
  TheLAN=0;
  entry.active=0;
  { AsciiString gadget("AptLanLobby::InitGadgets"); _bfme_closeAptScreen(gadget); }
  if (TheWindowManager) ((WindowManagerView*)TheWindowManager)->slot45();
  s_instance=0;
  Rva00511F73Run();
 }
}

void AptLanLobby::rva004443E7() {
 ((Member004443E7*)&panel)->s1();
 Global004443E7958View *g=(Global004443E7958View*)TheLAN;
 if (g) g->g18();
 TheGameEngine->stopHeadlessClients();
}

#include "../../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
void Rva00512069Register();
// Native445EE3..446386: complete1187B constructor. Target callback strings,
// member construction, field stores and the existing6C4-byte factory prove
// this screen identity and layout. Keep the name-entry destructor implicit:
// an explicit empty destructor adds a non-retail table store to teardown.
#pragma pointers_to_members(full_generality, multiple_inheritance)
AptLanLobby::AptLanLobby(void *context)
 :_bfme_AptGameWindow(context),panel((MpGameSetupOwner*)static_cast<Rva004444D2*>(this),0x400001A0),
 sorter((Rva005248D0*)this),preferences(-1),state(0),games(0) {
 entry.flag0=0;entry.flag1=0;entry.active=0;entry.flag3=0;entry.kind=2;entry.flag4=0;
 if (!s_instance) {
  s_instance=this;
  {
   FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptLanLobby::OnInitialized);
   AsciiString name("AptLanLobby::OnInitialized");
   AddCommandMap(name,AptRef<AptCommandMap>(MakeBinding(method,reinterpret_cast<FunctorTarget*>(this))));
  }
  {
   FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptLanLobby::Cancel);
   AsciiString name("AptLanLobby::OnCancelBttn");
   AddCommandMap(name,AptRef<AptCommandMap>(MakeBinding(method,reinterpret_cast<FunctorTarget*>(this))));
  }
  {
   FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptLanLobby::OnExitBttn);
   AsciiString name("AptLanLobby::OnExitBttn");
   AddCommandMap(name,AptRef<AptCommandMap>(MakeBinding(method,reinterpret_cast<FunctorTarget*>(this))));
  }
  {
   FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptLanLobby::OnStartGameBttn);
   AsciiString name("AptLanLobby::OnStartGameBttn");
   AddCommandMap(name,AptRef<AptCommandMap>(MakeBinding(method,reinterpret_cast<FunctorTarget*>(this))));
  }
  {
   FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptLanLobby::OnCreateGameBttn);
   AsciiString name("AptLanLobby::OnCreateGameBttn");
   AddCommandMap(name,AptRef<AptCommandMap>(MakeBinding(method,reinterpret_cast<FunctorTarget*>(this))));
  }
  {
   FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptLanLobby::OnJoinGameBttn);
   AsciiString name("AptLanLobby::OnJoinGameBttn");
   AddCommandMap(name,AptRef<AptCommandMap>(MakeBinding(method,reinterpret_cast<FunctorTarget*>(this))));
  }
  {
   FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptLanLobby::OnLoadGameBttn);
   AsciiString name("AptLanLobby::OnLoadGameBttn");
   AddCommandMap(name,AptRef<AptCommandMap>(MakeBinding(method,reinterpret_cast<FunctorTarget*>(this))));
  }
  {
   FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptLanLobby::OnOptionsBttn);
   AsciiString name("AptLanLobby::OnOptionsBttn");
   AddCommandMap(name,AptRef<AptCommandMap>(MakeBinding(method,reinterpret_cast<FunctorTarget*>(this))));
  }
  {
   FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptLanLobby::OnLoadScreen);
   AsciiString name("AptLanLobby::OnLoadScreen");
   AddCommandMap(name,AptRef<AptCommandMap>(MakeBinding(method,reinterpret_cast<FunctorTarget*>(this))));
  }
  {
   FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptLanLobby::InitGadgets);
   AsciiString name("AptLanLobby::InitGadgets");
   _bfme_setAptScreenRef(name,AptRef<AptScreenInitGadgets>(MakeBinding(method,reinterpret_cast<FunctorTarget*>(this))));
  }
  { AsciiString name("APT:OnlineOrNetwork");
    g_bfmeAptWindowManager->bfmeSetText(name,TheGameText->fetch("APT:Network"),false); }
  Rva00512069Register();
 }
}

// Native constructor445FC7 pairs AptLanLobby::OnInitialized at83E414 with
// function pointer47A69C at445FD5 and the full-screen receiver. Retail folds
// this empty RET4 callback; its complete3B body has no relocations.
void AptLanLobby::OnInitialized(const char *)
{
}
