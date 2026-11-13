// cl: /O1 /G7 /MD /EHs /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Gy
// stlport
//
// ?iniParseScienceVectorVector@@YAXPAVINI@@PAX1PBX@Z @0x0033A310 222B: INI
// field parser for a vector of science vectors ("A B OR C D"): the store is
// resized to one empty inner vector, each token is scanned as a science and
// appended to the current inner vector, "OR" opens a new inner vector (an
// empty current one ends the list), "None" clears the current one, and an
// empty current vector at the end clears the whole store.
//
// Shape evidence (see Rva0033A2E9Resize.cpp): cl drops the dead allocator
// temporary of SciVec() only when the _Vector_base<ScienceType> constructor
// is visible, so it is instantiated here ahead of the parser. The outer
// vector is a hand-written view (retail passes elements by value); its
// push_back is the rowed 12-byte-element push_back 0x0033A23A and erase the
// rowed 0x00339E80. The new current vector comes from end() - 1.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport, and <stddef.h> with it so
// their _errno declarations agree.
#define _CRTIMP
#include <stddef.h>
#include <stdlib.h>
#undef _CRTIMP

#include <vector>
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

enum ScienceType { SCIENCE_INVALID = -1 };
struct Rva0033A23AElement { char words[12]; };
struct DynamicPortalLink;

#include "../../Include/Common/Rva00339E80.h"

typedef _STL::vector<ScienceType, _STL::allocator<ScienceType> > SciVec;
typedef _STL::vector<Rva0033A23AElement, _STL::allocator<Rva0033A23AElement> > Rva0033A23AVector;

template _STL::_Vector_base<ScienceType, _STL::allocator<ScienceType> >::_Vector_base(const _STL::allocator<ScienceType> &);
template <> void Rva0033A23AVector::push_back(const Rva0033A23AElement &);

// Retail calls the rowed out-of-line push_back (0x002E01C6) and range erase
// (0x00532803); this unit's own instantiations (and push_back's guarded
// overflow path) lost to retail's copies at link time. Retail has no copy of
// ~_Vector_base<ScienceType>: every use is inline.
namespace _STL {
template <> ScienceType *SciVec::erase(ScienceType *, ScienceType *);
template <> void SciVec::push_back(const ScienceType &);
template <> __declspec(dllimport) __forceinline
_Vector_base<ScienceType, allocator<ScienceType> >::~_Vector_base()
{
	if (_M_start != 0)
		_M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start);
}
}

namespace _STL {
template <>
class vector<SciVec, allocator<SciVec> >
{
public:
	void resize(unsigned int n, SciVec value);
	void resize(unsigned int n);
	void push_back(const SciVec &sciVec) { ((Rva0033A23AVector *)this)->push_back((const Rva0033A23AElement &)sciVec); }
	SciVec *erase(SciVec *first, SciVec *last)
	{
		return (SciVec *)((Rva00339E80 *)this)->rva00339E80((DynamicPortalLink *)first, (DynamicPortalLink *)last);
	}
	SciVec *begin() { return m_start; }
	SciVec *end() { return m_finish; }
	bool empty() { return m_start == m_finish; }
	void clear() { erase(begin(), end()); }

private:
	SciVec *m_start;
	SciVec *m_finish;
	SciVec *m_end_of_storage;
};
}

typedef _STL::vector<SciVec, _STL::allocator<SciVec> > SciVecVec;

#include "../../Include/Common/INI/INI.h"

void iniParseScienceVectorVector(INI *ini, void *, void *store, const void *)
{
	SciVecVec *asv = (SciVecVec *)store;
	asv->resize(1);
	SciVec *vec = asv->end() - 1;
	for (const char *token = ini->getNextTokenOrNull(); token; token = ini->getNextTokenOrNull())
	{
		if (_strcmpi(token, "None") == 0)
		{
			vec->clear();
			break;
		}
		if (_strcmpi(token, "OR") == 0)
		{
			if (vec->empty())
				break;
			asv->push_back(SciVec());
			vec = asv->end() - 1;
		}
		else
			vec->push_back(INI::scanScience(token));
	}
	if (vec->empty())
		asv->clear();
}
