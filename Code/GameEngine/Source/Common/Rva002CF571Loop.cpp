// cl: /MD
// ?Rva002CF571Loop@@YAXPAURva002CF571Item@@0PAX@Z @0x002CF571 26B.
// Range loop over 0x5c-byte records: for each item calls virtual slot 0 with
// literal 0 (push 0, ecx=item, call [vptr]), stride add esi,0x5c, bounds
// cmp/jne with an initial jmp into the test. The caller at 0x002CF891 pushes
// three args (begin, end, &local) and cleans 0xc: the third arg is never read
// by retail, modeled as an unused void*. Item type is an honest Rva dummy tag
// (cf. Rva005E7198 precedent): vptr at +0, total size 0x5c, one virtual taking
// int (thiscall callee cleanup keeps the push-0/call stack balanced).
struct Rva002CF571Item
{
	virtual void Slot0(int value);
	unsigned char m_pad[0x58];
};

void __cdecl Rva002CF571Loop(Rva002CF571Item *first, Rva002CF571Item *last, void * /*unused*/)
{
	for (; first != last; ++first)
		first->Slot0(0);
}
