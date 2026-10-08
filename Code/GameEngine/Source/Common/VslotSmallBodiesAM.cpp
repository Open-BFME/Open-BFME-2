// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry, batch
// AM. Classes and methods are address-derived unless the ledger names them,
// and model only what each body touches. Meanings are not recovered.

typedef int Int;
typedef float Real;

class Xfer
{
public:
	void Version1();
};

// 0x0033FB0B (16 tables): a StateMachine xfer override that chains to the
// pinned StateMachine::xfer, then stamps version 1.
class StateMachine
{
protected:
	virtual void xfer(Xfer *xfer);
};
class Rva0033FB0B : public StateMachine
{
protected:
	virtual void xfer(Xfer *xfer);
};
void Rva0033FB0B::xfer(Xfer *xfer)
{
	StateMachine::xfer(xfer);
	xfer->Version1();
}

// 0x003511C9: an onExit override that chains to the rowed
// AIExitState::onExit, then virtual slot 14 (0) of the +0x18 machine.
enum StateExitType
{
	EXIT_NORMAL = 0
};
class Rva003511C9Machine
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14(Int a);
};
class AIExitState
{
public:
	virtual void onExit(StateExitType status);
	char m_pad04[0x14];
	Rva003511C9Machine *m_18;
};
class Rva003511C9 : public AIExitState
{
public:
	virtual void onExit(StateExitType status);
};
void Rva003511C9::onExit(StateExitType status)
{
	AIExitState::onExit(status);
	m_18->v14(0);
}

// 0x003A389E: clears +0xBC/+0xC0 and runs the pinned TeamFactory::clear.
class TeamFactory
{
public:
	void clear();
	void rva003A389E();
private:
	char m_pad00[0xBC];
	Int m_BC;
	Int m_C0;
};
void TeamFactory::rva003A389E()
{
	m_BC = 0;
	m_C0 = 0;
	clear();
}

// 0x004201D5: byte i of the +0x70 array.
class Rva004201D5
{
public:
	unsigned char rva004201D5(Int i) const;
private:
	char m_pad00[0x70];
	unsigned char m_70[1];
};
unsigned char Rva004201D5::rva004201D5(Int i) const
{
	return m_70[i];
}

// 0x00420B55: clears +0x14 and the +0x10 int list (pinned list clear).
namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class _List_base
{
public:
	void clear();
	void *_M_node;
};
}
class Rva00420B55
{
public:
	void rva00420B55();
private:
	char m_pad00[0x10];
	_STL::_List_base<int, _STL::allocator<int> > m_10;
	bool m_14;
};
void Rva00420B55::rva00420B55()
{
	m_14 = false;
	m_10.clear();
}

// 0x004523E9 and 0x0045F393 / 0x004B471F: own virtual slot 9 with 0 (after
// clearing +0x0C) resp. with 1 / 0.
class Rva004523E9
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09(Int a);
	void rva004523E9();
	void rva0045F393();
	void rva004B471F();
private:
	Int m_04;
	Int m_08;
	Int m_0C;
};
void Rva004523E9::rva004523E9()
{
	m_0C = 0;
	v09(0);
}
void Rva004523E9::rva0045F393()
{
	v09(1);
}
void Rva004523E9::rva004B471F()
{
	v09(0);
}

// 0x00452D8C and 0x00452D98: store the argument (resp. 0xFFFFFE) at VA
// 0x00DC908C.
extern int g_Va00DC908C;
class Rva00452D8C
{
public:
	void rva00452D8C(Int a);
	void rva00452D98();
};
void Rva00452D8C::rva00452D8C(Int a)
{
	g_Va00DC908C = a;
}
void Rva00452D8C::rva00452D98()
{
	g_Va00DC908C = 0xFFFFFE;
}

// 0x00466E58 (four tables): the +0x13C byte of the +0x04 object.
struct Rva00466E58Info
{
	char m_pad00[0x13C];
	unsigned char m_13C;
};
class Rva00466E58
{
public:
	unsigned char rva00466E58(Int unused) const;
private:
	Int m_00;
	Rva00466E58Info *m_04;
};
unsigned char Rva00466E58::rva00466E58(Int) const
{
	return m_04->m_13C;
}

// 0x00488988 (four tables): -2.
class Rva00488988
{
public:
	Int rva00488988();
};
Int Rva00488988::rva00488988()
{
	return -2;
}

// 0x004FF363: 1.0 for any two arguments; 0x0050BD7C (ten tables): true.
class Rva004FF363
{
public:
	Real rva004FF363(Int a, Int b);
	bool rva0050BD7C(Int a, Int b);
};
Real Rva004FF363::rva004FF363(Int, Int)
{
	return 1.0f;
}
bool Rva004FF363::rva0050BD7C(Int, Int)
{
	return true;
}

// 0x0052AF88 (four tables): entry i of the +0x2C array.
class Rva0052AF88
{
public:
	Int rva0052AF88(Int i) const;
private:
	char m_pad00[0x2C];
	Int *m_2C;
};
Int Rva0052AF88::rva0052AF88(Int i) const
{
	return m_2C[i];
}

// 0x00541F11: hands this object to virtual slot 0 of the argument.
class Rva00541F11;
class Rva00541F11Visitor
{
public:
	virtual void v00(Rva00541F11 *o);
};
class Rva00541F11
{
public:
	void rva00541F11(Rva00541F11Visitor *v);
};
void Rva00541F11::rva00541F11(Rva00541F11Visitor *v)
{
	v->v00(this);
}

// 0x0054F990: whether +0x6C differs from +0x70.
class Rva0054F990
{
public:
	bool rva0054F990() const;
private:
	char m_pad00[0x6C];
	Int m_6C;
	Int m_70;
};
bool Rva0054F990::rva0054F990() const
{
	return m_6C != m_70;
}

// 0x00550618 and 0x00550626: the +0x52 byte resp. +0x54 word of the +0x64
// object, 0 without it.
struct Rva00550618Info
{
	char m_pad00[0x52];
	bool m_52;
	char m_pad53;
	Int m_54;
};
class Rva00550618
{
public:
	bool rva00550618() const;
	Int rva00550626() const;
private:
	char m_pad00[0x64];
	Rva00550618Info *m_64;
};
bool Rva00550618::rva00550618() const
{
	Rva00550618Info *info = m_64;
	if (info)
		return info->m_52;
	return false;
}
Int Rva00550618::rva00550626() const
{
	Rva00550618Info *info = m_64;
	if (info)
		return info->m_54;
	return 0;
}

// 0x00567B42: the rowed 0x005C392A of the +0x0C object's +0x08 object.
class Rva005C392A
{
public:
	void rva005C392A();
};
struct Rva00567B42Info
{
	Int m_00;
	Int m_04;
	Rva005C392A *m_08;
};
class Rva00567B42
{
public:
	void rva00567B42();
private:
	char m_pad00[0x0C];
	Rva00567B42Info *m_0C;
};
void Rva00567B42::rva00567B42()
{
	m_0C->m_08->rva005C392A();
}

// 0x00573E74: counts +0x5C and tail-calls the rowed 0x0055AD91, the virtual
// AIBuildable::registerWithBuilder (slot 6), by a qualified direct call.
class AIBuildable
{
public:
	virtual void registerWithBuilder(void *a, bool b);
};
class Rva00573E74 : public AIBuildable
{
public:
	void rva00573E74(void *a, bool b);
private:
	char m_pad04[0x58];
	Int m_5C;
};
void Rva00573E74::rva00573E74(void *a, bool b)
{
	m_5C++;
	AIBuildable::registerWithBuilder(a, b);
}

// 0x005D99E4: sets bit 7 of the +0x20 byte.
class Rva005D99E4
{
public:
	void rva005D99E4();
private:
	char m_pad00[0x20];
	unsigned char m_20;
};
void Rva005D99E4::rva005D99E4()
{
	m_20 |= 0x80;
}

// Secondary-base slots (interface at +0x10, +0x0C, +0x0C resp. +0x04):
// 0x0028F976 runs the pinned Object 0x0028DB3C on the owning object and
// answers 1; 0x005E189B stores the complete object into +0x28 of the
// interface's +0x04 object; 0x005E19B4 runs the rowed 0x005E197E of the
// complete object; 0x0049CE63 dispatches to the complete object's virtual
// slot 16 (the arguments are unused).
class Object
{
public:
	void rva0028DB3C();
};
class Rva0028F976Primary
{
public:
	virtual void primarySlot();
protected:
	Int m_04;
	Object *m_object; // +0x08
	Int m_0C;
};
class Rva0028F976Iface
{
public:
	virtual Int rva0028F976() = 0;
};
class Rva0028F976 : public Rva0028F976Primary, public Rva0028F976Iface
{
public:
	Int rva0028F976();
};
Int Rva0028F976::rva0028F976()
{
	m_object->rva0028DB3C();
	return 1;
}
struct Rva005E189BInfo
{
	char m_pad00[0x28];
	void *m_28;
};
class Rva005E197E
{
public:
	virtual void primarySlot();
	void rva005E197E();
private:
	Int m_04_;
	Int m_08_;
};
class Rva005E189BIface
{
public:
	virtual void rva005E189B(Int unused) = 0;
	virtual void rva005E19B4(Int unused) = 0;
protected:
	Rva005E189BInfo *m_info04;
};
class Rva005E189B : public Rva005E197E, public Rva005E189BIface
{
public:
	void rva005E189B(Int unused);
	void rva005E19B4(Int unused);
};
void Rva005E189B::rva005E189B(Int)
{
	m_info04->m_28 = static_cast<Rva005E197E *>(this);
}
void Rva005E189B::rva005E19B4(Int)
{
	rva005E197E();
}
class Rva0049CE63Primary
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
};
class Rva0049CE63Iface
{
public:
	virtual void rva0049CE63(Int unused) = 0;
};
class Rva0049CE63 : public Rva0049CE63Primary, public Rva0049CE63Iface
{
public:
	void rva0049CE63(Int unused);
};
void Rva0049CE63::rva0049CE63(Int)
{
	v16();
}

// 0x00372DA6: clears the +0x15 flag.
class Rva00372DA6
{
public:
	void rva00372DA6();
private:
	char m_pad00[0x15];
	bool m_15;
};
void Rva00372DA6::rva00372DA6()
{
	m_15 = false;
}
