// cl: /MD
//
// ?Rva00419CC8Init@@YAXXZ, retail 0x00419CC8, 12 bytes. Pushes global
// 0x00E030D0 then calls rowed ?Rva00419CB2Init@@YAXPAX@Z. Evidence: packet
// annotates push VA 0x00E030D0 with no name yet and call to rowed 0x00419CB2;
// callers at 0x002301EC and 0x00230490; unblocks none listed; chain after
// just-landed 0x00419CB2.
void __cdecl Rva00419CB2Init(void *p);

extern int g_00E030D0;

void __cdecl Rva00419CC8Init(void)
{
	Rva00419CB2Init(&g_00E030D0);
}
