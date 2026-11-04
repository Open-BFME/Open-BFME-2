# ObjectSMCHelper consolidation prerequisite

Inspected revision: `9781cec8bb`; worker: `yasinschroeder-codexb`.
No source or ledger change was retained, and no file reduction is claimed.

The default picker selected `Code/GameEngine/Source/GameLogic/Object/Helper/ObjectSMCHelper.cpp`
and its `ObjectSMCHelperDtor.cpp` donor. The consolidation evidence planner
reported differing compiler settings and duplicate type definitions. The current
TU map rebuilt in memory by `tu_skeleton.py` approved nine rows; the separate
`SpecialPowerTimerList.cpp` remained mixed (two rows) and was not moved.

Both originals passed `find_declared_unmatched.py`. `tu_views.py` reported a
conflict: the destination derives ObjectSMCHelper from `ObjectHelper`, while
the destructor donor derives it from `Rva004DF7C2`. It applied no reconciliation.
`tu_skeleton.py --merge ... --dry-run` accepted no donors and rejected
`ObjectSMCHelperDtor.cpp` with `bytes`, exiting 2. This is a failed composition,
not evidence of a regression in either original or a specific mismatching opcode.

The destination uses `UpdateModule` through ObjectHelper and a
`list<BfmeSpecialPowerTimer8>` at +0x20. The donor uses an opaque three-base
hierarchy and `list<int>` at +0x20, with declaration-only list destruction and
clear specializations. Its destructor calls the rowed opaque base destructor at
0x004DF7C2. The cl lines also differ (`/EHs` versus `/EHsc`, and the destination
defines `_STLP_NO_EXCEPTIONS`). These are source facts, not proof that any one
difference caused the byte rejection.

Next: reconcile the destructor's base, container identities and exception settings
in a separately verified prerequisite commit, preserving its destructor and
funclet rows, then retry the merge. The destination's existing Drawable,
ModelConditionFlags and Thing header-queue entries remain outstanding. No debt
was retired, no alias was removed, and no new link clearance is claimed.
