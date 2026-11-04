# ToggleMountedSpecialAbilityUpdate constructor merge, 2026-11-04

Prerequisite: constructor-view reconciliation commit `13d153b03b`, handed to the
fleet publisher before applying this move. See
[treatment and rejected hypotheses](togglemounted-constructor-reconciliation-20261104-codexb4.md).

`tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Update/ToggleMountedSpecialAbilityUpdate.cpp`
absorbs `Update/ToggleMountedSpecialAbilityUpdateCtor.cpp`, removing one source
file. The constructor at 0x004ADAB5 moves into its currently approved TU.
The merger retains all 18 matched rows. It leaves the rejected module-data
constructor/deleter and both mixed donors intact; their remaining blockers are
unchanged from the prerequisite evidence.

## Verification and ownership

- `./build.sh` on the final TU: 18/18 code rows exact, two string literals and
  two compiler floats verified. Four renumbered funclet labels resolve through
  parent EH data (`build/toggle-mounted-merged-build.log`).
- Frozen-source validation, `check_csv.py` and staged whitespace checks pass.
- The supported merger's census-linked guard accepts the combined object while
  preserving the seed, constructor and rejected donors' provider/consumer
  bindings. No alias is removed; the existing SpecialAbilityUpdate alternatename
  and its hatch entry are unchanged.
- Final-path `link_check.py`: LINKS, authored bytes 1,485 -> 1,559 against index
  40fe1783d7 (2026-11-04 12:23). The extra 74 bytes are transferred from the
  removed donor; the two old units already predicted 1,559 bytes together.
  This is not a census measurement or new linked coverage.
- The six changed data-ledger records are strictly old-to-new source-path
  substitutions; row totals, names, definitions and references remain intact.
  `functions.csv` and only the moved row's source column in `tu_map.csv` repoint
  to the destination; the map is not regenerated.
- No code/data identity baseline or gate key belongs to the removed donor.
  The supported merger refreshes header and Microsoft-header queues; neither
  changes for this donor. The seed retains its five pending header adoptions.
  No debt is retired and the hatch register is unchanged.
- Shadow findings from the prerequisite hook remain follow-up work: the seed's
  AsciiString destructor binding and duplicate Rva004ADBD7 definition, plus the
  two getModuleNameKey/triggerAbilityEffect static data names. Byte equality
  and the link preview do not clear them.

## Scoped naming

The final-path constructor/trigger packet covers nine bindings across those two
complete functions, with no coverage warnings. A native child proposed the
batch and the parent scanned all mappings and the diff. `obj` becomes
`owningObject`; eight bindings are retained. The parent's one correction keeps
`key` because preview identifies a possible WorldBuilder EA spelling. Unknown
virtual-slot meanings remain unnamed. `scoped apply` verifies the resulting TU
again: 18/18 code rows and all literals/float references pass. The inferred-name
register records the applied local; no static symbol name changes.

## Complete pending path audit

Audited `origin/master..13d153b03b` plus this staged merge. The complete pending
batch has two removals: this constructor and the already documented
`WWLib/stlport_vector_nocasepair_assign.cpp` -> `Common/TerrainTypes.cpp` move.
Combined basename/full-path searches cover tools, hooks, workflows, Code source
and includes, build/configuration files, docs and reverse registries. No active
consumer still needs either removed source. Remaining old-path mentions are TU
origin comments, historical attempt evidence/logs and `reverse/link_status.csv`,
a census snapshot intentionally not rewritten. No directory is removed.

Both moves' active body owners, data bindings, TU rows, protected debt queues
and hatch/flag registers resolve to surviving files. Relative includes and shim
flags compile at the final paths. Ordinary publication hooks retain the outgoing
batch-wide link audit; any inconclusive consumers still require the next census.
