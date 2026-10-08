// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /Oy-
//
// ??0TooltipUpgradeModuleData@@QAE@XZ, retail 0x0025588E, 91 bytes.
// EH ctor over the rowed Rva00253487Base base (0x253487): the
// compiler-emitted vtable store lands mid-init, so the classes are virtual
// with declared-only dtors and no source store (Devastate precedent).
// DisplayName at +0x118 and Description at +0x11C are AsciiStrings: implicit
// default construction zeroes both, then the body assigns the global empty
// string (VA 0xDE0878, DIR32-masked push) through the folded AsciiString
// op= (pinned at 0x366F0) twice. Own table 0x00858C38 holds exactly
// DisplayName at +0x118 plus Description at +0x11C; the TooltipUpgrade pool
// key tail at 0x4B7A13 ends where the rowed proc begins; the EH factory at
// 0x2558E9 news 0x120 and is the only raw caller.

class Rva00253487Base
{
public:
	Rva00253487Base();
	virtual ~Rva00253487Base();

private:
	unsigned char m_pad[0x118 - 4];
};

#include "ascii_string.h"


class TooltipUpgradeModuleData : public Rva00253487Base
{
public:
	TooltipUpgradeModuleData();
	virtual ~TooltipUpgradeModuleData();

private:
	AsciiString m_displayName; // +0x118
	AsciiString m_description; // +0x11C
};

// ??0TooltipUpgradeModuleData@@QAE@XZ @0x25588E
TooltipUpgradeModuleData::TooltipUpgradeModuleData()
{
	m_displayName = AsciiString::TheEmptyString;
	m_description = AsciiString::TheEmptyString;
}
