# PlayerAITypeSet consolidation evidence (2026-11-04)

Allocated destination: `Code/GameEngine/Source/GameLogic/System/PlayerAITypeSet.cpp`.
The current allocation check passed. The narrow consolidation snapshot was
current before the merge (`name_lane.py consolidate --check build/consolidation`).

`tu_skeleton.py --merge ... --dry-run` accepted only the unchanged ICF twin
`StlSweepW5Rva00215696AssignTwin.cpp`, moving row 0x00215530 into the destination.
The applied merge removed one source file and preserved the destination's rows.
`./build.sh Code/GameEngine/Source/GameLogic/System/PlayerAITypeSet.cpp` passed
all 16 matched rows and verified three funclet pins. `find_declared_unmatched.py`
reported all defined functions already matched. `check_csv.py` passed. Staged
code identity found 0 new findings across 16 rows; staged data check found 0
findings; `tu_ownership.py --staged` passed; `hatch_counters.py --staged`
credited the generated present-unmatched total from 2378 to 2376. The
two W3DModelDraw entries it removed no longer correspond to definitions;
`find_declared_unmatched.py` reports all definitions in that file matched.

LinkGuard accepted the donor and reported the destination and donor among the
census-linked units. The two remaining exact donors were refused: the parse
donor fails on undeclared `BfmeItemERE`; the vector allocation/copy donor and
the W4 fill-insert donor fail byte verification. The mixed
`StringVectorRecordCopyBFME2.cpp` split carved only 0x002154F3, refused
0x0021559C because no definition spells it, and failed combined compilation on
`_STL::allocator::deallocate`. The mixed `StlportMapForwardersSeat8.cpp` split
could not carve 0x00215A88 because no definition spells its name. These sources
remain unchanged; class reconciliation and exact helper providers are
prerequisites for further consolidation.

The merge changes source paths only for the absorbed ICF twin. The combined
active-consumer search found no donor-path reference in tools, hooks, workflows,
or include trees; historical path text in the generated TU and ledgers is
retained as evidence. The complete outgoing link-batch audit remains the
publisher hook's check; no new census result is claimed.
