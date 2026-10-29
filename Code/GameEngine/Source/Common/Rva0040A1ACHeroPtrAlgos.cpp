// cl: /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport46
// STLport 4.5.3 pointer-range algorithms over the CreateAHeroData* vector
// (see Rva0040A3F9Find.cpp): for_each releasing every element through
// TheHeroManager (rowed 0x21929D), and the 4x unrolled random-access
// __find_if with the two by-value comparison functors rowed at 0x40A16E and
// 0x40A187 (one resp. two dwords of state). Evidence: target bytes of
// 0x40A1AC/0x40A1D7/0x40A283; functor spelling is donor inference.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <algorithm>
#include <vector>

class CreateAHeroData;

// Retail inlines the pointer copy helper and has no out-of-line copy; another
// unit's copy is first in link order, so dllimport keeps this one inline-only.
namespace _STL {
template <> __declspec(dllimport) __forceinline
CreateAHeroData **__copy_ptrs(CreateAHeroData **__first, CreateAHeroData **__last, CreateAHeroData **__result, const __true_type &)
{ return (CreateAHeroData **)__copy_trivial(__first, __last, __result); }
}

class Rva00219251
{
public:
	void rva0021929D(CreateAHeroData **data);
};

// 0x009FE344 under its data-ledger primary name (defined in CreateAHero.cpp).
class CreateAHeroManager;
extern CreateAHeroManager *TheCreateAHeroManager;

class Rva0040A16E
{
public:
	Rva0040A16E(int value) : m_val0(value) {}
	bool rva0040A16E(const void *arg) const;
	bool operator()(CreateAHeroData *p) const { return rva0040A16E(p); }
private:
	int m_val0;
};

class Rva0040A187
{
public:
	Rva0040A187(int major, int minor) : m_val0(major), m_val4(minor) {}
	bool rva0040A187(const void *arg) const;
	bool operator()(CreateAHeroData *p) const { return rva0040A187(p); }
private:
	int m_val0;
	int m_val4;
};

struct Rva0040A1ACRelease
{
	void operator()(CreateAHeroData *p) const { ((Rva00219251 *)TheCreateAHeroManager)->rva0021929D(&p); }
};

template Rva0040A1ACRelease _STL::for_each<CreateAHeroData **, Rva0040A1ACRelease>(CreateAHeroData **, CreateAHeroData **, Rva0040A1ACRelease);
template CreateAHeroData **_STL::__find_if<CreateAHeroData **, Rva0040A16E>(CreateAHeroData **, CreateAHeroData **, Rva0040A16E, const _STL::random_access_iterator_tag &);
template CreateAHeroData **_STL::__find_if<CreateAHeroData **, Rva0040A187>(CreateAHeroData **, CreateAHeroData **, Rva0040A187, const _STL::random_access_iterator_tag &);
template CreateAHeroData **_STL::find_if<CreateAHeroData **, Rva0040A16E>(CreateAHeroData **, CreateAHeroData **, Rva0040A16E);
template CreateAHeroData **_STL::find_if<CreateAHeroData **, Rva0040A187>(CreateAHeroData **, CreateAHeroData **, Rva0040A187);

// Native 0x0040A59B..0x0040A5CF (52 bytes): clears the hero-data list: when
// it owns its elements (+0xC) each is released through the for_each above
// (the empty functor value-initialised, hence retail's STOSB), then the range
// is erased (STLport pointer-vector erase folded at 0x0031BD55).
class Rva0040A59B
{
public:
	void rva0040A59B();
private:
	_STL::vector<CreateAHeroData *> m_data;	// +0x00
	bool m_ownsData;			// +0x0C
};

void Rva0040A59B::rva0040A59B()
{
	if (m_ownsData)
		_STL::for_each(m_data.begin(), m_data.end(), Rva0040A1ACRelease());
	m_data.erase(m_data.begin(), m_data.end());
}

// Native 0x0040A3B1..0x0040A3D2 (33 bytes, RET4, no caller left in retail):
// the hero-data list's lookup through the one-word functor: find_if
// (0x0040A34B, above) over the +0/+4 range with the functor built in its
// argument slot from the key, null when absent, else the element.
class Rva0040A3F9
{
public:
	CreateAHeroData *rva0040A3B1(int key);
private:
	CreateAHeroData **m_begin;	// +0x00
	CreateAHeroData **m_end;	// +0x04
};

CreateAHeroData *Rva0040A3F9::rva0040A3B1(int key)
{
	CreateAHeroData **end = m_end;
	CreateAHeroData **found = _STL::find_if(m_begin, end, Rva0040A16E(key));
	if (found == end)
		return 0;
	return *found;
}
