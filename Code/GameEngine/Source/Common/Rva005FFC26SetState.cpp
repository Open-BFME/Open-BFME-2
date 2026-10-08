// cl: /MD /EHsc
//
// ?rva005FFC26@Rva005FFC26@@QAEXH@Z, retail 0x005FFC26 101 bytes.
// Unlock: missing callee of 0x005FFED5; landing makes it ready.
// Evidence: AptCall row 0x0050E9FE with SetState literal and empty fallback
// g_Rva0107301CEmptyString plus TheRva00222A8BTarget; caller jmp 0x005FFED8;
// length-prefixed m_8 with chars at +8; word-copy zero loop reusing dead arg.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
extern const char *g_00C7A570[];
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *, void *, const char *, const char *, const char **);

class Rva005FFC26
{
public:
	void rva005FFC26(int arg);
private:
	char m_pad0[4];
	void *m_4;
	const char *m_8;
	char m_padC[0x18 - 0xC];
	int m_18;
	char m_pad1C[0x4C - 0x1C];
	int m_4C;
	int m_50;
};

void Rva005FFC26::rva005FFC26(int arg)
{
	if (arg == m_18)
		return;
	const char *s = m_8 ? m_8 + 8 : "";
	Rva0050E9FEAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_4, s, "SetState", &g_00C7A570[arg]);
	char z[2] = { 0, 0 };
	short *p = (short *)&m_4C;
	short *end = (short *)&m_50;
	while (p != end) {
		*p = *(short *)z;
		++p;
	}
	m_18 = arg;
}
