// cl: /O1 /DNDEBUG /MD
//
// ?rva00362862@Rva00362862Item@@QAEXHH@Z retail 0x00362862 68 bytes:
// vector element notify helper. Evidence: rowed caller 0x00239300 loops
// (*it)->rva00362862(a,b) over the vector at this+0xE8 (thiscall, ret 8);
// fresh game.dat decode of [0x362862,0x3628A6): if the +0x04 aux pointer
// is non-null, push aux->auxValue() (thiscall 0x002763E6, int result,
// 138B Ghidra body) into this->rva002676EA(v) (thiscall 0x003626EA, 1
// int arg, 24B 9-countdown loop into 0x362675); if the second arg, read
// as a byte-tested flag (retail cmp is byte-granularity, hence (char)b),
// is nonzero, run the 9 entries at +0x08+k*0x44 through
// entry->rva003627B8(a) (thiscall 0x003627B8, 1 int arg, 65B body calling
// rowed 0x362499) in a push-9/pop-ebx countdown loop, then call
// this->rva0036276F() (thiscall 0x0036276F, no args, the Lever L/M lane).
// Same +0x04/+0x08/9x0x44 holder layout as sibling Rva00362E1C. Callee
// names are opaque address-derived labels; their symbols.csv pins carry
// the retail REL32 evidence and prove no identity. The mask call routes
// through an opaque Rva0036276F view so the CLOSED lane keeps one name.
class Rva002763E6Aux
{
public:
	int auxValue();
};

class Rva003627B8Entry
{
	unsigned char m_data[0x44];
public:
	void rva003627B8(int a);
};

class Rva0036276F
{
public:
	void rva0036276F();
};

class Rva00362862Item
{
	unsigned char m_pad00[4];
	Rva002763E6Aux *m_04;
	Rva003627B8Entry m_entries[9];
public:
	void rva00362862(int a, int b);
	void rva002676EA(int v);
};

void Rva00362862Item::rva00362862(int a, int b)
{
	if (m_04 != 0)
		rva002676EA(m_04->auxValue());
	if ((char)b) {
		Rva003627B8Entry *e = m_entries;
		int n = 9;
		do {
			e->rva003627B8(a);
			++e;
		} while (--n != 0);
		((Rva0036276F *)this)->rva0036276F();
	}
}
