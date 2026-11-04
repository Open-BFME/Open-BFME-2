# W3DSnow blend/state consolidation

2026-11-04, yasinschroeder-codex4. Applied after canonical Overridable
adoption (074c2ac184) and shared resource-view reconciliation (a7d6eb80bc).
The supported consolidation planner was refreshed and its snapshot check passed.

`tu_skeleton.py --merge` accepted the existing W3DSnow.cpp plus
W3DSnowBlendPhase.cpp and W3DSnowStateTransition.cpp. The two absorbed methods
are approved for this TU in the current map. Only their source columns changed
in functions.csv and tu_map.csv; the map was not regenerated. Two source files
are removed, with no added or removed function rows. The composer reports 22
row identities; the ordinary byte gate verifies 23 ledger rows, including the
pre-existing duplicate funclet spelling at 0076007A, unchanged by this work.

Verification and provider audit:

- ./build.sh final TU: 23/23 exact, seven float literals, one empty-string
  reference and import checks pass. Frozen-source check clear; check_csv passes.
- EH: 3/3 EXACT. data_check: zero findings. Staged TU ownership check passes.
- Saved the three standalone objects before composition. Comparing all 48
  external definitions with the final object finds no added/removed definition
  and no changed bytes, relocation names/offsets/types or section flags.
- The supported merge link guard passes against the current census index,
  including selected COMDAT variants and provider/consumer preservation. Normal
  link_check predicts LINKS, 1,932 owned bytes. Its seed-only baseline of 1,384
  excludes the absorbed donors' already-linked 548 bytes: this is consolidation,
  not a measured linking gain. Census referenced: f12552d0a7, 2026-11-04 20:47.
- No data, identity, header or ms-header register keys remain on either donor;
  destination has no findings in those registers. Body/data owner ledgers and
  doxygen input list have no donor entries to transfer. The merge tool ran
  hatch_counters --update; counts and baseline content remain unchanged.

Tooling compatibility audit covers origin/master..a7d6eb80bc plus this staged
merge. This range has exactly two removed source paths, both absorbed here.
A combined full-path/basename search across tools, hooks, workflows, Code,
reverse and docs found no active consumer requiring an edit. Old references
remain only in historical attempt evidence/census/logs, the canonical class
contract's historical private-view evidence, and the composer's source-origin
comments. Neither donor defines a private Overridable view now. Active ledger
source columns resolve to the destination. No alternatename was removed.

Remaining prerequisites: update/updateIniSettings still encounter RefCountPtr
and OVERRIDE declaration conflicts (the earlier float-codegen trial remains
banked); render encounters OVERRIDE conflicts; renderSubBox encounters a
DX8Wrapper redefinition. RenderAsQuads remains mixed. Those donors were left
unchanged. Scoped local naming for the two moved methods follows separately.

Local logs: build/codex4-snow-merge.log, build/codex4-snow-merged-build.log,
build/codex4-snow-merged-eh.log, build/codex4-snow-merged-data.log,
build/codex4-snow-merged-link.log, build/codex4-snow-merged-comparison.log,
build/codex4-snow-final-path-audit.log. Object snapshots and comparison script
are scratch under build/codex4-snow-premerge and build/codex4-snow-compare.py.
