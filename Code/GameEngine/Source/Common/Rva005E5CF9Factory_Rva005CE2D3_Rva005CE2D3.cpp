// Split from Rva005E5CF9Factory_Rva005CE2D3.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Split from Rva005E5CF9Factory.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
// cl: /EHsc /Oy- /Ob2 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?rva005E5CF9@Rva005E5CF9@@QAE?AURvaF1Handle@@H@Z, retail 0x005E5CF9 (84B).
// Factory method returning RvaF1Handle by value: allocates 0x28 bytes, runs
// rowed ??0Rva005F5819@@QAE@HPAX@Z with (int arg, this+8), null-checked AddRef
// (inc [eax+4]) and hidden-pointer return (ret 8). Evidence: callee row
// 0x005F589E, new row 0x0002FDA0, EH_prolog row 0x00629188, ret-8 + hidden
// pointer shape matching RvaFamily1Clones clones, this+8 as second ctor arg.
struct RvaF1Handle
{
	void *m_p;
	__forceinline RvaF1Handle(void *p) : m_p(p)
	{
		if (p)
			++((int *)p)[1];
	}
	~RvaF1Handle();
};

class Rva005F5819
{
	char m_pad[0x28];
public:
	Rva005F5819(int a1, void *a2);
};

struct Rva005E5CF9In
{
	void *m_00;
	int m_04;
	void *m_08;
};

struct Rva005E5CF9
{
	char m_pad08[8];
	Rva005E5CF9In m_in;
	RvaF1Handle rva005E5CF9(int a1);
};


// Widened queue: three independently witnessed members of this factory
// pattern. Each has a hidden one-word result, AddRef at object +4 and a
// context pointer at receiver +8. Constructor arguments are opaque words:
// target callees forward them without interpreting them here. These names
// and storage-only views do not claim an application class or enum identity.
// The constructor at 0x005E8DCF is rowed as Rva005E8D71's
// (Rva005E8D71Ctor.cpp); the one at 0x006004C1 as Rva00600505's
// (Rva00600505Dtor.cpp). Each view declares that row's signature; the
// factories pass the same words.
struct Rva005E8DCFIn;
class Rva005E8D71
{
	char m_pad[0x24];
public:
	Rva005E8D71(void *frame, Rva005E8DCFIn *in);
};
class Rva005E91A9
{
	char m_pad[0x20];
public:
	Rva005E91A9(unsigned int argument, void *context);
};
struct Rva005FEF11Input;
class Rva00600505
{
	char m_pad[0x28];
public:
	Rva00600505(int a, int b, const Rva005FEF11Input **inputs);
};
struct Rva005CE2D3
{
	char m_prefix[8];
	Rva005E5CF9In m_context;
	RvaF1Handle rva005CE2D3(unsigned int frame);
};
struct Rva005CEA92
{
	char m_prefix[8];
	Rva005E5CF9In m_context;
	RvaF1Handle rva005CEA92(unsigned int argument);
};
struct Rva005FB418
{
	char m_prefix[8];
	Rva005E5CF9In m_context;
	RvaF1Handle rva005FB418(unsigned int first, unsigned int second);
};

RvaF1Handle Rva005CE2D3::rva005CE2D3(unsigned int frame)
{
	return RvaF1Handle(new Rva005E8D71((void *)frame, (Rva005E8DCFIn *)&m_context));
}


// Native 005E5D4D..005E5DA1 and 005E5DA1..005E5DF5 each return a
// one-word handle through a hidden pointer (ret 8). Both allocate 40 bytes,
// forward the explicit pointer and receiver+8 to the independently rowed
// constructors, and increment the result's reference count at +4.
// The constructor providers establish the three-word context layouts;
// factory/application names remain unknown. Earlier attempts lacked these
// providers; no donor identity is inferred from the matching instruction shape.
class Rva005A0B4CList;
struct Rva005F5C77In
{
	void *m_00;
	int m_04;
	Rva005A0B4CList *m_08;
};
struct Rva005F5F2BIn
{
	void *m_00;
	int m_04;
	Rva005A0B4CList *m_08;
};
class Rva005F5BF2
{
	char m_storage[0x28];
public:
	Rva005F5BF2(void *argument, Rva005F5C77In *context);
};
class Rva005F5EA6
{
	char m_storage[0x28];
public:
	Rva005F5EA6(void *argument, Rva005F5F2BIn *context);
};
struct Rva005E5D4D
{
	char m_prefix[8];
	Rva005F5C77In m_context;
	RvaF1Handle rva005E5D4D(void *argument);
};
struct Rva005E5DA1
{
	char m_prefix[8];
	Rva005F5F2BIn m_context;
	RvaF1Handle rva005E5DA1(void *argument);
};


class Rva005E92F7
{
	char m_storage[0x28];
public:
	Rva005E92F7(unsigned int argument, void *context);
};
struct Rva005CEB03
{
	char m_prefix[8];
	Rva005E5CF9In m_context;
	RvaF1Handle rva005CEB03(unsigned int argument);
};


// ?rva005FB243@Rva005FB243@@QAE?AURvaF1Handle@@HH@Z, retail 0x005FB243 (87B): the same factory shape with two
// opaque int arguments and the rowed constructor Rva005FF13A (0x005FF0F6); its context argument is receiver+8.
// Target evidence: retail body and the constructor's REL32 read byte for byte; names are address-derived.
// The canonical panel preserves the native 40-byte allocation and existing
// three-argument constructor at 005FF0F6. Its verified base/clip/vector layout
// replaces the private storage-only class; the factory/result names stay opaque.
// stlport
#include "BattlePromptArmyPanelView.h"
typedef char FactoryPanelSizeProof[(sizeof(Rva005FF13A) == 0x28) ? 1 : -1];
struct Rva005FB243
{
	char m_prefix[8];
	Rva005E5CF9In m_context;
	RvaF1Handle rva005FB243(int first, int second);
};


// ?rva00574AD9@Rva00574AD9@@QAE?AURvaF1Handle@@PAX@Z, retail 0x00574AD9 (84B): sibling of rva005CEA92 above with a
// 0x20-byte object built by the rowed constructor Rva005CC37C (0x005CC3C0) from the explicit pointer and receiver+8.
// Constructor-only view of Rva005CC37C: opaque 0x20-byte storage view; only the constructor is called
class Rva005CC37C
{
	char m_pad[0x20];
public:
	Rva005CC37C(void *argument, struct Rva005CC3C0In *context);
};
struct Rva00574AD9
{
	char m_prefix[8];
	Rva005E5CF9In m_context;
	RvaF1Handle rva00574AD9(void *argument);
};


// ?rva00567F3D@Rva00567F3D@@QAE?AURvaF1Handle@@H@Z, retail 0x00567F3D (84B): the same factory shape with a 0x1C-byte
// object built by the rowed constructor Rva00567960 (0x00567CCD) from the int argument and receiver+8 (an Info view).
// Constructor-only view of Rva00567960: opaque 0x1C-byte storage view; only the constructor is called
class Rva00567960
{
	char m_pad[0x1C];
public:
	Rva00567960(int argument, const struct Rva00567CCDInfo *info);
};
struct Rva00567F3D
{
	char m_prefix[8];
	Rva005E5CF9In m_context;
	RvaF1Handle rva00567F3D(int argument);
};


// Three more factories of the same family at 0x005E9761, 0x005E97D5 and 0x005E9849 (ret 0xC): two opaque words and
// receiver+8 forwarded to rowed-by-address constructors 0x005FB14E (0x24-byte object), 0x005FB30A and 0x005FB4DF
// (0x20-byte objects). Target evidence: retail bodies and constructor REL32s read byte for byte; constructor
// identities and argument meanings are unresolved and the names are address-derived.
// Constructor-only view of the 0x005FB14E constructor, rowed as Rva005FB1AD's
// (Rva005FB1ADCtor.cpp) with that row's signature.
class Rva005FB1AD
{
	char m_pad[0x24];
public:
	Rva005FB1AD(void *a, void *b, void *c);
};
// Constructor-only storage view of the owner whose 207-byte constructor is
// verified in Rva005FB204Ctor.cpp; allocation and three arguments are unchanged.
class Rva005FB204
{
	char m_pad[0x20];
public:
	Rva005FB204(unsigned int first, unsigned int second, void *context);
};
// Constructor-only view of the second verified Rva005FB204Ctor.cpp owner.
class Rva005FB3D9
{
	char m_pad[0x20];
public:
	Rva005FB3D9(unsigned int first, unsigned int second, void *context);
};
struct Rva005E9761
{
	char m_prefix[8];
	Rva005E5CF9In m_context;
	RvaF1Handle rva005E9761(unsigned int first, unsigned int second);
};
struct Rva005E97D5
{
	char m_prefix[8];
	Rva005E5CF9In m_context;
	RvaF1Handle rva005E97D5(unsigned int first, unsigned int second);
};
struct Rva005E9849
{
	char m_prefix[8];
	Rva005E5CF9In m_context;
	RvaF1Handle rva005E9849(unsigned int first, unsigned int second);
};



