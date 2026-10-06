// cl: /MD /EHsc
// ?rva0038404A@Rva0038404A@@QAEXPAURva0038404ANode@@@Z 0x0038404A 53B
// Tree free with member dtor at +16: recurse child, save next, destroy, free.
// Evidence: self-call plus 0x00382B3F dtor plus _free; caller 0x00384E9C.
extern "C" void __cdecl free(void* block);

struct BuddyInfo
{
	~BuddyInfo();
};

struct Rva00382B3F
{
	unsigned int m_00;
	BuddyInfo m_04;
	~Rva00382B3F();
};

struct Rva0038404ANode
{
	int m0;
	int m4;
	Rva0038404ANode* m_next;
	Rva0038404ANode* m_child;
	Rva00382B3F m10;
};

class Rva0038404A
{
public:
	void rva0038404A(Rva0038404ANode* n);
};

void Rva0038404A::rva0038404A(Rva0038404ANode* n)
{
	Rva0038404ANode* cur = n;
	if (!cur)
		return;
	do {
		rva0038404A(cur->m_child);
		Rva0038404ANode* next = cur->m_next;
		cur->m10.~Rva00382B3F();
		free(cur);
		cur = next;
	} while (cur);
}
