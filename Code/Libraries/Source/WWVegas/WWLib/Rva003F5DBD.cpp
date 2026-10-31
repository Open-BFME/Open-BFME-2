// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva003F5DBD@Rva003F5DBD@@QAEXPAXH@Z @0x003F5DBD 130B: element science push_back via rowed 0x002E01C6 plus inner vector loop via rowed 0x002B7250 plus erase via rowed 0x003F5C72; callers at 0x003F5E7A; class from this+4 vector and this+10 ScienceType vector
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

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> vector<void *, allocator<void *> > & vector<void *, allocator<void *> >::operator=(vector<void *, allocator<void *> > const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}
// stlport_vector_voidptr_alloc.cpp owns vector<void*>::operator= (0x00027BA0);
// call it rather than emit this unit's copy for Rva003F610FElement's assignment.
namespace _STL { template <> vector<void *, allocator<void *> > &vector<void *, allocator<void *> >::operator=(vector<void *, allocator<void *> > const &); }

enum ScienceType
{
	SCIENCE_0 = 0
};

// Retail calls the shared push_back at 0x002E01C6; keep its growth helper there.
namespace _STL { template <> void vector<ScienceType>::push_back(const ScienceType &); }

class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

struct SciSrc
{
	char m_pad00[0x14];
	ScienceType m_14;
};

struct Rva003F610FElement
{
	void *m_00;
	_STL::vector<void *> m_04;
	char m_pad10[0x30 - 4 - 12];
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> Rva003F610FElement * vector<Rva003F610FElement,allocator<Rva003F610FElement> >::erase(Rva003F610FElement *); }

class Rva003F5DBD
{
	char m_pad00[4];
	_STL::vector<Rva003F610FElement> m_04;
	_STL::vector<ScienceType> m_10;
public:
	void rva003F5DBD(void *a, int idx);
	void rva003F5E3F(void *a, void *key);
};

void Rva003F5DBD::rva003F5DBD(void *a, int idx)
{
	Rva003F610FElement &element = m_04[idx];
	if (element.m_00 != 0)
	{
		ScienceType m_scienceType = ((SciSrc *)element.m_00)->m_14;
		m_10.push_back(m_scienceType);
	}
	int cnt = (int)element.m_04.size();
	CreateAHeroData *createAHeroData;
	int i = 0;
	if (i < cnt)
	{
		createAHeroData = a ? (CreateAHeroData *)((char *)a + 4) : 0;
		for (; i < cnt; ++i)
		{
			void *p = element.m_04[i];
			((Rva002B7250 *)((char *)p + 8))->rva002B7250(createAHeroData);
		}
	}
	m_04.erase(m_04.begin() + idx);
}

void Rva003F5DBD::rva003F5E3F(void *a, void *key)
{
	for (unsigned int i = 0; i < m_04.size(); ++i)
	{
		if (m_04[i].m_00 == key)
		{
			rva003F5DBD(a, (int)i);
			return;
		}
	}
}
