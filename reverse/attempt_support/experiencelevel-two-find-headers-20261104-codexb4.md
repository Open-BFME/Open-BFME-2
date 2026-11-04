# Experience-level find consumers: canonical Overridable

Base: `e723539154`; ordinary link preview uses the census from
2026-11-04 07:28 at `a62ac1c10b`.

The two remaining find consumers at 0x0028951F (144 bytes) and 0x002897A8
(106 bytes) now include Common/Overridable.h instead of defining private
Overridable classes. Both explicitly select the const
friend_getFinalOverride overload, preserving the call to 0x00288609.

Target/compiler facts: the first consumer reads its list key at node +0x1C
and calls the base at node +8. Its canonical 16-byte base replaces the old
eight-byte view and the following eight bytes of padding, preserving that
key offset. The second consumer's value reads are at complete-object +0x18,
beyond the canonical base; these remain explicit offset reads rather than
inventing a base member. Its unused embedded base is removed from the
node's traversal-only view. Neither consumer creates, destroys, allocates,
or takes sizeof these node views. No application type identity is recovered.

Verification:

- Ordinary `./build.sh` over both sources, before and after: 2/2 complete
  function rows, string, float and import checks pass.
- `find_declared_unmatched.py` over both sources passes before and after.
- External symbol sets and relocation-aware COMDAT digests are identical
  before and after, compared using `tu_views.coff_externals` and
  `link_census.comdat_bodies` on the ordinary build objects. The 0x0028951F
  source has 27 external symbols and 23 COMDAT bodies; 0x002897A8 has five
  external symbols and one COMDAT body. This also preserves the unrowed
  static helper's existing binding and all incidental providers.
- `header_adopt_lane.py accept --class Overridable` passes both sources
  together and retires exactly their two header_queue.tsv rows.
- Ordinary `link_check.py` predicts LINKS for both: 144 -> 144 and
  106 -> 106 authored bytes. This is a scoped preview, not a new census
  or real-link measurement.

The supported consolidation planner was run under
Code/GameEngine/Source/GameLogic/System/ before choosing this prerequisite.
The current approved TU plan still contains 14 donor files. The wider
base/virtual and container composition blockers remain; no full merge was
rerun and no source-count gain is claimed. No paths, function ledger rows,
pins, aliases, hatches, or data/code-identity debt keys changed.
