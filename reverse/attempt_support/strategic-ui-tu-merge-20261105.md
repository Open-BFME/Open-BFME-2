# Strategic UI destructor TU merge, 2026-11-05

Base: `8b692bd586`, the separately verified canonical-holder adoption.
Absorbed `Code/GameEngine/Source/Common/Rva005E5FFBDtor.cpp` into
`Code/GameEngine/Source/GameClient/GUI/StrategicInGameUI.cpp` with
`tools/tu_skeleton.py --merge`, after its successful dry run. The apply reused
the verified plan and accepted both sources with no rejected donor.

The current in-memory TU map approves this grouping. Its provisional path is
not proof of retail's original filename. The naming planner's original-path
evidence, alternatives and blockers were reviewed before applying the merge;
mixed and refused donors were left alone. This removes one source file and
preserves coverage; it does not recover new bytes.

## Verification

- `./build.sh Code/GameEngine/Source/GameClient/GUI/StrategicInGameUI.cpp`:
  66/66 function rows matched; the existing data row and literal/import checks
  passed.
- `find_declared_unmatched.py`: all defined functions already matched. The
  existing absent-from-retail anchor remains documented.
- `eh_verify.py`: 13 parents, all EXACT; no missing or baseline entries.
- The merge link guard recognized both inputs as census-linked.
- `link_check.py` on the final TU: LINKS, 2,587 own bytes. The previous seed
  had 2,366 bytes; the difference is absorbed donor code, not a census gain.
  This preview is not a real-link or new linking-coverage measurement.

## Debt, ownership and path-consumer audit

Seven function-ledger rows, including their fold-proof path token, moved with
the source. The five TU-map edits change only source columns; assignments and
evidence were not regenerated. All new ledger sources are tracked.

The donor's canonical-holder header row was retired through
`header_adopt_lane.py accept` in the prerequisite commit. Neither input has
gate, code-identity or data debt to retire here. Remaining destination header
debt is retained. The destination's two existing link-wide alternatename
pragmas and hatch entries are unchanged. The merge's whole-tree hatch refresh
also proposed removing an unrelated stale pin entry; that unrelated edit was
restored, leaving no hatch-baseline change in this commit.

Audited the removed path and basename across active tools, hooks, workflows,
source includes, documentation configuration and root build/configuration
files before publication. No active consumer needs the deleted source path.
Remaining references are the merged source's provenance comment, historical
attempt evidence and the historical link census; those records retain their
original paths. Current path-keyed registers contain no deleted-source key.
Provider/consumer verification comprises the successful merge link guard,
final TU link preview and outgoing hook audit. No alias was removed.

The linking-obstacle register has no entry for this donor or observer; this
merge introduces no new obstacle or changed prerequisite. Existing broad
historical entries were left unchanged. Inspected local names already describe
their supported roles; uncertain placeholder identities remain evidence-limited.
