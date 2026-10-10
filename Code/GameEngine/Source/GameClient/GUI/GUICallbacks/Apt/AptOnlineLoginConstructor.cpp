// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /G6 /arch:SSE
// stlport
//
// AptOnlineLogin::AptOnlineLogin, retail 0x00572885 (981 bytes).
//
// Identity (target evidence): WorldBuilder's AptOnlineLogin.cpp names the
// body; it builds the 0x60-byte Apt screen base 0x0056DC4C, installs the
// vftable 0x00C6DBBC, constructs the GameSpyLoginPreferences member at
// +0x60 and, for the first instance (0x00E062EC), binds the
// "AptOnline::Login::..." commands to the rowed handlers and the
// "AptOnlineLogin::InitGadgets" screen reference. The binding idiom is the
// matched AptScoreScreen constructor's.

#include <vector>
#include "unicode_string.h"
#include "ascii_string.h"

class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
	FunctorBinding(FunctorMethod method, FunctorTarget *target) : m_target(target), m_method(method) {}
	FunctorTarget *m_target;
	unsigned int m_pad;
	FunctorMethod m_method;
};

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
class AptOverButtonHandler;

class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);
private:
	_STL::vector<AsciiString> m_names;
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);
private:
	_STL::vector<AsciiString> m_names;
};

class AptOverButtonHandlerAdder
{
public:
	void AddOverButtonHandler(const AsciiString &name, AptRef<AptOverButtonHandler> handler);
private:
	_STL::vector<AsciiString> m_names;
};

class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

// The 0x60-byte Apt screen base (constructor 0x0056DC4C); its command map
// adder is at +0x04.
class Rva0056DC4C
{
public:
	Rva0056DC4C(void *shell);
	virtual ~Rva0056DC4C();
	AptCommandMapAdder m_commandMaps; // +0x04
private:
	unsigned char m_pad10[0x60 - 0x10];
};

class GameSpyLoginPreferences
{
public:
	GameSpyLoginPreferences();
	virtual ~GameSpyLoginPreferences();
private:
	unsigned char m_pad04[0x44 - 0x04];
};

class IMEManager
{
public:
#define IME_SLOT(N) virtual void slot##N();
	IME_SLOT(00) IME_SLOT(01) IME_SLOT(02) IME_SLOT(03) IME_SLOT(04) IME_SLOT(05)
	IME_SLOT(06) IME_SLOT(07) IME_SLOT(08) IME_SLOT(09) IME_SLOT(10) IME_SLOT(11)
	IME_SLOT(12) IME_SLOT(13) IME_SLOT(14) IME_SLOT(15) IME_SLOT(16)
#undef IME_SLOT
	virtual void slot17();
};

extern IMEManager *TheIMEManager;

class BfmeObjELB;
extern BfmeObjELB *g_bfmeObjELB; // the first login screen
// Owned here: set once from the first login screen above; retail .data
// starts it at 0 (VA 0x00A062EC).
BfmeObjELB *g_bfmeObjELB = 0;

class Rva0056EE5F
{
public:
	unsigned char rva0056EE5F();
};

class GameWindow;

class AptOnline
{
public:
	class Login
	{
	public:
		void ServiceTerms(const char *unused);
		void AcceptLocale(const char *unused);
		void CancelLogin(const char *unused);
		void OfficialSite(const char *unused);
		void GameSpy(const char *unused);
	};
};

class AptOnlineLogin : public Rva0056DC4C
{
public:
	AptOnlineLogin(AptOnline *shell);
	virtual ~AptOnlineLogin();
	void rva00572632(const char *unused); // "AptOnline::Login::Login"
	void DeleteNickname(const char *unused);
	void OnBttnRegisterFESL(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
private:
	GameSpyLoginPreferences m_preferences; // +0x60
	void *m_A4;
	void *m_A8;
	void *m_AC;
	void *m_B0;
	void *m_B4;
	int m_B8;
	int m_BC;
	int m_C0;
	bool m_C4;
	bool m_C5;
	unsigned char m_padC6[2];
	int m_C8;
	bool m_CC;
	bool m_CD;
	bool m_CE;
	unsigned char m_CF;
	unsigned char m_padD0[2];
	unsigned char m_D2;
	unsigned char m_padD3;
	int m_D4;
	AsciiString m_D8;
	bool m_DC;
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
AptOnlineLogin::AptOnlineLogin(AptOnline *shell)
	: Rva0056DC4C(shell),
	  m_A4(0),
	  m_A8(0),
	  m_AC(0),
	  m_B0(0),
	  m_B4(0),
	  m_BC(1),
	  m_C0(0),
	  m_C4(false),
	  m_C5(true),
	  m_C8(0),
	  m_CC(false),
	  m_CD(true),
	  m_CE(true),
	  m_CF(0),
	  m_D2(0),
	  m_D4(0),
	  m_DC(false)
{
	if (g_bfmeObjELB != 0)
		return;
	g_bfmeObjELB = (BfmeObjELB *)this;
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOnlineLogin::rva00572632);
		AsciiString name("AptOnline::Login::Login");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOnlineLogin::DeleteNickname);
		AsciiString name("AptOnline::Login::DeleteNickname");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOnlineLogin::OnBttnRegisterFESL);
		AsciiString name("AptOnline::Login::Register");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOnline::Login::ServiceTerms);
		AsciiString name("AptOnline::Login::ServiceTerms");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOnline::Login::AcceptLocale);
		AsciiString name("AptOnline::Login::AcceptLocale");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOnline::Login::CancelLogin);
		AsciiString name("AptOnline::Login::CancelLogin");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOnline::Login::OfficialSite);
		AsciiString name("AptOnline::Login::OfficialSite");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOnline::Login::GameSpy);
		AsciiString name("AptOnline::Login::GameSpy");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOnlineLogin::InitGadgets);
		AsciiString name("AptOnlineLogin::InitGadgets");
		_bfme_setAptScreenRef(name, AptRef<AptScreenInitGadgets>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	m_CF = ((Rva0056EE5F *)this)->rva0056EE5F();
	m_D2 = ((Rva0056EE5F *)this)->rva0056EE5F();
	TheIMEManager->slot17();
}
