# Preserved-work recovery, 2026-11-04

Recovered the four commits preserved by
`refs/runner/preparation/1793752277323057256` onto `53af3e7376`.
The preparation record had no stash, resync stash, or untracked edits to restore.
The only conflict was the Script TU consolidation against upstream
`e7c35237e0`: retain the three added WindowStatusNames in the single merged
array, avoiding duplicate copies of the globals/prototypes. All four commits
were replayed; none was skipped. The backup ref remains available.

`check_csv.py`, the Script frozen-file check, and `git diff --check` pass.
`BFME_PUSH_SPACING_S=0 python3 tools/push.py --dry-run` passed the normal hook:
34/34 rows across Script and GrantUpgradeCreate_onBuildComplete, six EXACT
EH graphs, literal/import, converged-data, and DIR32 checks. The output's
"landed" line comes from the dry-run transport; publication is separately
performed by `/opt/runner/publish --now`.

The mandatory batch link audit remains INCONCLUSIVE: index `8661f15284`
predates outgoing base `53af3e7376`, and both changed source objects lack
current link receipts. Carry these sources and their affected consumers into
the next scheduled census:

- `Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Create/GrantUpgradeCreate_onBuildComplete.cpp`

The byte-verification scope above is established; global link preservation
and any census gain remain unverified. No maintainer-only measurement was run.
See [push-dry-run.log](push-dry-run.log) for the hook evidence.

The outgoing path audit covers `53af3e7376..871c12002a`, with one removed
parseTooltip donor. Searches of tools, hooks, workflows, source/includes,
registers and documentation find no active old-path consumer. Remaining
mentions are merge provenance and historical evidence/census records. No
aliases or hatch entries were removed. The preserved consolidation audit and
object-union comparison remain in `../gui-script-consolidation-20261104/`;
the W3D factory trial remains banked in
`../w3d-gameclient-factory-adoption-20261104/` with no source trial retained.
