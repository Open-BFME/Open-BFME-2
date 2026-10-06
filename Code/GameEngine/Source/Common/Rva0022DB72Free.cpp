// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva0022DB72@Rva0022DB72@@QAEXPAX@Z @0x0022DB72 28B
// Destroys the Rva0022D1DF member at +4 of the node then frees the node
// with the game's _free when non-null. Chain body: calls just-landed
// ??1Rva0022D1DF@@QAE@XZ at 0x0022D1DF and rowed _free 0x00030830 with
// lea ecx [esi+4] call-test-je free shape. Caller at 0x0022DD3A sets ecx
// (thiscall) and pushes the node pointer; incoming this is unused.
// Unblocks 0x0022DD19.
extern "C" void __cdecl free(void *);

class Rva0022D1DF
{
public:
	~Rva0022D1DF();
};

class Rva0022DB72
{
public:
	void rva0022DB72(void *p);
};

void Rva0022DB72::rva0022DB72(void *p)
{
	((Rva0022D1DF *)((char *)p + 4))->~Rva0022D1DF();
	if (p)
		free(p);
}
