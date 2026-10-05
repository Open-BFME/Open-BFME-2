// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva005DCE72@Rva005DCE72@@QAEXABVAsciiString@@PAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z, retail 0x005DCE72, 59 bytes.
// Loop over ModuleData* array at this+4..this+8; for each element compare
// AsciiString at +0xC with arg1 via rowed StringBase::compare 0x000069D6,
// on match push the element into vector arg2 via rowed push_back 0x004DFCB0.
// Evidence: callees rowed, caller 0x005AD99C passes through. Honest address name.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
#include "ascii_string.h"

class Rva005DCEB7Arg
{
public:
	virtual ~Rva005DCEB7Arg();
	virtual bool f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual void f7();
	virtual void f8();
	virtual void f9();
	virtual void f10(void *p);
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual void f17();
	virtual void f18();
	virtual void f19();
	virtual void f20();
	virtual void f21();
	virtual void f22();
	virtual void f23();
	virtual void f24();
	virtual void f25();
	virtual void f26();
	virtual void f27();
	virtual void f28();
	virtual void f29();
	virtual void f30(void *p);
	virtual void f31(void *p);
	virtual void f32();
	virtual void f33();
	virtual void f34();
	virtual void f35();
	virtual void f36(void *p);
};

class ModuleData
{
public:
	virtual ~ModuleData();
	virtual void m1();
	virtual void m2();
	virtual void m3();
	virtual void m4();
	virtual void m5();
	virtual void m6(int a, int b);
	virtual void m7();
	virtual void m8();
	virtual void m9();
	virtual void m10();
	virtual void m11();
	virtual void m12(Rva005DCEB7Arg *p, int v);
	char m_pad4[8]; // +4..+11 keeps m_name at +0xC with vtable at +0
	AsciiString m_name; // +0xC
};

class Rva00573E7C
{
public:
	Rva00573E7C();
	virtual ~Rva00573E7C();
private:
	char m_pad[0x60 - 4];
};

class Rva005DCE72
{
public:
	void rva005DCE72(const AsciiString &name, _STL::vector<const ModuleData *> *out);
	void rva005DCEB7(Rva005DCEB7Arg *p);
private:
	char m_pad0[4];
	const ModuleData **m_begin; // +0x4
	const ModuleData **m_end; // +0x8
	const ModuleData **m_capacity; // +0xC vector capacity keeps push_back rowed
	int m_10; // +0x10
	int m_14; // +0x14
};

void Rva005DCE72::rva005DCE72(const AsciiString &name, _STL::vector<const ModuleData *> *out)
{
	for (const ModuleData **it = m_begin; it != m_end; ++it)
	{
		const ModuleData *md = *it;
		if (md->m_name.compare(name) == 0)
			out->push_back(md);
	}
}

// ?rva005DCEB7@Rva005DCE72@@QAEXPAVRva005DCEB7Arg@@@Z retail 0x005DCEB7 274B
// Chain from 0x00573E7C ctor row; prev 0x005DCE72 same TU/class; vector at +4
// holds ModuleData* rowed push_back 0x004DFCB0; new 0x60 via rowed ??2 0x0002FDA0.
// Evidence: virtual slots 0x28/0x90/0x7c/0x78/0x4 on arg; slots 0x30/0x18 on elements.
void Rva005DCE72::rva005DCEB7(Rva005DCEB7Arg *p)
{
	struct TwoBytes { unsigned char a; unsigned char b; };
	TwoBytes tb;
	tb.a = 1;
	tb.b = 2;
	p->f10(&tb);
	p->f36(this);
	p->f36(&m_pad0[1]);
	p->f31(&m_10);
	if (tb.b >= 2)
		p->f36(&m_pad0[2]);
	const ModuleData ***base = (const ModuleData ***)&m_begin;
	unsigned int n = (unsigned int)(base[1] - base[0]);
	p->f30(&n);
	if (!p->f1())
		goto second;
	unsigned int i = 0;
	if (n <= 0)
		goto second;
	do
	{
		Rva00573E7C *nn = new Rva00573E7C;
		const ModuleData *tmp = (const ModuleData *)nn;
		((_STL::vector<const ModuleData *> *)base)->push_back(tmp);
		++i;
	} while (i < n);
second:
	const ModuleData **end = m_end;
	for (const ModuleData **it = m_begin; it != end; ++it)
	{
		((ModuleData *)*it)->m12(p, m_14);
		if (!p->f1())
			continue;
		if (m_pad0[1] == 0)
			continue;
		if (*(int *)((char *)*it + 0x10) != 0)
			continue;
		((ModuleData *)*it)->m6(m_14, 1);
	}
}
