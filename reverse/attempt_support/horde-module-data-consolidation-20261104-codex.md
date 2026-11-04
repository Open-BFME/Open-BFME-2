# Horde module-data constructor consolidation, 2026-11-04

Starting revision: a701181f67. The preceding view reconciliation is documented
in [horde-module-data-view-20261104-codex.md](horde-module-data-view-20261104-codex.md).
Scope claims belong to yasinschroeder-codex.

Regenerated `name_lane.py consolidate --under Code/GameEngine/Source/Common/`
after reconciling the views; `--check build/consolidation` passed before the
merge. Its original-path lead remains provisional; this change follows the
current approved TU assignment, without upgrading that provenance claim.

`tu_skeleton.py --merge Code/GameEngine/Source/Common/W3DHordeModelDrawManager.cpp`
accepted the module-data constructor donor. It moved the existing 159-byte row
at 0x000789E3 into the manager TU, removed one source file, and repointed the
source cells in functions.csv and tu_map.csv. No assignment or row coverage
changed. The merge's current-object link guard protected the twelve touched
census-linked units and their outside providers; this is a consolidation
preview, not a new census measurement.

The ten remaining donors retain their compile, byte-shape, class-adoption or
provider prerequisites. In particular, PairInit's trial still loses another
unit's allocator<LocomotorTemplate const*>::allocate provider; that donor is
retained. The manager's conflicting private container views at +0xC are also
untouched. See the earlier handoff for their context; no linking repair is
claimed here.

Consolidation ownership audit: no donor key exists in the gate, code-identity,
data, header or Microsoft-header registers. The existing ProcessGroup
RefCountClass adoption remains with its unchanged source. The merge tool ran
the hatch transfer; hatch_baseline.tsv has no net diff. Both destination
/alternatename directives and the constructor's vtable binding are retained.
No debt retirement is claimed.

The outgoing source-path audit found no active tool, hook, workflow, include
or explicit source-list consumer of W3DHordeModelDrawModuleDataCtor.cpp. Its
remaining references are provenance comments, historical naming votes and
agreements, the historical link-status snapshot and this handoff. Those
historical records stay unchanged. Only the approved source cell changed in
tu_map.csv; no regenerated map is committed.
The audited range is origin/master at 7d7c230301 through a701181f67 plus this
staged merge; its only source-path removal is this donor.

Constructor locals f15, f8 and f05 still name the literal values they hold;
the inspected constructor supplies no evidence for stronger local identities.

Verification: `./build.sh` on the final TU passes all 72 function checks, both
data rows, three parent-generated EH funclets, three nonempty string literals,
the empty-string references and four floating-point literals.
`find_declared_unmatched.py` reports all defined functions already matched.
`check_csv.py`, staged `tu_ownership.py` and `git diff --cached --check` pass.
The merge engine refreshes header ownership and the Microsoft-header queue;
the follow-up Microsoft-header scan finds no local Microsoft prototypes and
leaves its queue unchanged. Staged data identity reports zero findings.
Staged code identity runs in shadow mode and reports the same existing
0x000799D0 list-clear binding finding seen before the merge; its body and
binding were not changed here. This finding remains unresolved.
The converged-data check passes against the final object: eleven addresses,
zero second names and zero unjudged rows.
