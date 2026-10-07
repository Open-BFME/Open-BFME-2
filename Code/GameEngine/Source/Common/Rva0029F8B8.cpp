// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// ?rva0029F8B8@Rva0029F8B8@@QAE?AVRva0043FC20@@XZ retail 0x0029F8B8 130B
// By-value getter over +0x7AC member with GlobalLanguage +0x104 override.
// Evidence: copy ctor row 0x0029D81D twice plus isEmpty/set/releaseBuffer rows;
// TheGlobalLanguageData frame; ret 4 with hidden return pointer.
#include "ascii_string.h"

class Rva0043FC20
{
public:
	Rva0043FC20(const Rva0043FC20 &other);

	AsciiString m_00;
	int m_04;
	unsigned char m_08;
	char _pad[3];
	int m_0C;
};

struct GlobalLanguage
{
	char _pad[0x104];
	Rva0043FC20 m_104;
};

extern GlobalLanguage *TheGlobalLanguageData;

class Rva0029F8B8
{
public:
	Rva0043FC20 rva0029F8B8();

private:
	char _pad[0x7AC];
	Rva0043FC20 m_7AC;
};

Rva0043FC20 Rva0029F8B8::rva0029F8B8()
{
	Rva0043FC20 tmp(m_7AC);
	Rva0043FC20 *e = &TheGlobalLanguageData->m_104;
	if (!e->m_00.isEmpty())
	{
		((StringBase<char> *)&tmp.m_00)->set(*(const StringBase<char> *)&e->m_00);
		tmp.m_04 = e->m_04;
		tmp.m_08 = e->m_08;
	}
	return tmp;
}
// ?TheGlobalLanguageData@@3PAUGlobalLanguage@@A: the global at VA 0xdfdc84 is ?TheGlobalLanguageData@@3PAVGlobalLanguage@@A.
#pragma comment(linker, "/alternatename:?TheGlobalLanguageData@@3PAUGlobalLanguage@@A=?TheGlobalLanguageData@@3PAVGlobalLanguage@@A")

// Native29D844..29D8C6,29D8C6..29D948,29D948..29D9CA:
// three complete130B RET4 getters using the same rowed39B copy ctor29D81D.
// Their local records start at receiver+7BC/+7CC/+7DC. The language
// overrides independently start at global+110/+11C/+128. Those globals
// supply only the string/int/byte prefix; they do not supply the local
// record's final dword at+C. The copy ctor preserves that fourth field.
// The target130B getter29F8B8 above is the control-flow guide. No original
// owner or method names are asserted by this consumed-layout view.
struct Rva0029D844Override
{
 AsciiString m_00;
 int m_04;
 unsigned char m_08;
};
class Rva0029D844
{
public:
 Rva0043FC20 rva0029D844();
 Rva0043FC20 rva0029D8C6();
 Rva0043FC20 rva0029D948();
private:
 char m_pad00[0x7BC];
 Rva0043FC20 m_7BC, m_7CC, m_7DC;
};

Rva0043FC20 Rva0029D844::rva0029D844()
{
 Rva0043FC20 tmp(m_7BC);
 Rva0029D844Override *e = (Rva0029D844Override *)((char *)TheGlobalLanguageData + 0x110);
 if (!e->m_00.isEmpty())
 {
  ((StringBase<char> *)&tmp.m_00)->set(*(const StringBase<char> *)&e->m_00);
  tmp.m_04 = e->m_04;
  tmp.m_08 = e->m_08;
 }
 return tmp;
}

Rva0043FC20 Rva0029D844::rva0029D8C6()
{
 Rva0043FC20 tmp(m_7CC);
 Rva0029D844Override *e = (Rva0029D844Override *)((char *)TheGlobalLanguageData + 0x11C);
 if (!e->m_00.isEmpty())
 {
  ((StringBase<char> *)&tmp.m_00)->set(*(const StringBase<char> *)&e->m_00);
  tmp.m_04 = e->m_04;
  tmp.m_08 = e->m_08;
 }
 return tmp;
}

Rva0043FC20 Rva0029D844::rva0029D948()
{
 Rva0043FC20 tmp(m_7DC);
 Rva0029D844Override *e = (Rva0029D844Override *)((char *)TheGlobalLanguageData + 0x128);
 if (!e->m_00.isEmpty())
 {
  ((StringBase<char> *)&tmp.m_00)->set(*(const StringBase<char> *)&e->m_00);
  tmp.m_04 = e->m_04;
  tmp.m_08 = e->m_08;
 }
 return tmp;
}
