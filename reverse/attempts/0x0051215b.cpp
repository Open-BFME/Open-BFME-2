// ??0AptMessenger@@QAE@PAX@Z
// partial score=0.99 date=2026-10-10
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs
// NEAR draft for ??0AptMessenger@@QAE@PAX@Z retail 0x0051215B (1159 bytes).
// Size exact; the only residue is the slot of the vector<unsigned short>
// value temporary for m_280(2 0): retail packs it into the dead context
// parameter home [ebp+8] (beside the allocator temporary at [ebp+0xB]),
// this build puts it at [ebp-0x10] (2 instructions: lea eax and the zero
// store). Tried: int/short/bool/unsigned/value-initialised temporaries, a
// default-argument temporary, an explicit allocator argument, allocator
// with user copy ctor/dtor, init-list reordering, /EHsc and /G6, real
// STLport <vector>, and forceinline wrapper ctors (those also reorder
// push 2 / lea ecx).
// Link notes: the unwind funclets name ??1?$vector@GV?$allocator@G@_STL@@@_STL@@QAE@XZ
// (retail 0x0007FAB3; no row) and ??1?$vector@URva00511E48@@...@QAE@XZ
// (retail 0x0051211C, rowed as ??1Rva0051211C@@QAE@XZ).
#include "ascii_string.h"

class GameWindow
{
public:
	unsigned int winSetStatus(unsigned int status);

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

class Rva0023E8D8
{
public:
	Rva0023E8D8() {}
	Rva0023E8D8(void *function);
	FunctorWrapperHead *m_ptr;
};

class Rva0057BC63FunctorHolder : public Rva0023E8D8
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
	__forceinline Rva0057BC63FunctorHolder(void *function) : Rva0023E8D8(function) {}
	Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &other)
	{
		m_ptr = other.m_ptr;
		if (m_ptr)
			++m_ptr->m_refCount;
	}
};

__forceinline FunctorBinding MakeBinding(FunctorMethod method, FunctorTarget *target)
{
	FunctorBinding binding(method, target);
	return binding;
}

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

typedef void (__cdecl *AptStaticCommand)(int);

template <class T> class AptRef : public Rva0057BC63FunctorHolder
{
public:
	AptRef(const FunctorBinding &binding) : Rva0057BC63FunctorHolder(binding) {}
	AptRef(AptStaticCommand function) : Rva0057BC63FunctorHolder(&function) {}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

namespace _STL
{
	template <class T> class allocator
	{
	public:
		allocator() {}
	};

	template <class T, class A = allocator<T> > class vector
	{
	public:
		vector(unsigned int n, const T &value, const A &alloc = A());
		explicit vector(unsigned int n);
		~vector();

	private:
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};

	// The retail constructor 0x00511E1C (one ICF body for the 4-byte element
	// vectors) carries the ledger name of vector<unsigned short>; the unwind
	// funclet destroys through the vector<int> destructor row 0x0007FAB3.
	template <> class vector<int, allocator<int> > : public vector<unsigned short>
	{
	public:
		__forceinline vector(unsigned int n, const int &value,
			const allocator<unsigned short> &alloc = allocator<unsigned short>())
			: vector<unsigned short>(n, (const unsigned short &)value, alloc) {}
		~vector();
	};
}

struct Rva00511E48;

class Rva0051211C : public _STL::vector<Rva00511E48>
{
public:
	__forceinline Rva0051211C(unsigned int n) : _STL::vector<Rva00511E48>(n) {}
	~Rva0051211C();
};

class AptCommandMap;
class AptExternHandler;
class AptCustomRender;
class AptScreenInitGadgets;

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

class AptCustomRenderAdder
{
public:
	void AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render);

private:
	_STL::vector<AsciiString> m_names;
};

void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

class Rva005248D0
{
public:
	virtual ~Rva005248D0();

	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10

private:
	unsigned char m_pad01C[0x34 - 0x1C];

public:
	AptCustomRenderAdder m_customRenders; // +0x34

private:
	unsigned char m_pad040[0x58 - 0x40];
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

class AptInGameChat
{
public:
	void rva004E8213(const char *unused); // 0x004E8213, shared OnClosed body
};

class Coord2D;
void Rva00511730(int);

extern int g_Va00E046B8;

class AptMessenger : public _bfme_AptGameWindow
{
public:
	AptMessenger(void *context);
	virtual ~AptMessenger();

	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void rva00511AD4(int query, char *value, bool set);
	void OnInitialized(const char *unused);
	void OnButtonSend(const char *unused);
	void GameWindowSize(const Coord2D *a, const Coord2D *b, void *c, void *d);

private:
	int m_27C;
	_STL::vector<unsigned short> m_280;
	_STL::vector<Rva00511E48> m_28C;
	int m_298;
	bool m_29C;
	bool m_29D;
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
AptMessenger::AptMessenger(void *context)
	: _bfme_AptGameWindow(context),
	  m_27C(0),
	  m_280(2, 0),
	  m_28C(2),
	  m_298(0),
	  m_29C(true),
	  m_29D(false)
{
	winSetStatus(0x20);
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMessenger::InitGadgets);
		AsciiString screen("AptMessenger::InitGadgets");
		_bfme_setAptScreenRef(screen, AptRef<AptScreenInitGadgets>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMessenger::rva00511AD4);
		AsciiString name("MessengerX");
		m_externHandlers.AddExternHandler(name, 0, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMessenger::rva00511AD4);
		AsciiString name("MessengerY");
		m_externHandlers.AddExternHandler(name, 1, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMessenger::rva00511AD4);
		AsciiString name("MessengerActiveTab");
		m_externHandlers.AddExternHandler(name, 2, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMessenger::rva00511AD4);
		AsciiString name("IsMaximized");
		m_externHandlers.AddExternHandler(name, 3, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMessenger::rva00511AD4);
		AsciiString name("ShowPlayerButtons");
		m_externHandlers.AddExternHandler(name, 4, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMessenger::rva00511AD4);
		AsciiString name("MessengerSetDragging");
		m_externHandlers.AddExternHandler(name, 5, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMessenger::OnInitialized);
		AsciiString name("AptMessenger::OnInitialized");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptInGameChat::rva004E8213);
		AsciiString name("AptMessenger::OnClosed");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMessenger::OnButtonSend);
		AsciiString name("AptMessenger::OnButtonSend");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		AsciiString name("AptMessenger::CloseScreen");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(&Rva00511730));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMessenger::GameWindowSize);
		AsciiString name("AptMessenger::GameWindowSize");
		m_customRenders.AddCustomRender(name, AptRef<AptCustomRender>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	g_Va00E046B8 = (int)this;
}
