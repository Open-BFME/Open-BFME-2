# GameSpy chat: canonical PlayerInfo copy construction

Inspected revision: `dca81b67b5bd23be19fc3ff7853418230d7ed840`.
Owner: `yasinschroeder-codex5`; model: `gpt-6.1-sol`.

`Common/Open2RecChain146.cpp` now includes the canonical `PlayerInfo.h`
instead of maintaining a private class. The header declares the copy
constructor out of line, so the source defines the existing row's constructor
with member initializers for the three strings and ten trailing dwords. Its
137 bytes and relocation targets remain exact. The canonical signed field at
+0x18 has the same copy representation as the old unsigned field. This does
not infer additional member names or change the class layout.

Verification:

- Before and after `./build.sh` pass all nine code rows. The two parent-bound
  EH graphs are EXACT (`eh_verify.py`); the five unwind rows still bind through
  their parent tables after compiler-label renumbering.
- `find_declared_unmatched.py` passes. `header_adopt_lane.py accept --class
  PlayerInfo Code/GameEngine/Source/Common/Open2RecChain146.cpp` passes and
  retires exactly one queue row through the owning tool.
- `link_check.py` predicts LINKS, 291 -> 291 bytes, against the published index
  dated 2026-11-05 05:17 at `c95fcfcfcd`. This is a scoped preview, not a
  new census or full-image link result.

## Consolidation remains blocked on seed code generation

The supported `name_lane.py consolidate --under
Code/GameEngine/Source/GameNetwork/GameSpy/` planner was run and its packet
reviewed. The current in-memory TU map approves 52 rows for `Chat.cpp`; two
mixed donors remain excluded. The dry run accepts zero of five eligible
external donors: the seed's carried empty override loses 4/5/2/6 rows from
map-find/chain/chat-thunk/addChat, and the wide-string donor reports no baseline
match in this composition. These are composition refusals, not source
regressions.

A supported `flag_defaults.py generate` scan confirms the seed's regional
`/O2 /G7` fails only `equal_range` at 0x0061F840: ESI is saved/restored inside
one branch instead of across the function. Seed `/O1` flag trials, with and
without `/G7 /arch:SSE`, did not preserve all matches. They were reverted,
including all tool-generated flag-register changes. The restored seed passes
all four code rows and its data row. No extra pragma or pin was added, no
source path moved, and no regenerated TU map is committed.

The explicit copy constructor removes the chain donor's canonical-header
prerequisite. The next merge prerequisite remains a seed/template code-shape
repair that preserves all existing matches under compatible donor flags;
private GameSpyInfo/shim declarations may require reconciliation afterwards.
See [the previous handoff](chat-header-adoption-20261104-codex5.md) and
[the earlier flag experiments](chat-playerinfo-views-20261030-codex4.md).
