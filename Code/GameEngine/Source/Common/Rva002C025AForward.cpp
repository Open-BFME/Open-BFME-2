// cl: /MD
// ?rva002C025A@@YGXPAXI_N@Z @0x002C025A 33B.
// Stdcall forwarder: packs the dword and the bool argument into a two-field
// stack pair and passes its address with the first argument to the unrowed
// stdcall 0x002C00E0 (pinned by its REL32 at 0x002C0272).
// Evidence: target only; identity of the pair and of both callers is unproven,
// so the names are address-derived. The pair stores the dword at +0 and the
// byte at +4 (`mov [ebp-8],eax; mov [ebp-4],al`).
struct Rva002C025APair
{
	unsigned int m_00;
	unsigned char m_04;
};

void __stdcall rva002C00E0(void *target, Rva002C025APair *pair);

void __stdcall rva002C025A(void *target, unsigned int a, bool b)
{
	Rva002C025APair pair;
	pair.m_00 = a;
	pair.m_04 = b;
	rva002C00E0(target, &pair);
}
