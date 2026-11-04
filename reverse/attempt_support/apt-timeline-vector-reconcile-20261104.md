# AptTimeLine vector consolidation prerequisite, 2026-11-04

Inspected master bd70c5a4ce; census index f6d845ecd4 (2026-11-04 13:15).
Scope: StlSweepR3Rva0051F7AD.cpp, assignment at RVA 0x0051F7AD, 206 B.

The approved destination is GameClient/GUI/GUICallbacks/Apt/AptTimeLine.cpp.
The original donor redeclared STLport allocator/vector/__false_type, preventing
composition with the destination's real <vector> include. The cleanup uses
STLport's complete vector for the assignment and its allocation proxy storage.
Only the external allocation owner's opaque specialization remains bounded.
Declaring that member specialization on the complete vector triggers cl 7.1
C1001 (P2 main.c:148); the bounded specialization preserves its native symbol.
A derived false-type tag with a user-provided constructor prevents the extra
zero initialization emitted for STLport's POD tag. No element identity is inferred.

Checks: ./build.sh donor passes 1/1 (206 B), including call relocations;
find_declared_unmatched reports all definitions matched; link_check predicts
LINKS, 206 -> 206 B against the stated index. No census gain is claimed.
The merge dry run now accepts this donor without losing a seed row or link.
StlSweepW4Rva005205DA.cpp remains rejected for its existing 80-byte element
identity conflict (LINK-002); it is unchanged. The scoped planner report was
regenerated after the initial trial, before the prerequisite source edits.

## Applied consolidation

After prerequisite commit b1bd8a1ad6, the planner was regenerated against the
rebased inputs, then tu_skeleton --merge AptTimeLine.cpp was applied. The tool absorbs the
assignment donor, repoints its sole functions.csv row and tu_map source cell,
and deletes the source. No TU assignment or regenerated map is committed.
SOURCE FILES decreases by one; no matched/link census gain is claimed.
The final ./build.sh reports 136/136 functions exact, the data row exact,
70 funclet pins verified and two emitted STLport constructors folded to retail.
The frozen-source check passes (the pre-existing one unclaimed anchor remains).
check_csv passes with all ledger row counts unchanged.

The final ordinary link preview predicts LINKS: AptTimeLine.cpp 9,826 ->
10,032 B, accounting for the absorbed 206 B rather than a newly linked body.
Its nine diagnostics concern unreferenced differing COMDAT copies, not blockers.
The merge LinkGuard checks both previously census-linked units together.

## Consolidation and tooling audit

Audited all outgoing source-path changes through this merge: the previously
handed-off DamageFilteredCreateObjectDieDamageSlots.cpp move and this donor.
Combined searches of tools/, .githooks/, .github/, Code/, source configuration,
active ledgers/registers and documentation find no active hard-coded consumers
requiring edits. Remaining old paths are historical census link_status.csv
entries, historical evidence/docs and merge provenance comments. The explanatory
provider comment in StlSweepW5Rva0051FC54AssignTwin.cpp was updated to name
AptTimeLine.cpp, with its assignment body unchanged. No include names an
absorbed donor, and no tooling directory/glob depends on its continued presence.

The donor owns no data/code-identity debt or header/ms-header queue rows. The
merge tool refreshed/transferred those reports and hatch ownership; their
committed contents are unchanged. Existing AptTimeLine header adoption debt stays
registered, and no debt key is retired. The data row stays in the destination.
No aliases or pins are removed; the external allocation/copy bindings are kept.

Scoped naming was attempted on the inspected complete operator= scope at the
final TU path. The picker reports no available complete functions fit; no
inventory or naming application is claimed. Existing STL donor spellings stay.

## Broader link audit limitation

The staged-tree batch audit was rerun after preparing the destination and its
unchanged assignment consumer. Both sources have reusable receipts accepted by
the audit. Consumer StlSweepW5Rva0051FC54AssignTwin.cpp passes 1/1 byte checks
(111 B) and previews LINKS, 111 -> 111 B. Only its provider comment changed.
The destination's prepare-current run passed all normal byte/data/ref gates but
reported "preparation inputs or verified objects moved; no witnesses accepted";
no witness/index exception was recorded. Its receipt was accepted by the next
batch audit. The consumer's prepare-current run completed successfully.

Final batch audit (HEAD b1bd8a1ad6 to staged tree), exit 2:

    INCONCLUSIVE baseline: index at f6d845ecd4, outgoing base HEAD
    INCONCLUSIVE: affected consumer lacks current receipt:
      Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp

The older index also differs from the outgoing base. This is unverified broader
consumer scope, not a clean batch result; carry this affected consumer and the
merged destination into the next census. Do not attribute a new link headline
to the ordinary previews or the merge guard. No shared declarations or aliases
were removed, and the byte-verified native calls retain the same provider names.
