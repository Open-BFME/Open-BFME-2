// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?secondarySetCount@Rva005C6D4D@@QAEXH@Z, retail 0x005C6F9D (144 bytes):
// Rva005C6D4D::secondarySetCount(int). Evidence: pinned name, 2 callers
// including Rva0053ED1A::rva0053EFC7, prev/next TUs, RB_tree clear at
// +0x30 (rowed 0x005C6B83), vtable slots 2/3 per-iteration plus
// pin-only rva005C6D9C/rva005C674A tail calls. Layout from retail
// immediates: count+8, flag+4, -500 at +0xC/+0x10, zeros to +0x24,
// 0.0f at +0x28/+0x2C, tree at +0x30 (same as Rva005C6C7B dtor view).
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include "ascii_string.h"

struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; };
struct Rva0027EA49
{
	~Rva0027EA49();
	int m_00;
	TargetRef00217D4C *m_04;
};
bool operator<(const Rva0027EA49 &a, const Rva0027EA49 &b);
typedef _STL::_Rb_tree<Rva0027EA49, Rva0027EA49, _STL::_Identity<Rva0027EA49>, _STL::less<Rva0027EA49>, _STL::allocator<Rva0027EA49> > Rva0027EA49Tree;

class Rva005C674A
{
public:
	void rva005C674A();
};

class Rva005C6D4D
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2(int a, void *b, void *c);
	virtual void v3(int a, int b);
	void rva005C6D9C();
	void secondarySetCount(int count);
	void rva005C674AHelper();
private:
	char m_04flag; // +0x4 (byte 1)
	char m_pad05[3];
	int m_08; // +0x8 count
	int m_0C; // +0xC -500
	int m_10; // +0x10 -500
	int m_14; // +0x14 0
	int m_18; // +0x18 0
	int m_1C; // +0x1C 0
	int m_20; // +0x20 0
	int m_24; // +0x24 0
	float m_28; // +0x28 0.0f
	float m_2C; // +0x2C 0.0f
	Rva0027EA49Tree m_30; // +0x30
};

struct TwoInts
{
	int a;
	int b;
};

void Rva005C6D4D::secondarySetCount(int count)
{
	m_08 = count;
	m_04flag = 1;
	m_10 = -500;
	m_0C = -500;
	m_18 = 0;
	m_14 = 0;
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0.0f;
	m_2C = 0.0f;
	m_30.clear();
	for (int i = 0; i < m_08; ++i)
	{
		TwoInts zero;
		zero.a = 0;
		zero.b = 0;
		TwoInts four;
		four.a = 4;
		four.b = 4;
		v2(i, &zero, &four);
		v3(i, 0);
	}
	rva005C6D9C();
	((Rva005C674A *)this)->rva005C674A();
}
