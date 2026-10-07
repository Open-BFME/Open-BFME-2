// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// Wave-3 shape-family batch: twelve 45-byte STLport _Construct<T, T>
// placement-copy helpers with the shape
//   mov call push mov mov and test je push call mov mov leave ret
// (mov eax,<frame>; call __EH_prolog 0x00629188; null-guarded placement-new
// copy through the element copy ctor under an EH frame). Same recipe as
// StlportConstructFamily.cpp: each element is an address-named placeholder
// declared here only with the copy constructor the retail body calls, which
// is pinned at that address. No element layout is claimed.
//
//   _Construct  element                 copy ctor
//   0x0014F647  Rva0014F647Element       0x0014F4E3
//   0x002B91ED  Rva002B91EDElement       0x002B90D6
//   0x002BAE2A  Rva002BAE2AElement       0x002B9247 (rowed vector copy ctor)
//   0x002E160F  Rva002E160FElement       0x002E134C
//   0x00423648  Rva00423648Element       0x004220CD
//   0x004C734D  Rva004C734DElement       0x004C7330
//   0x004F868A  Rva004F868AElement       0x004F802C
//   0x00502082  Rva00502082Element       0x00501DD4
//   0x00502667  Rva00502667Element       0x005020AF
//   0x00502C53  Rva00502C53Element       0x00502909
//   0x00557C90  Rva00557C90Element       0x005564EB
//   0x00600F9C  Rva00600F9CElement       0x00600F76
//
// Evidence is per-row in reverse/functions.csv. Retail callers of each body
// are unrowed vector-helper sites (uninitialized copy/fill and node-factory
// neighbours); e.g. 0x002B91ED is called from 0x002B922D/0x002BADC0/0x002BBCD0
// and 0x00502667 from the 0x005028E7 node factory. 0x002BAE2A's callee is the
// rowed vector<Rva002B72C9> copy ctor; the element stays an address-named
// placeholder (its copy ctor is pinned at 0x002B9247) and no layout beyond
// that of the sibling placeholders is claimed.
#include <memory>

struct Rva0014F647Element
{
	int a;
	Rva0014F647Element(const Rva0014F647Element &that);
};

struct Rva002B91EDElement
{
	int a;
	Rva002B91EDElement(const Rva002B91EDElement &that);
};

struct Rva002E160FElement
{
	int a;
	Rva002E160FElement(const Rva002E160FElement &that);
};

struct Rva00423648Element
{
	int a;
	Rva00423648Element(const Rva00423648Element &that);
};

struct Rva004C734DElement
{
	int a;
	Rva004C734DElement(const Rva004C734DElement &that);
};

struct Rva004F868AElement
{
	int a;
	Rva004F868AElement(const Rva004F868AElement &that);
};

struct Rva00502082Element
{
	int a;
	Rva00502082Element(const Rva00502082Element &that);
};

struct Rva00502667Element
{
	int a;
	Rva00502667Element(const Rva00502667Element &that);
};

struct Rva00502C53Element
{
	int a;
	Rva00502C53Element(const Rva00502C53Element &that);
};

struct Rva00557C90Element
{
	int a;
	Rva00557C90Element(const Rva00557C90Element &that);
};

struct Rva00600F9CElement
{
	int a;
	Rva00600F9CElement(const Rva00600F9CElement &that);
};

struct Rva002BAE2AElement
{
	int a;
	Rva002BAE2AElement(const Rva002BAE2AElement &that);
};

template void _STL::_Construct<Rva0014F647Element, Rva0014F647Element>(Rva0014F647Element *, const Rva0014F647Element &);
template void _STL::_Construct<Rva002B91EDElement, Rva002B91EDElement>(Rva002B91EDElement *, const Rva002B91EDElement &);
template void _STL::_Construct<Rva002E160FElement, Rva002E160FElement>(Rva002E160FElement *, const Rva002E160FElement &);
template void _STL::_Construct<Rva00423648Element, Rva00423648Element>(Rva00423648Element *, const Rva00423648Element &);
template void _STL::_Construct<Rva004C734DElement, Rva004C734DElement>(Rva004C734DElement *, const Rva004C734DElement &);
template void _STL::_Construct<Rva004F868AElement, Rva004F868AElement>(Rva004F868AElement *, const Rva004F868AElement &);
template void _STL::_Construct<Rva00502082Element, Rva00502082Element>(Rva00502082Element *, const Rva00502082Element &);
template void _STL::_Construct<Rva00502667Element, Rva00502667Element>(Rva00502667Element *, const Rva00502667Element &);
template void _STL::_Construct<Rva00502C53Element, Rva00502C53Element>(Rva00502C53Element *, const Rva00502C53Element &);
template void _STL::_Construct<Rva00557C90Element, Rva00557C90Element>(Rva00557C90Element *, const Rva00557C90Element &);
template void _STL::_Construct<Rva002BAE2AElement, Rva002BAE2AElement>(Rva002BAE2AElement *, const Rva002BAE2AElement &);
template void _STL::_Construct<Rva00600F9CElement, Rva00600F9CElement>(Rva00600F9CElement *, const Rva00600F9CElement &);

#include <deque>

struct BfmeOpaqueOwnedRecord1432
{
	~BfmeOpaqueOwnedRecord1432();
};

struct BfmeOpaqueOwnedRecord1408
{
	~BfmeOpaqueOwnedRecord1408();
};

class Rva00557CBD
{
public:
	void rva00557CBD();
};

void Rva00557CBD::rva00557CBD()
{
	((_STL::deque<BfmeOpaqueOwnedRecord1432> *)this)->~deque();
}

class Rva00557CC2
{
public:
	void rva00557CC2();
};

void Rva00557CC2::rva00557CC2()
{
	((_STL::deque<BfmeOpaqueOwnedRecord1408> *)this)->~deque();
}

class Rva005562DD
{
public:
	~Rva005562DD();
};

class Rva00557CC7
{
public:
	void rva00557CC7();
};

void Rva00557CC7::rva00557CC7()
{
	((Rva005562DD *)this)->~Rva005562DD();
}
