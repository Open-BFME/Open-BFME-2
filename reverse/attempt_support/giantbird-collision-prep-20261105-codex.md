# GiantBird collision consolidation prerequisite

The first guarded merge rejected `GiantBirdAIUpdateOnCollide.cpp` because
the seed's `GiantBirdAIUpdate` did not declare `onCollide`. The seed now
declares that existing canonical-base override and carries the donor's
`Object` method declarations and radius field at +0xB8. The seed's inherited
template pointer remains at +0x04; its accessor uses `Thing::getTemplate`.

The collision donor now reads byte zero of the seed's existing +0x108
template byte array, rather than spelling the same byte as a separate scalar.
This reconciles private views; it establishes no new target names or layouts.
The target offsets and method signatures were already used by the verified
collision donor. No source or ledger path has moved in this prerequisite.

Validation:

- `./build.sh` on the seed and collision donor: 19/19 matched, including
  three renumbered unwind labels and one STLport constructor fold.
- `find_declared_unmatched.py` on both sources: all definitions rowed.
- `link_check.py` on both sources: 2/2 LINKS, 2,487 -> 2,487 bytes,
  against the 2026-11-05 05:17 census at c95fcfcfcd. This is a prediction.
- `git diff --check`: clean.

Next: refresh the consolidation evidence snapshot and rerun the guarded merge.
The earlier factory, Xfer, waypoint and private Object-view blockers remain
independent prerequisites unless a new trial proves otherwise.
