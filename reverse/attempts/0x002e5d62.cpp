// ?rva002E5D62@Rva002E66F2@@UAE_NH@Z
// partial score=0.93 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /EHsc
// ?rva002E5D62@Rva002E66F2@@UAE_NH@Z 0x002E5D62 248B
// Evidence: vslot 4 offset 0x10 of vtable 0x00804FA8 class Rva002E66F2; flag at +0x1C selects lang FileSystem path vs literal path then Rva002E5611 compare at +0xC then slot22 slot1 InGameUI slot16 g_009FF000 walk; donor Rva002E66F2Dtor layout plus FileSystemRva wrappers plus ReloadIniFileNotices InGameUI message pattern.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva002E5611
{
public:
	int rva002E5611(const Rva002E5611 &other);
private:
	int m_00;
	int m_04;
	int m_high;
	int m_low;
};

class FileSystem;
extern FileSystem *TheFileSystem;

class InGameUI
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void message(UnicodeString format, ...);
};
extern InGameUI *TheInGameUI;

class Rva002D06CA;
extern Rva002D06CA *g_009FF000;

class Rva002CF1E2
{
public:
	void rva002CF1E2();
};

extern const char g_Rva0107301CEmptyString[];
extern const char *g_00DA5F18;
extern const char *g_00DA5F14;
extern unsigned short g_00C04F74[];

AsciiString __cdecl GetRegistryLanguage();
bool __stdcall Rva00077BF8Get(const AsciiString &a, const char *b);
bool __stdcall Rva00600E3AGet(const char *a, const char *b);

class Rva002E66F2
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual bool rva002E5D62(int unused);
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
private:
	char m_pad04[8];
	Rva002E5611 m_key0C;
	unsigned char m_flag1C;
};

// ?rva002E5D62@Rva002E66F2@@UAE_NH@Z present-unmatched
bool Rva002E66F2::rva002E5D62(int unused)
{
	Rva002E5611 buf;
	(void)unused;
	if (m_flag1C) {
		AsciiString file;
		{
			AsciiString lang = GetRegistryLanguage();
			const char *raw = *(const char *const *)&lang;
			const char *t = raw ? raw + 8 : g_Rva0107301CEmptyString;
			file.format(g_00DA5F18, t);
		}
		Rva00077BF8Get(file, (const char *)&buf);
	} else {
		Rva00600E3AGet(g_00DA5F14, (const char *)&buf);
	}
	if (m_key0C.rva002E5611(buf) == 0)
		return false;
	slot22();
	slot01();
	if (TheInGameUI)
		TheInGameUI->message(UnicodeString((const unsigned short *)g_00C04F74));
	if (g_009FF000)
		((Rva002CF1E2 *)g_009FF000)->rva002CF1E2();
	return true;
}
