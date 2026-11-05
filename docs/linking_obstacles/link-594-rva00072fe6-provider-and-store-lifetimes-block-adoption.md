### LINK-594: Rva00072FE6 provider and store lifetimes block final header adoption
Status: Blocked. Updated: 2026-11-05; inspected revision: `10b5d79f4820`.
Completed / evidence: three consumers adopted the canonical header; 95/95 byte checks and 17/17 EH graphs pass, all three link previews preserve 3,927 B, and cohort acceptance retires three header-queue rows; [scope and remaining prerequisites](../../reverse/attempt_support/rva00072fe6-consumer-adoption-20261105/readme.md).
Remaining / next check: `Common/RvaTreeDtorFamily.cpp` needs its holder-member normal/EH cleanup preserved; `Common/RTS/PlayerTemplate.cpp` needs its inherited set constructor and operations preserved. Both private views and queue rows remain unchanged.
Clearance: three consumer adoptions verified; the provider and store remain blocked. Census confirmation: awaiting; no new measurement claimed.
