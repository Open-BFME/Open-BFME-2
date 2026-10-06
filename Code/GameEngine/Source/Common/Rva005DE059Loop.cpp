// cl: /O1 /DNDEBUG /MD
// _rva005DE059 @0x005DE059 47B cdecl loop-forwarder.
// For p in [begin,end) step 0x18: p->Callee(a,b) via pinned 0x005DDBAB
// (this+2 ints void); then out->{a0=b4} = (a,b) with +4 stored first.
// Ret void (cdecl, caller cleans). Address-derived.
class Rva005DDBAB
{
public:
	void rva005DDBAB(int a, int b);
protected:
	unsigned char m_pad[0x18];
};

struct Rva005DE059Out
{
	int m_0;
	int m_4;
};

extern "C" void __cdecl rva005DE059(Rva005DE059Out *out, Rva005DDBAB *begin, Rva005DDBAB *end, int a, int b)
{
	for (Rva005DDBAB *p = begin; p != end; p++)
		p->rva005DDBAB(a, b);
	out->m_4 = b;
	out->m_0 = a;
}
