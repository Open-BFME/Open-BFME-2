// ??A?$hash_map@VAsciiString@@W4BuildableStatus@@U?$hash@VAsciiString@@@rts@@U?$equal_to@VAsciiString@@@4@V?$allocator@U?$pair@$$CBVAsciiString@@W4BuildableStatus@@@_STL@@@_STL@@@_STL@@QAEAAW4BuildableStatus@@ABVAsciiString@@@Z
// partial score=0.95 date=2026-10-07
// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Instantiate inside GameLogicInit.cpp (needs its AsciiString from bfme2_ascii).
// Near miss: iterator temp at ebp-0x20 instead of sharing ebp-0x18 with the pair temp
// (frame 0x14 vs retail 0xc); every other byte and callee matches.
#include "ascii_string.h"

// ??A?$hash_map@VAsciiString@@W4BuildableStatus@@...@QAEAAW4BuildableStatus@@ABVAsciiString@@@Z
// @0x002460C3 121B: the buildable-override map's operator[], instantiated by
// GameLogic::setBuildableStatusOverride (caller 0x00246F80; second caller
// 0x00247ED4). Target evidence: hashtable find 0x0041534B returns an
// {node, table} iterator; a null node inserts a {key, 0} pair through
// _M_insert 0x00242F1A and returns its value at +4, a hit returns node+8.
// The map type and key are the ones setBuildableStatusOverride's own row
// already proves; the body is STLport's hash_map::operator[].
#include <hash_map>

enum BuildableStatus
{
	BSTATUS_YES
};

namespace rts
{
	template <class T> struct hash
	{
		unsigned int operator()(const T &value) const;
	};

	template <class T> struct equal_to
	{
		bool operator()(const T &left, const T &right) const;
	};
}

typedef _STL::hash_map<AsciiString, BuildableStatus, rts::hash<AsciiString>,
	rts::equal_to<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, BuildableStatus> > > BuildableMap;

template BuildableStatus &BuildableMap::operator[](const AsciiString &key);
