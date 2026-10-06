// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva0021572A@@QAE@PAVINI@@@Z @0x0021572A 89B INI ctor over AsciiString plus BfmeE16 vector.
// Evidence: thiscall ret 4 plus return-this plus caller 0x00215B2B;
// and-zero +0 plus Vector_base BfmeE16 0x00211E58 at +4 with allocator temp;
// getNextToken 0x0002DF97 with 0 plus StringBase set 0x000055F5; initFromINI
// 0x0002DE78 with table g_00BE574C; prev/next share vector stlport flags.
#include "ascii_string.h"
#include <vector>
struct BfmeE16 { float x, y, z, w; };

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *what, const FieldParse *parseTable);
};

extern const FieldParse g_00BE574C;

class Rva0021572A
{
public:
	Rva0021572A(INI *ini);
private:
	AsciiString m_00;
	_STL::vector<BfmeE16> m_04;
};

Rva0021572A::Rva0021572A(INI *ini)
{
	const char *tok = ini->getNextToken(0);
	m_00.set(tok);
	ini->initFromINI(this, &g_00BE574C);
}
