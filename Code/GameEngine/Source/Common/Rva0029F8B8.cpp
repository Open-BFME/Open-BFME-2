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
