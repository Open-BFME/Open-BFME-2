// ?rva003B65BF@@YA_NHHPAURva003B65Header@@@Z
// partial score=0.6 date=2026-10-05
// cl: /O1 /MD
// Twin list-append helpers over the Rva003B65Header lists, range-17 batch.
// ?rva003B65BF@@YA_NHHPAURva003B65Header@@@Z @0x003B65BF 58B: values the header
// through pinned 0x003B5EA5, then appends the result to the +0x34 list (head
// when empty, else the last +0x3c link). Always returns true.
// ?rva003B65F9@@YA_NHHPAURva003B65Header@@@Z @0x003B65F9 58B: same over the
// +0x38 list. Evidence: identical shapes apart from the head offset; the
// pinned callee takes (a1,a2,header); int args assumed.
struct Rva003B65Node
{
	char m_pad00[0x3c];
	Rva003B65Node *m_next3c;
};

struct Rva003B65Header
{
	char m_pad00[0x34];
	Rva003B65Node *m_list34;
	Rva003B65Node *m_list38;
};

int rva003B5EA5(int a1, int a2, Rva003B65Header *h);

bool __cdecl rva003B65BF(int a1, int a2, Rva003B65Header *h)
{
	int v = rva003B5EA5(a1, a2, h);
	Rva003B65Node *cur = h->m_list34;
	Rva003B65Node *next;
	if (cur != 0) {
		do {
			next = cur->m_next3c;
			if (next == 0)
				break;
		} while ((cur = next) != 0);
	}
	if (cur == 0)
		h->m_list34 = (Rva003B65Node *)v;
	else
		cur->m_next3c = (Rva003B65Node *)v;
	return true;
}

bool __cdecl rva003B65F9(int a1, int a2, Rva003B65Header *h)
{
	int v = rva003B5EA5(a1, a2, h);
	Rva003B65Node *cur = h->m_list38;
	Rva003B65Node *next;
	if (cur != 0) {
		do {
			next = cur->m_next3c;
			if (next == 0)
				break;
		} while ((cur = next) != 0);
	}
	if (cur == 0)
		h->m_list38 = (Rva003B65Node *)v;
	else
		cur->m_next3c = (Rva003B65Node *)v;
	return true;
}
