# Script TU consolidation audit (2026-11-04)

`tu_skeleton.py --merge` absorbed
`Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript_parseTooltip.cpp`
into `Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp`.
One source file is removed. The parent at 0x00315BA3 and its EH rows at
0x0077A555 and 0x0077A55D move without changing names, extents or notes;
all 33 resulting rows remain byte matched. No identifier is renamed.

The GUI consolidation planner was refreshed after the publisher's rebase.
The merge rebuilt current TU assignments in memory; all three moved rows have
the destination's approval. The committed TU map changes only their source
cells. Other donors remain separate: private class/header conflicts, duplicate
anchor bodies and the Rva0031763A layout need reconciliation first. The
[preceding validation](../gui-script-inline-depth-20261103/validation.json)
records those diagnostics and adoption prerequisites. The composition fix
preserves the seed's inline-depth scope around its four callback-name globals.

Verification: the original Script passed 30/30 rows before composition; the
merge preserved both inputs, and a normal `./build.sh` on the resulting TU
passed 33/33 rows, 27 literals plus two empty-string references and three
named imports. Parent EH verification accepted renumbered funclet labels.
Frozen-file checks passed before and after (the existing WindowLayoutInfo
constructor marker is unchanged). `check_csv.py` and `git diff --check` pass.

[objects.json](objects.json) compares receipt-current objects before and after.
The union of 35 strong definition names and 728 COMDAT (name, digest, size)
tuples is unchanged. All 13 distinct linker-directive tokens, all eight aliases
and empty COMMON/weak sets are preserved. The sole undefined-symbol change is
removal of the now-internal parseTooltip reference. No alternatename was removed.
The merge's LinkGuard accepted the inputs and outside consumers against the
2026-11-03 20:03 census index at 8661f15284. The final `link_check.py` preview
reports LINKS for 2,956 bytes, with one unreferenced register-allocation
diagnostic; this is not a new census or real-link measurement.

Neither input has gate, code/data identity or header-queue debt keys. The tool
repointed the three ledger and TU-map source cells; header queues and hatch
totals have no diff. No fold-proof or provider binding needed a path update.
The commit hook's shadow code-identity check reports a divergent const Object
list-iterator constructor. Its 11-byte COMDAT already existed in the original
Script object (digest `431f5c99fd6f`) and remains unchanged in the exact union
comparison; this is inherited identity cleanup, not a new emitted body.
The relevant GUI identity obstacle entry was checked; this merge changes no
identity route or next step, and no new linking obstacle was encountered.

The final compatibility audit fetched origin/master at e1ffb0b1df and covered
the pending range from common base 9fdd9449ea through dbede0d94a plus this
staged merge. Its two removed paths are this donor and the previously handed
gamebrowser donor `Code/GameEngine/Source/Common/Rva007F63D0Set.cpp` (see its
[audit](../gamebrowser-consolidation-20261103/README.md)). Combined searches of
tools, hooks, workflows, source/includes, root build/configuration files,
ledgers, registers and documentation found no active consumer needing a fix.
Remaining old-path mentions are the historical link_status census, provenance
comments and attempt evidence. The stale live comment referring readers to
the removed parseTooltip file was updated. No further path changes are pending.
