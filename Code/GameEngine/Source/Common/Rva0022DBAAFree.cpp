// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva0022DBAA@Rva0022DBAA@@QAEXPAX@Z @0x0022DBAA 28B: destroys the Rva0022D249 member at +4 of the node then frees the node with the games _free when non-null. Chain body: calls just-landed ??1Rva0022D249@@QAE@XZ at 0x0022D249 and rowed _free 0x00030830 with lea ecx [esi+4] call-test-je free shape. Caller at 0x0022DDCC sets ecx (thiscall) and pushes the node pointer; incoming this is unused. Unblocks 0x0022DDAB.
extern "C" void __cdecl free(void *);

class Rva0022D249
{
public:
	~Rva0022D249();
};

class Rva0022DBAA
{
public:
	void rva0022DBAA(void *p);
};

void Rva0022DBAA::rva0022DBAA(void *p)
{
	((Rva0022D249 *)((char *)p + 4))->~Rva0022D249();
	if (p)
		free(p);
}
