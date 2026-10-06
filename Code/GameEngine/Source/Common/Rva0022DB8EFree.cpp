// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva0022DB8E@Rva0022DB8E@@QAEXPAX@Z @0x0022DB8E 28B: destroys the Rva0022D214 member at +4 of the node then frees the node with the games _free when non-null. Chain body: calls just-landed ??1Rva0022D214@@QAE@XZ at 0x0022D214 and rowed _free 0x00030830 with lea ecx [esi+4] call-test-je free shape. Caller at 0x0022DD83 sets ecx (thiscall) and pushes the node pointer; incoming this is unused. Unblocks 0x0022DD62.
extern "C" void __cdecl free(void *);

class Rva0022D214
{
public:
	~Rva0022D214();
};

class Rva0022DB8E
{
public:
	void rva0022DB8E(void *p);
};

void Rva0022DB8E::rva0022DB8E(void *p)
{
	((Rva0022D214 *)((char *)p + 4))->~Rva0022D214();
	if (p)
		free(p);
}
