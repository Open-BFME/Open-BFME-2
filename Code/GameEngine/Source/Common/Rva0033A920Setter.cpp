// cl: /MD
// ?rva0033A920@Rva0033A920@@QAEXPBX@Z @0x0033A920 49B
// Lazy enum setter: if this int is not -1 return; else if the arg byte at
// +0x108 has 0x80 set this to 6, else this to 10 when the arg dword at +0x110
// has 0x4000000 else 0 (neg/sbb/and shape). Caller at 0x002CF666 passes
// esi with this at esi+0x520 and arg esi. Opaque Rva names: owning classes
// behind both pointers are unproven.
class Rva0033A920
{
public:
	void rva0033A920(const void *arg);

private:
	int m_val;
};

struct Rva0033A920Arg
{
	unsigned char m_pad00[0x108];
	unsigned char m_108;
	unsigned char m_pad109[0x110 - 0x108 - 1];
	unsigned int m_110;
};

void Rva0033A920::rva0033A920(const void *arg)
{
	if (m_val != -1)
		return;
	const Rva0033A920Arg *a = (const Rva0033A920Arg *)arg;
	if (a->m_108 & 0x80)
		m_val = 6;
	else
		m_val = (a->m_110 & 0x4000000) ? 10 : 0;
}
