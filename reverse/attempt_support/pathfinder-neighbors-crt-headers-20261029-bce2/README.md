# Pathfinder neighbors CRT header cleanup

Base 385303a9af9, 2026-10-29. The picker claimed the whole
PathfinderRva002F83F5Neighbors.cpp file for three local Microsoft declarations.
Replace fabs, fprintf and memset declarations with math.h, stdio.h and
string.h. The existing intrinsic memset directive remains. No shared header,
source path, function row, pin or hatch is changed.

The current ledger owns one 1,803-byte neighbor-expansion body at 0x002F83F5.
It builds exact before and after; five compiler float literals and both
named import references verify. All 27 normalized code-reference records
are identical. External COMDAT fingerprints/verdicts, definitions, undefined
names and weak aliases are identical as sorted multisets, retaining duplicate
counts; the raw COFF listing order changes. There are no ledger-parent EH
graphs in this unit. The defined-body check passes with its pre-existing
unclaimed-definition note; no new body or marker is introduced.

The fresh scoped Microsoft-header classification is clean. The owning
refresh_queue API removes only this source's queue row, preserving every
unrelated record. This is header debt retirement, not new C++ coverage,
census linking progress or runtime verification. Earlier selected-copy
blockers in other Pathfinder units are not repaired by this declaration edit.

A strict reusable source receipt is prepared. The outgoing audit at base
385303a9af9 is INCONCLUSIVE: index 840db2d676 predates the base and affected
consumer Common/0CreateAHeroManager21FE49.cpp lacks a current receipt.
Carry this provider/consumer scope into the next normal census. Full batch
linking remains unverified; the scoped object controls do not replace it.

The normal hook expands verification to three included-file-dependent units:
39 rows, four data rows and four EH graphs pass. Its wider audit is also
INCONCLUSIVE: two source objects lack current receipts, first GameClient/Eva.cpp.
Carry this wider consumer scope into the next census as well.
