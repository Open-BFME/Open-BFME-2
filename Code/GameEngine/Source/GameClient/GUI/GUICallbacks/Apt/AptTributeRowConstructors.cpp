// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
#include "ascii_string.h"
// Native0050F85D..0050F909 RET8; target color callback0050E7EB reads58.
// WorldBuilder AptPlayerTribute.cpp binds the same _level%u.%s_color query.
// Existing row destructor0050FAEC and C65518 one-entry vtable prove this
// neutral class identity; adjacent C6551C is a separate page vtable.
// Registry58 comes from existing target callback views; constructor calls
// existing002D2C34 and the16B multiple-inheritance binding holder0057BC63.
// Original constructor/class spelling unknown; no donor-layout fact claimed.
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
	unsigned char m_names[12]; // an STLport vector<AsciiString>
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);

private:
	unsigned char m_names[12]; // an STLport vector<AsciiString>
};

// The 0x58-byte callback registry (as in BfmeAptGameWindowDestructor.cpp),
// constructed by the pinned 0x002D2C34.
class Rva002D2C34
{
public:
	void rva002D2C34();
};

class __declspec(novtable) Rva005248D0
{
public:
	__forceinline Rva005248D0() { ((Rva002D2C34 *)this)->rva002D2C34(); }
	virtual ~Rva005248D0();

	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10

private:
	unsigned char m_pad01C[0x58 - 0x1C];
};


class Rva0050FAEC:public Rva005248D0 {public:Rva0050FAEC(int level,const AsciiString&name);virtual ~Rva0050FAEC();void color(int,char*,bool);private:int m_color;};
#pragma pointers_to_members(full_generality, multiple_inheritance)
Rva0050FAEC::Rva0050FAEC(int level,const AsciiString&name):m_color(0){AsciiString key;key.format("_level%u.%s_color",level,name.str());FunctorMethod method=reinterpret_cast<FunctorMethod>(&Rva0050FAEC::color);m_externHandlers.AddExternHandler(key,0,AptRef<AptExternHandler>(MakeBinding(method,reinterpret_cast<FunctorTarget*>(this))));}
