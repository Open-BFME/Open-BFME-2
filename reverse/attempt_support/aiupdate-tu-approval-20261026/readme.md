# AIUpdate TU approval: three distinct routing prerequisites

Inspected upstream `766153ce00`, BFME 1 reference `f633d0e97a`.
The default queue selected
`Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp`: 299 proposed
rows in 177 files. No code, name, ledger, baseline or TU-map edit was attempted.

The complete 2,538-line source was read. Its SHA-256 is
`6b272fab4611ee4d20739a7eb145c34c6b8c2f1388ac9babecd0dc77badc5477`.
Normal verification passes its eight existing rows (241 bytes), one string
reference and one EXACT EH graph. The frozen-file checker accepts it and also
reports 64 existing unclaimed definitions. Those are not new matches or new
markers. The donor source still has independent layout, identity and hatch debt.

## Official result and current inputs

The supported consolidation survey under `Code/GameEngine/Source/GameLogic/Object/Update/`
is current (`name_lane.py consolidate --check build/consolidation` passes).
It correctly labels the committed TU map stale; that map is not used as approval.
The ordinary `tu_skeleton.py --plan` rebuilds from current inputs in memory and
reports **0 approved rows, 0 donor files, 1 mixed file, 0 refused files**.

The source owns only one main-code row assigned back to the proposed AIUpdate
TU: `privateGoProne`, 0x00262F5E..0x00262FC3. Its EH handler is 0x00772D9D.
Other current rows include the 13-byte vector-empty body at 0x00142C90,
approved by its brackets for `WW3D2/rinfo.cpp`; unresolved/displaced template,
getter and handler rows remain. A whole-file move is not admissible.

## Separate the broad span from the remaining anchor

The current mapper assigns 299 code rows to AIUpdate: 102 Z, 110 S, 80 C and
7 K. Six distant K-only placeholder-class propagations expand its start-address
span to 0x000658DB..0x004D6F86:

| RVA | Placeholder class | Current source suffix |
| --- | --- | --- |
| 0x000658DB | Rva00065964ObjectPool | WWLib/Rva000658DBObjectPoolAllocate.cpp |
| 0x00065964 | Rva00065964ObjectPool | WWLib/Rva00065964ObjectPoolFree.cpp |
| 0x00285A3B | Rva00065964ObjectPool | WWLib/Rva00285A3BObjectPoolAllocate.cpp |
| 0x00285AC4 | Rva00065964ObjectPool | WWLib/Rva00285AC4ObjectPoolAllocate.cpp |
| 0x003681DC | Rva002645FF | Common/GapBodiesGE14.cpp |
| 0x004D6F86 | Rva00263895Member | Common/Rva004D6F86.cpp |

The other K row, 0x0026891F, stays inside the main cluster. `tu_map.build`
includes assigned K rows when computing a TU's own min/max bounds, while K
does not qualify as a foreign `SPAN_BREAKERS` category. This explains span
amplification, but does not establish that the complete TU refusal is false.

The main cluster has 293 rows at 0x00260DED..0x0026FF1E. Within it are 47
foreign assignments: 37 approved (one DisplayStringManager and 36 Upgrade),
four proposed K and six proposed N. They are not 47 proven blockers.

The last AIUpdate row is the seven-byte `getCurLocomotor` at 0x0026FF1E.
The ZH `GameEngine/Include/GameLogic/Module/AIUpdate.h` lines 426-427 define
the getter inline; its current BFME 2 source also defines it inside the class.
`tu_map.header_comdat` only excludes header constructors and virtual methods,
so this nonvirtual getter retains an S class-site assignment. That is a
classification lead, not proof of the getter's original retail TU.

The attached read-only `span_report.py` observes the mapper's actual anchored
roots and applies its exact `SPAN_BREAKERS` predicate to a hypothetical narrow
span. Removing only the six outer K rows and that last getter from the bounds
leaves 0x00260DED..0x0026E9BD (the last ctor's 984-byte body ends at 0x0026ED95).
The whole Upgrade block then lies outside the span. All four remaining K and
six N assignments fail the actual blocker predicate; only this row remains:

`DisplayStringManager::link`, 0x00262027, 30 bytes, Z, anchored root.

This diagnostic does not modify or approve a map. Even the hypothetical bounds
still have a real conflicting assignment; neither approval nor a false reject
is claimed.

## Identity limit and linking status

The complete current DisplayStringManager source is a 30-byte linked-list insert
using head +0x0C and node links +0x0C/+0x10. `wb_show.py 0x00262027 --gd`
reports the WorldBuilder body at 0x00D2E1A0 with evidence **seed**: its pairing
uses the existing ledger name. Its path/asserts and structural resemblance are
not independent proof that this retail address has that identity or original
TU. `callers_of.py 0x00262027` finds no named direct caller. This pass has no
sound basis for renaming that row merely to make the map contiguous.

The unchanged AIUpdate source's ordinary link preview against index
`f995f30157` (2026-10-25 21:36 UTC) still fails: 17 unresolved names, six COMDAT
findings and five wrong-selected definitions, LINKED 0 -> 0 bytes. These are
separate from TU approval. The historical target checklist's 231-byte figure
is retained; this source's current eight rows total 241 bytes including EH.

## Next useful checks

Establish independent retail identity/ICF/original-placement evidence for the
30-byte DisplayStringManager assignment before changing its name or route.
Separately review distant K propagation and nonvirtual inline classification
with guarded tooling fixtures; preserve genuine F/Z/S conflicts. No mapper
change, weakening of approval, or regeneration of the committed map belongs to
this handoff. Re-run the supported plan after those prerequisites change, then
resolve the seed's mixed rows and donor debt through their owning lanes.

Reproduce from the repository root:

```text
python3 tools/tu_skeleton.py --plan Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
python3 reverse/attempt_support/aiupdate-tu-approval-20261026/span_report.py
./build.sh Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
python3 tools/eh_verify.py Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
python3 tools/link_check.py Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
```

The last command is expected to report existing blockers, not success.
