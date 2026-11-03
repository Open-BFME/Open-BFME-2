### LINK-148: Rva006F84C0's destructor is an implicit derived destructor folded with Rva006F8460's (2026-10-29, seat b1)

Status: open (hatch retired, unit still unlinked). Rva006F84C0DeletingDtor.cpp
(35 B) defined a fake `present-unmatched` `~Rva006F84C0` (`m_pad[0] = 0`)
that the link selected for `??1Rva006F84C0@@UAE@XZ`, which symbols.csv pins to
0x006F8460 (rowed `??1Rva006F8460`). The class is now modelled as deriving
from Rva006F8460 with an implicit destructor (no vptr reset), and an
`absent-from-retail` construction anchor emits the vtable and `??_G`
(1/1 exact; present_unmatched -1). Remaining: VC7.1 keeps the implicit
`??1Rva006F84C0` out of line as a call to `~Rva006F8460` instead of inlining
it into `??_G`, so link_check still reports that COMDAT as not retail's.
Retail's twin is the base body inlined into the implicit destructor, which
needs the base destructor visible inline in one unit without a second
`??1Rva006F8460`/`??_7Rva006F8460` copy.
