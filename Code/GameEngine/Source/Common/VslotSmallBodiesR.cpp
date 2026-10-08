// cl: /O1 /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch R. As in VslotSmallBodiesA-Q, each class and
// method is address-derived unless the ledger already names it, and models
// only what its body touches; the comment above each gives what references
// it. Meanings are not recovered.

typedef int Int;
typedef unsigned int UnsignedInt;

// texture-family slot at 0x0017FAFB: 0x58 bytes per entry of the +0x14
// object's +0x10 count plus a 0x34 header, 0 without the object.
struct Rva0017FAFBInfo
{
	char m_pad00[0x10];
	UnsignedInt m_count10;
};
class Rva0017FAFB
{
public:
	UnsignedInt rva0017FAFB() const;
private:
	char m_pad00[0x14];
	Rva0017FAFBInfo *m_14;
};
UnsignedInt Rva0017FAFB::rva0017FAFB() const
{
	if (m_14)
		return m_14->m_count10 * 0x58 + 0x34;
	return 0;
}

// slot at 0x0018E6B0: whether entry i (0x24 bytes each) of the array at
// +0x50 has a non-zero +0x1C.
struct Rva0018E6B0Entry
{
	char m_pad00[0x1C];
	Int m_1C;
	Int m_20;
};
class HRawAnimClass
{
public:
	bool Has_VisibilityF(Int i) const;
private:
	char m_pad00[0x50];
	Rva0018E6B0Entry *m_50;
};
bool HRawAnimClass::Has_VisibilityF(Int i) const
{
	return m_50[i].m_1C != 0;
}

// slot at 0x00200BD9: runs the rowed 0x001E35DF on the +0x04 member of the
// object held at VA 0x00DFF488, when there is one.
class Overridable
{
public:
	Overridable *friend_getFinalOverride();
};
struct Rva00200BD9Holder
{
	Int m_00;
	Overridable *m_04;
};
extern Rva00200BD9Holder *g_rva00200BD9Holder;
class Rva00200BD9
{
public:
	void rva00200BD9();
};
void Rva00200BD9::rva00200BD9()
{
	Overridable *o = g_rva00200BD9Holder->m_04;
	if (o)
		o->friend_getFinalOverride();
}

// slot at 0x00222D26: writes the +0x04 object's leading byte, then its +0x04
// pair through the rowed Rva000B3F84Pair::write; returns the bytes written.
struct Rva000B3F84Pair
{
	Int write(char *buf);
};
struct Rva00222D26Data
{
	char m_00;
	char m_pad01[3];
	Rva000B3F84Pair m_pair04;
};
class Rva00222D26
{
public:
	Int rva00222D26(char *buf);
private:
	Int m_00;
	Rva00222D26Data *m_04;
};
Int Rva00222D26::rva00222D26(char *buf)
{
	Rva00222D26Data *d = m_04;
	buf[0] = d->m_00;
	return d->m_pair04.write(buf + 1) + 1;
}

// slot at 0x0033F504: the rowed BfmeSub932C query of the +0x20 object, 0
// without one.
class BfmeSub932C
{
public:
	unsigned char bfmeQuery932C();
};
class Rva0033F504
{
public:
	Int rva0033F504();
private:
	char m_pad00[0x20];
	BfmeSub932C *m_20;
};
Int Rva0033F504::rva0033F504()
{
	if (m_20)
		return m_20->bfmeQuery932C();
	return 0;
}

// slots at 0x003413A1 and 0x0034143C: virtual slot 11 (bool) resp. slot 6 of
// the +0x24 object, false/nothing without one.
class Rva003413A1Target
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
	virtual bool v11();
};
class Rva003413A1
{
public:
	bool rva003413A1();
	void rva0034143C();
private:
	char m_pad00[0x24];
	Rva003413A1Target *m_24;
};
bool Rva003413A1::rva003413A1()
{
	if (!m_24)
		return false;
	return m_24->v11();
}
void Rva003413A1::rva0034143C()
{
	if (m_24)
		m_24->v06();
}

// slot at 0x004444EB (screen tables beside BfmeAptScreenLanLobby): a new
// 0x0C-byte object with table VA 0x00C3D490 and both words cleared; its base
// destructor is the shared 0x004E84A4.
class Rva004444EBBase
{
public:
	Rva004444EBBase() : m_04(0), m_08(0) {}
	virtual ~Rva004444EBBase();
	Int m_04;
	Int m_08;
};
class Rva004444EBObject : public Rva004444EBBase
{
public:
	Rva004444EBObject() {}
};
class Rva004444EB
{
public:
	Rva004444EBBase *rva004444EB();
};
Rva004444EBBase *Rva004444EB::rva004444EB()
{
	return new Rva004444EBObject;
}

// slots at 0x00072F49 and 0x00072F64: state 2 on the +0x0C object then
// virtual slot 2 of the +0x08 object (false without one); resp. virtual slot
// 6 of the +0x08 object then state 0.
struct Rva00072F49State
{
	char m_pad00[0x44];
	Int m_44;
};
class Rva00072F49Target
{
public:
	virtual void v00();
	virtual void v01();
	virtual bool v02(Int a, Int b);
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
};
class Rva00072F49
{
public:
	bool rva00072F49(Int a, Int b);
	void rva00072F64();
private:
	Int m_00;
	Int m_04;
	Rva00072F49Target *m_08;
	Rva00072F49State *m_0C;
};
bool Rva00072F49::rva00072F49(Int a, Int b)
{
	m_0C->m_44 = 2;
	Rva00072F49Target *t = m_08;
	if (!t)
		return false;
	return t->v02(a, b);
}
void Rva00072F49::rva00072F64()
{
	Rva00072F49Target *t = m_08;
	if (t)
		t->v06();
	m_0C->m_44 = 0;
}

// slot at 0x003FF271: stores the argument at +0x14, runs virtual slot 17
// when the object at VA 0x00DFE78C is in state 3, then sets +0x11.
struct Rva003FF271Global
{
	char m_pad00[0x114];
	Int m_114;
};
extern class GameLogic *TheGameLogic;
class Rva003FF271
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
	void rva003FF271(Int value);
private:
	char m_pad04[0x0D];
	bool m_11;
	char m_pad12[2];
	Int m_14;
};
void Rva003FF271::rva003FF271(Int value)
{
	m_14 = value;
	if ((*(Rva003FF271Global **)&TheGameLogic)->m_114 == 3)
		v17();
	m_11 = true;
}

// slots at 0x00330AD8 and 0x00330B85: the rowed setter of the +0x08 member,
// then virtual slot 12.
struct BfmeE8;
class Rva0030BAA0
{
public:
	void rva0030BAA0(Int a, const BfmeE8 &b);
};
class Rva0030B92C
{
public:
	void rva0030B1A7(float f);
};
class Rva00330AD8Base
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
};
class Rva00330AD8 : public Rva00330AD8Base
{
public:
	void rva00330AD8(Int a, const BfmeE8 &b);
private:
	Int m_04;
	Rva0030BAA0 m_08;
};
void Rva00330AD8::rva00330AD8(Int a, const BfmeE8 &b)
{
	m_08.rva0030BAA0(a, b);
	v12();
}
class Rva00330B85 : public Rva00330AD8Base
{
public:
	void rva00330B85(float f);
private:
	Int m_04;
	Rva0030B92C m_08;
};
void Rva00330B85::rva00330B85(float f)
{
	m_08.rva0030B1A7(f);
	v12();
}
