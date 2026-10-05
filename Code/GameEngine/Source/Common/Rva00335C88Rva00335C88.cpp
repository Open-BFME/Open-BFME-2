// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oy-
//
// ?rva00335C88@Rva00335C88@@QAEPAXPAX0@Z, retail 0x00335c88, 38 bytes. Banked partial (score 0.99) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
//
// ?rva00335C88@Rva00335C88@@QAEXXZ @ 0x00335C88 (38B).
// Unlock: thin wrapper over Rva000ADE45Copy.
// Evidence: callees rowed Copy 0x000ADE45; callers at 0x000B06F5,
// 0x003360FB, 0x00337CE3; prev/next TU flags.

struct BfmeStringRecord00063BE4 {
	unsigned int word0, word1, word2, word3, word4, word5, word6;
	char text[4];
	unsigned char tail0, tail1;
};
BfmeStringRecord00063BE4 *__cdecl Rva000ADE45Copy(BfmeStringRecord00063BE4 *a, BfmeStringRecord00063BE4 *b, BfmeStringRecord00063BE4 *c, BfmeStringRecord00063BE4 *d);

class Rva00335C88
{
public:
	void *rva00335C88(void *a, void *b);
private:
	char m_pad00[4];
	BfmeStringRecord00063BE4 *m_04;
};

void *Rva00335C88::rva00335C88(void *a, void *b)
{
	BfmeStringRecord00063BE4 *r = Rva000ADE45Copy((BfmeStringRecord00063BE4 *)b, m_04, (BfmeStringRecord00063BE4 *)a, (BfmeStringRecord00063BE4 *)((char *)&a + 3));
	m_04 = r;
	return a;
}
