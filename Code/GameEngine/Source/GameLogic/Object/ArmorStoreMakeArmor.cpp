// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?makeArmor@ArmorStore@@QBE?AVArmor@@ABVAsciiString@@@Z, retail 0x001D9001 (26B).
// Zero Hour's inline ArmorStore::makeArmor (`return Armor(tmpl);`), out of line
// in BFME 2 and taking the armor's name: the returned Armor is copy-built from
// the AsciiString (StringBase copy ctor 0x000365F0); `this` is unused (ret 8:
// hidden return slot plus the name). Caller: ActiveBody::validateArmorAndDamageFX
// 0x004BE1AE on TheArmorStore with the armor set's armor name.

#include "ascii_string.h"

class Armor
{
public:
	Armor(const AsciiString &asciiString) : m_templateName(asciiString) {}

private:
	AsciiString m_templateName;
};

#include "../../../Include/GameLogic/ArmorStore.h"

Armor ArmorStore::makeArmor(const AsciiString &name) const
{
	return Armor(name);
}
