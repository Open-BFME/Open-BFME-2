// ??0AptSaveLoad@@QAE@PAX@Z
// partial score=0.98 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /G6 /arch:SSE
// stlport
//
// AptSaveLoad::AptSaveLoad, retail 0x00436259 (1192 bytes).
//
// Identity (target evidence): WorldBuilder names the body
// AptSaveLoad::AptSaveLoad; it builds the Apt window base (0x0051268C),
// installs the vftables 0x00C3CDC8/0x00C3CDC4, records whether the game was
// paused, and for the first instance (0x00E032E0) binds the
// "AptSaveLoad::..." commands to the rowed handlers, registers its extern
// queries (names at 0x00DC8A20) with the Apt player, binds the InitGadgets
// screen reference, pauses the game and shows the background when no movie
// is playing. The binding idiom is the matched AptScoreScreen,
// AptOnlineLogin and AptStrategicPlayerStatus constructors'.

#include <vector>
#include <list>
#include "unicode_string.h"
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"

class GameWindow
{
protected:
	virtual ~GameWindow();
private:
	unsigned char m_pad004[0x218 - 4];
};

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

// The image binder at +0x40 of the Apt window half (0x00524306 family):
// window name to image name.
class Rva00524306
{
public:
	void rva00524767(const AsciiString &name, const AsciiString &image);
private:
	_STL::vector<AsciiString> m_names;
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10
	AptOverButtonHandlerAdder m_overButtonHandlers; // +0x1C
private:
	unsigned char m_pad028[0x40 - 0x28];
public:
	Rva00524306 m_imageAdder; // +0x40
private:
	unsigned char m_pad04C[0x58 - 0x4C];
};

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();
private:
	AsciiString m_filename; // +0x270
	int m_274;
	char m_278;
};


extern GameLogic *TheGameLogic;

class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

class AptPlayer
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);
};

extern AptPlayer *TheAptPlayer;

class Rva00222A8BTarget
{
public:
	void rva002233A6(int show);
	unsigned char m_pad000[0x31C];
	int m_31C; // +0x31C, nonzero while a movie plays
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

extern int g_Va00E032E0; // the first save/load screen

// The extern query enumeration's cursor (0x00435CFE starts it,
// 0x00435B4F compares, 0x0043611F advances, 0x0043549A maps to an index).
class Rva00435CFE
{
public:
	void rva00435CFE(unsigned short start);
	int m_0;
	int m_4;
};

class Gen_0056E190
{
public:
	explicit Gen_0056E190(int hash) { m_4 = hash; }
	~Gen_0056E190() {}
	bool bfmeDiffers(const Gen_0056E190 &other) const;
	int m_0;
	int m_4;
};

class Rva00435B82
{
public:
	Rva00435B82 *rva0043611F(Rva00435B82 *previous);
	int m_0;
	int m_4;
};

int Rva0043549AHook(int a, int b);

// The extern queries' names (0x00DC8A20).
static const char *s_externNames[] = { "SaveLoadMode", "GameTypes", "CurrentGameType" };

struct TreeHintOpaque0043671B
{
	void *m_0;
	void *m_4;
};

class GameWindow;

class AptSaveLoad : public _bfme_AptGameWindow
{
public:
	AptSaveLoad(void *context);
	virtual ~AptSaveLoad();
	void rva00433DF1(const char *unused); // "OnInitialized" and "ConfirmationCancel"
	void OnClosed(const char *unused);
	void Load(const char *unused);
	void Save(const char *unused);
	void Delete(const char *unused);
	void Cancel(const char *unused);
	void ConfirmationOk(const char *unused);
	void Externs(int query, char *value, bool set);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
private:
	int m_27C;
	int m_280;
	unsigned char m_wasPaused; // +0x284
	int m_288;
	int m_28C;
	int m_290;
	int m_294;
	int m_298;
	bool m_29C;
	bool m_29D;
	int m_2A0;
	bool m_2A4;
	int m_2A8;
	_STL::list<TreeHintOpaque0043671B> m_2AC;
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
AptSaveLoad::AptSaveLoad(void *context)
	: _bfme_AptGameWindow(context),
	  m_27C(0),
	  m_280(0),
	  m_wasPaused(TheGameLogic->isGamePaused()),
	  m_288(0),
	  m_28C(0),
	  m_290(0),
	  m_294(0),
	  m_298(0),
	  m_29C(false),
	  m_29D(true),
	  m_2A0(0),
	  m_2A4(false),
	  m_2A8(0)
{
	if (g_Va00E032E0 != 0)
		return;
	g_Va00E032E0 = (int)this;
#define BIND_COMMAND(handler, label) \
	{ \
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptSaveLoad::handler); \
		AsciiString name(label); \
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this)))); \
	}
	BIND_COMMAND(rva00433DF1, "AptSaveLoad::OnInitialized")
	BIND_COMMAND(OnClosed, "AptSaveLoad::OnClosed")
	BIND_COMMAND(Load, "AptSaveLoad::Load")
	BIND_COMMAND(Save, "AptSaveLoad::Save")
	BIND_COMMAND(Delete, "AptSaveLoad::Delete")
	BIND_COMMAND(Cancel, "AptSaveLoad::Cancel")
	BIND_COMMAND(ConfirmationOk, "AptSaveLoad::ConfirmationOk")
	BIND_COMMAND(rva00433DF1, "AptSaveLoad::ConfirmationCancel")
#undef BIND_COMMAND
	{
		Rva00435CFE query;
		query.rva00435CFE(0);
		Rva00435B82 previous;
		for (; ((const Gen_0056E190 *)&query)->bfmeDiffers(Gen_0056E190(0x3a76d6c6)); ((Rva00435B82 *)&query)->rva0043611F(&previous))
		{
			FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptSaveLoad::Externs);
			AsciiString name(s_externNames[(short)Rva0043549AHook(query.m_4, query.m_4)]);
			TheAptPlayer->AddExternHandler(name, (short)Rva0043549AHook(query.m_4, query.m_4),
				AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptSaveLoad::InitGadgets);
		AsciiString name("AptSaveLoad::InitGadgets");
		_bfme_setAptScreenRef(name, AptRef<AptScreenInitGadgets>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	TheGameLogic->rva0023CD9E(true, 2, true);
	m_2A4 = TheRva00222A8BTarget->m_31C == 0;
	if (m_2A4)
		TheRva00222A8BTarget->rva002233A6(1);
}
