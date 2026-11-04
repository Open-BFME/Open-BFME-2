# LivingWorldScoreKeeper transfer consolidation (2026-11-04)

Base: 45a6a985e0. Approved destination:
`Code/GameEngine/Source/Common/LivingWorldScoreKeeper.cpp`.

The supported `tu_skeleton.py --merge` absorbed `Rva004EE15BFwd.cpp`,
repointed its 0x004EE15B row and source cell in the TU map, and deleted the
single-function donor. Source files decrease by one; matched coverage is kept.
The prerequisite commit replaced its private Xfer slots with the canonical
Version and short overloads. Existing PerTurnStats storage is retained.

Verification:
- Dry run and applied plan accept the seed and transfer donor (70 baseline rows).
- Final `./build.sh` passes 78/78 ledger rows, two data rows, one string,
  seven named imports and the existing parent-proven funclet label checks.
- The frozen-file check passes. `check_csv.py` passes.
- LinkGuard accepts composition against the 2026-11-04 census. Scoped
  `link_check.py` predicts the destination LINKS at 3,425 B versus its old
  3,347 B plus the absorbed donor's 78 B. This is preserved coverage, not a
  census gain or a real-link measurement.
- The native-child scoped naming batch reviews both complete-function bindings;
  `transfer` and `versionBytes` apply together and pass all 78 rows again.

Path/debt audit covers the entire pending path-change batch at this base:
only this donor is removed. Searches of tools, hooks, workflows, sources,
headers, configuration, ledgers and documentation find no active hard-coded
consumer. Remaining mentions are the source provenance comment, the historical
census `reverse/link_status.csv`, prior attempt evidence and LINK-182's dated
handoff. These remain historical. No baseline, hatch, pin or alias is removed.
The donor has no protected debt keys. The three existing destination header
queue rows remain; the merge tool refreshes the Microsoft-header queue and
preserves its destination debt (the only diff is row ordering).

Remaining donors are unchanged: collectEndOfTurnStats needs canonical member
views; the division/tree and vector helpers redefine STLport internals; the
transfer-vector parent still fails composition bytes. LINK-182 and the
uw_gen_004 obstacle already cover the PerTurnStats family and stack-frame
prerequisites; this merge does not change their next steps. Claims initially
failed transport confirmation, then the normal claim-tool retry succeeded.

Commit-hook follow-up: all 78 rows, four EXACT EH records, data and pin checks
pass. The identity shadow scan reports four out-of-register definition
findings (two TemplateCountKey allocator divergences and duplicates of
rva004EE8B8/rva004EE950); no identity key is retired. The source bodies and
compiler flags of those existing helpers are untouched. Publication rebasing
also preserves the concurrent dx8webbrowser header-queue append.
