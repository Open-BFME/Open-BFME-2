# SiegeDockingBehavior consolidation: one donor unblocked

2026-11-04; inspected base `823f33323e`, reconciliation `502d358f19`.

The default picker claimed the TU and eight candidate donors. The current
in-memory TU map approves the provisional Behavior/SiegeDockingBehavior.cpp
group; this does not establish retail's original source-path spelling. The
committed map was not regenerated. The consolidation planner under
GameLogic/Object/Behavior surveyed 428 sources, with no missing inputs; its
packets grant no placement approval.

Before reconciliation, `tu_skeleton.py --merge ... --dry-run` accepted no donors.
The seed includes SiegeDockingBehaviorView.h, whose class lacked stopDocking.
The donor instead declared a separate padded class and a vector<void *> at
+0x24. The existing constructor view has its three vector words at that offset.

Reconciliation adds the existing private, nonvirtual, nothrow declaration to
the shared view and makes StopDocking.cpp include it. The body views that
storage as the existing void-pointer vector for erase. It keeps loop begin/end
accesses through the member, preserving retail's separate this/vector register
lifetimes. Using only the local vector pointer changed register allocation and
failed comparison; that version was replaced before committing.

Verification of the committed reconciliation:

- Scoped header gate: 8/8 rows exact across the seed and StopDocking.cpp;
  string, float and import checks pass; no newly unmatched definitions.
- Code identity: zero new findings; data identity: zero findings, including
  the enforced converged-address check. No debt key or hatch was retired.
- Microsoft-header scan: two sources, zero local Microsoft declarations.
- Published index: `5a13f2cd61`, census 2026-11-04 02:25. Link preview retained
  204/204 authored bytes for the seed and 49/49 for StopDocking.cpp. This is
  preview evidence, not a new census or real-link measurement.
- New merge dry run accepts exactly the seed and StopDocking.cpp, eight rows.
  Its census link guard passes. The other seven donors remain rejected:
  missing member declarations/class-view conflicts, STL specialization ordering,
  NameKeyGenerator redefinition, and destructor bytes. Mixed donors remain put.

Application was attempted normally, without --no-claim. It wrote nothing:

```text
blocked: held by another worker: 0x00068E15, 0x0007E48F, 0x002DFCF6
```

A read-only claim dry run confirms all three belong to
`yasinschroeder-claude2`. They are container ICF addresses in candidate donors
that the dry run rejects, but the merger claims its whole candidate scope
before composing. Its CLI has no donor-subset application option. No check was
bypassed and no source move or file-count reduction is claimed.

Next: after those claims clear, reclaim the TU scope and run the ordinary
`tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Behavior/SiegeDockingBehavior.cpp`.
Then build the merged TU, check unmatched declarations, audit path consumers,
queues, identity/provider bindings and the outgoing link batch before publishing.
The current dry run proves one donor can be absorbed; it does not approve the
remaining donors. The earlier "accepts 0" attempt is superseded only for this
verified subset. The existing LINK-168 repair's vtable scope is unchanged.
