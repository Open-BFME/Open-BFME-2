// cl: /O1 /DNDEBUG /MD
// Reconstruction of the 71B wheel orchestrator at 0x003195C9: resolve
// the two banked helpers, run the banked 0x3190BB gate into a local,
// then fan all four pointers into the pinned 0x538F6B worker on the
// +0x90 subobject. Callee names reuse the banked attempts so the rows
// unify when those bodies land; all other names are address-derived.
class Rva00318FA1MainOwner
{
public:
	int rva00318FA1();
};

class Rva00318C32Owner
{
public:
	int rva00318C32();
};

class Rva003190BBOwner
{
public:
	bool rva003190BB(int *out);
};

class Rva00538F6B
{
public:
	void rva00538F6B(void *a, void *b, void *c, void *d);
};

class Rva003195C9Owner
{
public:
	void rva003195C9();
private:
	unsigned char m_pad[0x90];
	Rva00538F6B m_90;
};

void Rva003195C9Owner::rva003195C9()
{
	int a = ((Rva00318FA1MainOwner *)this)->rva00318FA1();
	if (a != 0)
	{
		int b = ((Rva00318C32Owner *)this)->rva00318C32();
		if (b != 0)
		{
			__int64 localStorage;
			((Rva003190BBOwner *)this)->rva003190BB((int *)&localStorage);
			m_90.rva00538F6B(&m_pad[0x44], (void *)b, (void *)&localStorage, (void *)a);
		}
	}
}
