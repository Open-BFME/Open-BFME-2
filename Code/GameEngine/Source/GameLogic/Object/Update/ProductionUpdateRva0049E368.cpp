// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0049E368@ProductionUpdate@@QAEXXZ @0x0049E368 77B
// ProductionUpdate queue clear: per-element ThingTemplate lookup via rowed
// rva002D06CA 0x002D06CA through g_009FF000 plus virtual at +0x34 on the
// +0x20 iface with (template, 1), then vector<AsciiString> erase-begin-end
// via rowed 0x0002CCFC. Evidence: prev row ProductionUpdate deleting dtor
// 0x0049E34C same TU dir, vector element stride 4 with erase(first,last)
// row name, caller 0x0049E41F in 0x0049E3B5.
#include "ascii_string.h"
#include <vector>

class ThingTemplate;
class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &key);
};

extern class ThingFactory *TheThingFactory;

// Bind the erase-begin-end call to the rowed 0x0002CCFC instead of emitting a
// second copy of the header's inline definition.
namespace _STL
{
template <> AsciiString *vector<AsciiString, allocator<AsciiString> >::erase(AsciiString *, AsciiString *);
}

// The canonical vector keeps its three pointers protected; read them through a
// layout view of the same 12 bytes.
struct BfmeAsciiVecView
{
	AsciiString *m_start;
	AsciiString *m_finish;
	AsciiString *m_end;
};

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
	for (AsciiString *asciiString = ((BfmeAsciiVecView *)&m_vec130)->m_start; asciiString != ((BfmeAsciiVecView *)&m_vec130)->m_finish; ++asciiString)
	{
		void *tmpl = (void *)TheThingFactory->findTemplate(*asciiString);
		m_iface20.slot34(tmpl, 1);
	}
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > &v = m_vec130;
	v.erase(((BfmeAsciiVecView *)&v)->m_start, ((BfmeAsciiVecView *)&v)->m_finish);
}
