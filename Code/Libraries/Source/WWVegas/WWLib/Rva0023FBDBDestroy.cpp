// cl: /MD /EHsc
//
// ?rva0023FBDB@Rva0023FBDB@@QAEXPAURva0023FBDBNode@@@Z @0x0023FBDB 53B.
// Tree destroy: recurse on +0xC child, destroy Rva0023D377 value at +0x10,
// free node, loop on +0x8 next. Evidence: chain lane (calls landed 0x0023D377);
// same value dtor plus free as landed Rva00383F9CErase; callers 0x0023FBED
// self plus 0x00240C6E; ghidra size 53 vs 72 trust ret plus int3.
extern "C" void __cdecl free(void *block);

struct Rva00438FC5
{
	~Rva00438FC5();
};

struct Rva0023D377
{
	unsigned int m_00;
	Rva00438FC5 m_04;
	~Rva0023D377();
};

struct Rva0023FBDBNode
{
	char m_pad00[8];
	Rva0023FBDBNode *m_next08;
	Rva0023FBDBNode *m_child0C;
	Rva0023D377 m_value10;
};

class Rva0023FBDB
{
public:
	void rva0023FBDB(Rva0023FBDBNode *pos);
};

void Rva0023FBDB::rva0023FBDB(Rva0023FBDBNode *pos)
{
	if (pos == 0)
		return;
	for (Rva0023FBDBNode *cur = pos; cur != 0;) {
		rva0023FBDB(cur->m_child0C);
		Rva0023FBDBNode *next = cur->m_next08;
		cur->m_value10.~Rva0023D377();
		free(cur);
		cur = next;
	}
}
