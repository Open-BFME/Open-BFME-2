// cl: /MD
// ?rva005E74AA@Rva005E74AA@@QAEPAXI@Z @0x005E74AA 37B
// Deleting-dtor shape: releases holder target via rowed fastcall Release at 0x0007DEEF
// then conditionally deletes this when flag bit0 is set and returns this.
// Same 37B shape as rva005F0647 deleting 0x005F0647 (push esi mov esi ecx test holder
// lea +0x24 fastcall Release test flags push esi call delete 0x0002FD60 ret 4).
// Evidence: lea [eax+0x24] plus Release 0x7DEEF matches Rva005E7198 holder layout;
// callers at 0x005E7BDC 0x005E7BED 0x005E7D33 0x005E7D65 0x005E8737; loop at 0x005E7BE2
// destroys 4B elements with flag 0.
struct TargetRef00217D4C { virtual void *destroy(unsigned int); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
void operator delete(void *);
struct Rva005E74AAHolder { char pad[0x24]; TargetRef00217D4C target; };
struct Rva005E74AA { Rva005E74AAHolder *holder; void *rva005E74AA(unsigned int); };
void *Rva005E74AA::rva005E74AA(unsigned int flags)
{
    if (holder)
        ReleaseTreeHintRef00217D4C(&holder->target);
    if (flags & 1)
        ::operator delete(this);
    return this;
}
void __cdecl Rva005E7BE2Destroy(Rva005E74AA *first, Rva005E74AA *last, void *ignored)
{
	while (first != last) {
		first->rva005E74AA(0);
		++first;
	}
}
void __cdecl Rva005E7FB0Forward(Rva005E74AA *first, Rva005E74AA *last)
{
	char tag;
	Rva005E7BE2Destroy(first, last, &tag);
}
