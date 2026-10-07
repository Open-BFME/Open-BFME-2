// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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

class Rva00253487Base
{
public:
	Rva00253487Base();
	virtual ~Rva00253487Base() {}

private:
	char m_pad[0x118 - 4];
};

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
