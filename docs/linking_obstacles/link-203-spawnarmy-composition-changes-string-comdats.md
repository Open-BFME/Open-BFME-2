### LINK-203: SpawnArmy composition changes string COMDAT selection

Status: Blocked for the Equal and Notify donor merges; standalone units remain separate. Inspected `5001bb6e79`, 2026-11-04.
The merge guard rejects Rva004E20ABEqual.cpp's non-retail AsciiString::compare selection and Rva004E35D5Notify.cpp's StringBase operator< reference / less<AsciiString> selection. Reconcile their declaration and inline-overload bindings before retrying.
Evidence and the verified contains-helper merge: [2026-11-04 handoff](../../reverse/attempt_support/spawnarmy-consolidation-20261104.md).
Batch linking remains unverified: strict receipts for SpawnArmy.cpp and its Glo012F1024Item.cpp consumer are missing against the older index; carry both into the next scheduled census. No census gain claimed.

2026-11-04, codex4: Equal's owner repair passes 76/76 bytes, standalone LINKS and the merge trial; apply is deferred by another worker's live claim on shared RVA `0x0007FAB3`. Retry after release. Notify remains blocked. [Scoped checks and handoff](../../reverse/attempt_support/spawnarmy-equality-owner-20261104-codex4.md).


**2026-11-14 supported merge (merge-climb).** The fresh current-tip trial and
application now accept `Rva004E35D5Notify.cpp` with the snapshot destructor
and sub-object-color donor. 87/87 rows and seven data rows verify; three
source files are absorbed into `SpawnArmy.cpp`. All 214 external definitions,
COMDAT bodies/relocations and weak defaults are conserved, with no new
undefined symbols. In particular this move does not select a new StringBase
or less<AsciiString> body. The affected `Glo012F1024Item.cpp` consumer has the
same object except its COFF timestamp and verifies with the merged TU
(129/129 rows). Both have current strict provider receipts and preview LINKS
on census index SHA256
`a5dce5d8f1f697c358276325b8b5237fa360d962837eaf82bcc083acdaf79c0e`.
This clears the Notify composition refusal for the bounded three-donor
cohort. Other rejected donors and broader census/real-link confirmation
remain separate. Evidence: `sweeps/merge-climb/gate-freed-landings/spawnarmy/`.
