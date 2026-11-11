// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 set/map operator= (`_M_t = __x._M_t; return *this;`), the
// two 18-byte container assignments at retail 0x00389A28 and 0x00389A3A.
// Each calls the rowed tree assignment it wraps: 0x00387568 (the opaque
// eight-byte stats-set tree, stlport_modulefactory_map_copy.cpp) and
// 0x003876A4 (the uchar/int map tree, same file). The element types keep
// those rows' address-derived and stand-in spellings; the application's
// container identities are not established. The tree assignments are
// declared as explicit specializations so this unit emits no copy of them.
#include <set>
#include <map>

#include "../../../../GameEngine/Include/Common/Rva00387568Element.h"

namespace _STL {
template <> _Rb_tree<Rva00387568Element, Rva00387568Element,
	_Identity<Rva00387568Element>, less<Rva00387568Element>,
	allocator<Rva00387568Element> > &
_Rb_tree<Rva00387568Element, Rva00387568Element,
	_Identity<Rva00387568Element>, less<Rva00387568Element>,
	allocator<Rva00387568Element> >::operator=(const _Rb_tree &other);

template <> _Rb_tree<unsigned char, pair<const unsigned char, int>,
	_Select1st<pair<const unsigned char, int> >, less<unsigned char>,
	allocator<pair<const unsigned char, int> > > &
_Rb_tree<unsigned char, pair<const unsigned char, int>,
	_Select1st<pair<const unsigned char, int> >, less<unsigned char>,
	allocator<pair<const unsigned char, int> > >::operator=(const _Rb_tree &other);
}

template _STL::set<Rva00387568Element> &
_STL::set<Rva00387568Element>::operator=(const _STL::set<Rva00387568Element> &);
template _STL::map<unsigned char, int> &
_STL::map<unsigned char, int>::operator=(const _STL::map<unsigned char, int> &);
