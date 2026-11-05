### LINK-400: AptAnimation AptCIH adoption changes loader parameter-load order
Status: Blocked. Updated: 2026-11-05; inspected revision: c1a5a2b848.
Scope: Code/Libraries/Source/Apt/AptAnimation.cpp, AptCIH header adoption; loader RVA 0x006E5050.
Completed: canonical consumer trial passes seven of eight rows; restored source passes 8/8. Header debt remains.
Remaining / next check: isolate the declaration/inlining input controlling the loader's two independent parameter loads; five code/helper-order trials retain the same four-byte difference.
Clearance: pending; no source change, link preview or census gain claimed.
Evidence: [candidate patch and exact mismatch](../../reverse/attempt_support/aptcih-animation-adoption-20261105-codex5/README.md).
