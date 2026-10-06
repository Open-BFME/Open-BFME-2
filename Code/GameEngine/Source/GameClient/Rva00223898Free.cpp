// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00223898@Rva00223898@@QAEXPAX@Z @0x00223898 28B
// Destroys the Rva0022304A member at +4 of the node, then frees the node
// with the game's _free when non-null. Chain body: calls just-landed
// ??1Rva0022304A@@QAE@XZ and rowed _free 0x00030830. Caller at 0x00224184
// sets ecx (thiscall) and pushes the node pointer; incoming this is unused.
// Unblocks 0x00224163.
extern "C" void __cdecl free(void *);

class Rva0022304A
{
public:
	~Rva0022304A();
};

class Rva00223898
{
public:
	void rva00223898(void *p);
};

void Rva00223898::rva00223898(void *p)
{
	((Rva0022304A *)((char *)p + 4))->~Rva0022304A();
	if (p)
		free(p);
}
