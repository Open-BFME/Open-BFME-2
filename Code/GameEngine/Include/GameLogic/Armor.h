// Target facts: ArmorTemplate has no virtual functions or bases. Constructor RVA 0x001D8F68 initializes AsciiString at +0x78, calls clear (0x001D8F1F), then assigns its string argument through 0x000366F0; neither it nor destructor 0x001D8FA5 stores a vtable. The destructor adds 0x78 to this and tail-jumps to string release 0x00036410. Allocations at 0x001D94E5 and 0x001D9594 request 0x7C bytes before calls to that constructor at 0x001D9512 and 0x001D95C4.
// Target facts: clear writes 27 float coefficients at +0x04, float 1 at +0x70, signed -1 at +0x74, float zero at +0x00, and the default string at +0x78. The INI table VA 0x00BD9D10 names DamageScalar (parser 0x001D8F02, store +0x70), FlankedPenalty (percent parser 0x0002F1BA, offset zero), and Armor (parser 0x001D8E99, 27 coefficients at +0x04). Readers 0x001D8E7F, 0x001D8E88 and 0x001D8E8B read signed +0x74 > 0, float +0x00 and coefficient [input+0x0C], respectively. These methods and both special members remain out of line.
// Donor names: Zero Hour GameLogic/Armor.h supplies ArmorTemplate, clear, parseArmorCoefficients and m_damageCoefficient; its array extent is not BFME2's. AsciiString must be complete before this header is included.

#pragma once

#ifndef __BFME2_ARMOR_H_
#define __BFME2_ARMOR_H_

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
class INI;
struct Rva001D8E8BInput;

class ArmorTemplate
{
public:
	ArmorTemplate(const AsciiString &name);
	~ArmorTemplate();
	void clear();
	static void parseArmorCoefficients(INI *ini, void *instance, void *store, const void *userData);
	static void parseDamageScalar(INI *ini, void *instance, void *store, const void *userData);
	bool rva001D8E7F() const;
	float rva001D8E88() const;
	float getDamageCoefficient(const Rva001D8E8BInput &input) const;

	float m_flankedPenalty; // +0x00
	float m_damageCoefficient[27]; // +0x04
	float m_damageScalar; // +0x70
	int m_field74; // +0x74
	AsciiString m_name; // +0x78
};

typedef char ArmorTemplateSizeCheck[sizeof(ArmorTemplate) == 0x7C ? 1 : -1];

#endif
