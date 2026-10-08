// cl: /DNDEBUG /MD /EHsc
//
// Destructors of the 59-byte member-then-base shape: store the class vptr,
// destroy one member at a fixed offset (EH state 0), then call the base
// destructor; the same shape as the rowed ??1Rva0098477@@UAE@XZ
// (SubsystemDerivedDtors.cpp) and ??1Rva001E4DB0@@UAE@XZ.  Each class is
// named after its destructor address; the base and member destructors are
// declared, not defined, and resolve to their ledger rows or address-named
// pins at the addresses the retail calls prove.  Layout is modelled only as
// far as the member offset; identities are not recovered.
//
//   dtor        vptr        member      base
//   0x00413A24  0x00BE7660  +0xC   0x0022DC9B  0x001B4E74
//   0x00414166  0x00BE7698  +0xC   0x0022DCDA  0x001B4E74
//   0x005685EE  0x00C6CF74  +0xC   0x0056850D  0x005C3549
//   0x00575D45  0x00C6E664  +0x8   0x00577010  0x00575395
//   0x00576B5E  0x00C6E7D4  +0x8   0x00577010  0x00575395
//   0x005772BF  0x00C6E960  +0x8   0x00577010  0x00575395
//   0x00577FA7  0x00C6EA28  +0x44  0x00577EB2  0x005C6C7B
//   0x005CF7BF  0x00C75254  +0x8   0x005CF363  0x005E6810
//   0x005E1FBC  0x00C77A64  +0xC   0x005E1E81  0x004E84A4
//   0x005E362F  0x00C77BD0  +0xC   0x005E35DA  0x004E84A4
//   0x005F64F5  0x00C796D0  +0x8   0x005F64DB  0x005F38CA
//   0x005F86C3  0x00C79CBC  +0x20  0x005F85E1  0x00577936
//   0x005FB1AD  0x00C79EDC  +0x20  0x005FAFB2  0x006003FC

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
};

class Rva0022DC9B
{
public:
	~Rva0022DC9B();

private:
	void *m_value;
};

class Rva0022DCDA
{
public:
	~Rva0022DCDA();

private:
	void *m_value;
};

class Rva005C3549
{
public:
	virtual ~Rva005C3549();
};

class Rva0056850D
{
public:
	~Rva0056850D();

private:
	void *m_value;
};

class Rva00575395
{
public:
	virtual ~Rva00575395();
};

class Rva00577010
{
public:
	~Rva00577010();

private:
	void *m_value;
};

class Rva005C6C7B
{
public:
	virtual ~Rva005C6C7B();
};

class Rva00577EB2
{
public:
	~Rva00577EB2();

private:
	void *m_value;
};

class Rva005E6810
{
public:
	virtual ~Rva005E6810();
};

class Rva005CF363
{
public:
	~Rva005CF363();

private:
	void *m_value;
};

class Rva00539926Base
{
public:
	virtual ~Rva00539926Base();
};

class Rva005E1E81
{
public:
	~Rva005E1E81();

private:
	void *m_value;
};

class Rva005E35DA
{
public:
	~Rva005E35DA();

private:
	void *m_value;
};

class Rva005F38CA
{
public:
	virtual ~Rva005F38CA();
};

class Rva005F64DB
{
public:
	~Rva005F64DB();

private:
	void *m_value;
};

class Rva00577936
{
public:
	virtual ~Rva00577936();
};

class Rva005F85E1
{
public:
	~Rva005F85E1();

private:
	void *m_value;
};

class Object;

// The base's rowed slot 1 (0x006003AD) and the one body its slots 2-4 fold
// to (0x006003A5).
class Rva006003FC
{
public:
	virtual ~Rva006003FC();
	void rva006003AD();
	void rva006003A5(Object *value);
};

class Rva005FAFB2
{
public:
	~Rva005FAFB2();

	void *m_value;
};



class Rva00413A24 : public GameEngineDeletingBase
{
public:
	virtual ~Rva00413A24();

private:
	char m_unmodelled_04[0x8];
	Rva0022DC9B m_member;	// +0xC
};

Rva00413A24::~Rva00413A24()
{
}

class Rva00414166 : public GameEngineDeletingBase
{
public:
	virtual ~Rva00414166();

private:
	char m_unmodelled_04[0x8];
	Rva0022DCDA m_member;	// +0xC
};

Rva00414166::~Rva00414166()
{
}

class Rva005685EE : public Rva005C3549
{
public:
	virtual ~Rva005685EE();

private:
	char m_unmodelled_04[0x8];
	Rva0056850D m_member;	// +0xC
};

Rva005685EE::~Rva005685EE()
{
}

class Rva00575D45 : public Rva00575395
{
public:
	virtual ~Rva00575D45();
	int rva00575D88(const void *buf, int len);

private:
	char m_unmodelled_04[0x4];
	Rva00577010 m_member;	// +0x8
};

Rva00575D45::~Rva00575D45()
{
}

class Rva00576B5E : public Rva00575395
{
public:
	virtual ~Rva00576B5E();
	void rva00576B99(int a);
	void rva00576ACB(void *unused, void *lookup);

private:
	char m_unmodelled_04[0x4];
	Rva00577010 m_member;	// +0x8
};

Rva00576B5E::~Rva00576B5E()
{
}

class Rva00576B99Target
{
public:
	virtual int v00(int a);
	char m_pad04[0x3C];
	int m_40;
};
class Rva00577302
{
public:
	void rva005753A4(int a);
};
void Rva00576B5E::rva00576B99(int a)
{
	Rva00576B99Target *t = *(Rva00576B99Target **)(void *)&m_member;
	if (t->m_40 == 0) {
		if (t->v00(a) == 1)
			return;
	}
	((Rva00577302 *)this)->rva005753A4(a);
}

class Rva004FBED6Call
{
public:
	void *rva004FBED6();
};
class Rva005768CBCall
{
public:
	void rva005768CB(void *lookup);
};
class Rva00576ACBExpected
{
public:
	char m_unmodelled_00[0x14];
	void *m_expected;
};
// Target evidence: slot 4 of the vptr stored by the destructor at 0x00576B5E;
// the body reads this+0x0C and that pointer's +0x14 field, compares it with
// the 0x004FBED6 call result, and conditionally calls 0x005768CB on this-0x0C.
// The record and helper interfaces are structural views; their identities and
// argument meanings remain unknown.
void Rva00576B5E::rva00576ACB(void *unused, void *lookup)
{
	(void)unused;
	Rva00576ACBExpected *expected = *(Rva00576ACBExpected **)((char *)this + 0xC);
	void *expected_value = expected->m_expected;
	if (((Rva004FBED6Call *)lookup)->rva004FBED6() == expected_value)
		((Rva005768CBCall *)((char *)this - 0xC))->rva005768CB(lookup);
}

class GameMessage;

class Rva005772BF : public Rva00575395
{
public:
	virtual ~Rva005772BF();
	void rva00577324(const void *buf, int len);
	int rva005771F4(GameMessage *message);

private:
	char m_unmodelled_04[0x4];
	Rva00577010 m_member;	// +0x8
};

Rva005772BF::~Rva005772BF()
{
}

class Rva005D1F14
{
public:
	int rva005D1F14(int a, int b);
};

struct Rva005772BFHolder
{
	char m_pad00[0x14];
	Rva005D1F14 *m_14;
};

class Rva005753AC
{
public:
	int rva005753AC(const void *buffer, int bytes);
};

// 0x00575D88: vtable slot 3 of the 0x00C6E664 table owned by Rva00575D45.
// Its +0x8 holder points to an object with a +0x28 delegate. The target bytes
// call delegate slot 3 and fall back to the rowed write method on -1/null.
template <int N>
class Rva00575D88Slots : public Rva00575D88Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <>
class Rva00575D88Slots<0>
{
};
class Rva00575D88Dispatch : public Rva00575D88Slots<3>
{
public:
	virtual int write(const void *buf, int len);
};
struct Rva00575D88Holder
{
	char m_pad00[0x28];
	Rva00575D88Dispatch *m_28;
};
int Rva00575D45::rva00575D88(const void *buf, int len)
{
	Rva00575D88Dispatch *delegate = ((Rva00575D88Holder *)*(void **)(void *)&m_member)->m_28;
	if (delegate) {
		int result = delegate->write(buf, len);
		if (result != -1)
			return result;
	}
	return ((Rva005753AC *)this)->rva005753AC(buf, len);
}

void Rva005772BF::rva00577324(const void *buf, int len)
{
	Rva005D1F14 *p = ((Rva005772BFHolder *)*(void **)(void *)&m_member)->m_14;
	if (p && p->rva005D1F14((int)buf, len) != -1)
		return;
	((Rva005753AC *)this)->rva005753AC(buf, len);
}

class Rva00577FA7 : public Rva005C6C7B
{
public:
	virtual ~Rva00577FA7();

private:
	char m_unmodelled_04[0x40];
	Rva00577EB2 m_member;	// +0x44
};

Rva00577FA7::~Rva00577FA7()
{
}

class Rva005CF7BF : public Rva005E6810
{
public:
	virtual ~Rva005CF7BF();

private:
	char m_unmodelled_04[0x4];
	Rva005CF363 m_member;	// +0x8
};

Rva005CF7BF::~Rva005CF7BF()
{
}

class Rva005E1FBC : public Rva00539926Base
{
public:
	virtual ~Rva005E1FBC();

private:
	char m_unmodelled_04[0x8];
	Rva005E1E81 m_member;	// +0xC
};

Rva005E1FBC::~Rva005E1FBC()
{
}

class Rva005E362F : public Rva00539926Base
{
public:
	virtual ~Rva005E362F();

private:
	char m_unmodelled_04[0x8];
	Rva005E35DA m_member;	// +0xC
};

Rva005E362F::~Rva005E362F()
{
}

class Rva005F64F5 : public Rva005F38CA
{
public:
	virtual ~Rva005F64F5();

private:
	char m_unmodelled_04[0x4];
	Rva005F64DB m_member;	// +0x8
};

Rva005F64F5::~Rva005F64F5()
{
}

class Rva005F86C3 : public Rva00577936
{
public:
	virtual ~Rva005F86C3();

private:
	char m_unmodelled_04[0x1C];
	Rva005F85E1 m_member;	// +0x20
};

Rva005F86C3::~Rva005F86C3()
{
}

class Rva005FB1AD : public Rva006003FC
{
public:
	virtual ~Rva005FB1AD();
	void rva005FAA90();
	void rva005FA9E0(int value);
	void rva005FA9FC(int value);
	void rva005FAA15(int value);

private:
	char m_unmodelled_04[0x1C];
	Rva005FAFB2 m_member;	// +0x20
};

Rva005FB1AD::~Rva005FB1AD()
{
}

// Slots 1-4 of Rva005FB1AD's vtable 0x00C79EDC: each runs the base's own slot
// (rowed 0x006003AD, or 0x006003A5 that slots 2-4 fold to) and then hands the
// value to the object the +0x20 member holds: its 0x005FAA4D refresh (not
// yet rowed; pinned), its rowed 0x005FA91C and 0x005FA97C, or straight into
// its +0x50 (the int 0x005FAA4D tests).
class Rva005FAA4D
{
public:
	void rva005FAA4D();
};

class Rva005FA91C
{
public:
	void rva005FA91C(int value);
};

class Rva005FA97C
{
public:
	void rva005FA97C(int value);
};

struct Rva005FA9FCTarget
{
	unsigned char m_pad00[0x50];
	int m_50;
};

// ?rva005FAA90@Rva005FB1AD@@QAEXXZ @0x005FAA90 17B, slot 1.
void Rva005FB1AD::rva005FAA90()
{
	rva006003AD();
	reinterpret_cast<Rva005FAA4D *>(m_member.m_value)->rva005FAA4D();
}

// ?rva005FA9E0@Rva005FB1AD@@QAEXH@Z @0x005FA9E0 28B, slot 2.
void Rva005FB1AD::rva005FA9E0(int value)
{
	rva006003A5((Object *)value);
	reinterpret_cast<Rva005FA91C *>(m_member.m_value)->rva005FA91C(value);
}

// ?rva005FA9FC@Rva005FB1AD@@QAEXH@Z @0x005FA9FC 25B, slot 3.
void Rva005FB1AD::rva005FA9FC(int value)
{
	rva006003A5((Object *)value);
	reinterpret_cast<Rva005FA9FCTarget *>(m_member.m_value)->m_50 = value;
}

// ?rva005FAA15@Rva005FB1AD@@QAEXH@Z @0x005FAA15 28B, slot 4.
void Rva005FB1AD::rva005FAA15(int value)
{
	rva006003A5((Object *)value);
	reinterpret_cast<Rva005FA97C *>(m_member.m_value)->rva005FA97C(value);
}

class Rva005CC26E
{
public:
	int rva005CC26E(void *arg);
};
class Rva00574910Dispatch
{
public:
	virtual int gap0();
	virtual int gap1();
	virtual int check(void *arg);
};
class Rva005C9BE3Call
{
public:
	int rva005C9BE3(void *arg);
};
class Rva005CBC95Call
{
public:
	int rva005CBC95(void *arg);
};
class Rva00574910
{
public:
	int rva00574910(void *arg);
};

// Target evidence: calls 0x005CC26E on this+0x5C, virtual slot 2 through the
// pointer at this+0x54, 0x005C9BE3 on this+0x28, then 0x005CBC95 on this.
// Address-derived class and offsets do not establish the original identity.
// ?Rva00574910::rva00574910 present-unmatched
int Rva00574910::rva00574910(void *arg)
{
	if (((Rva005CC26E *)((char *)this + 0x5C))->rva005CC26E(arg) == 1)
		return 1;
	Rva00574910Dispatch *dispatch = *(Rva00574910Dispatch **)((char *)this + 0x54);
	if (dispatch && dispatch->check(arg) == 1)
		return 1;
	if (((Rva005C9BE3Call *)((char *)this + 0x28))->rva005C9BE3(arg) == 1)
		return 1;
	return ((Rva005CBC95Call *)this)->rva005CBC95(arg);
}


struct IRegion2D;
class Rva005D1F45
{
public:
	int rva005D1F45(IRegion2D *region, int value);
	int rva005D1FD3(GameMessage *message);
};
class Rva005CD8F7Call
{
public:
	int rva005CD8F7(void *arg);
};
class Rva005CD690Call
{
public:
	int rva005CD690(void *arg);
};

// Target evidence: adjacent Rva005772BF methods and its vtable support the
// class association. This body reads +0x14/+0x18/+0x28 and short-circuits on
// result 1; the rowed 0x005D1FD3 call identifies the argument as GameMessage*.
// ?Rva005772BF::rva005771F4 present-unmatched
int Rva005772BF::rva005771F4(GameMessage *message)
{
	Rva005D1F45 *dispatcher = *(Rva005D1F45 **)((char *)this + 0x14);
	if ((!dispatcher || dispatcher->rva005D1FD3(message) != 1)
		&& ((Rva005CD8F7Call *)((char *)this + 0x18))->rva005CD8F7(message) != 1
		&& ((Rva005CD690Call *)((char *)this + 0x28))->rva005CD690(message) != 1)
		return ((Rva005CBC95Call *)this)->rva005CBC95(message);
	return 1;
}
