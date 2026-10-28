// cl: /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport46
//
// ??$_Construct@U?$pair@$$CBW4NameKeyType@@VDamageFX@@@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBW4NameKeyType@@VDamageFX@@@0@ABU10@@Z,
// retail 0x00360917, 34 bytes. Dedicated TU.
//
// STLport builds hashtable node payloads with _Construct(&node->_M_val, obj),
// which placement-new constructs the pair in place; the pair copy is a flat
// dword copy because both members are trivially copyable. Retail copies the
// key word and then rep-movsd 0x1E0 dwords, so the pair is 0x784 bytes and the
// DamageFX value is 0x780 bytes. BFME1's build of the same TU used 0x100
// dwords (16 damage types x 4 veterancy levels x 16-byte DFX); BFME2's table
// is 0x200 bytes larger. The TU-local model below carries only that
// retail-measured size; it makes no claim about BFME2's real DamageFX layout.

#define _STLP_NO_EXCEPTIONS 1
#include <utility>
#include <stl/_construct.h>

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class DamageFX
{
public:
	int m_valueWords[0x1E0];
};

typedef _STL::pair<const NameKeyType, DamageFX> DamageFXPair;

// Anchor: emits the _Construct COMDAT this TU exists to place.
void damageFXPairConstructAnchor(DamageFXPair *at, const DamageFXPair &from)
{
	_STL::_Construct(at, from);
}

// ?damageFXPairCopyAnchor@@YAXPAUDamageFXPair@@ABU1@@Z absent-from-retail
// Anchor: emits the pair copy-ctor COMDAT (retail 0x00360896) via
// placement new; the anchor itself never shipped.
void damageFXPairCopyAnchor(DamageFXPair *at, const DamageFXPair &from)
{
	new (at) DamageFXPair(from);
}
