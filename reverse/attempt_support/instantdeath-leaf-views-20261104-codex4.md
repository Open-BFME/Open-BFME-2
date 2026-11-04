# InstantDeathBehavior leaf declarations (2026-11-04, codex4)

Scope: the constructor, onDie and pool-key donors for
`Code/GameEngine/Source/GameLogic/Object/Behavior/InstantDeathBehavior.cpp`,
on inspected base `be689b7e4f`. This is a consolidation prerequisite, not a
completed merge or a link/census gain.

## Evidence and change

- The supported planner (`name_lane.py consolidate --under Code/GameEngine/Source/`)
  reports the retail original-path string
  `C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Behavior\InstantDeathBehavior.cpp`
  at string RVA `0x00841EB8`, with WB corroboration. This is path evidence;
  `tu_skeleton.py` independently rebuilt the current TU assignment in memory:
  28 approved rows, eight direct files and two mixed files. The planner's
  pre-edit freshness check passed. No regenerated TU map is committed.
- The constructor and onDie donors already use canonical `DieModule.h`.
  `tu_views.py --class InstantDeathBehavior --no-merge-check` reconciled their
  leaf declarations with the pool-key donor. The pool-key file first needed
  the same canonical base include; the earlier tool trial restored its files.
  The retained declarations share the base, constructor, static pool-key
  method and virtual onDie declaration. No implementation or row changed.
- Native constructor/base and existing onDie declarations supply the target
  hierarchy. The tool reports size `0x14` from the constructor; the former
  empty pool-key view did not establish a competing object layout. The donor
  path string does not prove any additional layout or method identity.

## Verification and remaining boundary

- `./build.sh` on the three changed donors: **8/8 rows byte-exact**, including
  their EH funclets; string checks passed (2 rows). The separate pool-key
  include trial also passed 3/3 before reconciliation.
- `find_declared_unmatched.py` passed each of the eight files before work and
  each changed file afterwards. `git diff --check` passed. No pin, hatch,
  provider, ledger path or debt-register entry changed.
- `link_check.py` before and after: all three donors **LINKS**, unchanged
  **521 bytes** (67 + 42 + 412), against the 2026-11-03 20:03 census index
  at `8661f15284`. This preview is not a new census measurement.
- `tu_skeleton.py --merge ... --dry-run`, before and after: **accepted []**;
  no applying merge. Parser donors conflict with the seed's INI and
  SubsystemInterface; pool-key conflicts with SubsystemInterface; constructor
  conflicts with Module/ObjectModule; onDie conflicts with GameLogic and
  SubsystemInterface; module-data constructor conflicts with ModuleData and
  DieMuxData; module-data destructor fails bytes. The two mixed sources remain
  `Common/RvaVectorDtorFamily.cpp` (89 rows) and `Object/Die/DieModuleDerived.cpp`
  (18 rows). The onDie header prerequisites remain AIUpdateInterface and
  Rva0036CA00Str.
- Preserve the seed's legacy parser provider and registered unmatched bodies.
  [LINK-068](../../docs/linking_obstacles/link-068-removing-diemodule-s-unrowed-field-parser-removes-a-live.md)
  records its live link dependency. The next consolidation step remains
  reconciling the seed's legacy header contexts and module-data views, while
  keeping those providers and the eight census-linked units.

## Link audit and outgoing-path audit

The staged batch audit initially reported an inconclusive baseline (index
`8661f15284` versus outgoing base `HEAD`) and three missing current receipts.
The first explicit `link_check.py --prepare-current` run overlapped the merge
dry run and refused moved preparation inputs; no witnesses were accepted.
The sequential retry and final batch-audit outcome are recorded below.

- The sequential `--prepare-current` retry passed: three explicit providers
  byte-verified with strict reusable receipts; 8/8 rows and both strings still
  passed. The compiler reused those receipts for its normal gates.
- Repeating `link_batch_audit.py --base HEAD --tip <staged-tree>` with the
  three verified sources removed the missing-provider-receipt finding. It
  still exited 2, **INCONCLUSIVE**: the index baseline is `8661f15284`, and
  affected consumer `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`
  lacks a current receipt. No consumer-link clearance is claimed; carry this
  three-source declaration scope and that consumer into the next scheduled
  census. No census, nightly or smoke runner was started.

The inherited outgoing range (`9f938bbe30..be689b7e4f`) contains the
W3DSnowManager_reset.cpp absorption; these three declaration changes add no
source moves. A batch-wide search of tools, hooks, workflows, Code, reverse
and docs for that deleted source found only the retained W3DSnow.cpp
provenance comment and historical attempt/audit documents, with no active
path consumer to update. The prior snow audit remains in
`w3dsnow-reset-merge-20261103-codex4.md`. No new linked bytes, lower source-file
count, TU-approved increase or closed obstacle is claimed by this change.
