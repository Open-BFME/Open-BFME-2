### LINK-197: AptScriptFunction GC donor needs compatible AptValue and receiver views

Status: Blocked. Updated: 2026-11-03; inspected revision: 7c99285f90.
Scope: AptObject/AptScriptFunction.cpp and Common/Rva00709C10Cluster.cpp, RVA 0x00709D80.
Completed: canonical AptValue adoption in the donor; owning acceptance retires one header-debt row, byte check passes, ordinary preview preserves LINKS 113 -> 113 bytes at index 8661f15284.
Remaining / next check: reconcile AptScriptFunction.h's private AptValue with the canonical header, then Rva00709B80's Rva006D6470Owner/Rva006D6360 base and method views; current tu_skeleton merge accepts no donor.
Clearance: donor header debt only; no merge, source-file reduction or census gain claimed.
Evidence: [scoped checks and rejected merge](../../reverse/attempt_support/apt-script-gc-donor-20261103-codex3/README.md).
Publication recovery: [upstream ID collision and correction](../../reverse/attempt_support/preparation-recovery-publication-20261104-codex3.md).
