// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// AptCallbackAdders.cpp -- Apt callback adders recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names each adder and the
// AptPlayer method it forwards to; retail supplies the bytes.
//
// Every adder takes the callback name and a reference-counted callback by
// value, registers it with the Apt player (global 0x00DFE4CC) when one exists
// and remembers the name in its own vector<AsciiString> at +0x00 so it can be
// removed later. The callback reference bumps the count at +4 on copy and
// releases through the out-of-line worker at 0x0007DEEF (rowed under a
// placeholder name). Callback class names are inferred from the adder names.
#include "ascii_string.h"

typedef int Int;

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);	// 0x0007DEEF

class AptRefCounted
{
public:
	void *m_vtbl;
	Int m_refCount;				// +0x04
};

template <class T> class AptRef
{
public:
	AptRef(const AptRef &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			m_ptr->m_refCount++;
	}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}

private:
	T *m_ptr;
};

class AptCommandMap : public AptRefCounted {};
class AptOverButtonHandler : public AptRefCounted {};
class AptCustomRender : public AptRefCounted {};
class AptTimer : public AptRefCounted {};
class AptExternHandler : public AptRefCounted {};

// STLport vector<AsciiString> view; push_back is the rowed out-of-line copy
// (0x0002DBE6).
namespace _STL
{
	template <class T> class allocator {};

	template <class T, class A = allocator<T> > class vector
	{
	public:
		void push_back(const T &value);

	private:
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

class AptPlayer
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);		// 0x002243E3
	void AddExternHandler(const AsciiString &name, Int arg, AptRef<AptExternHandler> handler);	// 0x0022445D
	void AddOverButtonHandler(const AsciiString &name, AptRef<AptOverButtonHandler> handler);	// 0x002244D2
	void AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render);		// 0x0022464C
	void AddTimer(const AsciiString &name, AptRef<AptTimer> timer);			// 0x002246B9
};

// The Apt player global (0x00DFE4CC) under the spelling other units use.
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
#define TheAptPlayer ((AptPlayer *)g_bfmeAptWindowManager)

// AptPlayer::RemoveExternHandler (WorldBuilder name), rowed under its
// address name: removes the handler registered under the name.
class Rva002244CA
{
public:
	int rva002244CA(const AsciiString *name);
};

// Registers one extern handler for its own lifetime; keeps the name.
class AptSingleExternHandlerAdder
{
public:
	AptSingleExternHandlerAdder(const AsciiString &name, Int arg, AptRef<AptExternHandler> handler);
	~AptSingleExternHandlerAdder();
	void rva00523D5A();

private:
	AsciiString m_name;
};

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
	void AddExternHandler(const AsciiString &name, Int arg, AptRef<AptExternHandler> handler);

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

class AptCustomRenderAdder
{
public:
	void AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render);

private:
	_STL::vector<AsciiString> m_names;
};

class AptTimerAdder
{
public:
	void AddTimer(const AsciiString &name, AptRef<AptTimer> timer);

private:
	_STL::vector<AsciiString> m_names;
};

// AptSingleExternHandlerAdder::AptSingleExternHandlerAdder, retail 0x00523E4C.
AptSingleExternHandlerAdder::AptSingleExternHandlerAdder(const AsciiString &name, Int arg, AptRef<AptExternHandler> handler)
	: m_name(name)
{
	TheAptPlayer->AddExternHandler(m_name, arg, handler);
}

// Retail 0x00523D5A 18B (unnamed in WorldBuilder; it calls
// AptPlayer::RemoveExternHandler): unregisters the handler by its name.
void AptSingleExternHandlerAdder::rva00523D5A()
{
	if (TheAptPlayer)
		((Rva002244CA *)TheAptPlayer)->rva002244CA(&m_name);
}

// AptSingleExternHandlerAdder::~AptSingleExternHandlerAdder, retail
// 0x00523D88 47B: the destructor the army details clip runs on the adders
// it built with the constructor above (0x005F37EB, 0x005F37F7).
AptSingleExternHandlerAdder::~AptSingleExternHandlerAdder()
{
	rva00523D5A();
}

// AptCommandMapAdder::AddCommandMap, retail 0x0052458E.
void AptCommandMapAdder::AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map)
{
	if (TheAptPlayer)
	{
		TheAptPlayer->AddCommandMap(name, map);
		m_names.push_back(name);
	}
}

// AptExternHandlerAdder::AddExternHandler, retail 0x005245F3.
void AptExternHandlerAdder::AddExternHandler(const AsciiString &name, Int arg, AptRef<AptExternHandler> handler)
{
	if (TheAptPlayer)
	{
		TheAptPlayer->AddExternHandler(name, arg, handler);
		m_names.push_back(name);
	}
}

// AptOverButtonHandlerAdder::AddOverButtonHandler, retail 0x0052465B.
void AptOverButtonHandlerAdder::AddOverButtonHandler(const AsciiString &name, AptRef<AptOverButtonHandler> handler)
{
	if (TheAptPlayer)
	{
		TheAptPlayer->AddOverButtonHandler(name, handler);
		m_names.push_back(name);
	}
}

// AptCustomRenderAdder::AddCustomRender, retail 0x005246C0.
void AptCustomRenderAdder::AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render)
{
	if (TheAptPlayer)
	{
		TheAptPlayer->AddCustomRender(name, render);
		m_names.push_back(name);
	}
}

// AptTimerAdder::AddTimer, retail 0x005247A9.
void AptTimerAdder::AddTimer(const AsciiString &name, AptRef<AptTimer> timer)
{
	if (TheAptPlayer)
	{
		TheAptPlayer->AddTimer(name, timer);
		m_names.push_back(name);
	}
}
