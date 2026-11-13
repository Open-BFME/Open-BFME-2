// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
//
// ??0Rva0057A4E7@@QAE@XZ, retail 0x0057AA45, 144 bytes.
//
// Evidence (retail body only; names are address-derived):
//  57aa45: mov eax, FuncInfo / call __EH_prolog
//          AsciiString temp("Checklist") at [ebp-0x10] through the folded
//          StringBase ctor 0x00037BA0, then the pinned base ctor Rva0022167C
//          0x00221635 with &temp, then the temp release at 0x00036410.
//          vtable 0x00C6F098 at +0; FontDesc member at +8 default-constructed
//          through the rowed 0x00376900; then +0x14 = -1, +0x18 = 0xFFFF0000,
//          +0x1C = 0xFFFFFF00, +0x20 = 0.0f, then the name at +8 reset with
//          StringBase<char>::set 0x000055F5 ("Albertus MT"), then the font
//          size 0xC at +0xC and bold 0 at +0x10.
// The class owns the rowed non-deleting dtor 0x0057A4E7 and the rowed slot-0
// deleting dtor 0x0057AAD5 (vtable 0x00C6F098); its slot1 is the rowed INI
// parse 0x0057A260. Identity beyond the dtor family is not recovered.

#include "ascii_string.h"

class Rva0022167C
{
public:
	Rva0022167C(const AsciiString &name);
	virtual ~Rva0022167C();

private:
	void *m_at4;
};

// The rowed FontDesc default ctor 0x00376900: AsciiString name at +0, int size
// at +4, bool bold at +8.
#include "../../Include/Common/FontDesc.h"

class Rva0057A4E7 : public Rva0022167C
{
public:
	Rva0057A4E7();
	virtual ~Rva0057A4E7();

private:
	FontDesc m_font; // +0x08
	int m_14;        // -1
	int m_18;        // 0xFFFF0000
	int m_1c;        // 0xFFFFFF00
	float m_20;      // 0.0f
};

Rva0057A4E7::Rva0057A4E7()
	: Rva0022167C(AsciiString("Checklist")), m_14(-1), m_18(0xFFFF0000), m_1c(0xFFFFFF00), m_20(0.0f)
{
	m_font.name = "Albertus MT";
	m_font.size = 12;
	m_font.bold = false;
}
