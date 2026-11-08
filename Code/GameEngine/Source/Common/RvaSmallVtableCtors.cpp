// cl: /O1 /DNDEBUG /MD
//
// Small constructors that install a vtable, in two shapes of rowed bodies:
//   18 bytes as ??0Rva005CB22A (V3PolyCopyCtors.cpp): store the vtable, then the
//     pointer argument at +4;
//   13 bytes as ??0NetCommandWrapperList: zero +4, then store the vtable, the
//     order an inlined base constructor followed by the derived vtable store gives.
// Each copy differs from its template only in the vtable it installs. One class
// per copy names that vtable; its destructor is inline and empty so the vtable
// the compiler emits resolves in this unit. The owning classes are not
// recovered, so each keeps its address.

#include <new.h>

struct RvaSmallVtableZeroBase
{
	void *m_04;
	RvaSmallVtableZeroBase() : m_04(0) {}
};

// ??0Rva000ABD56@@QAE@PAX@Z @0x000ABD56 18B, vtable VA 0xbc957c
class Rva000ABD56
{
public:
	Rva000ABD56(void *payload);
	virtual ~Rva000ABD56() {}
private:
	void *m_04;
};

Rva000ABD56::Rva000ABD56(void *payload) : m_04(payload)
{
}

// ??0Rva00222A19@@QAE@PAX@Z @0x00222A19 18B, vtable VA 0xbe6d5c
class Rva00222A19
{
public:
	Rva00222A19(void *payload);
	virtual ~Rva00222A19() {}
private:
	void *m_04;
};

Rva00222A19::Rva00222A19(void *payload) : m_04(payload)
{
}

// ??0Rva002293F9@@QAE@PAX@Z @0x002293F9 18B, vtable VA 0xbe73e4
class Rva002293F9
{
public:
	Rva002293F9(void *payload);
	virtual ~Rva002293F9() {}
private:
	void *m_04;
};

Rva002293F9::Rva002293F9(void *payload) : m_04(payload)
{
}

// ??0Rva002AAD77@@QAE@PAX@Z @0x002AAD77 18B, vtable VA 0xbfdc60
class Rva002AAD77
{
public:
	Rva002AAD77(void *payload);
	virtual ~Rva002AAD77() {}
private:
	void *m_04;
};

Rva002AAD77::Rva002AAD77(void *payload) : m_04(payload)
{
}

// ??0Rva002AAD9C@@QAE@PAX@Z @0x002AAD9C 18B, vtable VA 0xbfdc6c
class Rva002AAD9C
{
public:
	Rva002AAD9C(void *payload);
	virtual ~Rva002AAD9C() {}
private:
	void *m_04;
};

Rva002AAD9C::Rva002AAD9C(void *payload) : m_04(payload)
{
}

// ??0Rva002B29D8@@QAE@PAX@Z @0x002B29D8 18B, vtable VA 0xbfe000
class Rva002B29D8
{
public:
	Rva002B29D8(void *payload);
	virtual ~Rva002B29D8() {}
private:
	void *m_04;
};

Rva002B29D8::Rva002B29D8(void *payload) : m_04(payload)
{
}

// ??0Rva0032A3C6@@QAE@PAX@Z @0x0032A3C6 18B, vtable VA 0xc0d938
class Rva0032A3C6
{
public:
	Rva0032A3C6(void *payload);
	virtual ~Rva0032A3C6() {}
private:
	void *m_04;
};

Rva0032A3C6::Rva0032A3C6(void *payload) : m_04(payload)
{
}

// ??0Rva003A538E@@QAE@PAX@Z @0x003A538E 18B, vtable VA 0xc1b320
class Rva003A538E
{
public:
	Rva003A538E(void *payload);
	virtual ~Rva003A538E();
private:
	void *m_04;
};

// ??1Rva003A538E@@UAE@XZ @0x003A53A0 7B: the empty destructor, restoring the vtable
// (VA 0x00C1B320).
Rva003A538E::~Rva003A538E()
{
}

Rva003A538E::Rva003A538E(void *payload) : m_04(payload)
{
}

// ??0Rva003EE734@@QAE@PAX@Z @0x003EE734 18B, vtable VA 0xc363c0
class Rva003EE734
{
public:
	Rva003EE734(void *payload);
	virtual ~Rva003EE734() {}
private:
	void *m_04;
};

Rva003EE734::Rva003EE734(void *payload) : m_04(payload)
{
}

// ??0Rva003F3FEC@@QAE@PAX@Z @0x003F3FEC 18B, vtable VA 0xc37064
class Rva003F3FEC
{
public:
	Rva003F3FEC(void *payload);
	virtual ~Rva003F3FEC() {}
private:
	void *m_04;
};

Rva003F3FEC::Rva003F3FEC(void *payload) : m_04(payload)
{
}

// ??0Rva003F424F@@QAE@PAX@Z @0x003F424F 18B, vtable VA 0xc37080: the
// LivingWorldBattle traversal visitor (invoke at 0x003F55B6 in
// VslotSmallBodiesL.cpp, inlined construction in Rva003F6A91Dtor.cpp); its
// one-slot interface base keeps the emitted table and deleting destructor
// identical in every unit.
class Rva003F498ACallback
{
public:
	virtual bool invoke(int) = 0;
	~Rva003F498ACallback() {}
};
class Rva003F424F : public Rva003F498ACallback
{
public:
	Rva003F424F(void *payload);
	virtual bool invoke(int);
	virtual ~Rva003F424F() {}
private:
	void *m_04;
};

Rva003F424F::Rva003F424F(void *payload) : m_04(payload)
{
}

// ??0Rva003F82E2@@QAE@PAX@Z @0x003F82E2 18B, vtable VA 0xc37310
class Rva003F82E2
{
public:
	Rva003F82E2(void *payload);
	virtual ~Rva003F82E2() {}
private:
	void *m_04;
};

Rva003F82E2::Rva003F82E2(void *payload) : m_04(payload)
{
}

// ??0Rva003FC428@@QAE@PAX@Z @0x003FC428 18B, vtable VA 0xc37c20
class Rva003FC428
{
public:
	Rva003FC428(void *payload);
	virtual ~Rva003FC428() {}
private:
	void *m_04;
};

Rva003FC428::Rva003FC428(void *payload) : m_04(payload)
{
}

// ??0Rva004318C6@@QAE@PAX@Z @0x004318C6 18B, vtable VA 0xc3c970
class Rva004318C6
{
public:
	Rva004318C6(void *payload);
	virtual ~Rva004318C6();
private:
	void *m_04;
};

Rva004318C6::Rva004318C6(void *payload) : m_04(payload)
{
}

// The 0x00431A64 family below stores the pointer before the vtable: the order
// an inlined base constructor taking it, then the derived vtable store, gives.
struct RvaSmallVtablePtrBase
{
	void *m_04;
	RvaSmallVtablePtrBase(void *payload) : m_04(payload) {}
};

// ??0Rva004318FC@@QAE@PAX@Z @0x004318FC 18B, vtable VA 0xc3c97c (slot 0 the shared
// deleting dtor 0x00431A64 of this command-handler family)
class Rva004318FC : public RvaSmallVtablePtrBase
{
public:
	Rva004318FC(void *payload);
	virtual ~Rva004318FC() {}
};

Rva004318FC::Rva004318FC(void *payload) : RvaSmallVtablePtrBase(payload)
{
}

// ??0Rva0043190E@@QAE@PAX@Z @0x0043190E 18B, vtable VA 0xc3c988 (slot 0 the shared
// deleting dtor 0x00431A64 of this command-handler family)
class Rva0043190E : public RvaSmallVtablePtrBase
{
public:
	Rva0043190E(void *payload);
	virtual ~Rva0043190E() {}
};

Rva0043190E::Rva0043190E(void *payload) : RvaSmallVtablePtrBase(payload)
{
}

// ??0Rva004319C2@@QAE@PAX@Z @0x004319C2 18B, vtable VA 0xc3c9a0 (slot 0 the shared
// deleting dtor 0x00431A64 of this command-handler family)
class Rva004319C2 : public RvaSmallVtablePtrBase
{
public:
	Rva004319C2(void *payload);
	virtual ~Rva004319C2() {}
};

Rva004319C2::Rva004319C2(void *payload) : RvaSmallVtablePtrBase(payload)
{
}

// ??0Rva0059B060@@QAE@PAX@Z @0x0059B060 18B, vtable VA 0xc70e60
class Rva0059B060
{
public:
	Rva0059B060(void *payload);
	virtual ~Rva0059B060() {}
private:
	void *m_04;
};

Rva0059B060::Rva0059B060(void *payload) : m_04(payload)
{
}

// ??0Rva005B253F@@QAE@PAX@Z @0x005B253F 18B, vtable VA 0xc72b74
class Rva005B253F
{
public:
	Rva005B253F(void *payload);
	virtual ~Rva005B253F();
private:
	void *m_04;
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva005B253F::Rva005B253F(void *payload) : m_04(payload)
{
}

// ?bfmeAnchorRva005B253F absent-from-retail
void *bfmeAnchorRva005B253F(void *where, void *p)
{
	return ::new (where) Rva005B253F(p);
}


// ??0Rva005C1860@@QAE@PAX@Z @0x005C1860 18B, vtable VA 0xc743b8
class Rva005C1860
{
public:
	Rva005C1860(void *payload);
	virtual ~Rva005C1860() {}
private:
	void *m_04;
};

Rva005C1860::Rva005C1860(void *payload) : m_04(payload)
{
}

// ??0Rva005CD9AE@@QAE@PAX@Z @0x005CD9AE 18B, vtable VA 0xc75014
template <class T> class RvaCloneResult;
class Rva005CDB8F;
struct RvaPayloadInput16;

class Rva005CD9AE
{
public:
	Rva005CD9AE(void *payload);
	virtual RvaCloneResult<Rva005CDB8F> create(const RvaPayloadInput16 &input);
private:
	void *m_04;
};

Rva005CD9AE::Rva005CD9AE(void *payload) : m_04(payload)
{
}

// ??0Rva005CF872@@QAE@PAX@Z @0x005CF872 18B, vtable VA 0xc75290
// Retail table C75290 has two slots: the deleting wrapper 0x005CF884 and the
// shared empty body 0x004B3FD0 (slot 2 starts the next table at C75298); slot 1
// is the state handlers' Update (WB names the overrides Update).
class Rva005CF872
{
public:
	Rva005CF872(void *payload);
	virtual ~Rva005CF872() {}
	virtual void Update() {}
private:
	void *m_04;
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva005CF872::Rva005CF872(void *payload) : m_04(payload)
{
}

// ?bfmeAnchorRva005CF872 absent-from-retail
void *bfmeAnchorRva005CF872(void *where, void *p)
{
	return ::new (where) Rva005CF872(p);
}


// ??0Rva005EA1D5@@QAE@PAX@Z @0x005EA1D5 18B, vtable VA 0xc781b4
class Rva005EA1D5
{
public:
	Rva005EA1D5(void *payload);
	virtual ~Rva005EA1D5() {}
private:
	void *m_04;
};

Rva005EA1D5::Rva005EA1D5(void *payload) : m_04(payload)
{
}

// ??0Rva00656090@@QAE@PAX@Z @0x00656090 18B, vtable VA 0xce0fb4
class Rva00656090
{
public:
	Rva00656090(void *payload);
	virtual ~Rva00656090() {}
private:
	void *m_04;
};

Rva00656090::Rva00656090(void *payload) : m_04(payload)
{
}

// ??0Rva00040ECE@@QAE@XZ @0x00040ECE 13B, vtable VA 0xbc16b8
class Rva00040ECE : public RvaSmallVtableZeroBase
{
public:
	Rva00040ECE();
	virtual ~Rva00040ECE() {}
};

Rva00040ECE::Rva00040ECE()
{
}

// ??0Rva000421C8@@QAE@XZ @0x000421C8 13B, vtable VA 0xbc26e0
// The partition filter base. Retail's vftable has three slots: the deleting
// dtor 0x000421D5, __purecall 0x0003B810 (allow) and the shared `or eax,-1`
// body 0x0036CC7A (getPlayerMask), the view the other filter units declare.
class Object;
class Rva000421C8 : public RvaSmallVtableZeroBase
{
public:
	Rva000421C8();
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
};

// getPlayerMask resolves to the real byte-verified implementation in
// ActionManagerSpecialPowerChecks.cpp (retail 0x0036CC7A).

inline Rva000421C8::Rva000421C8()
{
}

// ??0Rva000657D9@@QAE@XZ @0x000657D9 13B, vtable VA 0xbc5c6c
class Rva000657D9 : public RvaSmallVtableZeroBase
{
public:
	Rva000657D9();
	virtual ~Rva000657D9() {}
};

Rva000657D9::Rva000657D9()
{
}

// ??0Rva0007DF07@@QAE@XZ @0x0007DF07 13B, vtable VA 0xbc6f20
#include "../../Include/Common/Rva0007DF07.h"

// ??0Rva0023DAE8@@QAE@H@Z @0x0023DAE8 15B (RET4, unused word), vtable VA
// 0xbedaa0 (the refcounted node table Bfme5NodeMakers.cpp stores by address).
// A Rva0007DF07: vtable 0xBEDAA0's slot 0 is the ICF-shared deleting dtor
// 0x005FAA31, whose dtor 0x004E84A4 restores Rva0007DF07's vtable 0xbc6f20.
// The inlined base zeroes +4 and its vptr store dies under the derived one;
// the empty derived dtor reduces to the base's restore, byte for byte the
// 0x004E84A4 body the linker folded it into (ICF alias row). Moved here from
// GapLeavesSeat8.cpp: that unit's /G7 turns the inlined and-zero store into
// a mov, while this unit's flags give retail's bytes for both.
class Rva0023DAE8 : public Rva0007DF07
{
public:
	Rva0023DAE8(int unused);
	virtual ~Rva0023DAE8();
};

Rva0023DAE8::Rva0023DAE8(int)
{
}

// ??1Rva0023DAE8@@UAE@XZ @0x004E84A4 7B: ICF-folded with the base restore.
Rva0023DAE8::~Rva0023DAE8()
{
}

// Two more Rva0007DF07 subclasses whose vtables' slot 0 is the same ICF-shared
// deleting dtor 0x005FAA31 (dtor 0x004E84A4): vtable VA 0xc7506c installed by
// the Rva002D76A6 ctor (Rva0004EFE9Ctor.cpp unwinds through it) and vtable VA
// 0xc7a630 of Rva00567960BaseMid (Rva00567CCDCtor.cpp). Their empty dtors fold
// into the same restore (ICF alias rows).
class Rva002D76A6 : public Rva0007DF07
{
public:
	virtual ~Rva002D76A6();
};

Rva002D76A6::~Rva002D76A6()
{
}

#include "../../Include/Common/Rva00567960BaseMid.h"

Rva00567960BaseMid::~Rva00567960BaseMid()
{
}

// ??0Rva000A882D@@QAE@XZ @0x000A882D 13B, vtable VA 0xbc93a0
class Rva000A882D : public RvaSmallVtableZeroBase
{
public:
	Rva000A882D();
	virtual ~Rva000A882D() {}
};

Rva000A882D::Rva000A882D()
{
}

// ??0Rva000FBA4A@@QAE@XZ @0x000FBA4A 13B, vtable VA 0xbcf364
class Rva000FBA4A : public RvaSmallVtableZeroBase
{
public:
	Rva000FBA4A();
	virtual ~Rva000FBA4A() {}
};

Rva000FBA4A::Rva000FBA4A()
{
}

// ??0Rva00217497@@QAE@XZ @0x00217497 13B, vtable VA 0xbe5aa8
class Rva00217497 : public RvaSmallVtableZeroBase
{
public:
	Rva00217497();
	virtual ~Rva00217497() {}
};

Rva00217497::Rva00217497()
{
}

// The two-slot native table shares WindowTranslator's handler.
class GameMessage;
enum GameMessageDisposition { KEEP_MESSAGE, DESTROY_MESSAGE };
class GameMessageTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg) = 0;
	virtual ~GameMessageTranslator() {}
};
class WindowTranslator : public GameMessageTranslator
{
public:
	__declspec(dllimport) __forceinline WindowTranslator() : m_mode(1) {}
	virtual ~WindowTranslator();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
protected:
	int m_mode;
};
class Rva002390F8 : public WindowTranslator
{
public:
	Rva002390F8();
	virtual ~Rva002390F8();
};

__declspec(noinline) inline Rva002390F8::Rva002390F8()
{
	m_mode = 0;
}

// ?bfmeAnchorRva002390F8 absent-from-retail
void *bfmeAnchorRva002390F8(void *where)
{
	return ::new (where) Rva002390F8();
}


// ??0Rva0026FFB1@@QAE@XZ @0x0026FFB1 13B, vtable VA 0xbfad1c
class Rva0026FFB1 : public RvaSmallVtableZeroBase
{
public:
	Rva0026FFB1();
	virtual ~Rva0026FFB1() {}
};

Rva0026FFB1::Rva0026FFB1()
{
}

// ??0Rva0030D346@@QAE@XZ @0x0030D346 13B, vtable VA 0xc089ec
class Rva0030D346 : public RvaSmallVtableZeroBase
{
public:
	Rva0030D346();
	virtual ~Rva0030D346() {}
};

inline Rva0030D346::Rva0030D346()
{
}

// ??0Rva003E3C0C@@QAE@XZ @0x003E3C0C 13B, vtable VA 0xc35b28
class Rva003E3C0C : public RvaSmallVtableZeroBase
{
public:
	Rva003E3C0C();
	virtual ~Rva003E3C0C() {}
};

Rva003E3C0C::Rva003E3C0C()
{
}

// ??0Rva0048B664@@QAE@XZ @0x0048B664 13B, vtable VA 0xc4bf78
class Rva0048B664 : public RvaSmallVtableZeroBase
{
public:
	Rva0048B664();
	virtual ~Rva0048B664() {}
};

Rva0048B664::Rva0048B664()
{
}

// ??0Rva004B236E@@QAE@XZ @0x004B236E 13B, vtable VA 0xc56930
class Rva004B236E : public RvaSmallVtableZeroBase
{
public:
	Rva004B236E();
	virtual ~Rva004B236E() {}
};

Rva004B236E::Rva004B236E()
{
}

// ??0Rva0051489D@@QAE@XZ @0x0051489D 13B, vtable VA 0xc65ee0
class Rva0051489D : public RvaSmallVtableZeroBase
{
public:
	Rva0051489D();
	virtual ~Rva0051489D() {}
};

Rva0051489D::Rva0051489D()
{
}

// ??0Rva0052510C@@QAE@XZ @0x0052510C 13B, vtable VA 0xc67e50
class Rva0052510C : public RvaSmallVtableZeroBase
{
public:
	Rva0052510C();
	virtual ~Rva0052510C() {}
};

Rva0052510C::Rva0052510C()
{
}

// Three more shapes, also differing from their rowed template only in the vtable:
//   20 bytes as ??0NetCommandList: store the vtable, then zero +4, +8 and +0xC;
//   17 bytes as BfmeThingTC::bfmeBaseTC: zero +4 and +8, then store the vtable;
//   23 bytes as ??0Rva0036247C: store the vtable, then zero +4 .. +0x10.

struct RvaSmallVtableZeroBase2
{
	virtual ~RvaSmallVtableZeroBase2() {}
	void *m_04;
	void *m_08;
	RvaSmallVtableZeroBase2() : m_04(0), m_08(0) {}
};

// ??0Rva00148AB0@@QAE@XZ @0x00148AB0 20B, vtable VA 0xbd3564
class Rva00148AB0
{
public:
	Rva00148AB0();
	virtual ~Rva00148AB0() {}
private:
	void *m_04;
	void *m_08;
	void *m_0C;
};

Rva00148AB0::Rva00148AB0()
	: m_04(0), m_08(0), m_0C(0)
{
}

// ??0Rva004E1780@@QAE@XZ @0x004E1780 20B, vtable VA 0xc61b78
class Rva004E1780
{
public:
	Rva004E1780();
	virtual ~Rva004E1780() {}
private:
	void *m_04;
	void *m_08;
	void *m_0C;
};

Rva004E1780::Rva004E1780()
	: m_04(0), m_08(0), m_0C(0)
{
}

// ??0Rva0054D54A@@QAE@XZ @0x0054D54A 20B, vtable VA 0xc6a774. Its destructor is
// rowed too (0x0054D55E, below): it frees the node list at +4 exactly as
// ~NetCommandWrapperList does, storing this class's vtable on entry.
struct Rva0054D54ANode
{
	virtual void *destroy(unsigned int flags);
	Rva0054D54ANode *m_next;
};

// The node list's view of a message: the argument count byte at +0x18 and
// the per-argument type query.
enum GameMessageArgumentDataType
{
	ARGUMENTDATATYPE_INTEGER,
	ARGUMENTDATATYPE_REAL,
	ARGUMENTDATATYPE_BOOLEAN,
	ARGUMENTDATATYPE_OBJECTID,
	ARGUMENTDATATYPE_DRAWABLEID,
	ARGUMENTDATATYPE_TEAMID,
	ARGUMENTDATATYPE_LOCATION,
	ARGUMENTDATATYPE_PIXEL,
	ARGUMENTDATATYPE_PIXELREGION,
	ARGUMENTDATATYPE_TIMESTAMP,
	ARGUMENTDATATYPE_WIDECHAR,
	ARGUMENTDATATYPE_UNKNOWN
};

#include "../../Include/Common/MessageStream.h"

class Rva0054D54A
{
public:
	Rva0054D54A();
	Rva0054D54A(GameMessage *msg);
	virtual ~Rva0054D54A();
private:
	Rva0054D54ANode *m_04;
	void *m_08;
	int m_0C;
};

Rva0054D54A::Rva0054D54A()
	: m_04(0), m_08(0), m_0C(0)
{
}

// ??1Rva0054D54A@@UAE@XZ @0x0054D55E 53B: the bytes of ~NetCommandWrapperList
// except the vtable stored on entry.
Rva0054D54A::~Rva0054D54A()
{
	while (m_04 != 0) {
		Rva0054D54ANode *next = m_04->m_next;
		void *p = m_04 ? m_04->destroy(0) : 0;
		::operator delete(p);
		m_04 = next;
	}
}

// ??0Rva001FD2B4@@QAE@XZ @0x001FD2B4 17B, vtable VA 0xbe1aa0
class Rva001FD2B4 : public RvaSmallVtableZeroBase2
{
public:
	Rva001FD2B4();
	virtual ~Rva001FD2B4() {}
};

Rva001FD2B4::Rva001FD2B4()
{
}

// ??0Rva002D24F6@@QAE@XZ @0x002D24F6 17B, vtable VA 0xc02a5c
class Rva002D24F6 : public RvaSmallVtableZeroBase2
{
public:
	Rva002D24F6();
	virtual ~Rva002D24F6() {}
};

Rva002D24F6::Rva002D24F6()
{
}

// ??0Rva0043A340@@QAE@XZ @0x0043A340 17B, vtable VA 0xc3d490
class Rva0043A340 : public RvaSmallVtableZeroBase2
{
public:
	Rva0043A340();
	virtual ~Rva0043A340() {}
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva0043A340::Rva0043A340()
{
}

// ?bfmeAnchorRva0043A340 absent-from-retail
void *bfmeAnchorRva0043A340(void *where)
{
	return ::new (where) Rva0043A340();
}


// ??0Rva004817F4@@QAE@XZ @0x004817F4 17B, vtable VA 0xc49174
class Rva004817F4 : public RvaSmallVtableZeroBase2
{
public:
	Rva004817F4();
	virtual ~Rva004817F4() {}
};

Rva004817F4::Rva004817F4()
{
}

// ??0Rva003E3C22@@QAE@XZ @0x003E3C22 23B, vtable VA 0xc35b34
class Rva003E3C22
{
public:
	Rva003E3C22();
	virtual ~Rva003E3C22() {}
private:
	void *m_04;
	void *m_08;
	void *m_0C;
	void *m_10;
};

Rva003E3C22::Rva003E3C22()
	: m_04(0), m_08(0), m_0C(0), m_10(0)
{
}

// ??0Rva0054D593@@QAE@PAX0@Z @0x0054D593 29B, vtable VA 0xc6a778: zero +4,
// store first arg at +8, vtable, then second arg at +0xC. Two new-placement
// calls in 0x0054D5D3 pass the outer args through after a 0x10 operator new.
class Rva0054D593
{
	friend class Rva0054D5D3;
public:
	Rva0054D593(void *a, void *b);
	virtual ~Rva0054D593();
private:
	Rva0054D593 *m_04;
	void *m_08;
	void *m_0C;
};

// ??1Rva0054D593@@UAE@XZ @0x0054D5B0 7B: the empty destructor, restoring the vtable
// (VA 0x00C6A778).
Rva0054D593::~Rva0054D593()
{
}

Rva0054D593::Rva0054D593(void *a, void *b)
	: m_04(0), m_08(a), m_0C(b)
{
}

// ?rva0054D5D3@Rva0054D5D3@@QAEX PAX0@Z @0x0054D5D3 93B: list append with
// 0x10 operator new of Rva0054D593. Empty list sets head and tail to the new
// node; otherwise tails next is set and tail advances via a reload. Callers
// at 0x0054D699 0x0054D6B7 0x0037B908 0x00591FA8 pass the two data args.
class Rva0054D5D3
{
public:
	virtual ~Rva0054D5D3();
	void rva0054D5D3(void *a, void *b);
private:
	Rva0054D593 *m_04;
	Rva0054D593 *m_08;
};

void Rva0054D5D3::rva0054D5D3(void *a, void *b)
{
	if (m_04 == 0)
	{
		Rva0054D593 *p = new Rva0054D593(a, b);
		m_04 = p;
		m_08 = p;
	}
	else
	{
		Rva0054D593 *p = new Rva0054D593(a, b);
		m_08->m_04 = p;
		m_08 = m_08->m_04;
	}
}

// ??0Rva0054D54A@@QAE@PAVGameMessage@@@Z @0x0054D64D 123B: ZH's
// GameMessageParser(GameMessage *) constructor, statement for statement: runs
// of equal argument types become one rva0054D5D3(type, count) append each,
// counted at +0xC (ARGUMENTDATATYPE_UNKNOWN, 11, seeds the run type). The
// add-game-command room check 0x0058D92F builds one with operator new(0x10)
// and walks the +4 list it makes, so this class is GameMessageParser in all but
// name; the append is reached through its own address-named class.
Rva0054D54A::Rva0054D54A(GameMessage *msg)
	: m_04(0), m_08(0), m_0C(0)
{
	unsigned char argCount = msg->getArgumentCount();
	GameMessageArgumentDataType lasttype = ARGUMENTDATATYPE_UNKNOWN;
	int thisTypeCount = 0;
	for (unsigned char i = 0; i < argCount; ++i) {
		GameMessageArgumentDataType type = msg->getArgumentDataType(i);
		if (type != lasttype) {
			if (thisTypeCount > 0) {
				((Rva0054D5D3 *)this)->rva0054D5D3((void *)lasttype, (void *)thisTypeCount);
				++m_0C;
			}
			lasttype = type;
			thisTypeCount = 0;
		}
		++thisTypeCount;
	}
	if (thisTypeCount > 0) {
		((Rva0054D5D3 *)this)->rva0054D5D3((void *)lasttype, (void *)thisTypeCount);
		++m_0C;
	}
}

// ??0Rva000421C8 is a header inline elsewhere: other units emit select-any
// copies of it, so a strong definition here was a duplicate symbol in the
// linked build. This anchor only makes this unit emit its copy for the ledger
// row; it is not retail code. ??0Rva0007DF07 and ??0Rva0030D346 below are the
// same: their inline copies elsewhere (static instance, dtor TUs) forced the
// strong definitions here into duplicates as well.
#pragma inline_depth(0)
// ?bfmeEmitRva000421C8Ctor@@YAXPAVRva000421C8@@@Z present-unmatched
void bfmeEmitRva000421C8Ctor(Rva000421C8 *p)
{
	p->Rva000421C8::Rva000421C8();
}
// ?bfmeEmitRva0007DF07Ctor@@YAXPAVRva0007DF07@@@Z present-unmatched
void bfmeEmitRva0007DF07Ctor(Rva0007DF07 *p)
{
	p->Rva0007DF07::Rva0007DF07();
}
// ?bfmeEmitRva0030D346Ctor@@YAXPAVRva0030D346@@@Z present-unmatched
void bfmeEmitRva0030D346Ctor(Rva0030D346 *p)
{
	p->Rva0030D346::Rva0030D346();
}
// Retain the inline base destructor's ledger body without changing its callers.
// ?bfmeEmitRva005B253FDtor@@YAXPAVRva005B253F@@@Z absent-from-retail
void bfmeEmitRva005B253FDtor(Rva005B253F *p)
{
	p->Rva005B253F::~Rva005B253F();
}
#pragma inline_depth()

// ??1Rva004318C6@@UAE@XZ @0x004318D8 7B: the empty dtor, restoring the vtable (the
// deleting dtor still expands it inline).
Rva004318C6::~Rva004318C6()
{
}

// ??1Rva005B253F@@UAE@XZ @0x005B2551 7B: the empty dtor, restoring the vtable (the
// deleting dtor still expands it inline). Match the consumers' select-any copy.
inline Rva005B253F::~Rva005B253F()
{
}


// Batch of further copies found in .text gaps (same three shapes as above).

// ??0Rva000FC59D@@QAE@XZ @0x000FC59D 13B, vtable VA 0x00bcf380
class Rva000FC59D : public RvaSmallVtableZeroBase
{
public:
	Rva000FC59D();
	virtual ~Rva000FC59D() {}
};

Rva000FC59D::Rva000FC59D()
{
}

// ??0Rva001F017B@@QAE@XZ @0x001F017B 13B, vtable VA 0x00be09e8
class Rva001F017B : public RvaSmallVtableZeroBase
{
public:
	Rva001F017B();
	virtual ~Rva001F017B() {}
};

Rva001F017B::Rva001F017B()
{
}

// ??0Rva002035D5@@QAE@XZ @0x002035D5 13B, vtable VA 0x00be3990
class Rva002035D5 : public RvaSmallVtableZeroBase
{
public:
	Rva002035D5();
	virtual ~Rva002035D5() {}
};

Rva002035D5::Rva002035D5()
{
}

// ??0Rva002D3347@@QAE@XZ @0x002D3347 13B, vtable VA 0x00c02a84
class Rva002D3347 : public RvaSmallVtableZeroBase
{
public:
	Rva002D3347();
	virtual ~Rva002D3347() {}
};

Rva002D3347::Rva002D3347()
{
}

// ??0Rva0037DE63@@QAE@XZ @0x0037DE63 13B, vtable VA 0x00c18d64
class Rva0037DE63 : public RvaSmallVtableZeroBase
{
public:
	Rva0037DE63();
	virtual ~Rva0037DE63() {}
};

Rva0037DE63::Rva0037DE63()
{
}

// ??0Rva004103DA@@QAE@XZ @0x004103DA 13B, vtable VA 0x00c3ed74
class Rva004103DA : public RvaSmallVtableZeroBase
{
public:
	Rva004103DA();
	virtual ~Rva004103DA() {}
};

Rva004103DA::Rva004103DA()
{
}

// ??0Rva00545D43@@QAE@XZ @0x00545D43 13B, vtable VA 0x00c6a13c
class Rva00545D43 : public RvaSmallVtableZeroBase
{
public:
	Rva00545D43();
	virtual ~Rva00545D43() {}
};

Rva00545D43::Rva00545D43()
{
}

// ??0Rva005CDB5F@@QAE@XZ @0x005CDB5F 13B, vtable VA 0x00c7506c
class Rva005CDB5F : public RvaSmallVtableZeroBase
{
public:
	Rva005CDB5F();
	virtual ~Rva005CDB5F() {}
};

Rva005CDB5F::Rva005CDB5F()
{
}

// ??0Rva005E96F8@@QAE@XZ @0x005E96F8 13B, vtable VA 0x00c79e44
class Rva005E96F8 : public RvaSmallVtableZeroBase
{
public:
	Rva005E96F8();
	virtual ~Rva005E96F8() {}
};

Rva005E96F8::Rva005E96F8()
{
}

// ??0Rva005F252A@@QAE@XZ @0x005F252A 13B, vtable VA 0x00c4ef80
class Rva005F252A : public RvaSmallVtableZeroBase
{
public:
	Rva005F252A();
	virtual ~Rva005F252A() {}
};

Rva005F252A::Rva005F252A()
{
}

// ??0Rva006003EF@@QAE@XZ @0x006003EF 13B, vtable VA 0x00c7a630
class Rva006003EF : public RvaSmallVtableZeroBase
{
public:
	Rva006003EF();
	virtual ~Rva006003EF() {}
};

Rva006003EF::Rva006003EF()
{
}

// ??0Rva005CF913@@QAE@PAX@Z @0x005CF913 18B, vtable VA 0x00c752a0
class Rva005CF913 : public RvaSmallVtablePtrBase
{
public:
	Rva005CF913(void *payload);
	virtual ~Rva005CF913() {}
};

Rva005CF913::Rva005CF913(void *payload) : RvaSmallVtablePtrBase(payload)
{
}

// ??0Rva005CF925@@QAE@PAX@Z @0x005CF925 18B, vtable VA 0x00c752a8
class Rva005CF925 : public RvaSmallVtablePtrBase
{
public:
	Rva005CF925(void *payload);
	virtual ~Rva005CF925() {}
};

Rva005CF925::Rva005CF925(void *payload) : RvaSmallVtablePtrBase(payload)
{
}

// ??0Rva005D1052@@QAE@PAX@Z @0x005D1052 18B, vtable VA 0x00c755a4
class Rva005D1052 : public RvaSmallVtablePtrBase
{
public:
	Rva005D1052(void *payload);
	virtual ~Rva005D1052() {}
};

Rva005D1052::Rva005D1052(void *payload) : RvaSmallVtablePtrBase(payload)
{
}

// ??0Rva000EF9F3@@QAE@PAX@Z @0x000EF9F3 18B, vtable VA 0x00bcef9c
class Rva000EF9F3
{
public:
	Rva000EF9F3(void *payload);
	virtual ~Rva000EF9F3() {}
private:
	void *m_04;
};

Rva000EF9F3::Rva000EF9F3(void *payload) : m_04(payload)
{
}

// ??0Rva002B29F8@@QAE@PAX@Z @0x002B29F8 18B, vtable VA 0x00bfe004
class Rva002B29F8
{
public:
	Rva002B29F8(void *payload);
	virtual ~Rva002B29F8() {}
private:
	void *m_04;
};

Rva002B29F8::Rva002B29F8(void *payload) : m_04(payload)
{
}

// ??0Rva00306A36@@QAE@PAX@Z @0x00306A36 18B, vtable VA 0x00c07dd8
class Rva00306A36
{
public:
	Rva00306A36(void *payload);
	virtual ~Rva00306A36() {}
private:
	void *m_04;
};

Rva00306A36::Rva00306A36(void *payload) : m_04(payload)
{
}

// ??0Rva0052787E@@QAE@PAX@Z @0x0052787E 18B, vtable VA 0x00c6805c
class Rva0052787E
{
public:
	Rva0052787E(void *payload);
	virtual ~Rva0052787E() {}
private:
	void *m_04;
};

Rva0052787E::Rva0052787E(void *payload) : m_04(payload)
{
}

// ??0Rva0056AC9C@@QAE@PAX@Z @0x0056AC9C 18B, vtable VA 0x00c6d0bc
class Rva0056AC9C
{
public:
	Rva0056AC9C(void *payload);
	virtual ~Rva0056AC9C() {}
private:
	void *m_04;
};

Rva0056AC9C::Rva0056AC9C(void *payload) : m_04(payload)
{
}

// ??0Rva005754ED@@QAE@PAX@Z @0x005754ED 18B, vtable VA 0x00c6e60c
class Rva005754ED
{
public:
	Rva005754ED(void *payload);
	virtual ~Rva005754ED() {}
private:
	void *m_04;
};

Rva005754ED::Rva005754ED(void *payload) : m_04(payload)
{
}

// ??0Rva005CDCDC@@QAE@PAX@Z @0x005CDCDC 18B, vtable VA 0x00c7508c
class Rva005CDCDC
{
public:
	Rva005CDCDC(void *payload);
	virtual ~Rva005CDCDC() {}
private:
	void *m_04;
};

Rva005CDCDC::Rva005CDCDC(void *payload) : m_04(payload)
{
}

// ??0Rva005CE8DC@@QAE@PAX@Z @0x005CE8DC 18B, vtable VA 0x00c751a8
class Rva005CE8DC
{
public:
	Rva005CE8DC(void *payload);
	virtual ~Rva005CE8DC() {}
private:
	void *m_04;
};

Rva005CE8DC::Rva005CE8DC(void *payload) : m_04(payload)
{
}

// ??0Rva005D1023@@QAE@PAX@Z @0x005D1023 18B, vtable VA 0x00c7559c
class Rva005D1023
{
public:
	Rva005D1023(void *payload);
	virtual ~Rva005D1023() {}
private:
	void *m_04;
};

Rva005D1023::Rva005D1023(void *payload) : m_04(payload)
{
}

// ??0Rva005E9F69@@QAE@PAX@Z @0x005E9F69 18B, vtable VA 0x00c780bc
class Rva005E9F69
{
public:
	Rva005E9F69(void *payload);
	virtual ~Rva005E9F69() {}
private:
	void *m_04;
};

Rva005E9F69::Rva005E9F69(void *payload) : m_04(payload)
{
}

// ??0Rva005E9F92@@QAE@PAX@Z @0x005E9F92 18B, vtable VA 0x00c780f4
class Rva005E9F92
{
public:
	Rva005E9F92(void *payload);
	virtual ~Rva005E9F92() {}
private:
	void *m_04;
};

Rva005E9F92::Rva005E9F92(void *payload) : m_04(payload)
{
}

// 9-byte copies: a class whose only state is its vtable; the constructor
// returns this after the vtable store (mov eax,ecx / mov [eax],vt / ret).
// Each copy installs the vtable named beside it; owners unrecovered.

// ??0Rva00001199@@QAE@XZ @0x00001199 9B, vtable VA 0x00bbb524
class Rva00001199
{
public:
	Rva00001199();
	virtual ~Rva00001199() {}
};

Rva00001199::Rva00001199()
{
}

// ??0Rva00035830@@QAE@XZ @0x00035830 9B, vtable VA 0x00be2b78
class Rva00035830
{
public:
	Rva00035830();
	virtual ~Rva00035830() {}
};

Rva00035830::Rva00035830()
{
}

// ??0Rva0003F330@@QAE@XZ @0x0003F330 9B, vtable VA 0x00bc0990
class Rva0003F330
{
public:
	Rva0003F330();
	virtual ~Rva0003F330() {}
};

Rva0003F330::Rva0003F330()
{
}

// ??0TScorch@@QAE@XZ @0x000665B0 9B, vtable VA 0x00bc5cb4: slot 2 is the name
// getter 0x000665B9 returning "TScorch" and slot 3 the rowed TScorch::xfer.
// The terrain constructor 0x0006C9CF builds its 500 scorches with it.
class TScorch
{
public:
	TScorch();
	virtual ~TScorch() {}
};

TScorch::TScorch()
{
}

// ??0Rva0007829C@@QAE@XZ @0x0007829C 9B, vtable VA 0x00bc6730
class Rva0007829C
{
public:
	Rva0007829C();
	virtual ~Rva0007829C() {}
};

Rva0007829C::Rva0007829C()
{
}

// ??0Rva0007DFE9@@QAE@XZ @0x0007DFE9 9B, vtable VA 0x00bc6f24
class Rva0007DFE9
{
public:
	Rva0007DFE9();
	virtual ~Rva0007DFE9() {}
};

Rva0007DFE9::Rva0007DFE9()
{
}

// ??0Rva0007E04D@@QAE@XZ @0x0007E04D 9B, vtable VA 0x00bc6f2c
class Rva0007E04D
{
public:
	Rva0007E04D();
	virtual ~Rva0007E04D() {}
};

Rva0007E04D::Rva0007E04D()
{
}

// ??0Rva0007E6E4@@QAE@XZ @0x0007E6E4 9B, vtable VA 0x00bc6f5c
class Rva0007E6E4
{
public:
	Rva0007E6E4();
	virtual ~Rva0007E6E4() {}
};

Rva0007E6E4::Rva0007E6E4()
{
}

// ??0Rva0007E6ED@@QAE@XZ @0x0007E6ED 9B, vtable VA 0x00bc6f64
class Rva0007E6ED
{
public:
	Rva0007E6ED();
	virtual ~Rva0007E6ED() {}
};

Rva0007E6ED::Rva0007E6ED()
{
}

// ??0Rva000B2E0B@@QAE@XZ @0x000B2E0B 9B, vtable VA 0x00bc9b78
class Rva000B2E0B
{
public:
	Rva000B2E0B();
	virtual ~Rva000B2E0B() {}
};

Rva000B2E0B::Rva000B2E0B()
{
}

// ??0Rva000E1490@@QAE@XZ @0x000E1490 9B, vtable VA 0x00bce4d0
class Rva000E1490
{
public:
	Rva000E1490();
	virtual ~Rva000E1490() {}
};

Rva000E1490::Rva000E1490()
{
}

// ??0Rva000E1499@@QAE@XZ @0x000E1499 9B, vtable VA 0x00bce4d8
class Rva000E1499
{
public:
	Rva000E1499();
	virtual ~Rva000E1499() {}
};

Rva000E1499::Rva000E1499()
{
}

// ??0Rva000E14A2@@QAE@XZ @0x000E14A2 9B, vtable VA 0x00bce4e0
class Rva000E14A2
{
public:
	Rva000E14A2();
	virtual ~Rva000E14A2() {}
};

Rva000E14A2::Rva000E14A2()
{
}

// ??0Rva000E14AB@@QAE@XZ @0x000E14AB 9B, vtable VA 0x00bce4e8
class Rva000E14AB
{
public:
	Rva000E14AB();
	virtual ~Rva000E14AB() {}
};

Rva000E14AB::Rva000E14AB()
{
}

// ??0Rva000E14B4@@QAE@XZ @0x000E14B4 9B, vtable VA 0x00bce4f0
class Rva000E14B4
{
public:
	Rva000E14B4();
	virtual ~Rva000E14B4() {}
};

Rva000E14B4::Rva000E14B4()
{
}

// ??0Rva000F5ACB@@QAE@XZ @0x000F5ACB 9B, vtable VA 0x00bcf1c8
class Rva000F5ACB
{
public:
	Rva000F5ACB();
	virtual ~Rva000F5ACB() {}
};

Rva000F5ACB::Rva000F5ACB()
{
}

// ??0Rva000F5B56@@QAE@XZ @0x000F5B56 9B, vtable VA 0x00bcf1d8
class Rva000F5B56
{
public:
	Rva000F5B56();
	virtual ~Rva000F5B56() {}
};

Rva000F5B56::Rva000F5B56()
{
}

// ??0Rva000F6320@@QAE@XZ @0x000F6320 9B, vtable VA 0x00bcf1e8
class Rva000F6320
{
public:
	Rva000F6320();
	virtual ~Rva000F6320() {}
};

Rva000F6320::Rva000F6320()
{
}

// ??0Rva000F6490@@QAE@XZ @0x000F6490 9B, vtable VA 0x00bcf204
class Rva000F6490
{
public:
	Rva000F6490();
	virtual ~Rva000F6490() {}
};

Rva000F6490::Rva000F6490()
{
}

// ??0Rva000FDDAF@@QAE@XZ @0x000FDDAF 9B, vtable VA 0x00bcf440
class Rva000FDDAF
{
public:
	Rva000FDDAF();
	virtual ~Rva000FDDAF() {}
};

Rva000FDDAF::Rva000FDDAF()
{
}

// ??0Rva00117DB0@@QAE@XZ @0x00117DB0 9B, vtable VA 0x00bcfbf0
class Rva00117DB0
{
public:
	Rva00117DB0();
	virtual ~Rva00117DB0() {}
};

Rva00117DB0::Rva00117DB0()
{
}

// ??0Rva001F45A8@@QAE@XZ @0x001F45A8 9B, vtable VA 0x00be16e8
class Rva001F45A8
{
public:
	Rva001F45A8();
	virtual ~Rva001F45A8() {}
};

Rva001F45A8::Rva001F45A8()
{
}

// ??0Rva001F45B1@@QAE@XZ @0x001F45B1 9B, vtable VA 0x00be16f0
class Rva001F45B1
{
public:
	Rva001F45B1();
	virtual ~Rva001F45B1() {}
};

Rva001F45B1::Rva001F45B1()
{
}

// ??0Rva001F45BA@@QAE@XZ @0x001F45BA 9B, vtable VA 0x00be16f8
class Rva001F45BA
{
public:
	Rva001F45BA();
	virtual ~Rva001F45BA() {}
};

Rva001F45BA::Rva001F45BA()
{
}

// ??0Rva0020E346@@QAE@XZ @0x0020E346 9B, vtable VA 0x00c62a20
class Rva0020E346
{
public:
	Rva0020E346();
	virtual ~Rva0020E346() {}
};

Rva0020E346::Rva0020E346()
{
}

// ??0Rva0020E38B@@QAE@XZ @0x0020E38B 9B, vtable VA 0x00be4318
class Rva0020E38B
{
public:
	Rva0020E38B();
	virtual ~Rva0020E38B() {}
};

Rva0020E38B::Rva0020E38B()
{
}

// ??0Rva0020E394@@QAE@XZ @0x0020E394 9B, vtable VA 0x00be4320
class Rva0020E394
{
public:
	Rva0020E394();
	virtual ~Rva0020E394() {}
};

Rva0020E394::Rva0020E394()
{
}

// ??0Rva0020E6D6@@QAE@XZ @0x0020E6D6 9B, vtable VA 0x00be4334
class Rva0020E6D6
{
public:
	Rva0020E6D6();
	virtual ~Rva0020E6D6() {}
};

Rva0020E6D6::Rva0020E6D6()
{
}

// ??0Rva0020E86A@@QAE@XZ @0x0020E86A 9B, vtable VA 0x00be4340
class Rva0020E86A
{
public:
	Rva0020E86A();
	virtual ~Rva0020E86A() {}
};

Rva0020E86A::Rva0020E86A()
{
}

// ??0Rva002262DE@@QAE@XZ @0x002262DE 9B, vtable VA 0x00be714c
class Rva002262DE
{
public:
	Rva002262DE();
	virtual ~Rva002262DE() {}
};

Rva002262DE::Rva002262DE()
{
}

// ??0Rva00238E00@@QAE@XZ @0x00238E00 9B, vtable VA 0x00bed660
class Rva00238E00
{
public:
	Rva00238E00();
	virtual ~Rva00238E00() {}
};

Rva00238E00::Rva00238E00()
{
}

// ??0Rva00238E09@@QAE@XZ @0x00238E09 9B, vtable VA 0x00bed668
class Rva00238E09
{
public:
	Rva00238E09();
	virtual ~Rva00238E09() {}
};

Rva00238E09::Rva00238E09()
{
}

// ??0Rva00238E12@@QAE@XZ @0x00238E12 9B, vtable VA 0x00bed670
class Rva00238E12
{
public:
	Rva00238E12();
	virtual ~Rva00238E12() {}
};

Rva00238E12::Rva00238E12()
{
}

// ??0Rva0024A788@@QAE@XZ @0x0024A788 9B, vtable VA 0x00bee900
class Rva0024A788
{
public:
	Rva0024A788();
	virtual ~Rva0024A788() {}
};

Rva0024A788::Rva0024A788()
{
}

// ??0Rva002856C6@@QAE@XZ @0x002856C6 9B, vtable VA 0x00bfb698
class Rva002856C6
{
public:
	Rva002856C6();
	virtual ~Rva002856C6() {}
};

Rva002856C6::Rva002856C6()
{
}

// ??0Rva0028AB0D@@QAE@XZ @0x0028AB0D 9B, vtable VA 0x00bfbcbc
class Rva0028AB0D
{
public:
	Rva0028AB0D();
	virtual ~Rva0028AB0D() {}
};

Rva0028AB0D::Rva0028AB0D()
{
}

// ??0Rva002B30CA@@QAE@XZ @0x002B30CA 9B, vtable VA 0x00bfe058
class Rva002B30CA
{
public:
	Rva002B30CA();
	virtual ~Rva002B30CA() {}
};

Rva002B30CA::Rva002B30CA()
{
}

// ??0Rva003889DF@@QAE@XZ @0x003889DF 9B, vtable VA 0x00c1980c
class Rva003889DF
{
public:
	Rva003889DF();
	virtual ~Rva003889DF() {}
};

Rva003889DF::Rva003889DF()
{
}

// ??0Rva003F7BBC@@QAE@XZ @0x003F7BBC 9B, vtable VA 0x00c37298
class Rva003F7BBC
{
public:
	Rva003F7BBC();
	virtual ~Rva003F7BBC() {}
};

Rva003F7BBC::Rva003F7BBC()
{
}

// ??0Rva003FDD38@@QAE@XZ @0x003FDD38 9B, vtable VA 0x00c37e18
class Rva003FDD38
{
public:
	Rva003FDD38();
	virtual ~Rva003FDD38() {}
};

Rva003FDD38::Rva003FDD38()
{
}

// ??0Rva003FE1BF@@QAE@XZ @0x003FE1BF 9B, vtable VA 0x00c37e30
class Rva003FE1BF
{
public:
	Rva003FE1BF();
	virtual ~Rva003FE1BF() {}
};

Rva003FE1BF::Rva003FE1BF()
{
}

// ??0Rva0040CFFF@@QAE@XZ @0x0040CFFF 9B, vtable VA 0x00c394c8
struct Rva0040E0C5Arg;

class Rva0040CFFF
{
public:
	Rva0040CFFF();
	virtual bool rva0040E0C5(Rva0040E0C5Arg *arg);
	~Rva0040CFFF() {}
};

// Select-any like Rva0040D43FRun.cpp's identical copy (a strong definition
// would duplicate it at link time); the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva0040CFFF::Rva0040CFFF()
{
}

// ?bfmeAnchorRva0040CFFF absent-from-retail
void *bfmeAnchorRva0040CFFF(void *where)
{
	return ::new (where) Rva0040CFFF();
}

// ??0Rva0045954A@@QAE@XZ @0x0045954A 9B, vtable VA 0x00be2b78
class Rva0045954A
{
public:
	Rva0045954A();
	virtual ~Rva0045954A() {}
};

Rva0045954A::Rva0045954A()
{
}

// ??0Rva004598C3@@QAE@XZ @0x004598C3 9B, vtable VA 0x00c4ef80
class Rva004598C3
{
public:
	Rva004598C3();
	virtual ~Rva004598C3() {}
};

Rva004598C3::Rva004598C3()
{
}

// ??0Rva0045B4B7@@QAE@XZ @0x0045B4B7 9B, vtable VA 0x00c40818
class Rva0045B4B7
{
public:
	Rva0045B4B7();
	virtual ~Rva0045B4B7() {}
};

Rva0045B4B7::Rva0045B4B7()
{
}

// ??0Rva0046249E@@QAE@XZ @0x0046249E 9B, vtable VA 0x00c430b4
class Rva0046249E
{
public:
	Rva0046249E();
	virtual ~Rva0046249E() {}
};

Rva0046249E::Rva0046249E()
{
}

// ??0Rva004626A6@@QAE@XZ @0x004626A6 9B, vtable VA 0x00c430e8
class Rva004626A6
{
public:
	Rva004626A6();
	virtual ~Rva004626A6() {}
};

Rva004626A6::Rva004626A6()
{
}

// ??0Rva00468A63@@QAE@XZ @0x00468A63 9B, vtable VA 0x00c4489c
class Rva00468A63
{
public:
	Rva00468A63();
	virtual ~Rva00468A63() {}
};

Rva00468A63::Rva00468A63()
{
}

// ??0Rva00468AA3@@QAE@XZ @0x00468AA3 9B, vtable VA 0x00c448a8
class Rva00468AA3
{
public:
	Rva00468AA3();
	virtual ~Rva00468AA3() {}
};

Rva00468AA3::Rva00468AA3()
{
}

// ??0Rva00468AE3@@QAE@XZ @0x00468AE3 9B, vtable VA 0x00c448b8
class Rva00468AE3
{
public:
	Rva00468AE3();
	virtual ~Rva00468AE3() {}
};

Rva00468AE3::Rva00468AE3()
{
}

// ??0Rva00488AC0@@QAE@XZ @0x00488AC0 9B, vtable VA 0x00c4b788
class Rva00488AC0
{
public:
	Rva00488AC0();
	virtual ~Rva00488AC0() {}
};

Rva00488AC0::Rva00488AC0()
{
}

// ??0Rva00492FB9@@QAE@XZ @0x00492FB9 9B, vtable VA 0x00c4e2b0
class Rva00492FB9
{
public:
	Rva00492FB9();
	virtual ~Rva00492FB9() {}
};

Rva00492FB9::Rva00492FB9()
{
}

// ??0Rva0049A642@@QAE@XZ @0x0049A642 9B, vtable VA 0x00c52ee8
class Rva0049A642
{
public:
	Rva0049A642();
	virtual ~Rva0049A642() {}
};

Rva0049A642::Rva0049A642()
{
}

// ??0Rva004BD75A@@QAE@XZ @0x004BD75A 9B, vtable VA 0x00c5ab68
class Rva004BD75A
{
public:
	Rva004BD75A();
	virtual ~Rva004BD75A() {}
};

Rva004BD75A::Rva004BD75A()
{
}

// ??0Rva004BDC1C@@QAE@XZ @0x004BDC1C 9B, vtable VA 0x00c5aeb0
class Rva004BDC1C
{
public:
	Rva004BDC1C();
	virtual ~Rva004BDC1C() {}
};

Rva004BDC1C::Rva004BDC1C()
{
}

// ??0Rva004BDCA3@@QAE@XZ @0x004BDCA3 9B, vtable VA 0x00c5aeb8
class Rva004BDCA3
{
public:
	Rva004BDCA3();
	virtual ~Rva004BDCA3() {}
};

Rva004BDCA3::Rva004BDCA3()
{
}

// ??0Rva004C9994@@QAE@XZ @0x004C9994 9B, vtable VA 0x00c5ebec
class Rva004C9994
{
public:
	Rva004C9994();
	virtual ~Rva004C9994() {}
};

Rva004C9994::Rva004C9994()
{
}

// ??0Rva004C9DC0@@QAE@XZ @0x004C9DC0 9B, vtable VA 0x00c6fffc
class Rva004C9DC0
{
public:
	Rva004C9DC0();
	virtual ~Rva004C9DC0() {}
};

Rva004C9DC0::Rva004C9DC0()
{
}

// ??0Rva004CE267@@QAE@XZ @0x004CE267 9B, vtable VA 0x00c5fe1c
class Rva004CE267
{
public:
	Rva004CE267();
	virtual ~Rva004CE267() {}
};

Rva004CE267::Rva004CE267()
{
}

// ??0Rva004FF334@@QAE@XZ @0x004FF334 9B, vtable VA 0x00c63b40
class Rva004FF334
{
public:
	Rva004FF334();
	virtual ~Rva004FF334() {}
};

Rva004FF334::Rva004FF334()
{
}

// ??0Rva0052B106@@QAE@XZ @0x0052B106 9B, vtable VA 0x00c685c8
class Rva0052B106
{
public:
	Rva0052B106();
	virtual ~Rva0052B106() {}
};

Rva0052B106::Rva0052B106()
{
}

// ??0Rva0056775B@@QAE@XZ @0x0056775B 9B, vtable VA 0x00c6ce84
class Rva0056775B
{
public:
	Rva0056775B();
	virtual ~Rva0056775B() {}
};

Rva0056775B::Rva0056775B()
{
}

// ??0Rva0056778A@@QAE@XZ @0x0056778A 9B, vtable VA 0x00c6ceb4
class Rva0056778A
{
public:
	Rva0056778A();
	virtual ~Rva0056778A() {}
};

Rva0056778A::Rva0056778A()
{
}

// ??0Rva0057434D@@QAE@XZ @0x0057434D 9B, vtable VA 0x00c6e360
class Rva0057434D
{
public:
	Rva0057434D();
	virtual ~Rva0057434D() {}
};

Rva0057434D::Rva0057434D()
{
}

// ??0Rva005743AE@@QAE@XZ @0x005743AE 9B, vtable VA 0x00c6e350
class Rva005743AE
{
public:
	Rva005743AE();
	virtual ~Rva005743AE() {}
};

Rva005743AE::Rva005743AE()
{
}

// ??0Rva005748A4@@QAE@XZ @0x005748A4 9B, vtable VA 0x00c6e430
class Rva005748A4
{
public:
	Rva005748A4();
	virtual ~Rva005748A4() {}
};

Rva005748A4::Rva005748A4()
{
}

// ??0Rva0057A3A9@@QAE@XZ @0x0057A3A9 9B, vtable VA 0x00c6ee20
class Rva0057A3A9
{
public:
	Rva0057A3A9();
	virtual ~Rva0057A3A9() {}
};

Rva0057A3A9::Rva0057A3A9()
{
}

// ??0Rva0059667D@@QAE@XZ @0x0059667D 9B, vtable VA 0x00c70a5c
class Rva0059667D
{
public:
	Rva0059667D();
	virtual ~Rva0059667D() {}
};

Rva0059667D::Rva0059667D()
{
}

// ??0Rva0059EB66@@QAE@XZ @0x0059EB66 9B, vtable VA 0x00c711bc
class Rva0059EB66
{
public:
	Rva0059EB66();
	virtual ~Rva0059EB66() {}
};

Rva0059EB66::Rva0059EB66()
{
}

// ??0Rva005CC93A@@QAE@XZ @0x005CC93A 9B, vtable VA 0x00c77e7c
class Rva005CC93A
{
public:
	Rva005CC93A();
	virtual ~Rva005CC93A() {}
};

Rva005CC93A::Rva005CC93A()
{
}

// ??0Rva005CFB8A@@QAE@XZ @0x005CFB8A 9B, vtable VA 0x00c75284
class Rva005CFB8A
{
public:
	Rva005CFB8A();
	virtual ~Rva005CFB8A() {}
};

Rva005CFB8A::Rva005CFB8A()
{
}

// ??0Rva005D248C@@QAE@XZ @0x005D248C 9B, vtable VA 0x00c078dc
class Rva005D248C
{
public:
	Rva005D248C();
	virtual ~Rva005D248C() {}
};

Rva005D248C::Rva005D248C()
{
}

// ??0Rva005E3994@@QAE@XZ @0x005E3994 9B, vtable VA 0x00c77be8
class Rva005E3994
{
public:
	Rva005E3994();
	virtual ~Rva005E3994() {}
};

Rva005E3994::Rva005E3994()
{
}

// ??0Rva005EEE6B@@QAE@XZ @0x005EEE6B 9B, vtable VA 0x00bfbc9c
class Rva005EEE6B
{
public:
	Rva005EEE6B();
	virtual ~Rva005EEE6B() {}
};

Rva005EEE6B::Rva005EEE6B()
{
}

// ??0Rva006560B0@@QAE@XZ @0x006560B0 9B, vtable VA 0x00ce0fb8
class Rva006560B0
{
public:
	Rva006560B0();
	virtual ~Rva006560B0() {}
};

Rva006560B0::Rva006560B0()
{
}

// ??0Rva006562A0@@QAE@XZ @0x006562A0 9B, vtable VA 0x00ce0fc8
class Rva006562A0
{
public:
	Rva006562A0();
	virtual ~Rva006562A0() {}
};

Rva006562A0::Rva006562A0()
{
}

// ??0Rva006586C0@@QAE@XZ @0x006586C0 9B, vtable VA 0x00c078dc
class Rva006586C0
{
public:
	Rva006586C0();
	virtual ~Rva006586C0() {}
};

Rva006586C0::Rva006586C0()
{
}

// ??0Rva0065CE40@@QAE@XZ @0x0065CE40 9B, vtable VA 0x00c40818
class Rva0065CE40
{
public:
	Rva0065CE40();
	virtual ~Rva0065CE40() {}
};

Rva0065CE40::Rva0065CE40()
{
}

// ??0Rva0065D800@@QAE@XZ @0x0065D800 9B, vtable VA 0x00ce1e30
class Rva0065D800
{
public:
	Rva0065D800();
	virtual ~Rva0065D800() {}
};

Rva0065D800::Rva0065D800()
{
}

// ??0Rva0065E8D0@@QAE@XZ @0x0065E8D0 9B, vtable VA 0x00ce2368
class Rva0065E8D0
{
public:
	Rva0065E8D0();
	virtual ~Rva0065E8D0() {}
};

Rva0065E8D0::Rva0065E8D0()
{
}

// ??0Rva0065F130@@QAE@XZ @0x0065F130 9B, vtable VA 0x00ce24a0
class Rva0065F130
{
public:
	Rva0065F130();
	virtual ~Rva0065F130() {}
};

Rva0065F130::Rva0065F130()
{
}

// ??0Rva0065FA20@@QAE@XZ @0x0065FA20 9B, vtable VA 0x00ce2730
class Rva0065FA20
{
public:
	Rva0065FA20();
	virtual ~Rva0065FA20() {}
};

Rva0065FA20::Rva0065FA20()
{
}

// ??0Rva006602B0@@QAE@XZ @0x006602B0 9B, vtable VA 0x00ce2870
class Rva006602B0
{
public:
	Rva006602B0();
	virtual ~Rva006602B0() {}
};

Rva006602B0::Rva006602B0()
{
}

// ??0Rva00660C90@@QAE@XZ @0x00660C90 9B, vtable VA 0x00ce2a6c
class Rva00660C90
{
public:
	Rva00660C90();
	virtual ~Rva00660C90() {}
};

Rva00660C90::Rva00660C90()
{
}

// ??0Rva00661E90@@QAE@XZ @0x00661E90 9B, vtable VA 0x00c6fffc
class Rva00661E90
{
public:
	Rva00661E90();
	virtual ~Rva00661E90() {}
};

Rva00661E90::Rva00661E90()
{
}

// ??0Rva00664D90@@QAE@XZ @0x00664D90 9B, vtable VA 0x00c1c780
class Rva00664D90
{
public:
	Rva00664D90();
	virtual ~Rva00664D90() {}
};

Rva00664D90::Rva00664D90()
{
}

// ??0Rva006655D0@@QAE@XZ @0x006655D0 9B, vtable VA 0x00ce3194
class Rva006655D0
{
public:
	Rva006655D0();
	virtual ~Rva006655D0() {}
};

Rva006655D0::Rva006655D0()
{
}

// ??0Rva006656D0@@QAE@XZ @0x006656D0 9B, vtable VA 0x00c4ef80
class Rva006656D0
{
public:
	Rva006656D0();
	virtual ~Rva006656D0() {}
};

Rva006656D0::Rva006656D0()
{
}

// ??0Rva00666BB0@@QAE@XZ @0x00666BB0 9B, vtable VA 0x00ce33d4
class Rva00666BB0
{
public:
	Rva00666BB0();
	virtual ~Rva00666BB0() {}
};

Rva00666BB0::Rva00666BB0()
{
}

// ??0Rva006672F0@@QAE@XZ @0x006672F0 9B, vtable VA 0x00ce34d0
class Rva006672F0
{
public:
	Rva006672F0();
	virtual ~Rva006672F0() {}
};

Rva006672F0::Rva006672F0()
{
}

// ??0Rva00668610@@QAE@XZ @0x00668610 9B, vtable VA 0x00ce36d8
class Rva00668610
{
public:
	Rva00668610();
	virtual ~Rva00668610() {}
};

Rva00668610::Rva00668610()
{
}

// ??0Rva0023DB34@@QAE@XZ @0x0023DB34 20B, vtable VA 0xbedaa8. Slot 0 of that
// vtable is the rowed 45B member 0x00306C15 (not a destructor), slots 1..3
// the rowed 0x00306C42/0x00306C49/0x00306C58 bodies; the same vtable store
// is inlined at 0x00240022 for a member at +0x10. Owner unresolved.
class Rva0023DB34
{
public:
	Rva0023DB34();
	virtual int slot00(void *p, int n);
	virtual int slot04();
	virtual bool slot08(int n);
	virtual bool slot0C();
private:
	void *m_04;
	void *m_08;
	void *m_0C;
};

Rva0023DB34::Rva0023DB34()
	: m_04(0), m_08(0), m_0C(0)
{
}

// ??0Rva002AA39B@@QAE@XZ @0x002AA39B 20B, vtable VA 0xbfdc48. That vtable is
// Energy's by its slots (slot 2 the "Energy" name getter 0x002AA3AF directly
// after this body, slot 3 the rowed Energy::xfer 0x004DF290), and the Player
// constructor inlines the same store at 0x002B0FE1. The ledger's
// ??0Energy@@QAE@XZ row sits elsewhere (0x00674870), so this body keeps an
// address-derived name until that is reconciled.
class Rva002AA39B
{
public:
	Rva002AA39B();
	virtual ~Rva002AA39B() {}
private:
	void *m_04;
	void *m_08;
	void *m_0C;
};

Rva002AA39B::Rva002AA39B()
	: m_04(0), m_08(0), m_0C(0)
{
}
