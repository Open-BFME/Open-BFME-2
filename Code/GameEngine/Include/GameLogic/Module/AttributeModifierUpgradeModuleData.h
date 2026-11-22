// AttributeModifierUpgradeModuleData: canonical class for the units that build, construct and parse it.
// Target facts: factory 0x00255802 allocates 0x11C bytes and calls constructor 0x002557E9, which
// stores the folded table 0x00BF38C0 over the Rva00253487Base base (0x00253487, size 0x118) and a
// zero word at +0x118; the field table 0x00858818 parses AttributeModifier at +0x118 with
// INI::parseAsciiString, and AttributeModifierUpgrade passes it to the attribute-modifier pool.
#ifndef CANONICAL_ATTRIBUTEMODIFIERUPGRADEMODULEDATA_H
#define CANONICAL_ATTRIBUTEMODIFIERUPGRADEMODULEDATA_H

#include "Rva00253487Base.h"
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

class INI;
class ModuleData;
class MultiIniFieldParse;

class __declspec(novtable) AttributeModifierUpgradeModuleData : public Rva00253487Base
{
public:
	AttributeModifierUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *);

public:
	AsciiString m_attributeModifierName; // +0x118
};

#endif // CANONICAL_ATTRIBUTEMODIFIERUPGRADEMODULEDATA_H
