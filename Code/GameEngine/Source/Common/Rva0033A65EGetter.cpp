// cl: /MD
// ?rva0033A65E@Rva0033A65E@@QAEPAXXZ @0x0033A65E 22B
// Evidence: callers at 0x0059ADE3 0x0059AF90 0x004FAA9 use result as Body-like ptr (byte +0x1D);
// falls back to global Rva0041811D table at 0x00E030B0 via rowed DefaultBody 0x00418825.
class Rva0041811D
{
public:
	void *rva00418825();
};

// g_Va00E030B0: VA 0x00E030B0 (.data/bss); zero-filled pointer to the
// Rva0041811D table used for the default-body fallback.
Rva0041811D *g_Va00E030B0;

class Rva0033A65E
{
public:
	void *rva0033A65E();
private:
	char m_pad[0x490];
	void *m_body; // +0x490
};

void *Rva0033A65E::rva0033A65E()
{
	if (m_body != 0)
		return m_body;
	Rva0041811D *table = g_Va00E030B0;
	return table->rva00418825();
}
