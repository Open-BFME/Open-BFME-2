// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Native EH action 0x7A1744 destroys the counted virtual base at +0x10 guarded by the most-derived constructor flag; the complete parent EH graph proves this 28B lifetime.
// Native 5CE93E..5CE9B4: primary +0, vbptr +4, base payload +8,
// derived pointer +C, Rva0007DF07 virtual base +10 and count +14.
// The native84B base destructor confirms the nonvirtual Rva005CC5E5
// parent whose57B constructor establishes the same vbptr/count layout.
// The derived pointer is the third explicit argument's +14 field.
#include "../../Include/Common/Rva0007DF07.h"

// Native primary callbacks read the source record at+C, then its target at+4.
#include "../../Include/Common/Rva00575674.h"
// Allocation-only helper view: native constructor5CF4A8 receives the owner and value.
// The existing constructor provider owns its actual member layout.
struct Rva005CF22CBig { char prefix00[0x1C]; Rva00575674 sub1C; };
class Rva005CEF2F { public: Rva005CEF2F(Rva005CF22CBig *, int); private: char storage[20]; };
class Rva005CEE9F { public: Rva005CEE9F(Rva005CF22CBig *, int); private: char storage[20]; };

struct Rva005CE93ESourcePrefix { unsigned int unknown00; void *target04; };
class Rva005E6826Mid { public: void fwd(); };
class Rva005E681EMid { public: void fwd(); };

struct Rva005CE93EContext
{
	char unknown00[0x14];
	void *source;
};

class Rva005CC5E5 : public virtual Rva0007DF07 {public:Rva005CC5E5() throw();virtual void slot0();virtual ~Rva005CC5E5(){}};

class Rva005CC698 : public Rva005CC5E5
{
public:
	Rva005CC698(void *, void *, Rva005CE93EContext *);
	virtual ~Rva005CC698();
	virtual void slot0();
private:
	void *payload;
};

class Rva005CE93E : public Rva005CC698
{
public:
	Rva005CE93E(void *, void *, Rva005CE93EContext *);
	virtual void slot1();
	virtual void slot2();
	virtual void slot3(int);
	virtual void slot4(int);
	// Implicit virtual destructor: native 5CEC55 adjusts the virtual-base
	// receiver by -4 and tail-calls Rva005CC698::~Rva005CC698 (5CC788).
	// An explicit empty destructor adds table writes absent from retail.
private:
	void *source;
};

Rva005CE93E::Rva005CE93E(void *a, void *b, Rva005CE93EContext *context)
	: Rva005CC698(a, b, context), source(context->source)
{
}

// ?rva005CEB7B@Rva005CEB7B@@QAE?AURva005CE93EHandle@@PAX0@Z, retail 0x005CEB7B (99B):
// a factory slot whose receiver keeps the constructor's context at +8. It
// allocates 0x18 bytes, constructs this class (most-derived flag 1) and
// returns a counted handle by hidden pointer (RET 0C); the AddRef reaches the
// shared Rva0007DF07 count through the vbptr at +4. Receiver and handle names
// are address-derived storage views.
struct Rva005CE93EHandle
{
	Rva005CC5E5 *m_p;
	__forceinline Rva005CE93EHandle(Rva005CC5E5 *refCountedObject) : m_p(refCountedObject)
	{
		if (refCountedObject)
			++static_cast<Rva0007DF07 *>(refCountedObject)->m_04;
	}
	~Rva005CE93EHandle();
};

struct Rva005CEB7B
{
	char m_prefix[8];
	Rva005CE93EContext m_context;
	Rva005CE93EHandle rva005CEB7B(void *a, void *b);
};

Rva005CE93EHandle Rva005CEB7B::rva005CEB7B(void *a, void *b)
{
	return Rva005CE93EHandle(new Rva005CE93E(a, b, &m_context));
}

void Rva005CE93E::slot1()
{
    reinterpret_cast<Rva005E6826Mid *>(static_cast<Rva005CE93ESourcePrefix *>(source)->target04)->fwd();
}

void Rva005CE93E::slot2()
{
    reinterpret_cast<Rva005E681EMid *>(static_cast<Rva005CE93ESourcePrefix *>(source)->target04)->fwd();
}

void Rva005CE93E::slot3(int value)
{
    Rva005CEF2F *helper = new Rva005CEF2F(static_cast<Rva005CF22CBig *>(source), value);
    static_cast<Rva005CF22CBig *>(source)->sub1C.rva00575674(reinterpret_cast<Object *>(helper));
}

void Rva005CE93E::slot4(int value)
{
    Rva005CEE9F *helper = new Rva005CEE9F(static_cast<Rva005CF22CBig *>(source), value);
    static_cast<Rva005CF22CBig *>(source)->sub1C.rva00575674(reinterpret_cast<Object *>(helper));
}
