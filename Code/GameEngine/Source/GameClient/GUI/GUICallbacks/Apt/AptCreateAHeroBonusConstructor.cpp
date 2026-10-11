// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /arch:SSE /G7
//
// ??0Rva005B2575@@QAE@PAVAptCreateAHero@@@Z, retail 0x005B25E7..0x005B265D
// (118 bytes, EH, ret 4). The create-a-hero bonus page (WB CahBonus): stores
// the owner at +4, installs vtable 0x00C72BAC and binds CahBonus::InitGadgets
// to its callback (a DIR32 reference). Built by the screen constructor
// 0x005142B0 (new 8, pinned until now). Pattern follows
// AptCreateAHeroManagerConstructor.cpp.
#include "ascii_string.h"

class Rva005B3676Owner;
class AptExternHandler;
class AptCommandMap;
class AptScreenInitGadgets;
class GameWindow;

class __single_inheritance AptDelegateTarget;
typedef void (AptDelegateTarget::*AptDelegateMethod)(void);

struct DelegateDesc
{
	template <class T, class M> DelegateDesc(T *object, M method)
		: m_object(reinterpret_cast<AptDelegateTarget *>(object))
		, m_method(reinterpret_cast<AptDelegateMethod>(method))
	{
	}

	AptDelegateTarget *m_object;
	AptDelegateMethod m_method;
};

template <class T, class M> __forceinline DelegateDesc MakeDelegate(T *object, M method)
{
	DelegateDesc desc(object, method);
	return desc;
}

// Link (AptRef lineage fork): the wrapper dtor copy (digest e67a72158686)
// lost to the majority inline-release copy (361dbf55f6ea, = rowed
// ??1Rva005F8F96 at 0x005F8F96 via the 0x7DEEF pin). Trivial base (no declared
// dtor; copy ctor kept declared) + inline release dtor emit retail's bytes.
class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);Rva00579E47(const Rva00579E47 &other);void*ptr;};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
template<class T> class AptRef:public Rva00579E47 {public:AptRef(const DelegateDesc &desc):Rva00579E47(desc){}~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);
};
class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &, AptRef<AptCommandMap>);
};
void _bfme_setAptScreenRef(const AsciiString &, AptRef<AptScreenInitGadgets>);


class AptCreateAHero;

class Rva005B2575Base
{
public:
	Rva005B2575Base(AptCreateAHero *owner) : m_owner(owner) {}
	virtual ~Rva005B2575Base() {}
protected:
	AptCreateAHero *m_owner;
};

class Rva005B2575 : public Rva005B2575Base
{
public:
	Rva005B2575(AptCreateAHero *owner);
	virtual ~Rva005B2575();
	void InitGadgets(const char *, void *, GameWindow *);
};

Rva005B2575::Rva005B2575(AptCreateAHero *owner)
	: Rva005B2575Base(owner)
{
	AsciiString name("CahBonus::InitGadgets");
	_bfme_setAptScreenRef(name, AptRef<AptScreenInitGadgets>(MakeDelegate(this, &Rva005B2575::InitGadgets)));
}
