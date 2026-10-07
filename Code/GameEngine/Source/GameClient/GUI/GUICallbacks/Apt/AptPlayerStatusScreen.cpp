// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// BFME2's in-game player status / objectives screen (PlayerStatus.apt and
// Objectives.apt share it): its constructor, which binds the callbacks of
// AptPlayerStatusCallbacks.cpp by name, and the Apt queries that need an
// EH frame. BFME 1's AptScreenFactories.cpp (0x0052C660) is the donor.

#include <vector>
#include "ascii_string.h"

extern "C" void *__cdecl memset(void *destination, int value, unsigned int count);

class GameWindow
{
protected:
	virtual ~GameWindow();

private:
	unsigned char m_pad004[0x218 - 4];
};

// The window manager's background switch (VA 0x00DFE4CC).
class Rva00222A8BTarget
{
public:
	void rva002233A6(int mode);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

// The Apt callback functors (Rva0057BC63FunctorHolder.cpp, as in
// AptScoreScreenCallbacks.cpp).
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

class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

// The Apt screen base (BfmeAptGameWindowDestructor.cpp): a 0x218-byte
// GameWindow and, at +0x218, the 0x58-byte callback registry.
class Rva005248D0
{
public:
	virtual ~Rva005248D0();

	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10

private:
	unsigned char m_pad01C[0x58 - 0x1C];
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

// The open player status screen (VA 0x00E04450).
extern int g_Va00E04450;

class GameWindow;

class AptPlayerStatus : public _bfme_AptGameWindow
{
public:
	AptPlayerStatus(void *context);
	virtual ~AptPlayerStatus();

	// AptPlayerStatusCallbacks.cpp.
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void rva004E4A34(const char *unused);
	void PlayerColor(int slot, char *result, bool set);
	void Objective(int row, char *result, bool skip);
	// "AptObjectivesMenu::ReturnToGame" (rowed as the stdcall
	// Rva004E40A6Enable), pinned by address.
	void rva004E40A6(const char *unused);
	// Unrowed 0x004E434C: "NumOfPlayers", "InSkirmish" and
	// "AptObjectivesMenu::InputEnabled" by index, pinned by address.
	void rva004E434C(int query, char *result, bool set);
	// Unrowed 0x004E4553: "Objective%d", the row's objective text, pinned
	// by address.
	void rva004E4553(int row, char *result, bool set);

private:
	_STL::vector<int> m_colors; // +0x27C
	int m_state; // +0x288
	GameWindow *m_mute[8]; // +0x28C
	signed char m_slot[8]; // +0x2AC
};

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

// The game mode at +0x110 (2 skirmish, 6 the one where the UI's +0x16
// flag decides whether input is enabled).
class GameLogic
{
public:
	unsigned char m_pad000[0x110];
	int m_gameMode; // +0x110
};

extern GameLogic *TheGameLogic;

class InGameUI
{
public:
	unsigned char m_pad00[0x16];
	bool m_16; // +0x16
};

extern InGameUI *TheInGameUI;

// The objectives (Rva0039B95FCount.cpp's g_00E031E8; its +0x10 list is
// Rva0051C0E7Ctor.cpp's Rva004266A1, whose rowed 0x004267E9 returns an
// objective's text).
struct Rva0039B95FHolder;
extern Rva0039B95FHolder *g_00E031E8;

class Rva004266A1
{
public:
	void *rva004267E9(int index);
};

struct AptPlayerStatusObjectives
{
	unsigned char m_pad00[0x10];
	Rva004266A1 *m_list; // +0x10
};

// AptPlayerStatusCallbacks.cpp's row-to-objective map, pinned by address.
int __cdecl Rva004E43F2(int row);

// The string's buffer header (ascii_string.h: a count, the length, the
// capacity, then the characters).
struct AptPlayerStatusTextData
{
	int m_refCount;
	unsigned short m_length; // +0x04
	unsigned short m_capacity;
	char m_chars[1]; // +0x08
};

// The extern queries' names, by index (0x00C621A8).
static const char *const s_externNames[] = { "NumOfPlayers", "InSkirmish", "AptObjectivesMenu::InputEnabled" };

// Retail 0x004E4A45, 954 bytes: the screen's constructor. The first one
// opened becomes g_Va00E04450 and binds its callbacks by name under both
// screens' prefixes, the three extern queries, "Objective1".."12" with
// their "Status" twins, "ScoreScreen:PlayerColor:0".."7", switches the
// window manager's background and binds InitGadgets as its screen
// reference.
#pragma pointers_to_members(full_generality, multiple_inheritance)
AptPlayerStatus::AptPlayerStatus(void *context)
	: _bfme_AptGameWindow(context),
	  m_state(2)
{
	if (g_Va00E04450 != 0)
		return;
	g_Va00E04450 = (int)this;
	memset(m_mute, 0, sizeof(m_mute));
	memset(m_slot, 0, sizeof(m_slot));
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptPlayerStatus::rva004E4A34);
		AsciiString name("AptObjectivesMenu::OnInitialized");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptPlayerStatus::rva004E40A6);
		AsciiString name("AptObjectivesMenu::ReturnToGame");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptPlayerStatus::rva004E4A34);
		AsciiString name("AptPlayerStatus::OnInitialized");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptPlayerStatus::rva004E40A6);
		AsciiString name("AptPlayerStatus::ReturnToGame");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptPlayerStatus::rva004E434C);
		int query = 0;
		FunctorBinding binding = MakeBinding(method, reinterpret_cast<FunctorTarget *>(this));
		for (; query < 3; ++query)
		{
			AsciiString name(s_externNames[query]);
			m_externHandlers.AddExternHandler(name, query, AptRef<AptExternHandler>(binding));
		}
	}
	AsciiString name;
	{
		FunctorMethod textMethod = reinterpret_cast<FunctorMethod>(&AptPlayerStatus::rva004E4553);
		int index = 0;
		FunctorBinding text = MakeBinding(textMethod, reinterpret_cast<FunctorTarget *>(this));
		FunctorMethod statusMethod = reinterpret_cast<FunctorMethod>(&AptPlayerStatus::Objective);
		FunctorBinding status = MakeBinding(statusMethod, reinterpret_cast<FunctorTarget *>(this));
		for (; index < 12; ++index)
		{
			name.format("Objective%d", index + 1);
			m_externHandlers.AddExternHandler(name, index, AptRef<AptExternHandler>(text));
			name.concat("Status");
			m_externHandlers.AddExternHandler(name, index, AptRef<AptExternHandler>(status));
		}
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptPlayerStatus::PlayerColor);
		int slot = 0;
		FunctorBinding binding = MakeBinding(method, reinterpret_cast<FunctorTarget *>(this));
		for (; slot < 8; ++slot)
		{
			name.format("ScoreScreen:PlayerColor:%d", slot);
			m_externHandlers.AddExternHandler(name, slot, AptRef<AptExternHandler>(binding));
		}
	}
	TheRva00222A8BTarget->rva002233A6(2);
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptPlayerStatus::InitGadgets);
		AsciiString screen("AptPlayerStatus::InitGadgets");
		_bfme_setAptScreenRef(screen, AptRef<AptScreenInitGadgets>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
}

// Retail 0x004E434C, 166 bytes: "NumOfPlayers" (the number of colors once
// the rows are up), "InSkirmish" and "AptObjectivesMenu::InputEnabled",
// answered "0" or "1" ("0" when set).
void AptPlayerStatus::rva004E434C(int query, char *result, bool set)
{
	result[0] = '0';
	result[1] = 0;
	switch (query)
	{
	case 0:
		if (!set && m_state == 1)
			sprintf(result, "%d", m_colors.size());
		break;
	case 1:
		if (!set)
			strcpy(result, TheGameLogic && TheGameLogic->m_gameMode == 2 ? "1" : "0");
		break;
	case 2:
		if (!set)
			strcpy(result, TheGameLogic->m_gameMode != 6 || TheInGameUI->m_16 ? "1" : "0");
		break;
	}
}

// Retail 0x004E4553, 167 bytes: "Objective%d" for each of the twelve rows,
// the row's objective text behind a '$' (empty otherwise).
void AptPlayerStatus::rva004E4553(int row, char *result, bool set)
{
	result[0] = 0;
	if (m_state == 0 && row >= 0 && row < 12 && !set)
	{
		AsciiString text;
		int index = Rva004E43F2(row);
		Rva004266A1 *list;
		if (index >= 0 && g_00E031E8 && (list = ((AptPlayerStatusObjectives *)g_00E031E8)->m_list) != 0)
			text = *(const AsciiString *)list->rva004267E9(index);
		const AptPlayerStatusTextData *data = *(AptPlayerStatusTextData *const *)&text;
		if (data && data->m_length && data->m_length + 2 < 255)
		{
			result[0] = '$';
			strcpy(result + 1, data->m_chars);
		}
	}
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
