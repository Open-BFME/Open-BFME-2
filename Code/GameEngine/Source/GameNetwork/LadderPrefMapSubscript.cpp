// cl: /DNDEBUG /MD /EHsc /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/inputs/reference/shims/stringbaseunicode /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// ??A?$map@JVLadderPref@@...@QAEAAVLadderPref@@ABJ@Z retail 0x005E017A, 135 bytes.
// Ported from the Open-BFME-1 donor game/Libraries/Source/WWVegas/WWLib/
// stlport_map_long_ladderpref_operator.cpp (reference/open-bfme-1 @ 6583b3c1) with
// BFME 2 include paths. At /O1 it is a unique masked placement on unclaimed .text.
// The callees are this map's rowed pair constructor 0x005DFB7F and LadderPref
// destructor 0x005BA3C0, plus the pinned _M_lower_bound 0x00382A92 and insert
// 0x005DFFB6. Kept apart from stlport_map_long_ladderpref.cpp because
// retail's subscript builds its default LadderPref inline, and that unit's
// out-of-line constructor declaration would change the other bodies.

// The retail map subscript at 0x000ACC40 belongs to LadderPreferences' recent
// ladder map.  The callers pass a signed time_t key and use the returned
// LadderPref reference to fill a newly inserted record.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>
#include "../../Include/GameNetwork/LadderPref.h"
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

// Retail builds the default record inline and destroys it through LadderPref.
inline LadderPref::LadderPref() {}
inline LadderPref::~LadderPref() {}

typedef std::map<long, LadderPref> LadderPrefMap;

template LadderPref &LadderPrefMap::operator[](const long &key);
