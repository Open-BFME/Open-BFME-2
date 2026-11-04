# GameSpy chat header adoption and consolidation handoff

Inspected revision: `7b402496061fb9e14c84c7dab08ec52b92d3c695`.
Owner: `yasinschroeder-codex5`; model: `gpt-6.1-sol`.

`GameSpyInfoAddChat.cpp` now includes the canonical `PlayerInfo.h` instead
of defining a private view. Its existing accesses use the header's offset
names. The owner-bit test casts the canonical signed word to unsigned,
preserving the original logical shift. No class layout or header changed.

Verification:

- `./build.sh Code/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfoAddChat.cpp`:
  all seven rows match, including the five parent-bound unwind funclets.
  Both string references pass; float and import checks pass.
- `find_declared_unmatched.py` on that source: all defined functions matched.
- `header_adopt_lane.py accept --class PlayerInfo` on that source: PASS,
  one queue row retired by the owning tool.
- `header_adopt_lane.py accept --class AudioManager` on that source: PASS,
  one stale queue row retired by the owning tool. The canonical audio and
  miscellaneous-audio headers were already included before this change.
- `link_check.py` on that source: LINKS, 681 -> 681 bytes in the prediction,
  using the census index dated 2026-11-04 07:28 at `a62ac1c10b`. This is not
  a new census or a real-link result.

## Consolidation remains blocked by compiler flags

The supported planner was run with
`name_lane.py consolidate --under Code/GameEngine/Source/GameNetwork/GameSpy/`.
Its Chat packet flags compiler settings, declarations, includes, data ownership
and incomplete routing. The committed TU map is stale; `tu_skeleton.py`
rebuilt its assignments in memory, without writing the map. Its current plan
assigns 52 rows to `GameSpy/Chat.cpp`, with five eligible external donors and
two mixed sources left in place.

`tu_skeleton.py --merge Code/GameEngine/Source/GameNetwork/GameSpy/Chat.cpp
--dry-run` accepted no donors. Under the destination's carried empty flag
override it loses four rows from `Open2Rec4F1120MapFind.cpp`, five from
`Open2RecChain146.cpp`, two from `Rva001EF552Chat.cpp`, and six from
`GameSpyInfoAddChat.cpp`. `stlport_wide_string_append_O1.cpp` reports no baseline
match in that merge trial; its ordinary `./build.sh` verifies all three rows.
That trial is not evidence of a byte-matching regression in the source.

The dry run wrote no sources or ledgers. No paths moved and no merge is
claimed. The next prerequisite is reconciling the destination's compiler
settings while retaining its existing matches and those of each donor.
The PlayerInfo copy-constructor donor still has its own pending adoption;
this change does not retire that source's queue row.

## Initial link pick was already repaired

The default picker first served `Win32BIGFileSystemRva006046B0.cpp` for the
old unresolved `?g_Va00E06E60@@3IA`. Its scoped build verifies all nine rows.
The current `Rva007B6880Thunks.cpp` already defines the same decorated name
with 40 bytes of storage, as recorded in the existing constructed-globals
obstacle entry. Including that provider in one `link_check.py` invocation
with the BIG filesystem unit, `Rva0060147B.cpp`, and
`System/FileSystemRestricted.cpp` predicts LINKS for all three consumers
(606, 177, and 394 bytes respectively). The provider itself still reports
`?g_Va00DF2984@@3PAIA` unresolved against that index. No global was changed,
no full-image link or census clearance is claimed, and the initial claim
was released.
