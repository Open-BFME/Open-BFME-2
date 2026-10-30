# Physics trajectory ObjectModule adoption (2026-10-30)

Base: `0c90b528d93036d423f549d023b68782399cac21`.
Scope: `Code/GameEngine/Source/GameLogic/Object/Update/PhysicsBehaviorTrajectory.cpp`.

The default picker claimed the PhysicsUpdate.cpp consolidation group. The
supported naming planner identified incompatible private views and compiler
flags, plus mixed sources. The earlier mechanical attempt is recorded in
`consolidation-mechanical-seat3-20261026.md`: no unchanged donor composed;
module-data fields, Coord3D definitions, virtual declarations and AudioEventRTS
providers remain prerequisites. No source path or ledger owner changes here.

The trajectory donor's queued ObjectModule adoption failed because its private
base named the ModuleData pointer `data` and Object pointer `object`. The
registered header already provides the target's pointers at +4 and +8 as
`m_moduleData` and `m_object`. This change includes that header and uses those
members. The existing PhysicsTrajectoryConfig remains a local data view,
accessed through an explicit pointer conversion; it is not a recovered
ModuleData class declaration. No new method or layout identity is asserted.

## Verification

- Before and after `./build.sh` pass all three rows: 0x00390E61,
  0x00390FAF and 0x0039114B, totaling 1,410 bytes. The one string and seven
  floating-point references also pass.
- `find_declared_unmatched.py` passes before and after. The existing inline
  copy of the separately rowed 0x00390557 helper remains unchanged in identity.
- `link_census.object_facts` compares identical before/after facts: all 28
  external COMDAT names, sizes and relocation-aware digests; all three strong
  definitions; all 22 undefined names; and no weak aliases. This covers the
  unrowed template/helper copies as well as the rowed bodies.
- Ordinary pre-edit preview retains LINKS 1,410 -> 1,410 against the
  2026-10-29 15:08 index at `85f6b7f40c`.
- `header_adopt_lane.py accept --class ObjectModule` passes its byte and
  per-unit link guards, retiring exactly one header queue row through the
  owning tool.
- `link_check.py --prepare-current` passes for this explicit provider with a
  strict reusable receipt. The subsequent ordinary preview retains LINKS
  1,410 -> 1,410 against the same index.
- The staged-tree `link_batch_audit.py` exits 2, INCONCLUSIVE: the index
  predates the base and the affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
  receipt. This is not a clean full-consumer verdict.
- `check_csv.py` passes (99,009 function rows, 9,415 symbols, 2,235 data rows).

The first compile trial used an include spelling outside this source's search
path and failed C1083. Correcting it to the relative spelling used by nearby
adopters resolves that diagnostic. The concurrent read-only tu_views report
encountered that temporary diagnostic; it supplies no layout or merge proof.

## Remaining prerequisites and measurement boundary

The same donor's Thing queue row stays open: its registered header
`Code/GameEngine/Source/Common/Thing/thing.h` lacks `setTransformMatrix`, which
the trajectory update calls. Establish that declaration from target evidence
and verify its dependents before adopting Thing. Other PhysicsBehavior and
UpdateModule views still require reconciliation before a supported TU merge.

This retires one header-debt row only. It claims no census linking gain,
ownership gain, source-file reduction or completed PhysicsUpdate consolidation.
The index predates the base; full affected-consumer verification and census
confirmation remain pending. Carry the trajectory provider, the named
CreateAHeroManager consumer and other affected consumers into the next
scheduled census.
