# Shroud erase canonical-header prerequisite

Inspected base: `4ff68e0f1b`. Scope: `Code/Libraries/Source/WWVegas/WWLib/Rva0007300FErase.cpp`.

The donor now includes the registered `Rva00072FE6.h` instead of a private
24-byte view. The target header documents the 12-byte extent and the header/count
offsets. Both bodies only access the header at +0; no new layout inference or
function identity is introduced. Range erase compares its existing iterator
nodes directly with the header and its left link, replacing private inline
begin/end wrappers. The two unrelated STL inline specializations remain.

Checks:
- `./build.sh Code/Libraries/Source/WWVegas/WWLib/Rva0007300FErase.cpp`: 2/2 matched (68 and 73 bytes), literal/import checks pass.
- `find_declared_unmatched.py` on the donor: all defined functions already matched; two pre-existing admitted STL definitions remain.
- `header_adopt_lane.py accept --class Rva00072FE6` on the donor: PASS; one queue row retired through the native tool.
- `hatch_counters.py --update`: present_unmatched 2348 -> 2346; only the deleted begin/end wrappers leave the register.

The W3DShroud merge dry run at this base accepts neither donor. The erase donor
still duplicates the seed's identical `less<int>::operator()` specialization
(C2995); placing that specialization in a TU-scoped header is the next repair.
The interpolation donor includes the canonical W3DShroud view, whereas the owning
seed still needs its private lifetime-bearing members (LINK-225). No merge, new
linked-byte figure, census or runtime result is claimed by this prerequisite.
