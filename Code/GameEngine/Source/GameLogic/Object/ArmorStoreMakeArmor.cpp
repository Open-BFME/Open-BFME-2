// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
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
	Armor(const AsciiString &templateName) : m_templateName(templateName) {}

private:
	AsciiString m_templateName;
};

class ArmorStore
{
public:
	Armor makeArmor(const AsciiString &name) const;
};

Armor ArmorStore::makeArmor(const AsciiString &name) const
{
	return Armor(name);
}
