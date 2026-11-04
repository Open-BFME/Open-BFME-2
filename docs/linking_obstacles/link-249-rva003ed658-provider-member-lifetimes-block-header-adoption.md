### LINK-249: Rva003ED658 provider member lifetimes block final header adoption
Status: Blocked. Updated: 2026-11-04; inspected revision: `b412381ec5`.
Completed / evidence: three consumer views now use the canonical header; 58/58 rows byte-match, all three link previews pass, and the acceptance tool retired three header-queue rows; [verification and remaining provider evidence](../../reverse/attempt_support/rva003ed658-header-adoption-20261104/readme.md).
Remaining / next check: `Common/BitRange.cpp` needs its vector-member copy/unwind lifetime preserved; `Common/RvaTreeDtorFamily.cpp` needs its holder-member cleanup preserved. Reconstruct those member lifetimes before replacing the provider views, then verify bytes/EH and run `header_adopt_lane.py accept` for both. Their queue rows remain.
Clearance: three consumer adoptions verified; the two provider adoptions remain blocked. Census confirmation: awaiting; no new measurement claimed.
