// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva005111FA@Rva00510D0C@@UAEXXZ
// retail 0x005111FA..0x005114B6 (701 bytes) thiscall RET 0.
//
// The tribute screen's Apt registration (vtable 0x00C6568C slot 12, the
// absolute reference 0x008656BC; WorldBuilder AptPlayerTribute.cpp). Under
// "_level<n>" (the screen's level at +0x274) it binds the command maps
// "_OnInitialized" (method 0x0047A69C, folded with an empty body),
// "_ReturnToGame" (0x0050EBBD), "_OnPageLoaded" (0x00511108),
// "_OnPageUnloaded" (0x00510ECC) and "_OnPageSelected" (0x00510F41) through
// the +0x21C adder, and the extern handler "_TributeEnabled" (0x0050E98A)
// through the +0x228 adder. Names are built with the rowed
// AsciiString + text builder (0x000B49C5 and its conversion 0x000BC4F7);
// the handlers are eight-byte multiple-inheritance member pointers bound
// through the rowed functor holder 0x0057BC63, as in
// AptQuitMenuCallbacks.cpp.
#include "ascii_string.h"

// "string + text" (RegistryAsciiPath.cpp).
struct AsciiStringRef
{
	const AsciiString *m_string;
};
class Rva000B3F84Pair
{
public:
	const char *m_ptr;
	int m_len;
};
struct AsciiStringPlusText : AsciiStringRef
{
	operator AsciiString();				// 0x000BC4F7

	Rva000B3F84Pair m_right;
};
AsciiStringPlusText operator+(const AsciiString &left, const char *right);	// 0x000B49C5

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
	int m_refCount;
};

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);	// 0x0057BC63
	Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
	}

	FunctorWrapperHead *m_ptr;
};

// Builds a binding by value: the named result is copied out.
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
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);	// 0x0052458E

private:
	void *m_names[3];
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);	// 0x005245F3

private:
	void *m_names[3];
};

template <int N> class Rva00510D0CSlots : public Rva00510D0CSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class Rva00510D0CSlots<1>
{
public:
	virtual void gap(char (*)[1]);
};

class Rva00510D0C : public Rva00510D0CSlots<12>
{
public:
	virtual void rva005111FA();		// slot 12, the Apt registration

	void OnInitialized(const char *unused);
	void ReturnToGame(const char *unused);
	void OnPageLoaded(const char *params);
	void OnPageUnloaded(const char *name);
	void OnPageSelected(const char *name);
	void TributeEnabled(int query, char *result, bool skip);

private:
	unsigned char m_pad004[0x21C - 0x04];
	AptCommandMapAdder m_commandMaps;	// +0x21C
	AptExternHandlerAdder m_externHandlers;	// +0x228
	unsigned char m_pad234[0x274 - 0x234];
	unsigned int m_level;			// +0x274
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
void Rva00510D0C::rva005111FA()
{
	unsigned int levelNumber = m_level;
	AsciiString level;
	level.format("_level%u", levelNumber);
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&Rva00510D0C::OnInitialized);
		AsciiString name = (level + "_OnInitialized").operator AsciiString();
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&Rva00510D0C::ReturnToGame);
		AsciiString name = (level + "_ReturnToGame").operator AsciiString();
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&Rva00510D0C::OnPageLoaded);
		AsciiString name = (level + "_OnPageLoaded").operator AsciiString();
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&Rva00510D0C::OnPageUnloaded);
		AsciiString name = (level + "_OnPageUnloaded").operator AsciiString();
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&Rva00510D0C::OnPageSelected);
		AsciiString name = (level + "_OnPageSelected").operator AsciiString();
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&Rva00510D0C::TributeEnabled);
		AsciiString name = (level + "_TributeEnabled").operator AsciiString();
		m_externHandlers.AddExternHandler(name, 0, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
}
