// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??0Rva005BA1FDBase@@QAE@HH@Z, retail 0x005A5BC7..0x005A61C6 (1535 bytes,
// EH, ret 8). The pinned spelling names it the base constructor the
// OnlineOpenPlay screen ctor 0x005BA1FD calls with (shell, 0) right after a
// 0x4E0-byte operator new.
//
// Identity: it installs vftable 0x00871414 -- the vftable of
// AptOnlineCustomMatch whose dtor 0x005A0009 is matched -- and binds the
// rowed AptOnlineCustomMatch callbacks to the "AptOnline::CustomMatch::*"
// Apt names (WorldBuilder twin 0x014E6450 pushes the same names), so it is
// the AptOnlineCustomMatch constructor.
//
// Body: the screen base (rowed ctor 0x0056DC4C taking the shell; unwind
// through the rowed 0x0056DC6B), the MpOwner interface at +0x60 (rowed
// 0x004444AE / 0x004444D2), the 4-byte interface at +0x6C (inline;
// vftable 0x008711BC), the game setup member at +0x70 (pinned 0x00441ECE
// with the +0x60 interface and mask 0x200001F0; dtor 0x004421E1), the
// GameSorter at +0x450 (rowed 0x00580842 with the screen), the custom
// preferences at +0x46C (rowed 0x0054F52F with the second argument), the
// state words +0x488.. and the "APT:NULL" AsciiString at +0x4D0. It then
// bumps the live-instance count 0x00E063F0, records itself at 0x00E063EC,
// runs the rowed setup members 0x004422B4 and 0x0044303D, binds the
// fourteen callbacks through the command map adder at +0x04 (rowed
// 0x0052458E; functor holder 0x0057BC63) and the InitGadgets screen ref
// (rowed 0x00411458), loads the sorter from the preferences (rowed
// 0x00580263) and resets TheGameSpyGame's +0xFF4/+0xFF8 before the rowed
// GameInfo 0x003FF1A7. Pattern and views follow the matched
// AptOnlineQuickMatchConstructor.cpp.

#include "ascii_string.h"

class GameWindow;

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
	unsigned char m_pad04[0x60 - 4];
};

class Rva0056DC4C : public Rva005248D0
{
public:
	Rva0056DC4C(void *);
	virtual ~Rva0056DC4C();
};

class __declspec(novtable) Rva0056DC6B : public Rva0056DC4C
{
public:
	Rva0056DC6B(void *shell) : Rva0056DC4C(shell) {}
	virtual ~Rva0056DC6B();
};

class Rva004444D2
{
public:
	Rva004444D2();
	virtual ~Rva004444D2();
private:
	unsigned char m_pad04[0x0C - 4];
};

class Rva0059EB41
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual ~Rva0059EB41() {}
};

class Rva004421E1
{
public:
	Rva004421E1(Rva004444D2 *owner, int mask);
	virtual ~Rva004421E1();
private:
	unsigned char m_pad04[0x450 - 0x70 - 4];
};

class AptMpGameSetup
{
public:
	void rva004422B4(int);
	void rva0044303D();
};

class GameSorter
{
public:
	GameSorter(Rva005248D0 *registry);
	~GameSorter();
private:
	unsigned char m_pad[0x46C - 0x450];
};

class Rva00580316
{
public:
	void rva00580263(void *prefs);
};

class Rva0054F508
{
public:
	Rva0054F508(int);
	virtual ~Rva0054F508();
private:
	unsigned char m_pad04[0x488 - 0x46C - 4];
};

class GameInfo
{
public:
	void rva003FF1A7(int);
};

class GameSpyStagingRoom : public GameInfo
{
public:
	void clearFF4()
	{
		m_FF8 = 0;
		m_FF4 = false;
	}
	unsigned char m_pad000[0xFF4];
	bool m_FF4;
	int m_FF8;
};
extern GameSpyStagingRoom *TheGameSpyGame;

extern int g_currentAptOnlineCustomMatch;
extern int g_Va00E063F0;

class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)();
struct FunctorBinding
{
	FunctorBinding(FunctorMethod m, FunctorTarget *t) : target(t), method(m) {}
	FunctorTarget *target;
	unsigned pad;
	FunctorMethod method;
};
class FunctorWrapperHead
{
public:
	void *vt;
	int count;
};
class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &);
	Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &x) : ptr(x.ptr)
	{
		if (ptr) ++ptr->count;
	}
	FunctorWrapperHead *ptr;
};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
template <class T> class AptRef : public Rva0057BC63FunctorHolder
{
public:
	AptRef(FunctorBinding b) : Rva0057BC63FunctorHolder(b) {}
	~AptRef()
	{
		if (ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)ptr);
	}
};
class AptCommandMap;
class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &, AptRef<AptCommandMap>);
};
class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

// The callbacks keep the multiple-inheritance member pointer form
// ({function, 0}); their classes are viewed with two bases for that.
class CustomMatchBindingA
{
public:
	virtual void a00();
};
class CustomMatchBindingB
{
public:
	virtual void b00();
};
class AptOnlineCustomMatch : public CustomMatchBindingA, public CustomMatchBindingB
{
public:
	void LoadGame(const char *);
	void AcceptJoinGame(const char *);
	void PlayGame(const char *);
	void OnBttnCancel(int);
	void Refresh(const char *);
	void OnOpenCreateDialog(const char *);
	void CancelPopUpCreate(const char *);
	void CancelPopUpHost(const char *);
	void OnOpenConnectionsScreen(const char *);
	void OnClosingConnectionsScreen(const char *);
	void InitGadgets(const char *, int, GameWindow *);
};
class Rva0059ECD2 : public CustomMatchBindingA, public CustomMatchBindingB
{
public:
	void rva0059ECD2(int);
	void rva0059EC72(int);
};
class Rva0059ECAD : public CustomMatchBindingA, public CustomMatchBindingB
{
public:
	void rva0059ECAD(int);
};

typedef void (AptOnlineCustomMatch::*CustomMatchText)(const char *);
typedef void (AptOnlineCustomMatch::*CustomMatchInt)(int);
typedef void (AptOnlineCustomMatch::*CustomMatchInitGadgets)(const char *, int, GameWindow *);
typedef void (Rva0059ECD2::*CustomMatchPopUp)(int);
typedef void (Rva0059ECAD::*CustomMatchJoin)(int);

class Rva005BA1FDBase : public Rva0056DC6B, public Rva004444D2, public Rva0059EB41
{
public:
	Rva005BA1FDBase(int shell, int profile);
	virtual ~Rva005BA1FDBase();

private:
	AptCommandMapAdder *commandMaps() { return (AptCommandMapAdder *)((char *)this + 4); }
	Rva004421E1 m_setup; // +0x70
	GameSorter m_sorter; // +0x450
	Rva0054F508 m_prefs; // +0x46C
	int m_state; // +0x488
	int m_48C;
	int m_490;
	int m_494;
	GameWindow *m_498;
	GameWindow *m_49C;
	bool m_4A0;
	int m_4A4;
	int m_4A8;
	int m_4AC;
	int m_4B0;
	bool m_4B4;
	int m_4B8;
	int m_4BC;
	bool m_4C0;
	bool m_4C1;
	bool m_4C2;
	int m_4C4;
	int m_4C8;
	int m_4CC;
	AsciiString m_4D0;
	int m_4D4;
	bool m_4D8;
	int m_4DC;
};

#define CM_BIND(text, pmf, type)                                                                \
	{                                                                                           \
		FunctorMethod method = reinterpret_cast<FunctorMethod>(static_cast<type>(pmf));         \
		AsciiString name(text);                                                                 \
		commandMaps()->AddCommandMap(name,                                                      \
			AptRef<AptCommandMap>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this)))); \
	}

Rva005BA1FDBase::Rva005BA1FDBase(int shell, int profile)
	: Rva0056DC6B((void *)shell), m_setup(this, 0x200001F0), m_sorter(this), m_prefs(profile),
	  m_state(0), m_48C(0), m_490(0), m_498(0), m_49C(0), m_4A0(false), m_4A4(0), m_4A8(-1),
	  m_4AC(0), m_4B0(0), m_4B4(false), m_4B8(0), m_4BC(0), m_4C0(false), m_4C1(true), m_4C2(true),
	  m_4C4(0), m_4C8(0), m_4CC(0), m_4D0("APT:NULL"), m_4D4(0), m_4D8(false), m_4DC(0)
{
	++g_Va00E063F0;
	g_currentAptOnlineCustomMatch = (int)this;
	reinterpret_cast<AptMpGameSetup *>(&m_setup)->rva004422B4(profile);
	CM_BIND("AptOnline::CustomMatch::CancelPopUpJoin", &Rva0059ECD2::rva0059ECD2, CustomMatchPopUp)
	CM_BIND("AptOnline::CustomMatch::CreateGame", &Rva0059ECD2::rva0059EC72, CustomMatchPopUp)
	CM_BIND("AptOnline::CustomMatch::JoinGame", &Rva0059ECAD::rva0059ECAD, CustomMatchJoin)
	CM_BIND("AptOnline::CustomMatch::LoadGame", &AptOnlineCustomMatch::LoadGame, CustomMatchText)
	CM_BIND("AptOnline::CustomMatch::AcceptJoinGame", &AptOnlineCustomMatch::AcceptJoinGame, CustomMatchText)
	CM_BIND("AptOnline::CustomMatch::PlayGame", &AptOnlineCustomMatch::PlayGame, CustomMatchText)
	CM_BIND("AptOnline::CustomMatch::Cancel", &AptOnlineCustomMatch::OnBttnCancel, CustomMatchInt)
	CM_BIND("AptOnline::CustomMatch::Refresh", &AptOnlineCustomMatch::Refresh, CustomMatchText)
	CM_BIND("AptOnline::OnOpenCreateDialog", &AptOnlineCustomMatch::OnOpenCreateDialog, CustomMatchText)
	CM_BIND("AptOnline::CustomMatch::CancelPopUpCreate", &AptOnlineCustomMatch::CancelPopUpCreate, CustomMatchText)
	CM_BIND("AptOnline::CustomMatch::CancelPopUpHost", &AptOnlineCustomMatch::CancelPopUpHost, CustomMatchText)
	CM_BIND("AptOnline::CustomMatch::OnOpenConnectionsScreen", &AptOnlineCustomMatch::OnOpenConnectionsScreen, CustomMatchText)
	CM_BIND("AptOnline::CustomMatch::OnClosingConnectionsScreen", &AptOnlineCustomMatch::OnClosingConnectionsScreen, CustomMatchText)
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(static_cast<CustomMatchInitGadgets>(&AptOnlineCustomMatch::InitGadgets));
		AsciiString name("AptOnlineCustomMatch::InitGadgets");
		_bfme_setAptScreenRef(name,
			AptRef<AptScreenInitGadgets>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	reinterpret_cast<AptMpGameSetup *>(&m_setup)->rva0044303D();
	reinterpret_cast<Rva00580316 *>(&m_sorter)->rva00580263(&m_prefs);
	if (TheGameSpyGame) {
		TheGameSpyGame->clearFF4();
		TheGameSpyGame->rva003FF1A7(profile);
	}
}
