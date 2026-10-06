// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ??0Rva0029B816@@QAE@HH_N00ABVAsciiString@@H0HH@Z @0x0029B74A 204B.
// Ctor vtable 0x7FD028: two newDisplayStrings via 0xDFEAD8 slot 0x38 with empty UnicodeString text then SuperweaponInfo::setFont. Callers 0x002A6AC2 0x002A70AE.
#include "ascii_string.h"

class UnicodeString {
public:
	UnicodeString(const UnicodeString &o)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&o);
	}
	static const UnicodeString TheEmptyString;
private:
	unsigned short *m_text;
};

class DisplayString {
public:
	virtual void s00();
	virtual void s01(UnicodeString s);
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
};

class DisplayStringManager {
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13();
	virtual DisplayString *newDisplayString();
	virtual void freeDisplayString(DisplayString *s);
};

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
	m_4->s05();
	m_4->s01(UnicodeString(UnicodeString::TheEmptyString));
	m_8 = TheDisplayStringManager->newDisplayString();
	m_8->s05();
	m_8->s01(UnicodeString(UnicodeString::TheEmptyString));
	((SuperweaponInfo *)this)->setFont(font, point, bold);
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?TheEmptyString@UnicodeString@@2V1@B=?TheEmptyString@UnicodeString@@2V1@A")
