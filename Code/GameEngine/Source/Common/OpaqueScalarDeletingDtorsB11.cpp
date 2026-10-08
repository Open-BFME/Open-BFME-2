// cl: /O1 /DNDEBUG /MD
//
// Opaque scalar deleting destructors, batch B11: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner (vtable bounds taken from the constructor vptr stores
// in .text; slots shared by three or more vtables are not counted as owners).
// Each destructor is declared, not defined, so the call resolves to its pin
// in reverse/symbols.csv; the dummy tag constructors (no retail counterpart)
// only make this TU emit each vtable and with it the deleting destructor.
// Owner identities are not recovered, and these declarations model no layout
// (docs/reconstruction/deleting-destructor-identity-audit.md).
//
//   wrapper     dtor        vtable#slot
//   0x00488D40  0x00488D5C  0x00C4B5C8#0
//   0x004AC021  0x004ABFD9  0x00C549F8#0
//   0x004AD538  0x004C6CC1  0x00C5F778#0
//   0x004C182F  0x004C1B7B  0x00C5BC48#0
//   0x004E0E5C  0x004E0D67  0x00C61618#0
//   0x004E4750  0x004E4655  0x00C62260#0
//   0x004EAB6E  0x004EA3B8  0x00C628A0#2
//   0x004EB778  0x004EB5E9  0x00C62928#0
//   0x004EF28F  0x004EED02  0x00C62AC4#0
//   0x004FB1FD  0x004FB130  0x00C63438#0
//   0x004FBD1E  0x004FBCBE  0x00C634E4#0
//   0x004FC563  0x004FC4D1  0x00C63530#0
//   0x004FD85E  0x004FD1BC  0x00C63564#0
//   0x004FF2D2  0x004FF2C0  0x00C63B34#0
//   0x005105BB  0x005105D7  0x00C65604#0
//   0x0051062D  0x0050FDDC  0x00C655BC#0
//   0x00510649  0x00510665  0x00C655C4#0
//   0x00511031  0x00510D0C  0x00C6568C#0
//   0x0051265C  0x005125ED  0x00C659A0#0
//   0x0051342D  0x00512E49  0x00C65B6C#0

extern "C" const void *const vtbl_00C65518[];  // ??_7Rva0050FAEC@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C65518=??_7Rva0050FAEC@@6B@")

class Object;
class StateMachine;

class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitionsFirst;
	void *m_transitionsLast;
	StateMachine *m_machine;
	bool m_tail1C;
	char m_pad1D[3];
};

class StateMachine
{
public:
	char m_pad00[0x14];
	Object *volatile m_owner;
	Object *getOwner() { return m_owner; }
};

class OpaqueCallResult;

class OpaqueOwnerInterface
{
public:
#define OWNER_SLOT(n) virtual void vslot##n() = 0;
OWNER_SLOT(00) OWNER_SLOT(01) OWNER_SLOT(02) OWNER_SLOT(03) OWNER_SLOT(04) OWNER_SLOT(05) OWNER_SLOT(06) OWNER_SLOT(07) OWNER_SLOT(08) OWNER_SLOT(09)
OWNER_SLOT(10) OWNER_SLOT(11) OWNER_SLOT(12) OWNER_SLOT(13) OWNER_SLOT(14) OWNER_SLOT(15) OWNER_SLOT(16) OWNER_SLOT(17) OWNER_SLOT(18) OWNER_SLOT(19)
OWNER_SLOT(20) OWNER_SLOT(21) OWNER_SLOT(22) OWNER_SLOT(23) OWNER_SLOT(24) OWNER_SLOT(25) OWNER_SLOT(26) OWNER_SLOT(27) OWNER_SLOT(28) OWNER_SLOT(29)
OWNER_SLOT(30) OWNER_SLOT(31) OWNER_SLOT(32) OWNER_SLOT(33) OWNER_SLOT(34) OWNER_SLOT(35) OWNER_SLOT(36) OWNER_SLOT(37) OWNER_SLOT(38) OWNER_SLOT(39)
OWNER_SLOT(40) OWNER_SLOT(41) OWNER_SLOT(42) OWNER_SLOT(43) OWNER_SLOT(44) OWNER_SLOT(45) OWNER_SLOT(46) OWNER_SLOT(47) OWNER_SLOT(48) OWNER_SLOT(49)
OWNER_SLOT(50) OWNER_SLOT(51) OWNER_SLOT(52) OWNER_SLOT(53) OWNER_SLOT(54) OWNER_SLOT(55) OWNER_SLOT(56) OWNER_SLOT(57) OWNER_SLOT(58) OWNER_SLOT(59)
OWNER_SLOT(60) OWNER_SLOT(61) OWNER_SLOT(62) OWNER_SLOT(63) OWNER_SLOT(64) OWNER_SLOT(65) OWNER_SLOT(66) OWNER_SLOT(67) OWNER_SLOT(68) OWNER_SLOT(69)
OWNER_SLOT(70) OWNER_SLOT(71) OWNER_SLOT(72) OWNER_SLOT(73) OWNER_SLOT(74) OWNER_SLOT(75) OWNER_SLOT(76) OWNER_SLOT(77) OWNER_SLOT(78) OWNER_SLOT(79)
OWNER_SLOT(80) OWNER_SLOT(81) OWNER_SLOT(82) OWNER_SLOT(83) OWNER_SLOT(84) OWNER_SLOT(85) OWNER_SLOT(86) OWNER_SLOT(87) OWNER_SLOT(88) OWNER_SLOT(89)
OWNER_SLOT(90) OWNER_SLOT(91) OWNER_SLOT(92)
#undef OWNER_SLOT
	virtual OpaqueCallResult *vslot93() = 0;
};

class OpaqueCallResult
{
public:
#define RESULT_SLOT(n) virtual void vslot##n() = 0;
RESULT_SLOT(00) RESULT_SLOT(01) RESULT_SLOT(02) RESULT_SLOT(03) RESULT_SLOT(04)
RESULT_SLOT(05) RESULT_SLOT(06) RESULT_SLOT(07) RESULT_SLOT(08) RESULT_SLOT(09)
#undef RESULT_SLOT
	virtual void vslot10(int value) = 0;
};

class Object
{
public:
	virtual ~Object();
	char m_pad04[0x258 - 4];
	OpaqueOwnerInterface *m_258;
};

extern void *__cdecl operator new(unsigned int size);

class Rva004885DE
{
public:
	virtual ~Rva004885DE();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	Rva004885DE(Object *owner, int value);
	char m_pad04[0x38];
	int m_3C;
};

struct EmitVtableTag;

class Rva00488D5C : public State
{
public:
	Rva00488D5C(EmitVtableTag *);
	Rva00488D5C(StateMachine *machine, int value);
public:
	virtual ~Rva00488D5C();
	virtual void vslot01();
	virtual void vslot02();
	virtual void vslot03();
	virtual int rva00488906();
	volatile int m_value;
	Rva004885DE *volatile m_child;
};

// ?<Rva00488D5C::Rva00488D5C> absent-from-retail
Rva00488D5C::Rva00488D5C(EmitVtableTag *) : State(0, 0)
{
}

// ??0Rva00488D5C@@QAE@PAVStateMachine@@H@Z, retail 0x00488883 (117 bytes).
// The state hash and State::m_machine are read from the target constructor;
// the vptr value is its raw store. Its allocation at +0x20 and owner load
// through StateMachine+0x14 match the child StateMachine ctor at 0x004885DE.
// The call through vtable slot 7 follows the child constructor on both arms.
// ?<Rva00488D5C::Rva00488D5C> present-unmatched
Rva00488D5C::Rva00488D5C(StateMachine *machine, int value)
	: State(machine, 0x473A607Fu)
{
	m_value = value;
	Rva004885DE *child = new Rva004885DE(m_machine->getOwner(), value);
	m_child = child;
	child->v07();
}

// ?rva00488906@Rva00488D5C@@UAEHXZ, retail 0x00488906 (54 bytes).
// Slot 4 of the vtable installed by this class's constructor; owner +0x258
// supplies the slot-93 result interface, then the retained child handles the
// final slot-6 call. Names for both interfaces remain address-derived.
// ?<Rva00488D5C::rva00488906> present-unmatched
int Rva00488D5C::rva00488906()
{
	OpaqueOwnerInterface *object = m_machine->getOwner()->m_258;
	if (!object)
		return -2;
	OpaqueCallResult *result = object->vslot93();
	result->vslot10(m_value);
	m_child->v06();
	return 0;
}

class Rva004ABFD9
{
public:
	Rva004ABFD9(EmitVtableTag *);
public:
	virtual ~Rva004ABFD9();
};

// ?<Rva004ABFD9::Rva004ABFD9> absent-from-retail
Rva004ABFD9::Rva004ABFD9(EmitVtableTag *)
{
}

class Rva004C6CC1
{
public:
	Rva004C6CC1(EmitVtableTag *);
public:
	virtual ~Rva004C6CC1();
};

// ?<Rva004C6CC1::Rva004C6CC1> absent-from-retail
Rva004C6CC1::Rva004C6CC1(EmitVtableTag *)
{
}

class Rva004C1B7B
{
public:
	Rva004C1B7B(EmitVtableTag *);
public:
	virtual ~Rva004C1B7B();
};

// ?<Rva004C1B7B::Rva004C1B7B> absent-from-retail
Rva004C1B7B::Rva004C1B7B(EmitVtableTag *)
{
}

class Rva004E0D67
{
public:
	Rva004E0D67(EmitVtableTag *);
public:
	virtual ~Rva004E0D67();
};

// ?<Rva004E0D67::Rva004E0D67> absent-from-retail
Rva004E0D67::Rva004E0D67(EmitVtableTag *)
{
}

class Rva004E4655
{
public:
	Rva004E4655(EmitVtableTag *);
public:
	virtual ~Rva004E4655();
};

// ?<Rva004E4655::Rva004E4655> absent-from-retail
Rva004E4655::Rva004E4655(EmitVtableTag *)
{
}

class Rva004EA3B8
{
public:
	Rva004EA3B8(EmitVtableTag *);
public:
	virtual ~Rva004EA3B8();
};

// ?<Rva004EA3B8::Rva004EA3B8> absent-from-retail
Rva004EA3B8::Rva004EA3B8(EmitVtableTag *)
{
}

class Rva004EB5E9
{
public:
	Rva004EB5E9(EmitVtableTag *);
public:
	virtual ~Rva004EB5E9();
};

// ?<Rva004EB5E9::Rva004EB5E9> absent-from-retail
Rva004EB5E9::Rva004EB5E9(EmitVtableTag *)
{
}

class Rva004EED02
{
public:
	Rva004EED02(EmitVtableTag *);
public:
	virtual ~Rva004EED02();
};

// ?<Rva004EED02::Rva004EED02> absent-from-retail
Rva004EED02::Rva004EED02(EmitVtableTag *)
{
}

class Rva004FB130
{
public:
	Rva004FB130(EmitVtableTag *);
public:
	virtual ~Rva004FB130();
};

// ?<Rva004FB130::Rva004FB130> absent-from-retail
Rva004FB130::Rva004FB130(EmitVtableTag *)
{
}

class Rva004FBCBE
{
public:
	Rva004FBCBE(EmitVtableTag *);
public:
	virtual ~Rva004FBCBE();
};

// ?<Rva004FBCBE::Rva004FBCBE> absent-from-retail
Rva004FBCBE::Rva004FBCBE(EmitVtableTag *)
{
}

class Rva004FC4D1
{
public:
	Rva004FC4D1(EmitVtableTag *);
public:
	virtual ~Rva004FC4D1();
};

// ?<Rva004FC4D1::Rva004FC4D1> absent-from-retail
Rva004FC4D1::Rva004FC4D1(EmitVtableTag *)
{
}

class Rva004FD1BC
{
public:
	Rva004FD1BC(EmitVtableTag *);
public:
	virtual ~Rva004FD1BC();
};

// ?<Rva004FD1BC::Rva004FD1BC> absent-from-retail
Rva004FD1BC::Rva004FD1BC(EmitVtableTag *)
{
}

class Rva004FF2C0
{
public:
	Rva004FF2C0(EmitVtableTag *);
public:
	virtual ~Rva004FF2C0();
};

// ?<Rva004FF2C0::Rva004FF2C0> absent-from-retail
Rva004FF2C0::Rva004FF2C0(EmitVtableTag *)
{
}

class Rva005105D7
{
public:
	Rva005105D7(EmitVtableTag *);
public:
	virtual ~Rva005105D7();
};

// ?<Rva005105D7::Rva005105D7> absent-from-retail
Rva005105D7::Rva005105D7(EmitVtableTag *)
{
}

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"


__forceinline const char *GetStr0050FDDC(const AsciiString &s)
{
	char *t = *(char **)(const void *)&s;
	return t ? t + 8 : "";
}

class Rva000B3F84Pair
{
public:
	const char *m_ptr;
	int m_len;
};

struct AsciiStringRef
{
	const AsciiString *m_string;
};

struct AsciiStringPlusText : AsciiStringRef
{
	operator AsciiString();
	Rva000B3F84Pair m_right;
};

struct AsciiStringPlusText __cdecl operator+(const AsciiString &lhs, const char *rhs);

void _bfme_closeAptScreen(const AsciiString &name);

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
};

// Source-only bridge for the target's observed base-vtable transition; this
// helper name does not assert an original intermediate class identity. Retail
// stores VA 0x00C65518 (RVA 0x00865518) immediately before the pinned base dtor.
class Rva0050FDDCRestore : public Rva005248D0
{
public:
	__forceinline virtual ~Rva0050FDDCRestore() { *(unsigned int *)this = ((unsigned int)vtbl_00C65518); }
};

class Rva0050FDDC : public Rva0050FDDCRestore
{
public:
	Rva0050FDDC(EmitVtableTag *);
	virtual ~Rva0050FDDC();
private:
	char m_pad04[0x5c - 4];
	unsigned int m_5c;
	AsciiString m_60;
};

// ?<Rva0050FDDC::Rva0050FDDC> absent-from-retail
Rva0050FDDC::Rva0050FDDC(EmitVtableTag *)
{
}

// Target 0x0050FDDC: formats the level/name screen identifiers, releases the
// temporary and member strings, then transitions through vtable RVA 0x00865518
// before calling the byte-pinned base destructor at 0x005248D0.
// Original class and complete parent layout remain unproven.
Rva0050FDDC::~Rva0050FDDC()
{
	AsciiString tmp;
	tmp.format("_level%u.%s", m_5c, GetStr0050FDDC(m_60));
	_bfme_closeAptScreen(tmp + "_InitTextEntry");
	_bfme_closeAptScreen(tmp + "_InitSlider");
}

class Rva00510665
{
public:
	Rva00510665(EmitVtableTag *);
public:
	virtual ~Rva00510665();
};

// ?<Rva00510665::Rva00510665> absent-from-retail
Rva00510665::Rva00510665(EmitVtableTag *)
{
}

class Rva00510D0C
{
public:
	Rva00510D0C(EmitVtableTag *);
public:
	virtual ~Rva00510D0C();
};

// ?<Rva00510D0C::Rva00510D0C> absent-from-retail
Rva00510D0C::Rva00510D0C(EmitVtableTag *)
{
}

class Rva005125ED
{
public:
	Rva005125ED(EmitVtableTag *);
public:
	virtual ~Rva005125ED();
};

// ?<Rva005125ED::Rva005125ED> absent-from-retail
Rva005125ED::Rva005125ED(EmitVtableTag *)
{
}

class Rva00512E49
{
public:
	Rva00512E49(EmitVtableTag *);
public:
	virtual ~Rva00512E49();
};

// ?<Rva00512E49::Rva00512E49> absent-from-retail
Rva00512E49::Rva00512E49(EmitVtableTag *)
{
}
