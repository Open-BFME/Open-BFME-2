// cl: /Ireference/shims/moduledata /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0ReplaceSelfUpgradeModuleData@@QAE@XZ, retail 0x004B790B, 83 bytes.
// ModuleData-side ctor in the ReplaceSelf file-unit: the rowed OpenContain
// base (0x253487, 0x118 bytes) builds first, the derived vtable 0xC58B40
// installs by compiler position (derived virtuals; the immediate is a masked
// DIR32 reloc), then the ReplaceWith/AndThenAddA string vector at +0x118
// builds through the AsciiString Vector_base alias (0x211E58) and is
// cleared through the rowed erase (0x2CCFC). Table 0xC58A88 carries both
// fields at +0x118; factory 0x2506CE news 0x124 with this ctor as sole
// caller (pinned). The base plus the vector drive the EH states 0 and 1.
// Row supersedes the sole-caller pin.

#include <vector>

#include "ascii_string.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> AsciiString *vector<AsciiString, allocator<AsciiString> >::erase(AsciiString*, AsciiString*);
}

// The base dtor (rowed 0x0049B47C in CommandSetUpgradeModuleDataCtor.cpp) is
// Snapshot's: it restores Snapshot's table 0x00BBB554. Spell it the same way so
// this TU's inline copy is the retail one.
#include "Common/Snapshot.h"

#include "../../../../Include/GameLogic/Module/Rva00253487Base.h"

class ReplaceSelfUpgradeModuleData : public Rva00253487Base
{
public:
	ReplaceSelfUpgradeModuleData();
	virtual ~ReplaceSelfUpgradeModuleData();

	_STL::vector<AsciiString> m_replaceWith; // +0x118
};

// ??0ReplaceSelfUpgradeModuleData@@QAE@XZ @0x4B790B
ReplaceSelfUpgradeModuleData::ReplaceSelfUpgradeModuleData()
{
	m_replaceWith.clear();
}
