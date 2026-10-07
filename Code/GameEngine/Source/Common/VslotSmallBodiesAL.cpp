// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry, batch
// AL: unrowed callees are pinned in reverse/symbols.csv under
// address-derived names with the argument counts their ret shows. Classes
// and methods are address-derived and model only what each body touches.

typedef int Int;
typedef unsigned int UnsignedInt;

// 0x00330AF6 and 0x00330BA3 (siblings of the rowed 0x00330AD8/0x00330B85):
// the pinned setter 0x0030BAD8 (index, pair) resp. 0x0030B232 (one
// argument) on the +0x08 member, then virtual slot 12.
struct BfmeE8;
class Rva0030BAD8
{
public:
	void rva0030BAD8(Int i, const BfmeE8 &value);
};
class Rva0030B232
{
public:
	void rva0030B232(Int a);
};
class Rva00330AF6Base
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
class Rva00330AF6 : public Rva00330AF6Base
{
public:
	void rva00330AF6(Int i, const BfmeE8 &value);
private:
	Int m_04;
	Rva0030BAD8 m_08;
};
void Rva00330AF6::rva00330AF6(Int i, const BfmeE8 &value)
{
	m_08.rva0030BAD8(i, value);
	v12();
}
class Rva00330BA3 : public Rva00330AF6Base
{
public:
	void rva00330BA3(Int a);
private:
	Int m_04;
	Rva0030B232 m_08;
};
void Rva00330BA3::rva00330BA3(Int a)
{
	m_08.rva0030B232(a);
	v12();
}

// 0x00526342, 0x00527111 and 0x00567D96: the pinned 0x00525E55 (no
// argument), 0x00526F85 (the argument) resp. 0x00567A6E (+0x0C) of the
// +0x08 object; answer true.
class Rva00525E55
{
public:
	void rva00525E55();
	void rva00526F85(Int a);
	void rva00567A6E(Int a);
};
class Rva00526342
{
public:
	bool rva00526342(Int unused);
	bool rva00527111(Int a);
	bool rva00567D96(Int unused);
private:
	Int m_00;
	Int m_04;
	Rva00525E55 *m_08;
	Int m_0C;
};
bool Rva00526342::rva00526342(Int)
{
	m_08->rva00525E55();
	return true;
}
bool Rva00526342::rva00527111(Int a)
{
	m_08->rva00526F85(a);
	return true;
}
bool Rva00526342::rva00567D96(Int)
{
	m_08->rva00567A6E(m_0C);
	return true;
}

// 0x005E1B41 (interface at +0x0C): the pinned 0x005E1AB6(0) of the
// complete object (the argument is unused).
class Image;
struct Rva005D2355In;
struct Rva005F002CIn;
class Rva005E1AB6Obj;
class Rva005E1B41Primary
{
public:
	virtual void primarySlot();
	void rva005E1AB6(Int a);
	Int m_04;
	Int m_08;
};
class Rva005E1B41Iface
{
public:
	virtual void rva005E1B41(Int unused) = 0;
};
class Image;
struct Rva005D2355In;
struct Rva005F002CIn;
const Image *Rva005F031DGet(Rva005D2355In *in);
const Image *Rva005F002CGet(Rva005F002CIn *in);
class Rva005E197E
{
public:
	void rva005E197E();
};
class Rva005E1928
{
public:
	void rva005E1928();
};
class Rva005E1AB6Obj
{
public:
	virtual bool v00();
	virtual void v04(void *p);
	virtual void v08();
	virtual void v0c(int n);
	virtual void v10();
	virtual void v14(const Image *img);
	virtual void v18();
	virtual void v1c(const Image *img);
};
class Rva005E1B41 : public Rva005E1B41Primary, public Rva005E1B41Iface
{
public:
	void rva005E1B41(Int unused);
	Int m_10;
	Rva005D2355In *m_14;
	Rva005E1AB6Obj *m_18;
	Int m_1C;
	unsigned char m_20;
};
void Rva005E1B41::rva005E1B41(Int)
{
	rva005E1AB6(0);
}

// ?rva005E1AB6@Rva005E1B41Primary@@QAEXH@Z @0x005E1AB6 139B: setter for interface at +0x18 with old release via v00/v04 and new init via v04/v0c plus two Image lookups.
// Evidence: pin ?rva005E1AB6@Rva005E1B41Primary@@QAEXH@Z; callers 0x005E1B46 rowed rva005E1B41 and 0x005E1B86; rowed 0x005E197E 0x005F031D 0x005F002C and pinned 0x005E1928; vtable slots 0/4/c/14/1c.
void Rva005E1B41Primary::rva005E1AB6(Int a)
{
	Rva005E1B41 *full = (Rva005E1B41 *)this;
	if ((Rva005E1AB6Obj *)a != full->m_18)
	{
		if (full->m_18 != 0)
		{
			if (full->m_18->v00())
				((Rva005E197E *)this)->rva005E197E();
			full->m_18->v04(0);
		}
		full->m_18 = (Rva005E1AB6Obj *)a;
		if (full->m_18 == 0)
			return;
		full->m_18->v04((void *)static_cast<Rva005E1B41Iface *>(full));
		full->m_18->v0c(1 + (full->m_20 != 0));
		const Image *img1 = Rva005F031DGet(full->m_14);
		full->m_18->v14(img1);
		const Image *img2 = Rva005F002CGet((Rva005F002CIn *)full->m_14);
		full->m_18->v1c(img2);
		if (full->m_18->v00())
			((Rva005E1928 *)this)->rva005E1928();
	}
}

// 0x00588A9D: the pinned 0x00588A72 on the +0x08 vector (0x3C-byte
// entries) with the count when it holds fewer.
template <class T>
struct Rva00588A9DVector
{
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
	UnsignedInt size() const { return _M_finish - _M_start; }
	void grow(UnsignedInt count);
};
struct Rva00588A9DEntry
{
	char m_pad00[0x3C];
};
class Rva00588A9D
{
public:
	void rva00588A9D(UnsignedInt count);
private:
	Int m_00;
	Int m_04;
	Rva00588A9DVector<Rva00588A9DEntry> m_08;
};
void Rva00588A9D::rva00588A9D(UnsignedInt count)
{
	if (m_08.size() < count)
		m_08.grow(count);
}

// 0x0006EE46 (interface at +0x108): the pinned cdecl 0x00118660 with the
// complete object and the +0x10 interface member, when that is set.
bool Rva00118660Call(void *owner, void *value);
class Rva0006EE46Primary
{
public:
	virtual void primarySlot();
private:
	char m_pad04[0x104];
};
class Rva0006EE46Iface
{
public:
	virtual void rva0006EE46() = 0;
protected:
	char m_pad04[0x0C];
	void *m_10;
};
class Rva0006EE46 : public Rva0006EE46Primary, public Rva0006EE46Iface
{
public:
	void rva0006EE46();
};
void Rva0006EE46::rva0006EE46()
{
	if (m_10)
		Rva00118660Call(this, m_10);
}
