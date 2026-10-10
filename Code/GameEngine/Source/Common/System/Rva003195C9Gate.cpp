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
	void rva003190BB(int *out);
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

// Native318FA1..318FBE,29B; WB102B5E0 independently preserves the
// nullable getter, unsigned sixteen-byte record count and back lookup.
// Reuse the existing neutral17B getter twin, rather than asserting the
// donor's wheel names for this army view. The old integer-return pin
// retains its ABI: EAX carries the resulting opaque pointer bits.
struct Rva00318F42View;
class Rva00318F42 {public:Rva00318F42View *rva00318B83() const;};
class Rva0020E89C;
class Rva00538CEF {public:Rva0020E89C *rva00538CEF();};
int Rva00318FA1MainOwner::rva00318FA1(){
 Rva00318F42View *v=((Rva00318F42*)this)->rva00318B83();
 if(v){int *span=(int*)v; if((unsigned)((span[1]-span[0])>>4)>0)
  return (int)((Rva00538CEF*)v)->rva00538CEF();}
 return 0;
}
