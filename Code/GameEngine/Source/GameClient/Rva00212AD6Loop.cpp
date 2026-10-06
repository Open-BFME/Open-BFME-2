// cl: /DNDEBUG /MD /EHsc
// ?Rva00212AD6Get@@YAXPAURva002115C5@@0@Z, RVA 0x00212AD6, 25B. Chain lane:
// range loop over 0x10-stride items calling rowed 0x002115C5 method with
// this in ecx; frameless push-esi with late-entry jmp. Callers at
// 0x00213968/0x00213984 pass first/last from [esi]/[esi+4]. Owner unknown
// so honest address-derived names.
struct Rva002115C5
{
	void rva002115C5();
	char m_pad[0x10];
};

void __cdecl Rva00212AD6Get(Rva002115C5 *first, Rva002115C5 *last)
{
	for (; first != last; ++first)
		first->rva002115C5();
}
