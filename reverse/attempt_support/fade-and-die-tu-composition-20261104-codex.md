# FadeAndDieOrnamentUpdate composition boundary, 2026-11-04

Inspected `f51b33c222`, seat `yasinschroeder-codex`, model
`gpt-6.1-sol`. No source or ledger change is retained from this attempt.

## Scope and baseline

The current TU map approves four rows in
`Code/GameEngine/Source/GameLogic/Object/Update/FadeAndDieOrnamentUpdate.cpp`:
`getModuleNameKey` at `0x003A4358` (69 bytes), the constructor at
`0x003A439D` (79 bytes), and the name-key method's two EH rows at
`0x00781B3F` and `0x00781B4C`. Only the constructor is in a separate donor,
`FadeAndDieOrnamentUpdateCtor.cpp`. Both file scopes were claimed before work.

The supported planner was run under
`Code/GameEngine/Source/GameLogic/Object/Update/`, followed by
`tu_skeleton.py --plan` and `--merge ... --dry-run`. There are no mixed or
refused donors for this target. The dry run accepts no merge: its seed view
declares only the virtual name-key getter, so the donor constructor is not a
member (C2511). `tu_views.py --dry-run` independently reports the incompatible
base clauses: no base in the seed, `public UpdateModule` in the constructor.

Before the trial, `./build.sh` on both sources passed all four rows, the data
row and string-reference verification. The paired `link_check.py` preview
reported both sources LINKS, 158 bytes in total, against the 2026-11-04
20:47 census/index revision `f12552d0a7`. This is a preview, not a new census.

## Canonical-header trial, reverted

The donor has a private, nonvirtual `UpdateModule` view with explicit vtable
pointer fields at offsets +0, +0x0C and +0x10. `UpdateModule` is registered
canonical. Its header queue row requires adoption of
`Code/GameEngine/Include/GameLogic/Module/UpdateModule.h`; the field
`UpdateModule::m_vtable` has no canonical data-field equivalent.

A trial removed that private view, included the canonical header, and wrote
the same three existing tables through `this`, a
`BehaviorModuleInterface *` cast and an `UpdateModuleInterface *` cast.
It preserved the constructor's member initializations and all existing
table symbols. `./build.sh` failed the constructor's 79-byte comparison:
the compiler inserted derived-class vtable writes in addition to the explicit
ones. The first extra store appears immediately after the call to the base
constructor, where retail instead computes the OrnamentData address at +0x28.
No header, pin, pragma or alias was added to suppress those stores.

The trial was restored from its pre-edit source snapshot. A fresh ordinary
`./build.sh` on both files again passed 4/4 rows, the data row and reference
checks. `find_declared_unmatched.py` on the restored constructor reports all
defined functions matched. No nonmatching reconstruction remains in `Code/`.

## Next useful work

Reconcile the derived class and its real virtual overrides against the
canonical base before retrying composition; adding a constructor declaration
to the minimal seed or merely adopting the base does not suffice. The
constructor still explicitly binds primary table `vtbl_00C1AF60`, the folded
BehaviorModuleInterface table emitted by AttributeModifierPoolUpdate, and
the placeholder `Rva003A4322` secondary table. Establish their native owners
and declaration compatibility before replacing explicit stores with compiler
stores. Any data identity or header debt must follow its owning tool; this
attempt retires no debt.

Historical LINK-168 mechanism 1 repaired this constructor's folded table
binding. The current baseline links; this composition failure is not a
reported link regression. No obstacle entry's status changed.


## Mechanical merge and outgoing-batch handoff (2026-11-05)

The approved merge absorbed `FadeAndDieOrnamentUpdateCtor.cpp` into the existing
TU and preserved all four matched rows. `./build.sh` passed 4/4; the TU frozen-file
check, staged code-identity and data checks, `tu_ownership.py --staged`, and the
converged data check passed. Header and Microsoft-header queues were refreshed.
The path consumer audit for the pending range `origin/master..HEAD` found no active
consumer requiring a manual change; the old path remains in the TU provenance
comment, historical `reverse/link_status.csv`, and `reverse/re_attempts.log`. The
publisher's outgoing-batch `link_batch_audit` remains the provider/consumer and
link comparison for this composition; no new link coverage is claimed until that
receipt is reported.

The fleet publisher currently holds this batch. Outstanding claims are rows
`0x003A4358`, `0x00781B3F`, `0x00781B4C` and file
`Code/GameEngine/Source/GameLogic/Object/Update/FadeAndDieOrnamentUpdateCtor.cpp`.
The audited path-change range is `origin/master..HEAD`; these claims remain live
until the runner lands the batch.
