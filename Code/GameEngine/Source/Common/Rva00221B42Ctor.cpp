// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD
// ??0Rva00221B42@@QAE@ABVAsciiString@@ABVRva00221A58@@PAVINI@@@Z @0x00221B42 75B
// Ctor: Rva00221A58 at +0 via rowed copy 0x00221A58 plus AsciiString at +0x1C
// via StringBase copy 0x000365F0 plus INI::initFromINI 0x0002DE78 with table
// g_00BE6BD8. Chain after 0x00221A58; caller 0x00221C15 passes same 3 args to
// member at +8. Evidence: retail bytes and callers.
#include "ascii_string.h"

class Rva0022185A
{
public:
	Rva0022185A(const Rva0022185A &other);
private:
	AsciiString m_str;
	int m_04;
	unsigned char m_08;
};

class Rva00221A58
{
public:
	Rva00221A58(const Rva00221A58 &other);
private:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	Rva0022185A m_0C;
	int m_18;
};

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

extern const FieldParse g_00BE6BD8[];

class Rva00221B42
{
public:
	Rva00221B42(const AsciiString &a, const Rva00221A58 &b, INI *ini);
private:
	Rva00221A58 m_00;
	AsciiString m_1C;
};

Rva00221B42::Rva00221B42(const AsciiString &a, const Rva00221A58 &b, INI *ini)
	: m_00(b)
	, m_1C(a)
{
	ini->initFromINI(this, g_00BE6BD8);
}
