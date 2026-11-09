### LINK-249: Rva003ED658 provider member lifetimes block final header adoption
Status: destructor provider repaired; copy provider blocked. Updated: 2026-11-09; inspected revision: `6f19db3538`.
Completed / evidence: three consumer views now use the canonical header; 58/58 rows byte-match, all three link previews pass, and the acceptance tool retired three header-queue rows; [verification and remaining provider evidence](../../reverse/attempt_support/rva003ed658-header-adoption-20261104/readme.md).
Remaining / next check: `Common/BitRange.cpp` needs its vector-member copy/unwind lifetime preserved; `Common/RvaTreeDtorFamily.cpp` needs its holder-member cleanup preserved. Reconstruct those member lifetimes before replacing the provider views, then verify bytes/EH and run `header_adopt_lane.py accept` for both. Their queue rows remain.
Clearance: three consumer adoptions verified; the two provider adoptions remain blocked. Census confirmation: awaiting; no new measurement claimed.

2026-11-09: the destructor provider now adopts the canonical12B descriptor
with a real owning first member. The shared4B holder's pointer is void*, so
the vector begin/end/capacity facts remain intact. Its existing14B cleanup
and the pinned58B descriptor destructor/EH graph stay native-exact; no new
alias/pin is admitted. All23 header dependents pass899 bodies,32 data rows,
149 exact EH graphs and23/23 LINKS35439->35439. Owning acceptance retires
this provider's one queue row. BitRange.cpp's vector-copy/unwind lifetime
remains required before accepting its separate row. Actual next-image
selection and runtime confirmation remain open.
[Current ownership and verification](../../reverse/attempt_support/vector-owner-lifetime-20261109.md).
