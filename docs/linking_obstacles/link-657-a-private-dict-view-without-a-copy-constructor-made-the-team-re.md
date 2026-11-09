### LINK-657: a private Dict view without a copy constructor made the team record copy skip its reference
Status: Repair landed / awaiting verification. Updated: 2026-11-09 (swarm Crash triage lane, P106).

Evidence / affected units: `SidesListTeamsInfoRecCopy.cpp` is the only object defining
`??0BfmeThingUBB@@QAE@ABV0@@Z`, the 16-byte team record's copy constructor, which the team vector's
`_Construct` reaches on `push_back` and growth. Its private `Dict` view had no copy constructor, so the
implicit record copy copied the Dict data pointer without a reference. Retail's body, 0x0032A304 (rowed as
`?set@Rva00193660@@...`, 58 B), ends `test ecx, ecx; mov [eax+0xC], ecx; je; inc word ptr [ecx]`. The record
destructor still releases. So each time a map's team vector grew, the old records' destructors freed
Dict data the new records still held, and the next Dict write landed in a freed 0x28 chunk.

Measured in skirmish receipts at base 0x2000000: the allocator faults popping fast bin 3 (0x28 chunks),
whose head is 0x7E030003 (registers, job 20261109T184515Z-1276399-1794249915288673412-game_smoke), during
`SidesList::rva0032F0AA`'s team `readDict`. Ruled out first by runs: P104's renderer free (receipt
2026-11-09T210051Z-game_smoke-89d7b22d70fa) and the MSVCR71 heap split (2026-11-09T194718Z-game_smoke-76ea42fd065b).
No row's byte gate could see this: the copy constructor has no row, and its callers match retail.

Repair: the unit's `Dict` view gets the copy constructor retail inlines. The emitted
`??0BfmeThingUBB@@QAE@ABV0@@Z` is now byte-identical to 0x0032A304. `./build.sh` 9/9; `link_check`
LINKS 248 -> 248. Not yet run: the pass test is a skirmish further than P106's allocator stop.

Lead, not repaired: `_Destroy<BfmePod128>` from `stlport_pod_vector_bodies.cpp` is a bare `ret` where retail
0x0032B580 destroys each element through 0x0032A3A9. That's a leak, not a heap write.
