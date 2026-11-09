### LINK-614: Rva00072FE6 provider and store lifetimes block final header adoption
Status: destructor provider repaired; store adoption blocked. Updated: 2026-11-09; inspected revision: `6856b21969`.
Completed / evidence: three consumers adopted the canonical header; 95/95 byte checks and 17/17 EH graphs pass, all three link previews preserve 3,927 B, and cohort acceptance retires three header-queue rows; [scope and remaining prerequisites](../../reverse/attempt_support/rva00072fe6-consumer-adoption-20261105/readme.md).
Remaining / next check: `Common/RvaTreeDtorFamily.cpp` needs its holder-member normal/EH cleanup preserved; `Common/RTS/PlayerTemplate.cpp` needs its inherited set constructor and operations preserved. Both private views and queue rows remain unchanged.
Clearance: three consumer adoptions verified; the provider and store remain blocked. Census confirmation: awaiting; no new measurement claimed.

2026-11-09: the canonical12B tree now carries a real4B owning first member;
count+4 and opaque+8 remain. Ten clear/range/visitor pointer expressions keep
their original reloads. The provider adopts the header; owning acceptance
retires its one row. Full22-source verification passes944 bodies,17 data rows
and199 exact EH graphs. Preview is21/22 LINKS: W3DShroud's existing8B
Rva00072FE1 table conflict is identical before/after under a private baseline
LinkGuard comparison; it is not introduced by this repair. PlayerTemplate's
set construction/operations, that independent table-selection gap and normal
census/image confirmation remain open.
[Ownership, baseline comparison and scope](../../reverse/attempt_support/int-tree-owner-lifetime-20261109.md).
