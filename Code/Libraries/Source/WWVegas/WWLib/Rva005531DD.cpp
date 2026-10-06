// cl: /MD
// ?rva005531DD@Rva005531DD@@QAEXPAX@Z @0x005531DD 45B: Tree erase helper recurses +0xC loops +8 frees via free. Evidence: unlock lane callee of 0x005532D6 plus self recursion plus free 0x00030830 rowed.
extern "C" void __cdecl free(void *block);
struct Rva005531DDNode
{
	char pad00[8];
	Rva005531DDNode *p08;
	Rva005531DDNode *p0C;
};
class Rva005531DD
{
public:
	void rva005531DD(void *p);
};
void Rva005531DD::rva005531DD(void *pp)
{
	Rva005531DDNode *p = (Rva005531DDNode *)pp;
	if (p == 0)
		return;
	while (p != 0)
	{
		rva005531DD(p->p0C);
		Rva005531DDNode *nxt = p->p08;
		free(p);
		p = nxt;
	}
}
