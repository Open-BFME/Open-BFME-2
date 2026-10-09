// cl: /Od
// Open-BFME5 conversions.

// Matched bfmeGoOV forwards to bfmeDoOV's find-first-not-in-set helper; the
// caller consumes that pointer from EAX despite bfmeGoOV's void C++ signature.
extern void __cdecl bfmeGoOV(void *first, void *last, void *setFirst, void *setLast);
typedef char *(__cdecl *BfmeSearch1155Fn)(char *first, char *last,
	const char *setFirst, const char *setLast);

class BfmeS1155
{
public:
	unsigned int bfmeFind1155(const char *s, unsigned int pos, unsigned int n);
	char *m_bfme00;
	char *m_bfme04;
};

unsigned int BfmeS1155::bfmeFind1155(const char *s, unsigned int pos, unsigned int n)
{
	char *n1;
	const char *n2;
	const char *n3;

	if (pos > (unsigned int)(m_bfme04 - m_bfme00))
		return 0xffffffff;

	n2 = s;
	n3 = s + n;
	n1 = reinterpret_cast<BfmeSearch1155Fn>(&bfmeGoOV)(m_bfme00 + pos, m_bfme04, n2, n3);
	return (n1 != m_bfme04) ? (unsigned int)(n1 - m_bfme00) : 0xffffffff;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
