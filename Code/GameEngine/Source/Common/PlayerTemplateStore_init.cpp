// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?init@PlayerTemplateStore@@UAEXXZ, retail 0x001FF223 (95 bytes): slot 1 of the
// subsystem vtable 0x007E1BB0 whose destructor is rowed in
// Rva001FDB55Dtor.cpp (vector of 0x1DC-byte Overridable records at +0x0C,
// the set at +0x18, the state word at +0x24). As Zero Hour's INI stores
// init: every record drops its INI overrides (Overridable::deleteOverrides
// 0x001E35ED), the vector is emptied (rowed erase 0x001FEFB9), the set is
// cleared (0x00072FE6) and the state returns to -1. Storage view: no
// constructor or destructor is defined here.
#include <vector>

class Overridable
{
public:
	Overridable *deleteOverrides();
};

struct BfmeObject476
{
	unsigned char m_bytes[0x1DC];
	Overridable *asOverridable() { return (Overridable *)this; }
};
// bfme link decl-only BfmeObject476
namespace _STL { template <> BfmeObject476 * vector<BfmeObject476, allocator<BfmeObject476> >::erase(BfmeObject476 *, BfmeObject476 *); }

class Rva00072FE6
{
public:
	~Rva00072FE6();
	void rva00072FE6();
};

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class PlayerTemplateStore : public SubsystemInterface
{
public:
	virtual void init();
private:
	_STL::vector<BfmeObject476> m_vec;	// +0x0C
	Rva00072FE6 m_set;			// +0x18
	unsigned char m_pad[0x24 - 0x19];
	int m_state24;				// +0x24
};

void PlayerTemplateStore::init()
{
	for (unsigned int i = 0; i < m_vec.size(); ++i)
		m_vec[i].asOverridable()->deleteOverrides();
	m_vec.clear();
	m_set.rva00072FE6();
	m_state24 = -1;
}
