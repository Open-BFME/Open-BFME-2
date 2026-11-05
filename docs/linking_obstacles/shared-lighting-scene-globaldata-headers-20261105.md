### Shared scene and GlobalData definitions in the lighting family (2026-11-05)

Status: Cleared for this source's two header adoptions. Inspected base c759a5bbbe9.
Scope: W3DDisplayLightingScale.cpp's seven existing native lighting rows.
Completed: remove private RTS3DScene/GlobalData bodies in favor of their unchanged
canonical headers. The native slot6 ambient call and field+0x144 remain intact;
shared GlobalData fields at+0x134/+0x3C8/+0x650 replace private padding/arrays.
The local recovered RGB assignment view preserves native three-input snapshots.
All7 rows,12 prior definition/relocation fingerprints and all old providers are
preserved; no virtual table is emitted. Strict-current and new-variant checks
pass; ordinary preview retains LINKS1119B against indexc95fcfcfcd (05:17 Nov5).
Both owning accept verdicts retire one header-queue row each, two total.
Remaining: other class consumers and original RGB/field0650 identities remain
unproved. Full outgoing consumer selection is not inferred from this preview;
carry this provider and affected consumers into the next scheduled census.
Census, real-link and runtime clearance: not claimed.
[Exact object and owning-acceptance evidence](../../reverse/attempt_support/lighting-shared-headers-20261105/readme.md).
