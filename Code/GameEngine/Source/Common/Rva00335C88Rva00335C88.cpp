// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oy-
//
// ?rva00335C88@Rva00335C88@@QAEPAXPAX0@Z, retail 0x00335c88, 38 bytes. Banked partial (score 0.99) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
//
// ?rva00335C88@Rva00335C88@@QAEXXZ @ 0x00335C88 (38B).
// Unlock: thin wrapper over STLport's by-reference-tag __copy_ptrs.
// Evidence: callees rowed __copy_ptrs 0x000ADE45; callers at 0x000B06F5,
// 0x003360FB, 0x00337CE3; prev/next TU flags.

struct BfmeStringRecord00063BE4 {
	unsigned int word0, word1, word2, word3, word4, word5, word6;
	char text[4];
	unsigned char tail0, tail1;
};
namespace _STL
{
struct __false_type
{
};
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &);
}

class Rva00335C88
{
public:
	void *rva00335C88(void *,void *);
	char m_pad00[0x4];
private:
	BfmeStringRecord00063BE4 *m_04; // +0x04
};

// Retail passes the tag at &a + 3; a __false_type() temporary lands in b's
// slot (&b + 3) under every flag set tried, so the address stays explicit.
void *Rva00335C88::rva00335C88(void *a, void *b)
{
	BfmeStringRecord00063BE4 *r = _STL::__copy_ptrs((BfmeStringRecord00063BE4 *)b, m_04, (BfmeStringRecord00063BE4 *)a, *(const _STL::__false_type *)((char *)&a + 3));
	m_04 = r;
	return a;
}
