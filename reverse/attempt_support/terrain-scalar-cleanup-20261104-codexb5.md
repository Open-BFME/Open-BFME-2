# TerrainType scalar cleanup reconciliation, 2026-11-04

Base: `d29d7b6f7b`. Scope: `Common/TerrainTypes.cpp`; existing TerrainType
class/header/source claims held by `yasinschroeder-codexb5`.

The canonical header retains neutral 12-byte storage at +0x10 and +0x24.
Both queued private views use typed vectors; the supported header adoption
refuses the +0x10 vector/array field mapping for both sources. No header queue
row is retired, and no element identity is inferred from equal storage size.

The seed's explicit ScienceType vector-base destructor instead had a concrete
composition mismatch: it used an imported, force-inlined specialization over
the allocator, while `TerrainType.cpp` defines an ordinary inline specialization
calling the already rowed game-memory wrapper. The seed now uses that same
definition. This preserves the existing private type identity; it does not
establish ScienceType as the retail terrain-class element name.

Verification: `./build.sh Code/GameEngine/Source/Common/TerrainTypes.cpp`
passes 31/31 rows, all string references and parent EH checks. Declared-unmatched
validation passes. The ordinary current-object link preview retains LINKS and
1,231 authored bytes against census `f12552d0a7` (2026-11-04 20:47).
No pin, alias, ledger ownership or protected debt is changed. This is a
prerequisite repair, with no measured linking gain or completed header adoption
claimed. Recheck the supported merger for the remaining private-layout conflict
and preserve the generated cleanup's independent parent/callee prerequisites.

## Follow-up boundary

Repair commit `eeed84bdd4` was handed to the runner's fleet publisher. The
supported merger rebuilt current approvals in memory (44 approved rows), but
accepted no donor and rejected `TerrainType.cpp` with a compile diagnostic
whose detail was empty. It still lists TerrainType adoption in both sources
as a prerequisite. `tu_views.py --dry-run --class TerrainType --no-merge-check`
explicitly routes the registered class to its canonical header and writes
nothing. The Common consolidation planner was refreshed and its currency
check passed before this trial. No source path, ledger row or debt key moved.

Strict current preparation also byte-verifies all 31 destination rows. The
ordinary commit hook passes seven EXACT EH graphs and reports one shadow
identity finding: the constructor's existing AsciiString::clear binding at
0x00036410. That finding is not cleared by this repair.

The scoped outgoing consumer audit exits 2, INCONCLUSIVE: census index
`f12552d0a7` predates outgoing base `d29d7b6f7b`, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry that consumer and TerrainTypes into the next scheduled census;
consumer preservation beyond the local destination preview is unverified.
