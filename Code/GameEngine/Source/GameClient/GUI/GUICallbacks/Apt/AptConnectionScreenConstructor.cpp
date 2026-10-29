// cl: /Ireference/shims/bfme2_ascii /O1 /G6 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0AptConnectionScreen@@QAE@PAX@Z, retail 0x005DB6E2..0x005DB7F0
// (272 bytes, EH, ret 4). The online connection grid (WB
// AptConnectionScreen::AptConnectionScreen; Connection::RedrawGrid and
// Connection::OnRetryConnections are its rowed callbacks in
// AptConnectionGridCallbacks.cpp). Two bases: the Apt window half
// (0x002D2C34, command map adder at +4) and a listener at +0x58 (vtable
// 0x00C711BC under the final 0x00C7678C), then the grid's level at +0x5C.
// While the global 0x00E063F8 exists the screen registers itself in its
// listener list at +0x2C (rowed append 0x005A0B4C), binds the two commands
// and draws the grid once (rowed 0x005DB630). Pattern follows
// AptMainMenuConstructor.cpp (functor bindings).
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

class AptCommandMap;
class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);
private:
	char m_pad[12];
};

class __declspec(novtable) Rva005248D0
{
public:
	Rva005248D0();
	virtual ~Rva005248D0();
	AptCommandMapAdder m_commandMaps; // +0x04
private:
	char m_pad[0x58 - 0x10];
};

struct Rva002BA8F1Listener
{
public:
	virtual ~Rva002BA8F1Listener();
};

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

class Rva005A6D47
{
public:
	virtual ~Rva005A6D47();
	unsigned char m_pad04[0x28 - 4];
	unsigned char m_28; // +0x28
	unsigned char m_pad29[0x2C - 0x29];
	Rva005A0B4CList m_listeners; // +0x2C
};
// Bind the existing NAT datum; retain this unit's access view at use sites.
struct NAT;
extern NAT *TheNAT;

// Native vftable 0x008711BC: slots 0 and 1 are the shared empty three-argument
// body 0x000D1407 (ret 0Ch), slot 2 the deleting destructor 0x0059EB41.
class Rva0059EB41
{
public:
	virtual void slot00(void *, void *, void *) {}
	virtual void slot01(void *, void *, void *) {}
	virtual ~Rva0059EB41() {}
};

class PortNegotiationSchema;
struct Elem005DB98E;

class AptConnectionScreen : public Rva005248D0, public Rva0059EB41
{
public:
	AptConnectionScreen(void *level);
	virtual ~AptConnectionScreen();
	void RedrawGrid(const char *unused);
	void OnRetryConnections(const char *unused);
	void rva005DB630();

	// Rowed 0x005DB3B3 refreshes one player's name and number.
	void UpdateSlotName(int player);
	void UpdateGrid(PortNegotiationSchema *schema, int row, int column);
	static int GetPingImageEnum(Elem005DB98E *ping);

private:
	void *m_level; // +0x5C
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
AptConnectionScreen::AptConnectionScreen(void *level)
	: m_level(level)
{
	if (TheNAT) {
		((Rva005A6D47 *)TheNAT)->m_listeners.append((Rva002BA8F1Listener *)static_cast<Rva0059EB41 *>(this));
		{
			FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptConnectionScreen::RedrawGrid);
			AsciiString name("Connection::RedrawGrid");
			m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
		{
			FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptConnectionScreen::OnRetryConnections);
			AsciiString name("Connection::OnRetryConnections");
			m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
		rva005DB630();
	}
}
