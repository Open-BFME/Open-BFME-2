### LINK-682: `ConnectionManager.cpp` tree rows and pins name another map's bodies

Status: Open. Updated: 2026-11-15; inspected revision: `2e75acaf83`.
Evidence / affected units: census 2026-11-15 08:36 (`331df3e3ff`) holds
`Code/GameEngine/Source/GameNetwork/ConnectionManager.cpp` (2,482 authored bytes) out on two names of its
`map<unsigned short, AsciiString>`: `??$_Construct@U?$pair@$$CBGVAsciiString@@@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBGVAsciiString@@@0@ABU10@@Z`
(pinned 0x006204B0, `reverse/symbols.csv` line 10) and the hinted `insert_unique` (pinned 0x0016DF60).
The unit's copies are the kept ones and are not the bodies at those addresses. This is not LINK-679's
begin() layout: the copies differ from the pinned bodies in 58 of 78 and 502 of 593 bytes.
What the pinned `_Construct` target is: retail 0x006204B0 is 23 bytes, `if (p) { p[0] = v[0]; p[1] = v[1]; }`,
a two-dword copy with no call. It is rowed twice, as `_Construct<Rva006204B0Element>`
(`StlSweepW6Rva006204B0.cpp`) and `_Construct<pair<const unsigned int, Rva00620A00Record>>`
(`AssetRefreshPendingInsert.cpp`); `pin_consistency.py --symbol` still reports the pin consistent. A
`pair<const unsigned short, AsciiString>` cannot be constructed without the string copy constructor
(`??0?$StringBase@D@@AAE@ABV0@@Z`, 0x000365F0, which this unit's own copy calls), so the pin is on another
element type's body. The other reading of that early pin, VA 0x006204B0 = RVA 0x002204B0, is the middle
of the function at 0x0022044C. The pin exists for one caller: `_M_create_node` at 0x00759460 (35 bytes,
rowed in this unit under the `map<unsigned short, AsciiString>` name) allocates 0x18 bytes and calls
0x006204B0 on node+0x10, so that row is an 8-byte-value tree's node factory under this map's name. The
hinted insert pin 0x0016DF60 is rowed as `insert_unique` of `Gen_p12pod` keys (712 bytes).
Completed: none; reading only.
Remaining / next check: find the real bodies from the map's own rowed `operator[]` (0x004D2941), whose
REL32s reach the lower bound 0x0046A9AB and the hinted insert 0x004D272E; follow 0x004D272E to its
`insert_unique`, `_M_insert` and `_M_create_node`, the last of which must reach the pinned pair constructor
0x004D04FF or the string copy constructor. Then repoint or retire the 0x00759460 row and the two
pins through their registers, and re-run the preview.
Clearance: pending.
Census confirmation: not claimed.
