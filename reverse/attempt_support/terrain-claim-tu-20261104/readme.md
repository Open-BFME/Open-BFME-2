# TerrainResourceClaimFeedback TU lead

Inspected 2026-11-04 at 132c321fb8. No source or ownership changes.

Target facts: retail rows 0x004E7A85 (82 bytes) and 0x004E7FCA (532
bytes) already have source owners. `find_declared_unmatched.py` passes both
owners. `./build.sh Code/GameEngine/Source/Common/Rva004E7A85Refresh.cpp
Code/GameEngine/Source/GameClient/GUI/TerrainResourceClaimFeedback.cpp`
passes 4/4 rows, including the latter owner's two EH rows. No matching
address or TerrainResourceClaimFeedback path appears in string_xrefs.tsv.
The committed TU map leaves both addresses unassigned with W evidence only.

Donor facts: `wb_show.py 0x004E7A85 --gd` identifies WB 0x131c5b0,
TerrainResourceClaimFeedback::Impl::show, with a show-count assert at line
154. Its callgraph pairing score is 2. WB 0x131c990 pairs with 0x004E7FCA
at score 3, with asserts at lines 223..247. Both WB bodies name
GameClient/Gui/TerrainResourceClaimFeedback.cpp. These are WorldBuilder
paths, not independent retail source-path proof.

Boundary: tu_map.py's W signal requires an independent naming hint and
rejects self-corroboration by WB-derived names (`wb_self`). The existing
retail names came from these WB leads; repeating the path as a class or file
rename would not add an independent anchor. Nearby ResourceEntryOwner
assignments are provisional naming groups, not proof of this path either.

Next step: find an independent retail F anchor or independently established
class/site evidence, then rebuild the map in memory and test the two
addresses. Do not create an empty TU, promote the WB path by hand, or call
these already-covered bodies regressions. This investigation does not
establish that the WB path is wrong; TU approval remains blocked.
