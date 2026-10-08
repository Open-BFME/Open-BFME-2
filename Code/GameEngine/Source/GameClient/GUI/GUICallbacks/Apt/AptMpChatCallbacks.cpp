// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// BFME2's lobby chat panel Apt callbacks "AptMpChat::Send" (0x0057FDE0)
// and "AptMpChat::InitGadgets" (0x0057FDEF), bound by those names as member
// pointers by the panel's registration 0x0057FFB9 (recovered below); that
// binding is their only reference. The class is named for the strings' prefix (the
// AptMpGameSetup panel's +0x244 member).

#include "unicode_string.h"
#include "ascii_string.h"

extern "C" int __cdecl strcmp(const char *left, const char *right);
extern "C" char *__cdecl strcpy(char *destination, const char *source);

class GameWindow;

// The Apt callback functors (Rva0057BC63FunctorHolder.cpp, as in
// MpGameSetupSlots.cpp): a binding of an
// object and an eight-byte multiple-inheritance member pointer, and the
// refcounted holder rowed 0x0057BC63 builds from it.
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

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

template <class T> class AptRef : public Rva0057BC63FunctorHolder
{
public:
	AptRef(FunctorBinding binding) : Rva0057BC63FunctorHolder(binding) {}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

class AptCommandMap;
class AptExternHandler;

namespace _STL
{
	template <class T> class allocator {};

	template <class T, class A = allocator<T> > class vector
	{
	private:
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

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

// 0x00411458 (pinned; see MpGameSetupSlots.cpp) stores the screen
// reference under the name.
class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

// The chat panel instance (ColdGlobalDwordGetters.cpp).
extern int g_Va00E06394;

// The chat panel's +0x58 object; the registration clears its +0x08.
struct Rva0057FFB9Owner
{
	int m_00;
	int m_04;
	int m_08;
};

// The chat helper the panel keeps at +0x64: its unrowed 0x005B000C (188
// bytes) sends the typed line, 0x005AFC21 and 0x005AFC4C take the chat and
// player list windows (all pinned by address), and the rowed 0x005AFD43
// sets the entry's text (its own address class).
class Rva005B000C
{
public:
	virtual void f0();
	virtual void f1();
	virtual ~Rva005B000C();
	void rva005B000C();
	void rva005AFC21(GameWindow *window);
	void rva005AFC4C(GameWindow *window);

	unsigned char m_pad04[0x24 - 0x04];
};

// The two helpers the registration creates (both 0x24 bytes, ctors rowed).
class Rva005D5802 : public Rva005B000C
{
public:
	Rva005D5802();
};

class Rva005D50C4 : public Rva005B000C
{
public:
	Rva005D50C4();
};

class Rva005AFD43
{
public:
	void rva005AFD43(GameWindow *window, const UnicodeString &text);
};

class AptMpChat
{
public:
	void Send(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	// Bound as "MpChat::Initialized" and "MpClans::Initialized": one body
	// or two folded, so it keeps its address.
	void rva0057FDBF(int query, char *result, bool skip);
	void OnInit();

private:
	unsigned char m_pad00[0x04];
	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10
	unsigned char m_pad1c[0x58 - 0x1C];
	Rva0057FFB9Owner *m_58; // +0x58
	unsigned char m_pad5c[0x60 - 0x5C];
	int m_flags; // +0x60
	Rva005B000C *m_entry; // +0x64
	bool m_initialized; // +0x68
};

// Retail 0x0057FDBF, 33 bytes: bound as "MpChat::Initialized" and
// "MpClans::Initialized", an Apt query answering "1".
void AptMpChat::rva0057FDBF(int query, char *result, bool skip)
{
	if (query == 0 && !skip)
		strcpy(result, "1");
}

// Retail 0x0057FDE0, 15 bytes: "AptMpChat::Send".
void AptMpChat::Send(const char *unused)
{
	if (m_entry)
		m_entry->rva005B000C();
}

// Retail 0x0057FDEF, 124 bytes: "AptMpChat::InitGadgets" hands the "Chat",
// "ChatPlayers" and (emptied) "ChatEntry" windows to the helper.
void AptMpChat::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	if (!m_entry)
		return;
	m_initialized = false;
	if (strcmp(name, "Chat") == 0)
		m_entry->rva005AFC21(window);
	else if (strcmp(name, "ChatPlayers") == 0)
		m_entry->rva005AFC4C(window);
	else if (strcmp(name, "ChatEntry") == 0)
		((Rva005AFD43 *)m_entry)->rva005AFD43(window, UnicodeString::TheEmptyString);
	m_initialized = true;
}

// Retail 0x0057FFB9, 411 bytes. Name unknown. The chat panel's Apt
// registration (called by AptMpGameSetup::rva0044303D on its +0x244
// member): publishes the instance, replaces the +0x64 helper by the kind
// the +0x60 flags select, then binds "MpChat::Initialized" (extern handler
// index 0), "AptMpChat::Send" and the "AptMpChat::InitGadgets" screen
// reference. Retail packs the last block's AsciiString fresh but keeps its
// binding in the shared slot (sub esp,0x2C), which needs the trailing scope.
// The handlers are bound as eight-byte multiple-inheritance member pointers.
#pragma pointers_to_members(full_generality, multiple_inheritance)
void AptMpChat::OnInit()
{
	g_Va00E06394 = (int)this;
	if (m_entry)
	{
		::delete m_entry;
		m_entry = 0;
	}
	if (m_flags & 0x20000000)
		m_entry = new Rva005D5802;
	else if (m_flags & 0x40000000)
		m_entry = new Rva005D50C4;
	m_58->m_08 = 0;
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMpChat::rva0057FDBF);
		AsciiString name("MpChat::Initialized");
		m_externHandlers.AddExternHandler(name, 0, AptRef<AptExternHandler>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMpChat::Send);
		AsciiString name("AptMpChat::Send");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMpChat::InitGadgets);
		AsciiString name("AptMpChat::InitGadgets");
		_bfme_setAptScreenRef(name, AptRef<AptScreenInitGadgets>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		{
			FunctorBinding unused(0, 0);
			(void)unused;
		}
	}
	m_initialized = true;
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
