// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <hash_map>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }



#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../../reference/shims/bfme2_ascii/unicode_string.h"
// rts::hash and rts::equal_to: the registered view (reverse/canonical_classes.csv).
#include "../../../../GameEngine/Source/GameLogic/AI/RtsHashView.h"
// MilesAudioManager's file-text map (m_fileText at +0x9E8), declared as MilesAudioManager.cpp declares it.
typedef _STL::hash_map<AsciiString, UnicodeString,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > MilesFileTextMap;
typedef _STL::hashtable<_STL::pair<AsciiString const, UnicodeString>, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<_STL::pair<AsciiString const, UnicodeString> >, rts::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<AsciiString const, UnicodeString> > > MilesFileTextTable;
// Its clear is retail 0x00057FC1, rowed in MilesAudioManager.cpp where m_fileText.clear() and the map's
// destructor instantiate it; declared only here.
namespace _STL { template<> void MilesFileTextTable::clear(); }

// 0x00058A81 (5B), unreferenced in retail: the out-of-line hash_map::clear of the same map, a tail jump into the
// hashtable clear 0x00057FC1.
template void MilesFileTextMap::clear(void);
