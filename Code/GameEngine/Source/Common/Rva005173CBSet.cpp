// cl: /O1 /MD /GX-
// ?rva005173CB@Rva005173CB@@QAEPAU1@ABURva0051732A@@@Z @0x005173CB 45B
// Allocating setter: new 12B Rva00517345 via rowed ctor at 0x00517345
// forwarding the holder arg, store into +0, AddRef the new object at +4,
// return this. Rowed operator new at 0x0002FDA0. Caller 0x0051755C.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

struct Rva0051732A
{
	TargetRef00217D4C *m_ptr;
};

struct Rva00517345
{
	void *m_vtbl;
	int m_04;
	TargetRef00217D4C *m_08;
	Rva00517345(const Rva0051732A &other);
};

void *__cdecl operator new(unsigned int size) throw();

struct Rva005173CB
{
	Rva00517345 *m_ptr;
	Rva005173CB *rva005173CB(const Rva0051732A &arg);
};

Rva005173CB *Rva005173CB::rva005173CB(const Rva0051732A &arg)
{
	Rva00517345 *p = new Rva00517345(arg);
	m_ptr = p;
	if (p)
		++p->m_04;
	return this;
}

// ?rva0044BEE6@Rva0044BEE6@@QAEPAU1@ABURva0051732A@@@Z, retail 0x0044BEE6, 45 bytes:
// the same setter over the rowed Rva0044BDA2 holder constructor (a twin of
// Rva00517345's that installs its own vtable), the only difference from
// rva005173CB's bytes.
struct Rva0044BDA2
{
	void *m_vtbl;
	int m_04;
	TargetRef00217D4C *m_08;
	Rva0044BDA2(const Rva0051732A &other);
};
struct Rva0044BEE6
{
	Rva0044BDA2 *m_ptr;
	Rva0044BEE6 *rva0044BEE6(const Rva0051732A &arg);
};
Rva0044BEE6 *Rva0044BEE6::rva0044BEE6(const Rva0051732A &arg)
{
	Rva0044BDA2 *p = new Rva0044BDA2(arg);
	m_ptr = p;
	if (p)
		++p->m_04;
	return this;
}

// ?rva0044BEB9@Rva0044BEB9@@QAEPAU1@ABURva004C5DD0Pair@@@Z @0x0044BEB9 45B
// Allocating setter twin of rva005173CB/rva0044BEE6 over the rowed
// Rva0044BD34 ctor (0x0044BD34 31B): new 16B, forward the holder as pointer
// to that ctor, store into +0, AddRef at +4, return this. Rowed operator new
// 0x0002FDA0. Caller 0x0044BF55; landing unblocks 0x0044BF40.
struct Rva004C5DD0Ref
{
	int m_00;
	int m_refs;
};

struct Rva004C5DD0Pair
{
	Rva004C5DD0Ref *a;
	Rva004C5DD0Ref *b;
};

class Rva004C5DD0
{
	Rva004C5DD0Ref *m_00;
	Rva004C5DD0Ref *m_04;

public:
	Rva004C5DD0 &set(const Rva004C5DD0Pair *p);
};

struct Rva0044BD34
{
	void *m_vtbl;
	int m_04;
	Rva004C5DD0 m_08;
	Rva0044BD34(const Rva004C5DD0Pair *p);
};

struct Rva0044BEB9
{
	Rva0044BD34 *m_ptr;
	Rva0044BEB9 *rva0044BEB9(const Rva004C5DD0Pair &arg);
};

Rva0044BEB9 *Rva0044BEB9::rva0044BEB9(const Rva004C5DD0Pair &arg)
{
	Rva0044BD34 *p = new Rva0044BD34(&arg);
	m_ptr = p;
	if (p)
		++p->m_04;
	return this;
}
