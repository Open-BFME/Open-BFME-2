// cl: /MD
// Target evidence: the 38-byte Ghidra body stores five 32-bit arguments at
// this+0x00 through this+0x10, preserves the incoming this pointer in EAX,
// and returns with ret 0x14. The address-derived owner and argument semantics
// remain unresolved; the source exposes the observed EAX value as void*.
class Rva002B2F71
{
public:
	void *rva002B2F71(int a0, int a1, int a2, int a3, int a4);
};

void *Rva002B2F71::rva002B2F71(int a0, int a1, int a2, int a3, int a4)
{
	int *fields = (int *)this;
	fields[0] = a0;
	fields[1] = a1;
	fields[2] = a2;
	fields[3] = a3;
	fields[4] = a4;
	return this;
}
