// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG
// stlport
// ??0Rva00220B04@@QAE@H@Z, retail 0x00220B04 124B.
// Ctor with two vectors at +8/+0x14 plus int at +0x20: vtables at +0/+4,
// second vector resized to global LocomotorStore count. Callers 0x00220B80
// and 0x00220E30 pass 0. Evidence: rowed Vector_base 0x00211E58 twice,
// rowed Drawable resize 0x000E6D39, holder g_00DFE490.
#include <vector>

struct BfmeE16 { float x, y, z, w; };
class Drawable;

extern const void *const g_00BE6A68[];
extern const void *const g_00BE6A64[];
extern "C" char s_slot3E4first;
extern void *g_00DFE490;

_STLP_BEGIN_NAMESPACE
template <>
class vector<Drawable *, allocator<Drawable *> > : public _Vector_base<Drawable *, allocator<Drawable *> >
{
public:
	void resize(unsigned int n, Drawable *x);
};
_STLP_END_NAMESPACE

struct LocomotorStore12 { char d[12]; };
struct Pointed10 {
	char m_pad[16];
	LocomotorStore12 *m_begin;
	LocomotorStore12 *m_finish;
};

class EmptyBase220B04 {
public:
	EmptyBase220B04() {}
	~EmptyBase220B04();
};

struct Root220B04 {
	unsigned m_v0;
	unsigned m_v4;
	Root220B04()
	{
		*(volatile unsigned *)&m_v4 = (unsigned)&s_slot3E4first;
	}
};

struct Base220B04 : public Root220B04 {
	Base220B04()
	{
		m_v0 = (unsigned)g_00BE6A68;
		m_v4 = (unsigned)g_00BE6A64;
	}
};

class Rva00220B04 : public EmptyBase220B04, public Base220B04 {
public:
	Rva00220B04(int a);
private:
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec08;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec14raw;
	int m_20;
};

Rva00220B04::Rva00220B04(int a)
	: EmptyBase220B04(),
	  Base220B04(),
	  m_vec08(_STL::allocator<BfmeE16>()),
	  m_vec14raw(_STL::allocator<BfmeE16>())
{
	m_20 = a;
	Pointed10 *p = *(Pointed10 **)&g_00DFE490;
	int count = (int)(p->m_finish - p->m_begin);
	((_STL::vector<Drawable *, _STL::allocator<Drawable *> > *)&m_vec14raw)->resize((unsigned)count, (Drawable *)0);
}

// ?g_00DFE490@@3PAXA: matched references place it at VA 0xdfe490; also referenced as ?g_00DFE490@@3VRva00575674@@A.
void * g_00DFE490 = 0;
#pragma comment(linker, "/alternatename:?g_00DFE490@@3VRva00575674@@A=?g_00DFE490@@3PAXA")
