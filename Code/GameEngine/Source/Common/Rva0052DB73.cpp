// cl: /DNDEBUG /MD
// ?rva0052DB73@Rva0052DB73@@QAE_NH@Z, retail 0x0052DB73, 38 bytes.
// Single-list all-match check returning true when every id equals arg.
// Evidence: unlock lane; no callees; callers 0x002EAB18 0x002F2E09.
struct Rva0052DB73Obj
{
	char _pad00[0x74];
	int m_74;
};

struct Rva0052DB73Node
{
	Rva0052DB73Node *m_next;
	char _pad04[4];
	void *m_8;
};

struct Rva0052DB73Head
{
	char _pad00[0x14];
	Rva0052DB73Node *m_14;
};

class Rva0052DB73
{
public:
	bool rva0052DB73(int arg);
private:
	Rva0052DB73Head *m_0;
};

bool Rva0052DB73::rva0052DB73(int arg)
{
	Rva0052DB73Head *h = m_0;
	if (!h)
		return true;
	for (Rva0052DB73Node *n = h->m_14; n; n = n->m_next)
	{
		if (((Rva0052DB73Obj *)n->m_8)->m_74 != arg)
			return false;
	}
	return true;
}
