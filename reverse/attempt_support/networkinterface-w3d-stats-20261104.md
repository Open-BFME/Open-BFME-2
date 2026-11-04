# NetworkInterface adoption in W3D statistics

2026-11-04; inspected revision `5199deee0b`; worker
`yasinschroeder-codex3`; model `gpt-6.1-sol`.

## Completed scope

Replaced the private `NetworkInterface` declarations in
`W3DDisplayGatherDebugStats.cpp` and `W3DDisplayGatherNetworkStats.cpp` under
`Code/GameEngineDevice/Source/W3DDevice/GameClient/` with the existing
`Code/GameEngine/Include/GameNetwork/NetworkInterfaceClass.h`.

Direct adoption had failed because the private declarations' method spellings
do not occur in the shared header. Calls now use its existing virtual slots;
comments retain the private spellings without claiming original retail names.
No shared header, provider name, pin, alias or ledger row was changed.

Target evidence: the private declarations and existing header place the calls
at these vtable byte offsets:

| Slot | Offset | Existing private spelling |
| --- | --- | --- |
| 43 | 0xAC | isPacketRouter |
| 44 | 0xB0 | getPacketRouterSlot |
| 47 | 0xBC | getPlayerName |
| 53 | 0xD4 | getIncomingBytesPerSecond |
| 54 | 0xD8 | getIncomingPacketsPerSecond |
| 55 | 0xDC | getOutgoingBytesPerSecond |
| 56 | 0xE0 | getOutgoingPacketsPerSecond |
| 59 | 0xEC | getFramesBehindPacketRouter |
| 60 | 0xF0 | getRunAheadCeilingHits |
| 61 | 0xF4 | getSequentialBuffer / getSequentialBufferCount |
| 62 | 0xF8 | getSlotFrame |

The debug stats unit uses only slot 61. This is interface reconciliation, not
new semantic naming evidence. No external donor was consulted for this change.

## Verification

- Scoped `./build.sh` for both units: **19/19 functions match**, seven data
  rows verified, 84 literals plus 16 empty references verified, 21 float
  literals and one named import verified. Fifteen funclet rows were verified
  through their parent EH graphs after compiler-local label renumbering.
- `find_declared_unmatched.py` for both units: all defined functions matched.
- `header_adopt_lane.py accept --class NetworkInterface` for both units:
  **PASS**, retired exactly their two `reverse/header_queue.tsv` rows.
- Explicit `link_check.py` preview: both **LINKS**; debug stats
  **4,083 -> 4,083 bytes**, network stats **2,241 -> 2,241 bytes**. Census
  baseline: **2026-11-04 17:56 at 8c757ea0db**. These are preservation previews,
  not a new census or a real-link measurement.
- Diff whitespace check passes with `core.whitespace=cr-at-eol` for the
  network stats unit's existing mixed line endings.

## Remaining W3DDisplay.cpp prerequisite

The third selected unit, `W3DDisplay.cpp`, was tried and restored to HEAD.
Mapping its calls to slots 43, 59 and 62 removes the missing-method issue,
but compilation still fails when the network header brings in
`SubsystemInterface.h -> ascii_string.h -> string_base.h` beside the TU's
private `StringBase<T>` definition. The data verifier reports compilation
failure, including `rva000481AA` member/undefined-`StringBase` diagnostics.

That local view deliberately has a private inline destructor and grants
`W3DDisplay` friend access. The existing row at **0x000481AA (194 bytes)**
returns `StringBase<char>` by value; its evidence distinguishes ordinary
`releaseBuffer` teardown from the private destructor wrapper used by
**0x0075D142**. Simply substituting the general string header is not established
as byte/EH equivalent. First reconcile this declaration and verify the parent,
its return-value cleanup, and all other rows/data in the complete TU; then
adopt the network header. Its header-queue row remains untouched.
