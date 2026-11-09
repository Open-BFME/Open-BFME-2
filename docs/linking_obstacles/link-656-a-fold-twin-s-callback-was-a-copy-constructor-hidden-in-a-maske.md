### LINK-656: a fold twin's callback was a copy constructor, hidden in a masked relocation
Status: Repair landed / awaiting verification. Updated: 2026-11-09 (swarm Crash triage lane, D1).

Evidence / affected units: D1, the first skirmish, receipt `2026-11-09T105552Z-game_smoke-97329605cf0c`
(plain master ccee751f5b, diagnostic image, base 0x2000000) stops 23.9 s into the run with an access violation
in `kernel32.dll+0x2605d`, InterlockedIncrement by its caller's shape, during map load. Stack by scan:
`WorldHeightMap::parse` -> `DataChunkInput::parse` -> `bfmeAskCW` -> `SidesList::parseLibraryMapListsChunk` ->
`DataChunkInput::parse` -> `??0Rva0041579E` -> `??0Rva0041573F` -> `??0BfmeOwnedRecordArray56` -> `??__C` ->
`??0Rva002390CB` -> `??0Rva0036CA00Str`.

Inferred from that stack plus the static read below: `DataChunkInput::parse` called a copy constructor as a chunk
callback, so `(file, info, userData)` were read as a source record, and the string pointer it incremented was
garbage. Retail doesn't reach this code on this path.

Read from retail's bytes and the map: retail's `LibraryMapsParser` constructor 0x00329F83 and the `BfmeScopeCO`
constructor call `DataChunkParser` 0x000ABB87, which registers callback 0x00306EDC (`bfmeAskCW`). The image's
call instead reaches `??0BfmeParserRegistrationVE`, an inline copy from `Gen004502D0ParserRegistrationCtor.cpp`,
rowed as a fold twin of 0x000ABB87. That copy registered `?bfmeChunkParserVE@@YAXXZ`, which the unit's own
`/alternatename` bound to `??0Rva0041579E@@QAE@ABV0@@Z`. The source comment gave 0x0041579E as the callback;
retail's body there is plainly a copy constructor. The byte gate masks the push's relocation, so the row
matched, and `fold-proof=` passed although its relocation targets differ. The real link's reports don't flag it.

Repair: the unit names `bfmeAskCW`, and the alias is gone, lowering the alternatename count by one. No object in
the seat's `build/match` (18,379) still names it. `./build.sh` 2/2. `link_check` 4 of 4, LINKED 418 -> 418 over
this unit, `LibraryMapsParser.cpp`, `BfmeConv1773.cpp` and `BfmeDataChunkParserBinding.cpp`. Not run yet: the pass test is
a skirmish receipt on a plain image containing the commit, further than this crash.

Lead, not repaired: why the fold proof accepted differing relocation targets is unread. The other relocated
code pointers in rows haven't been judged by body.
