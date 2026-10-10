// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva001FFA5A@Rva001FFA5A@@QAEXPAVCreateAHeroData@@@Z @0x001FFA5A 71B: push_back ModuleData vector at +0x18 via 0x004DFCB0 then flag +0xC then find 0x0020E873 plus voidptr erase 0x001FF51F over CreateAHeroData vector at +0xC. Evidence: callees rowed; caller 0x001FFF3A unclaimed; layout mirrors WeaponRva002CDB0E vectors at +0xC/+0x18.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include <algorithm>

class ModuleData;

class CreateAHeroData
{
public:
	char m_pad[0xC];
	int m_flag0C;
};

class Rva001FFA5A
{
public:
	void rva001FFA5A(CreateAHeroData *val);
private:
	char m_pad00[0xC];
	_STL::vector<CreateAHeroData *> m_vec0C;
	_STL::vector<const ModuleData *> m_vec18;
};

void Rva001FFA5A::rva001FFA5A(CreateAHeroData *val)
{
	if (val == 0)
		return;
	m_vec18.push_back(*(const ModuleData **)&val);
	val->m_flag0C = 1;
	CreateAHeroData **end = m_vec0C.end();
	CreateAHeroData **found = _STL::find(m_vec0C.begin(), end, val);
	if (found != end)
		((_STL::vector<void *> *)&m_vec0C)->erase((void **)found);
}
