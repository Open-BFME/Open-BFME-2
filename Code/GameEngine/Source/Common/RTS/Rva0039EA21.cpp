// cl: /DNDEBUG /MD

// ?rva0039EA21@Rva0039EA21@@QAEXPAURva0039EA21Node@@@Z, RVA 0x0039EA21, 45B.
// Unlock lane: recursive teardown; null entry returns, else recurses on the
// +0x0C child through this, frees the node through rowed _free at
// 0x00030830, follows +0x08 while non-null. this is only passed through the
// recursion. Self-caller plus 0x0039F56E; landing unblocks it. Owner and node
// head unknown so honest address-derived names. Flags copy the Team
// neighbour (plain /O1, no EH frame in retail).
extern "C" void free(void *);

struct Rva0039EA21Node {
	char m_pre[8];
	Rva0039EA21Node *m_08;
	Rva0039EA21Node *m_0c;
};

class Rva0039EA21
{
public:
	void rva0039EA21(Rva0039EA21Node *n);
};

void Rva0039EA21::rva0039EA21(Rva0039EA21Node *n)
{
	if (!n)
		return;
	do {
		rva0039EA21(n->m_0c);
		Rva0039EA21Node *next = n->m_08;
		free(n);
		n = next;
	} while (n);
}
