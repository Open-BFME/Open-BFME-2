# Camera timestep list-header adoption

Inspected revision: `40d4b4984fb1de1486f653e33c1614ec656a822f`.
Scope: `Code/GameEngine/Source/Common/Rva00065E3CMethod.cpp`.

The consolidation picker selected `camerashakesystem.cpp`, whose only clean
donor failed its merge trial on the private `GenericMultiListClass` field
names. The evidence planner surveyed the W3D GameClient subtree; its stale-map
and mixed-file warnings do not approve moves. `tu_skeleton.py` rebuilds the
map in memory and leaves `camerashakesystem_shaker.cpp` mixed and untouched.

The donor now includes the registered `GenericMultiListClass.h`. Its five
pointer words become the canonical `Head` node; `Head.Next` and `&Head`
preserve the target's +8 and +4 accesses. The local template exposes the two
protected operations used by the timestep, replacing the private base's friend
grant without changing either called symbol. No shared header changed.

Verification:

- `./build.sh Code/GameEngine/Source/Common/Rva00065E3CMethod.cpp`: 4/4 rows
  exact, including the 18-byte list constructor and the parent EH graph. The
  compiler label changed from `$L437` to `$L503`; verified parent EH data still
  places its funclet at RVA `0x0075E6AB`.
- `find_declared_unmatched.py`: all defined functions already matched.
- `header_adopt_lane.py accept --class GenericMultiListClass` on this file:
  PASS; retired exactly its one header-queue row, with byte/link acceptance.
- Merge dry run still refuses the donor because the destination template
  lacks the donor's public using-declarations. Reconcile that local template
  separately before merging. No source path moved in this change.

No new linked-byte or real-link result is claimed.
