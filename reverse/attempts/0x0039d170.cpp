// ?rva0039D170@Rva0039C190@@QAEXIHHHHH@Z
// partial score=0.5 date=2026-10-06
// cl: /O1 /Oy- /EHsc /MD
//
// ?rva0039D170@Rva0039C190@@QAEXIHHHHH@Z @0x0039D170 96B: index dispatch
// over a 20-byte stride array, range-17 dump lane.
//
// Count is (end-begin)/20 by signed idiv; an in-range index addresses the
// element for the rowed 0x0039C190 assign, else the index minus count plus
// end plus an out-param go through the pinned 0x0039C415 helper. Unsigned
// range compare; /O1 for the push/pop idiv shape; frame in the shared
// __EH_prolog helper (0x629188).

class Rva0039B893;

struct Rva0039D170Token
{
	int m_x;
	~Rva0039D170Token() {}
};

class Rva0039C190
{
public:
	Rva0039B893 *rva0039C190(Rva0039B893 *result, Rva0039B893 *first);
	void rva0039C415(void *end, int index, int *out);
	void rva0039D170(unsigned int index, int outVal, int d3, int d4, int d5, Rva0039D170Token tok);

private:
	char *m_begin00; // +0x00
	char *m_end04; // +0x04
};

// ?rva0039D170@Rva0039C190@@QAEXIHHHHH@Z
void Rva0039C190::rva0039D170(unsigned int index, int outVal, int d3, int d4, int d5, Rva0039D170Token tok)
{
	char *begin = m_begin00;
	char *end = m_end04;
	if (index < (unsigned int)((end - begin) / 0x14)) {
		unsigned int off = index * 0x14;
		char *elem = begin + off;
		rva0039C190((Rva0039B893 *)elem, (Rva0039B893 *)end);
	}
	else {
		end = m_end04;
		unsigned int adj = index - (end - begin) / 0x14;
		rva0039C415(end, adj, &outVal);
	}
}
