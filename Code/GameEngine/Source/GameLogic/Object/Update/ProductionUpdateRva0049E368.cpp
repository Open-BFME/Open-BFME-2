// cl: /Ireference/shims/bfme2_ascii /MD
// stlport
// ?rva0049E368@ProductionUpdate@@QAEXXZ @0x0049E368 77B
// ProductionUpdate queue clear: per-element ThingTemplate lookup via rowed
// rva002D06CA 0x002D06CA through g_009FF000 plus virtual at +0x34 on the
// +0x20 iface with (template, 1), then vector<AsciiString> erase-begin-end
// via rowed 0x0002CCFC. Evidence: prev row ProductionUpdate deleting dtor
// 0x0049E34C same TU dir, vector element stride 4 with erase(first,last)
// row name, caller 0x0049E41F in 0x0049E3B5.
#include "ascii_string.h"

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern class ThingFactory *TheThingFactory;

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Alloc>
class vector
{
public:
	typedef Type *iterator;
	iterator erase(iterator first, iterator last);
	Type *m_start;
	Type *m_finish;
	Type *m_end;
};
}

class ProdIface20
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
	virtual void slot34(void *tmpl, int flag);
};

class ProductionUpdate
{
public:
	void rva0049E368();
private:
	unsigned char m_pad00[0x20];
	ProdIface20 m_iface20;
	unsigned char m_pad24[0x130 - 0x24];
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_vec130;
};

void ProductionUpdate::rva0049E368()
{
	for (AsciiString *p = m_vec130.m_start; p != m_vec130.m_finish; ++p)
	{
		void *tmpl = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(p);
		m_iface20.slot34(tmpl, 1);
	}
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > &v = m_vec130;
	v.erase(v.m_start, v.m_finish);
}
