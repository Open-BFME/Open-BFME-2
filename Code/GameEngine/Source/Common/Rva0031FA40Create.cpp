// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?Rva0031FA40Create@@YAXPAVINI@@PAX@Z @0x0031FA40 78B factory.
// Retail new Rva0031F7AB 0x1C, initFromINI with table 0x0080D720, store to [out+8].
// Evidence: chain from 0x0031F7AB landing; rowed ctor 0x0031F7AB plus new 0x0002FDA0
// plus initFromINI 0x0002DE78; caller none; free-function cdecl (ret 0).
struct FieldParse;
extern const struct FieldParse g_0080D720;
class INI {
public: void initFromINI(void *what, const struct FieldParse *table);
};
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};
#include "ascii_string.h"
class Rva0031F7AB {
public:
	Rva0031F7AB();
private:
	AsciiString m_str;
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	int m_e;
	int m_f;
};
struct Rva0031FA40Out {
	char m_pad[8];
	Rva0031F7AB *m_obj;
};
void Rva0031FA40Create(INI *ini, Rva0031FA40Out *out)
{
	Rva0031F7AB *p = new Rva0031F7AB;
	ini->initFromINI(p, &g_0080D720);
	out->m_obj = p;
}
