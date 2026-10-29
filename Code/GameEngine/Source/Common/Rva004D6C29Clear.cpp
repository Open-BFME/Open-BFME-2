// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva004D6C29@Rva004D6C29@@QAEXXZ @0x004D6C29 (31B):
// Two-vector clear: erase of ScienceType vector at +0x04 via rowed erase
// @0x00532803 then erase of void* vector at +0x10 via rowed erase @0x0031BD55.
// Frameless push esi + reuse via esi (two members). Callers 0x002ACA86,
// 0x002ACAFB, 0x002ACC53 fetch the +0x708 slot array element and clear it;
// sibling add wrapper @0x004D6C9C pushes into the same +0x04 vector of the
// 0x1c object. Honest-address name: owner unproven.

enum ScienceType
{
	SCIENCE_INVALID = 0
};

#include <vector>

namespace _STL
{
// Bind both range erases to their rowed workers.
template <> ScienceType *vector<ScienceType, allocator<ScienceType> >::erase(ScienceType *first, ScienceType *last);
template <> void **vector<void *, allocator<void *> >::erase(void **first, void **last);
}

class Rva004D6C29
{
public:
	void rva004D6C29();

private:
	char m_pad04[4];
	_STL::vector<ScienceType> m_vec04;
	_STL::vector<void *> m_vec10;
};

void Rva004D6C29::rva004D6C29()
{
	_STL::vector<ScienceType> *vec04 = &m_vec04;
	vec04->erase(vec04->begin(), vec04->end());
	_STL::vector<void *> *vec10 = &m_vec10;
	vec10->erase(vec10->begin(), vec10->end());
}
