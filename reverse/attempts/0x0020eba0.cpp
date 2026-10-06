// ?rva0020EBA0@Rva0020EBA0@@QAEXXZ
// partial score=0.96 date=2026-10-06
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Oi
// ?rva0020EBA0@Rva0020EBA0@@QAEXXZ @0x0020EBA0 249B
// Evidence: chain lane via 0x003F830F; vector +0x14/+0x18 over Rva003F498A
//   like Rva0020E794Loop; global g_009FEF10 with rowed 0x002B254F/0x002B5256
//   and thunk 0x002B256E plus proxy 0x003F830F; loop compares rowed 0x003F4831
//   to 0x002B5256 count then callback via pinned 0x0020E7BD with BE433C/20 tmps.
#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

class Rva003F498A
{
public:
	int rva003F4831();
	bool rva003F48EF(void *p);
};

class Rva0020E794
{
public:
	Rva003F498A *rva0020E794();
};

class Rva0020E7BD
{
public:
	void rva0020E7BD(void *p);
};

class Rva002B254F
{
public:
	int rva002B254F();
};

class Rva002BA8F1Logic
{
public:
	int rva002B5256(bool flag);
};

class Rva003F81FDProxy
{
public:
	void rva003F830F(void *p);
};

void *Rva002B256EGet(void);

extern Rva002BA8F1Logic *g_009FEF10;
extern const void *const g_00BE433C[];
extern const void *const g_00BE4320[];

struct EmptyBase20EBA0
{
	EmptyBase20EBA0() {}
	~EmptyBase20EBA0() { _ReadWriteBarrier(); }
};

struct TmpBE433C : EmptyBase20EBA0
{
	const void *v;
	void *o;
	TmpBE433C(void *oo) : v(g_00BE433C), o(oo) {}
	~TmpBE433C() {}
};

struct TmpBE4320 : EmptyBase20EBA0
{
	const void *v;
	TmpBE4320() : v(g_00BE4320) {}
	~TmpBE4320() {}
};

class Rva0020EBA0
{
public:
	void rva0020EBA0();
private:
	unsigned char m_pad[0x14];
	Rva003F498A **m_begin;
	Rva003F498A **m_end;
};

void Rva0020EBA0::rva0020EBA0()
{
	if ((((int)m_end - (int)m_begin) >> 2) == 0)
		return;
	if ((unsigned char)((Rva002B254F *)g_009FEF10)->rva002B254F()) {
		((Rva003F81FDProxy *)Rva002B256EGet())->rva003F830F(this);
	}
	int n = g_009FEF10->rva002B5256(false);
	if (n <= 1)
		return;
	Rva003F498A **begin = m_begin;
	Rva003F498A **end = m_end;
	for (; begin != end; ++begin) {
		Rva003F498A *e = *begin;
		if (e->rva003F4831() == n) {
			if (!e)
				break;
			TmpBE433C tmp(e);
			((Rva0020E7BD *)this)->rva0020E7BD(&tmp);
			return;
		}
	}
	Rva003F498A *p = ((Rva0020E794 *)this)->rva0020E794();
	if (!p)
		return;
	void *q = *(void **)((char *)g_009FEF10 + 0x98);
	if (!q)
		return;
	if (p->rva003F48EF(q)) {
		TmpBE433C tmp(p);
		((Rva0020E7BD *)this)->rva0020E7BD(&tmp);
	}
	else {
		TmpBE4320 tmp;
		((Rva0020E7BD *)this)->rva0020E7BD(&tmp);
	}
}
