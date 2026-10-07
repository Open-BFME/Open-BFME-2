// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// BFME2's in-game chat screen (InGameChat.apt, built by the 0x288-byte
// factory at 0x002D1F3D): its constructor, which becomes the open chat
// screen and binds its callbacks by name (InitGadgets, OnInitialized and
// OnClosed are in AptLobbyScreenInitCallbacks.cpp). BFME 1's
// AptScreenFactories.cpp (BfmeAptScreenInGameChat) is the donor.

#include <vector>
#include "ascii_string.h"

class GameWindow
{
protected:
	virtual ~GameWindow();

private:
	unsigned char m_pad004[0x218 - 4];
};

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

// The open in-game chat screen (VA 0x00E04478).
extern int g_Va00E04478;

// Rva004E8220Method.cpp's view of this screen: Close, bound by its name,
// moves the +0x27C state from 1 to 2.
class Rva004E8220
{
public:
	void rva004E8220(int unused);
};

class AptInGameChat : public _bfme_AptGameWindow
{
public:
	AptInGameChat(void *context);
	virtual ~AptInGameChat();

	// AptLobbyScreenInitCallbacks.cpp.
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void OnInitialized(const char *unused);
	void rva004E8213(const char *unused);
	// Unrowed 0x004E8820, pinned by address.
	void Send(const char *unused);

private:
	int m_state; // +0x27C
	int m_280;
	GameWindow *m_entry; // +0x284
};

// Retail 0x004E8B38, 518 bytes: the screen's constructor. The first one
// becomes the open chat screen and binds InitGadgets as its screen
// reference and the OnInitialized, OnClosed, Close and Send commands.
#pragma pointers_to_members(full_generality, multiple_inheritance)
AptInGameChat::AptInGameChat(void *context)
	: _bfme_AptGameWindow(context),
	  m_state(0),
	  m_entry(0)
{
	if (g_Va00E04478 != 0)
		return;
	g_Va00E04478 = (int)this;
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptInGameChat::InitGadgets);
		AsciiString screen("AptInGameChat::InitGadgets");
		_bfme_setAptScreenRef(screen, AptRef<AptScreenInitGadgets>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptInGameChat::OnInitialized);
		AsciiString name("AptInGameChat::OnInitialized");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptInGameChat::rva004E8213);
		AsciiString name("AptInGameChat::OnClosed");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&Rva004E8220::rva004E8220);
		AsciiString name("AptInGameChat::Close");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptInGameChat::Send);
		AsciiString name("AptInGameChat::Send");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
}
