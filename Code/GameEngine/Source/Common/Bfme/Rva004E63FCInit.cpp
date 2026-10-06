// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??0Rva004E63FC@@QAE@XZ @0x004E63FC 89B
// Ctor-like init: AsciiString at +0 from "PlaceHolderReticle" via rowed
// StringBase ctor, FontDesc at +4 via rowed ctor, dword at +0x10 to -1 via
// or, FontDesc name to "Albertus MT" via rowed set, size 14 bold 0, return
// this. Evidence: unlock lane, rowed StringBase ctor 0x00037BA0 plus
// FontDesc ctor 0x00376900 plus set 0x000055F5, string literals, ret this,
// 1 caller, honest rva name.
#include "ascii_string.h"

struct FontDesc
{
	AsciiString name;
	int size;
	bool bold;
	FontDesc();
};

class Rva004E63FC
{
	AsciiString m_s00;
	FontDesc m_font04;
	int m_unk10;
public:
	Rva004E63FC();
};

Rva004E63FC::Rva004E63FC() : m_s00("PlaceHolderReticle"), m_font04()
{
	m_unk10 = -1;
	m_font04.name.set("Albertus MT");
	m_font04.size = 14;
	m_font04.bold = false;
}
