// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003F5970@Rva003F5970@@QAE@HPBVModuleData@@@Z @0x003F5970 142B
// Evidence: caller 0x003F652E builds Pod48 temp via this; dtor Rva003F610FElement 0x003F535B; vectors ModuleData* + Pod104; base E16 via 0x00211E58
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

class ModuleData;

struct BfmeE16
{
	float x, y, z, w;
};

struct BfmePod104
{
	int a[26];
};

struct BfmeAssignRecord104
{
	int a[26];
};

class ModuleData
{
public:
	char _pad[0x78];
	BfmePod104 *m_p78;
};

struct Rva003F5970
{
	int m_00;
	_STL::vector<BfmeE16> m_04;
	_STL::vector<BfmeE16> m_10;
	int m_1C[5];
	Rva003F5970(int a, const ModuleData *b);
};

Rva003F5970::Rva003F5970(int a, const ModuleData *b)
	: m_00(a)
	, m_04(_STL::allocator<BfmeE16>())
	, m_10(_STL::allocator<BfmeE16>())
{
	m_1C[0] = a;
	m_1C[1] = 0;
	m_1C[2] = 0;
	m_1C[3] = 0;
	m_1C[4] = 0;
	((_STL::vector<const ModuleData *> *)&m_04)->reserve(4);
	const ModuleData *tmp = b;
	((_STL::vector<const ModuleData *> *)&m_04)->push_back(tmp);
	((_STL::vector<BfmeAssignRecord104> *)&m_10)->reserve(4);
	((_STL::vector<BfmePod104> *)&m_10)->push_back(*b->m_p78);
}
