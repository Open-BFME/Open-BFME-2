# PhysicsUpdate seed uses BFME declarations

Inspected base: `de44d2023b`; date: 2026-11-05; seat: codexb4.

The approved PhysicsUpdate TU retained Zero Hour's broad include environment
although it owned only three matched bodies (173 bytes). Earlier consolidation
attempts recorded Coord3D/Xfer redefinitions and missing BFME-only members.
The seed now uses the existing BFME UpdateModule, Coord3D and BfmeE16 headers
and the PhysicsBehaviorCtor donor's existing data view. No donor moves in this
prerequisite commit; no function identity or ledger extent changes.

Target facts: the existing 21-byte row at RVA 0x0053EC42 reads Object +0x74
and stores at receiver +0x58, with zero for a null argument. Its existing
source identity is retained, not independently recovered here. The replacement
Object view and setter use those offsets. PhysicsBehavior's other members are
reused from the already matched constructor's BFME view, not inferred from the
Zero Hour header. No external donor path is claimed as BFME source evidence.

Verification:

- Normal `./build.sh` passes 3/3 rows before and after; see byte receipts.
- `find_declared_unmatched.py` passes before and after.
- All 17 common defined function bodies and their relocation lists compare
  exactly between the original and replacement COFF objects using
  `build.read_object_symbol_bytes`. No code symbol is added. The only removed
  code symbol is compiler helper `??_H@YGXPAXIHP6EPAX0@Z@Z`; its real row remains
  at RVA 0x1423 in `Code/Libraries/Source/ATL/atl_vector_constructor_iterator.cpp`.
- Removed static source helpers emit no code symbols in the original object.
- Link previews pass before and after against the census index dated
  2026-11-05 05:17 at `c95fcfcfcd`; both retain the TU's 173 linked bytes.
  These are previews, not a new census or a game runtime test.

The unchanged-seed merge dry run was interrupted after ten minutes without a
verdict; it wrote no source changes. A new dry run with the verified BFME seed
tests whether this resolves any donor composition blockers. Remaining private
PhysicsBehavior/Object views and header queues are separate prerequisites;
their debt is not retired by this change.
