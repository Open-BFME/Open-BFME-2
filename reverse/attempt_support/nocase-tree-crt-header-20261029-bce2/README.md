# Nocase tree CRT declaration cleanup

Base 8b86f9f4f75, 2026-10-29. The picker claimed the whole
stlport_rb_tree_insert_unique_nocase.cpp source for Microsoft-header cleanup.
Its only current ledger body is the 27-byte NoCaseTreeValue4 pair copy
constructor at 0x00466EA7; historical insertion comments are not fresh coverage.

Replace the local imported _memicmp declaration with <string.h>. The source
already declares compareNoCase out of line, so its actual comparison/import
call belongs to the existing provider. No import call or alternate binding
is introduced here. Existing optimization pragmas and other debt remain.

The full source builds 1/1 exact before and after and passes the defined-body
check. Its single normalized code binding is unchanged, as are all external
COMDAT digests/verdicts, definitions, undefined names and weak aliases.
The fresh Microsoft-header classification is clean. The owning tool's
refresh_queue API removes only this served row, preserving every unrelated
queue record byte-for-byte. An initial scoped CLI scan's whole-queue output
was restored before this supported refresh; it is not a project-wide result.

No source path, ledger row, pin, hatch or shared header changes. No new bytes,
census linking gain or runtime result is claimed. Whole-file checks and scoped
controls are retained with this handoff.

The supported preparation produces a strict reusable source receipt. The
outgoing audit at base 49d3bb379d5 remains INCONCLUSIVE: index 840db2d676
predates it and affected consumer Common/0CreateAHeroManager21FE49.cpp lacks
a current receipt. Carry the provider/consumer scope into the next normal
census. No full linking clearance is claimed.
