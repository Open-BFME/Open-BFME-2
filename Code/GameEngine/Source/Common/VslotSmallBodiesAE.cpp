// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry, batch
// AE. Unrowed callees are pinned in reverse/symbols.csv under
// address-derived names with the arguments their ret and call sites show.
// As in VslotSmallBodiesA-AD, classes and methods are address-derived
// unless the ledger already names them, and model only what each body
// touches. Meanings are not recovered.

typedef int Int;
typedef unsigned int UnsignedInt;

class Rva00585B16
{
public:
	Rva00585B16();
	Rva00585B16(const Rva00585B16 &other);
	~Rva00585B16();
private:
	int m_0;
	float m_4;
	float m_8;
	float m_C;
	int m_10;
	int m_14;
	int m_18;
	unsigned char m_1C;
	char m_pad1D[3];
	int m_20;
	int m_24;
	char m_deque[0x28];
	int m_50;
};
class Rva00586FC0
{
public:
	void rva00586FC0(UnsignedInt count, Rva00585B16 value);
};

// 0x00041B85 (tables VA 0x00BC24E8/0x00BC8748): the rowed Mouse
// 0x001EE5EE with both arguments, then the pinned 0x00041A83 with +0x4FA4.
class Mouse
{
public:
	void rva001EE5EE(unsigned char a, unsigned char *b);
};
class Rva00041B85 : public Mouse
{
public:
	void rva00041B85(unsigned char a, unsigned char *b);
	void rva00041A83(Int a);
private:
	char m_pad00[0x4FA4];
	Int m_4FA4;
};
void Rva00041B85::rva00041B85(unsigned char a, unsigned char *b)
{
	rva001EE5EE(a, b);
	rva00041A83(m_4FA4);
}

// 0x003FD1FA and 0x003FD321: overrides of the rowed xfer slot 0x003FD1FA
// chains to: the pinned helper 0x0030662A on +0x0C; resp. the pinned
// 0x005045E0 on the +0x0C member and Xfer slot 0x78 (unsigned int) on
// +0x18.
class Xfer
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
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void xferUnsignedInt(UnsignedInt *value);
};
void Rva0030662AXfer(Xfer *xfer, void *value);
class Rva005045E0
{
public:
	void rva005045E0(Xfer *xfer);
};
class Rva003FD1C5
{
public:
	virtual ~Rva003FD1C5();
protected:
	virtual void rva003FD1C5(Xfer *xfer);
private:
	UnsignedInt m_04;
	bool m_08;
};
class Rva003FD1FA : public Rva003FD1C5
{
protected:
	virtual void rva003FD1C5(Xfer *xfer);
private:
	Int m_0C;
};
void Rva003FD1FA::rva003FD1C5(Xfer *xfer)
{
	Rva003FD1C5::rva003FD1C5(xfer);
	Rva0030662AXfer(xfer, &m_0C);
}
class Rva003FD321 : public Rva003FD1C5
{
protected:
	virtual void rva003FD1C5(Xfer *xfer);
private:
	Rva005045E0 m_0C;
	char m_pad0D[0x0B];
	UnsignedInt m_18;
};
void Rva003FD321::rva003FD1C5(Xfer *xfer)
{
	Rva003FD1C5::rva003FD1C5(xfer);
	m_0C.rva005045E0(xfer);
	xfer->xferUnsignedInt(&m_18);
}

// 0x00540BE4 (table VA 0x00C69508): an override of the rowed chunk reader
// 0x0053F915 that chains to it, then the pinned 0x00540B48 on the +0x24
// member; answers true.
class DataChunkInput;
class Rva0053FB33
{
public:
	virtual bool rva0053F915(DataChunkInput *in, void *user);
};
class Rva00540B48
{
public:
	bool rva00540B48(DataChunkInput *in, void *user);
};
class Rva00540BE4 : public Rva0053FB33
{
public:
	virtual bool rva0053F915(DataChunkInput *in, void *user);
private:
	char m_pad04[0x20];
	Rva00540B48 m_24;
};
bool Rva00540BE4::rva0053F915(DataChunkInput *in, void *user)
{
	Rva0053FB33::rva0053F915(in, user);
	m_24.rva00540B48(in, user);
	return true;
}

// 0x00574356 (tables VA 0x00C6E4B8/0x00C6E4D4): whether the argument
// equals +0x14.
class Rva00574356
{
public:
	bool rva00574356(Int a) const;
private:
	char m_pad00[0x14];
	Int m_14;
};
bool Rva00574356::rva00574356(Int a) const
{
	return a == m_14;
}

// 0x00577302 (two tables): the pinned 0x005753A4 with the argument unless
// virtual slot 0 of the +0x08 object answers 1 for it.
class Rva00577302Target
{
public:
	virtual Int v00(Int a);
};
class Rva00577302
{
public:
	void rva00577302(Int a);
	void rva005753A4(Int a);
private:
	Int m_00;
	Int m_04;
	Rva00577302Target *m_08;
};
void Rva00577302::rva00577302(Int a)
{
	if (m_08->v00(a) != 1)
		rva005753A4(a);
}

// 0x00584A7D and 0x00587057: the pinned 0x00584A3D resp. 0x0058702C with
// the count when the +0x08 vector (0x1C- resp. 0x54-byte entries) holds
// fewer entries.
template <class T>
struct Rva00584A7DVector
{
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
	UnsignedInt size() const { return _M_finish - _M_start; }
	void grow(UnsignedInt count);
};
struct Rva00584A7DEntry
{
	char m_pad00[0x1C];
};
struct Rva00587057Entry
{
	char m_pad00[0x54];
};
template <>
void Rva00584A7DVector<Rva00587057Entry>::grow(UnsignedInt count)
{
	((Rva00586FC0 *)this)->rva00586FC0(count, Rva00585B16());
}
class Rva00584A7D
{
public:
	void rva00584A7D(UnsignedInt count);
private:
	Int m_00;
	Int m_04;
	Rva00584A7DVector<Rva00584A7DEntry> m_08;
};
void Rva00584A7D::rva00584A7D(UnsignedInt count)
{
	if (m_08.size() < count)
		m_08.grow(count);
}
class Rva00587057
{
public:
	void rva00587057(UnsignedInt count);
private:
	Int m_00;
	Int m_04;
	Rva00584A7DVector<Rva00587057Entry> m_08;
};
void Rva00587057::rva00587057(UnsignedInt count)
{
	if (m_08.size() < count)
		m_08.grow(count);
}

// 0x005AFA0E: the pinned cdecl 0x0038190F with both arguments.
void Rva0038190FCall(Int a, Int b);
class Rva005AFA0E
{
public:
	void rva005AFA0E(Int a, Int b);
};
void Rva005AFA0E::rva005AFA0E(Int a, Int b)
{
	Rva0038190FCall(a, b);
}

// 0x005AFCEC (eight tables): the pinned 0x005AFCB4(1) when the argument
// equals +0x04.
class Rva005AFCEC
{
public:
	void rva005AFCEC(Int a);
	void rva005AFCB4(Int a);
private:
	Int m_00;
	Int m_04;
};
void Rva005AFCEC::rva005AFCEC(Int a)
{
	if (a == m_04)
		rva005AFCB4(1);
}

// 0x005B023A: sets +0x150 and runs the pinned 0x004083FF(0).
class Rva005B023A
{
public:
	void rva005B023A();
	void rva004083FF(Int a);
private:
	char m_pad00[0x150];
	bool m_150;
};
void Rva005B023A::rva005B023A()
{
	m_150 = true;
	rva004083FF(0);
}

// 0x005C392A (one table, two tail jumps): the pinned 0x005C36F3 of the
// +0x08 object.
class Rva005C36F3
{
public:
	void rva005C36F3();
};
class Rva005C392A
{
public:
	void rva005C392A();
private:
	Int m_00;
	Int m_04;
	Rva005C36F3 *m_08;
};
void Rva005C392A::rva005C392A()
{
	m_08->rva005C36F3();
}

// 0x0051483C (table VA 0x00C65F3C): false after the rowed 0x002233A6(1) on
// the object at VA 0x00DFE4CC when TheGameLogic and the object at VA
// 0x00E01E48 exist, TheGameLogic's +0x110 is not 4 and that object's
// pinned 0x0035C194(true, false) agrees; else true.
class Rva00222A8BTarget
{
public:
	void rva002233A6(Int a);
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva0035C194
{
public:
	bool rva0035C194(bool a, bool b);
};
extern class Shell *TheShell;
struct Rva0051483CLogic
{
	char m_pad00[0x110];
	Int m_110;
};
extern Rva0051483CLogic *TheGameLogic;
class Rva0051483C
{
public:
	bool rva0051483C();
};
bool Rva0051483C::rva0051483C()
{
	if (TheGameLogic && (*(Rva0035C194 **)&TheShell) && TheGameLogic->m_110 != 4
		&& (*(Rva0035C194 **)&TheShell)->rva0035C194(true, false))
	{
		(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->rva002233A6(1);
		return false;
	}
	return true;
}

// 0x005391A9 (one table, three callers): the pinned 0x005C4C69 on each of
// the entries virtual slot 15 hands out for the count virtual slot 13
// gives.
class Rva005C4C69
{
public:
	void rva005C4C69();
};
class Rva005391A9
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
	virtual Int v13();
	virtual void v14();
	virtual Rva005C4C69 *v15(Int i);
	void rva005391A9();
};
void Rva005391A9::rva005391A9()
{
	Int count = v13();
	for (Int i = 0; i < count; i++)
		v15(i)->rva005C4C69();
}

// 0x00597426 (three tables): 2 while the argument's +0x94 is below +0x2C;
// else 4 when virtual slot 17 of the pinned Object 0x0028BC58(0) of the
// object whose id is +0x08 holds, otherwise the pinned Object 0x00294ADD
// with +0x30.
enum ObjectID
{
	INVALID_ID = 0
};
class Rva00597426Part
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
	virtual Int v17();
};
class Object
{
public:
	void *rva0028BC58(Int a);
	Int rva00294ADD(Int a);
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *g_rva00597426Logic;
struct Rva00597426Arg
{
	char m_pad00[0x94];
	UnsignedInt m_94;
};
// A virtual: slot 16 of the three tables 0x00C70B88, 0x00C70BD0 (installed by
// AIUpgrade's ctor 0x00597331) and 0x00C76640 that inherit it.
class AIUpgrade
{
public:
	virtual Int canMake(const Rva00597426Arg *arg);
private:
	Int m_04;
	ObjectID m_08;
	char m_pad0C[0x20];
	UnsignedInt m_2C;
	Int m_30;
};
Int AIUpgrade::canMake(const Rva00597426Arg *arg)
{
	if (arg->m_94 < m_2C)
		return 2;
	Object *obj = g_rva00597426Logic->findObjectByID(m_08);
	Rva00597426Part *part = (Rva00597426Part *)obj->rva0028BC58(0);
	if (!part->v17())
		return obj->rva00294ADD(m_30);
	return 4;
}

// 0x004E06B8 (interface at +0x04, table VA 0x00C61610): unless the first
// argument is set, virtual slot 9 (1, 1) of the +0x28 object and the rowed
// 0x004E06A7 of the complete object; unless the second is, the pinned
// 0x0052B045 and the rowed 0x005392C2 on the +0x28 object.
class Rva005392C2
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
	virtual void v09(bool a, bool b);
	void rva005392C2();
	void rva0052B045();
};
class Rva004E06A7
{
public:
	virtual void primarySlot();
	void rva004E06A7() const;
};
class Rva004E06B8Iface
{
public:
	virtual void rva004E06B8(Int a, Int b) = 0;
};
class Rva004E06B8 : public Rva004E06A7, public Rva004E06B8Iface
{
public:
	void rva004E06B8(Int a, Int b);
private:
	char m_pad08[0x24];
	Rva005392C2 *m_2C;
};
void Rva004E06B8::rva004E06B8(Int a, Int b)
{
	if (!a)
	{
		if (m_2C)
			m_2C->v09(true, true);
		rva004E06A7();
	}
	if (!b)
	{
		Rva005392C2 *p = m_2C;
		if (p)
		{
			p->rva0052B045();
			m_2C->rva005392C2();
		}
	}
}
