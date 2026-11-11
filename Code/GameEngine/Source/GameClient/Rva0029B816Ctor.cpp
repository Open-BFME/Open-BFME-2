// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ??0Rva0029B816@@QAE@HH_N00ABVAsciiString@@H0HH@Z @0x0029B74A 204B.
// Ctor vtable 0x7FD028: two newDisplayStrings via 0xDFEAD8 slot 0x38 with empty UnicodeString text then SuperweaponInfo::setFont. Callers 0x002A6AC2 0x002A70AE.
#include "ascii_string.h"

#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"

#include "../../Include/GameClient/DisplayString.h"

#include "../../Include/GameClient/DisplayStringManager.h"

extern DisplayStringManager *TheDisplayStringManager;

class SuperweaponInfo {
public:
	void setFont(const AsciiString &fontName, int pointSize, bool bold);
};

class Rva0029B816 {
public:
	Rva0029B816(int p1, int p2, bool b1, bool b2, bool b3, const AsciiString &font, int point, bool bold, int color, int tmpl);
	virtual ~Rva0029B816();
private:
	DisplayString *m_4;
	DisplayString *m_8;
	int m_c;
	int m_10;
	AsciiString m_14;
	int m_18;
	int m_1c;
	bool m_20;
	bool m_21;
	bool m_22;
	bool m_23;
};

Rva0029B816::Rva0029B816(int p1, int p2, bool b1, bool b2, bool b3, const AsciiString &font, int point, bool bold, int color, int tmpl)
	: m_4(0), m_8(0), m_c(color), m_10(tmpl), m_18(p1), m_1c(p2), m_20(b1), m_21(b2), m_22(b3), m_23(false)
{
	m_4 = TheDisplayStringManager->newDisplayString();
	m_4->reset();
	m_4->setText(UnicodeString(UnicodeString::TheEmptyString));
	m_8 = TheDisplayStringManager->newDisplayString();
	m_8->reset();
	m_8->setText(UnicodeString(UnicodeString::TheEmptyString));
	((SuperweaponInfo *)this)->setFont(font, point, bold);
}
