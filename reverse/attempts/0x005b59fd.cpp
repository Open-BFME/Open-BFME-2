// ?rva005B59FD@Class@AptCreateAHero@@QAEXXZ
// partial score=0.9 date=2026-10-10
// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /arch:SSE /G7
//
// ?rva005B59FD@Class@AptCreateAHero@@QAEXXZ, retail 0x005B59FD..0x005B5AAF
// (178 bytes, EH, ret 0). Factory callback of the create-a-hero class page
// (the Class of AptCreateAHeroClassConstructor.cpp, owner at +4): registers
// "AptCreateAHero::Class::Exit" (rowed member 0x005B5418) and
// "AptCreateAHero::Class::OnMapClick" (folded empty member 0x0047A69C) in
// the owner's command map adder (+0x21C). Both callbacks are DIR32
// references; the method has no WB name, so it keeps its address.
#include "ascii_string.h"

class AptCreateAHero;
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

class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc);
	Rva00579E47(const Rva00579E47 &other);
	~Rva00579E47();

private:
	void *m_ptr;
};

template <class T> class AptRef : public Rva00579E47
{
public:
	AptRef(const DelegateDesc &desc) : Rva00579E47(desc) {}
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);
};
class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &, AptRef<AptCommandMap>);
	char storage[12];
};
void _bfme_setAptScreenRef(const AsciiString &, AptRef<AptScreenInitGadgets>);

class GameWindow
{
protected:
	virtual ~GameWindow();
private:
	unsigned char m_pad004[0x218 - 4];
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
	AptCommandMapAdder m_commandMaps; // +0x04
private:
	unsigned char m_pad010[0x58 - 0x10];
};

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();
private:
	unsigned char m_pad[0x27C - 0x218 - 0x58];
};

class AptCreateAHero;

class Rva005B5420Base
{
public:
	Rva005B5420Base(AptCreateAHero *owner) : m_owner(owner) {}
	virtual ~Rva005B5420Base() {}
protected:
	AptCreateAHero *m_owner;
};

class AptCreateAHero : public _bfme_AptGameWindow
{
public:
	AptCreateAHero(void *context);
	virtual ~AptCreateAHero();
	class Class : public Rva005B5420Base
	{
	public:
		Class(AptCreateAHero *owner);
		virtual ~Class();
		void rva005B59FD();
		void rva005B5418(const char *);
		void rva0047A69C(const char *);
	private:
		char m_pad08[0x2C - 0x08];
	};
};

void AptCreateAHero::Class::rva005B59FD()
{
	{ AsciiString name("AptCreateAHero::Class::Exit"); m_owner->m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeDelegate(this, &Class::rva005B5418))); }
	{ AsciiString name("AptCreateAHero::Class::OnMapClick"); m_owner->m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeDelegate(this, &Class::rva0047A69C))); }
}
