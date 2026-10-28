# Anim2D lookup alias cleanup and placement prerequisite

Inspected base: `2d245982a2`. BFME 1 reference: `e74410b3738a2bb75d626085d9ebfd3406a43ff7`,
with the verified 2026-10-27 freshness receipt. Published preview index:
`41c28839bf`, 2026-10-28 11:08; fetching retains that local index.

The default picker served Anim2D.cpp TU approval: 46 proposed rows in nine
files. The supported System-subsystem planner flags incomplete routing and
private class views. `tu_skeleton.py --plan` still reports zero approved rows.
At 0x002D7554, `INI::parseAnim2DDefinition` has a Zero Hour INIAnimation.cpp
anchor inside the Anim2D run. Anim2DCollection::init at 0x002D75C6 follows it.
This is the already documented placement limitation in
[the TU approval handoff](tu_approval_20261028.md), session 3. The parser name
is not refuted. No name or map was changed, and no merge was attempted.
Further approval needs a supported way to express the target's placement;
the donor's path and adjacency alone do not authorize moving these rows.

The parser already calls the existing lookup owner at 0x002D752D directly,
but retained an /alternatename from Anim2DCollection::findTemplate. The index's
touch set identifies AutoHealBehaviorPlayerScan.cpp as the remaining caller
of that alias; current source confirms it. Change that caller to the same
call-only Rva002D752D declaration used by the parser, preserving the real
TheAnim2DCollection global's type and casting only at the call. The return
is still used as Anim2DTemplate. This establishes no new original name or
class layout. Remove the now-unneeded parser alias.

`hatch_counters.py --update` drops exactly one alternatename (2,915 -> 2,914).
The existing old-name pin is unchanged; this change introduces no pin or body.
[Object comparison](anim2d-alias-object-20261028-codex.json) preserves all
46 external COMDAT names across the two objects. Bodies and relocation targets
are identical after resolving the former alias. The only changed external
reference is AutoHealBehavior::update's lookup, now naming the existing owner
directly. The parser's three COMDAT fingerprints are unchanged.

Verification:

- Before and after builds pass all 15 affected rows; frozen-file checks pass.
- Both EH graphs are EXACT, including the existing renumbered AutoHeal funclets.
- Strict provider preparation passes the affected sources and the lookup owner
  (16 total rows). Ordinary preview preserves LINKS for all three units:
  parser 114, lookup 39, AutoHeal 1,719 authored bytes.
- The staged-tree batch audit exits 2, INCONCLUSIVE: its index predates the
  base and Common/0CreateAHeroManager21FE49.cpp lacks a current affected-consumer
  receipt. Carry the alias removal and changed caller into the next normal
  census; full consumer verification remains pending.

No census gain, TU approval or source-file reduction is claimed. Scratch
objects and comparison output are under `build/anim2d-alias-20261028/`.
