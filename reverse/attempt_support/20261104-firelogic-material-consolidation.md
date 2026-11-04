# FireLogicSystem material-parser consolidation (2026-11-04)

Scope: absorb `Code/GameEngine/Source/GameLogic/Map/FireLogicSystemParseMaterial.cpp`
into `Code/GameEngine/Source/GameLogic/Map/FireLogicSystem.cpp`. The prerequisite
import fix is `eab7d513f8`. No other donor is absorbed.

## Evidence and verification

- `name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Map/`
  supplied the original-path evidence and alternatives. The fresh in-memory TU
  map used by `tu_skeleton.py` approves parser RVA `0x00285FA9` for this TU.
  This is target placement evidence, not a donor-source identity claim.
- The initial merge changed the parser's imported `atoi` call to a direct call
  because the seed clears `_CRTIMP`. An explicit namespaced CRT import keeps
  the original IAT binding. The isolated parser passed its 293-byte row, five
  string references and one named import before consolidation.
- `tu_skeleton.py --merge` accepts the seed and material parser: 32 rows, with
  its link guard passing for the census-linked inputs. This is a guarded move,
  not a new real-link or census measurement.
- `./build.sh Code/GameEngine/Source/GameLogic/Map/FireLogicSystem.cpp` passes
  32/32 rows, five string references, six floating-point literals and one named
  import. Compiler-renumbered unwind labels are resolved through parent EH data.
- `find_declared_unmatched.py` reports all defined functions already matched.

## Consolidation audit

The parser's code row and its two data-owner records (`0x009BB768`,
`0x009FEC6C`) transfer to the destination. The committed TU map changes only the
row's source column. Existing header-queue keys remain at the seed; no gate,
identity or data-check baseline key belongs to the removed donor. No aliases,
pins or other hatches are added or removed. The result removes one source file
without removing a matched row.

The compatibility search covers the removed full path and basename across
tracked tools, hooks, workflows, includes, build/configuration files and source
registries. There are no active hard-coded consumers to update beyond the
mechanical ledger transfers. `reverse/link_status.csv` intentionally retains
its historical census observation for the old source. Historical attempt logs,
map inputs and the generated TU's provenance comment also retain their original
spelling. No linking-obstacle entry names these inputs or needs a changed next
step: the merge guard passes and no link repair is claimed.

## Remaining donors

`StlSweepR3Rva0028681A.cpp` and `stlport_map_int_ptr_tree_dtor.cpp` are rejected
for bytes and remain separate. A diagnostic composition under the seed flags
shortens the first tree destructor from 56 to 52 bytes, omitting its
`or [ebp-4], -1` EH-state store. Changing to the donor flag set instead changes
`FireLogicSystem::update` and two unwind bodies. The second tree destructor and
its handler also fail the seed composition. These are consolidation constraints;
no nonmatching source change is retained. Mixed donors were not split or edited.
