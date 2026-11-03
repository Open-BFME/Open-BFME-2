### Attack-path logging CRT declaration (2026-10-29, codexb4)

At base `95a2d4676d`, `AIUpdateInterface_requestAttackPath.cpp` now takes
`fprintf` and `FILE` from the toolchain's `stdio.h`. A TU-local `_CRTIMP`
configuration preserves the direct game `_fprintf` wrapper binding at
RVA 0x002CEC42. The log pointer uses `FILE *`; the conflicting local
`fprintf(void *, ...)` prototype is removed. The owning Microsoft-header
scanner refresh removes exactly this file's queue row.

The complete 250-byte function, its string reference, the frozen-source check
and strict current preparation pass. All five COMDAT digests/sizes, the one
exclusive definition and ten undefined external names are unchanged against
the pre-edit object. Ordinary preview retains LINKS, 250 -> 250 authored bytes
against index `840db2d676` (2026-10-28 20:44). This establishes scoped header
cleanup, with no census linking or ownership gain claimed.

BFME 1 upstream was checked at `326ef10249d19dd08940fbf18467af2c98a4305a`;
the update scope remains held by `yasinschroeder-codexb`. The verified
`e42b9782fd4cce1f79832a6ed591b0b8fdbbc2fc` input pin is retained, and no
freshness success stamp is written.

The outgoing staged-tree audit is INCONCLUSIVE: the index predates the base
and affected consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry this provider and consumer into the next scheduled census;
consumer-wide selection is not established by the scoped preview above.
