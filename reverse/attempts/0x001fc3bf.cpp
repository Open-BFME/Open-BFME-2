// ??0Rva001FC3BF@@QAE@ABV0@@Z
// partial score=0.8 date=2026-10-05
// ??0Rva001FC3BF@@QAE@ABV0@@Z
// partial score=0.8 date=2026-10-05
// ??0Rva001FC3BF@@QAE@ABV0@@Z @0x001FC3BF 69B chain head
// partial score=0.80 date=2026-10-05 model=muse-spark t=22
// Eight-link homogeneous EH copy-construction chain 0x001FC3BF -> 0x001FC19B
// -> 0x001FBEF2 -> 0x001FBB9F -> 0x001FBA00 -> 0x001FB864 -> 0x001FA631 ->
// 0x001F9C73 (69B each). v1 op= reading: 41/69, guard exact, frame absent.
// v2 copy-ctor reading (this file, COMPILES): frame reproduced byte-exact
// through +0xB, guard window exact, both calls resolve to correct targets,
// epilog exact; residual = member auto default-construction call (unresolved
// ??0Next@@QAE@XZ) + consequent order swap, 82B vs 69B. Union suppression
// refused (C2620/C2621). Next lever: init-list copy-construct of the +4
// member with body base-assign CANNOT match (init precedes body, retail runs
// base call first); needs a construct that builds the member in-body without
// auto-construction or placement branch. Full evidence in
// seat-8-continue-r1.json (Titan normal-restart).
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva001F41AFHelper {
	virtual void f0();
	virtual void *clone();
};

class Rva001F41AF
{
public:
	Rva001F41AFHelper *m_ptr;
	Rva001F41AF &operator=(const Rva001F41AF &other);
};

class Rva001F8C5B
{
public:
	Rva001F8C5B();
	Rva001F8C5B(const _STL::vector<void *> &src);
	~Rva001F8C5B();
};

struct Rva001F9C73Src {
	Rva001F41AF base;
	_STL::vector<void *> vec;
};

class Rva001F9C73 : public Rva001F41AF
{
public:
	Rva001F9C73();
	Rva001F9C73(const Rva001F9C73Src &src);
private:
	const Rva001F8C5B m_v;
};

class Rva001FA631 : public Rva001F41AF
{
public:
	Rva001FA631();
	Rva001FA631(const Rva001FA631 &src);
private:
	Rva001F9C73 m_next;
};

class Rva001FB864 : public Rva001F41AF
{
public:
	Rva001FB864();
	Rva001FB864(const Rva001FB864 &src);
private:
	Rva001FA631 m_next;
};

class Rva001FBA00 : public Rva001F41AF
{
public:
	Rva001FBA00();
	Rva001FBA00(const Rva001FBA00 &src);
private:
	Rva001FB864 m_next;
};

class Rva001FBB9F : public Rva001F41AF
{
public:
	Rva001FBB9F();
	Rva001FBB9F(const Rva001FBB9F &src);
private:
	Rva001FBA00 m_next;
};

class Rva001FBEF2 : public Rva001F41AF
{
public:
	Rva001FBEF2();
	Rva001FBEF2(const Rva001FBEF2 &src);
private:
	Rva001FBB9F m_next;
};

class Rva001FC19B : public Rva001F41AF
{
public:
	Rva001FC19B();
	Rva001FC19B(const Rva001FC19B &src);
private:
	Rva001FBEF2 m_next;
};

class Rva001FC3BF : public Rva001F41AF
{
public:
	Rva001FC3BF();
	Rva001FC3BF(const Rva001FC3BF &src);
private:
	Rva001FC19B m_next;
};

// ??0Rva001FC3BF@@QAE@ABV0@@Z @0x001FC3BF 69B (compiled 82B, see header)
Rva001FC3BF::Rva001FC3BF(const Rva001FC3BF &src)
{
	Rva001F41AF::operator=(src);
	const void *s = &src;
	const Rva001FC19B *p = (const Rva001FC19B *)(s ? (const char *)s + 4 : 0);
	m_next.Rva001FC19B::Rva001FC19B(*p);
}

// ??0Rva001FC19B@@QAE@ABV0@@Z @0x001FC19B 69B
Rva001FC19B::Rva001FC19B(const Rva001FC19B &src)
{
	Rva001F41AF::operator=(src);
	const void *s = &src;
	const Rva001FBEF2 *p = (const Rva001FBEF2 *)(s ? (const char *)s + 4 : 0);
	m_next.Rva001FBEF2::Rva001FBEF2(*p);
}

// ??0Rva001FBEF2@@QAE@ABV0@@Z @0x001FBEF2 69B
Rva001FBEF2::Rva001FBEF2(const Rva001FBEF2 &src)
{
	Rva001F41AF::operator=(src);
	const void *s = &src;
	const Rva001FBB9F *p = (const Rva001FBB9F *)(s ? (const char *)s + 4 : 0);
	m_next.Rva001FBB9F::Rva001FBB9F(*p);
}

// ??0Rva001FBB9F@@QAE@ABV0@@Z @0x001FBB9F 69B
Rva001FBB9F::Rva001FBB9F(const Rva001FBB9F &src)
{
	Rva001F41AF::operator=(src);
	const void *s = &src;
	const Rva001FBA00 *p = (const Rva001FBA00 *)(s ? (const char *)s + 4 : 0);
	m_next.Rva001FBA00::Rva001FBA00(*p);
}

// ??0Rva001FBA00@@QAE@ABV0@@Z @0x001FBA00 69B
Rva001FBA00::Rva001FBA00(const Rva001FBA00 &src)
{
	Rva001F41AF::operator=(src);
	const void *s = &src;
	const Rva001FB864 *p = (const Rva001FB864 *)(s ? (const char *)s + 4 : 0);
	m_next.Rva001FB864::Rva001FB864(*p);
}

// ??0Rva001FB864@@QAE@ABV0@@Z @0x001FB864 69B
Rva001FB864::Rva001FB864(const Rva001FB864 &src)
{
	Rva001F41AF::operator=(src);
	const void *s = &src;
	const Rva001FA631 *p = (const Rva001FA631 *)(s ? (const char *)s + 4 : 0);
	m_next.Rva001FA631::Rva001FA631(*p);
}

// ??0Rva001FA631@@QAE@ABV0@@Z @0x001FA631 69B
Rva001FA631::Rva001FA631(const Rva001FA631 &src)
{
	Rva001F41AF::operator=(src);
	const void *s = &src;
	const Rva001F9C73Src *p = (const Rva001F9C73Src *)(s ? (const char *)s + 4 : 0);
	m_next.Rva001F9C73::Rva001F9C73(*p);
}

// ??0Rva001F9C73@@QAE@ABURva001F9C73Src@@@Z @0x001F9C73 69B
Rva001F9C73::Rva001F9C73(const Rva001F9C73Src &src)
{
	Rva001F41AF::operator=(src.base);
	const void *s = &src;
	const _STL::vector<void *> *vp = (const _STL::vector<void *> *)(s ? (const char *)s + 4 : 0);
	new (const_cast<Rva001F8C5B *>(&m_v)) Rva001F8C5B(*vp);
}
