### LINK-682: `ConnectionManager.cpp` tree rows and pins name another map's bodies

Status: Blocked on a TU approval or identity respell for 0x0016E310 (one name left). Updated: 2026-11-19; inspected revision: `a6ff2665aa`.
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
Completed (2026-11-19): the remaining check is done and the first of the two wrong bindings is gone.
The FileCommandMap tree is retail 0x004D272E (`map::insert(hint)`, 29 B) -> 0x004D2209 (hinted `insert_unique`,
310 B) -> 0x004D20DA / 0x004D2050 (`insert_unique`, `_M_insert`, 138 B each) -> 0x004D1D0B (`_M_create_node`, 34 B)
-> 0x004D0FF6 (`_Construct`, 45 B) -> 0x004D05B8 (pair copy constructor, 31 B); each has one caller, the previous
link, and all are rowed on the stand-in `BfmeStringRecord004D05B8` (a 16-bit key and an AsciiString at +4) or
`map<int, Rva004D272ERecord>`. `reverse/attempt_support/connectionmanager-filecommandmap-chain-20261103/` already
had this chain.
Row 0x00759460 left this unit. Nothing in retail refers to that body (no REL32, no absolute reference), it sits
inside CollisionManagerImpl.cpp's range, and that unit's own `map<Rva009A2FE0Sub*, unsigned>` instantiation
already emitted `_M_create_node` byte-equal to it with its `_Construct` on the fold-proof pin 0x006204B0. The row
is now that name in CollisionManagerImpl.cpp, the address's approved unit (`add_match.py`, tombstone in
`reverse/deleted_rows.csv`), and the pin `_Construct<pair<const unsigned short, AsciiString>>` -> 0x006204B0 is
deleted. `./build.sh` on both units 85/85; `link_check.py`: CollisionManagerImpl.cpp LINKS 5,700 -> 5,735 bytes
and ConnectionManager.cpp (2,447 own bytes now) fails on one name instead of two (index `53b35fb75b`).
Remaining / blocked: the hinted `insert_unique` pin 0x0016DF60 serves one row, `map<unsigned short,
AsciiString>::insert(hint)` at 0x0016E310, which `Rva004D2941MapInstantiationAnchor` keeps emitted. Retail
0x0016E310 is unreferenced too and forwards to 0x0016DF60: it is `map<Gen_p12pod, int>::insert(hint)`, and
`RvaMapIndexGenP12pod00928690.cpp` (the same map's `operator[]`, 0x0016E330) already emits that name byte-equal
(31 B, relocations masked). `reverse/tu_map.csv` gives 0x0016E310 no unit, so the row cannot move there, and
respelling it in place is a code-identity rename that needs its votes. Either one frees the unit: with the row
gone the anchor and the 0x0016DF60 pin go too, and nothing in ConnectionManager.cpp emits a FileCommandMap
helper under a name bound to another tree. Not tried: a specialised `insert` that
reaches the other tree's hinted insert through a cast; it would bind the right callee and keep the wrong name.
Next check: after an approval or respell of 0x0016E310, delete the anchor and the 0x0016DF60 pin, then
`link_check.py` ConnectionManager.cpp with RvaMapIndexGenP12pod00928690.cpp; the chain's stand-in names are a
separate naming-lane respell and block nothing in the link.
Clearance: pending.
Census confirmation: not claimed.

#### 2026-11-18/19: the FileMaskMap and progress-map bindings (separate from the string map)

Read-only check: scratch `build/name_collision.py --depth 4` over `ConnectionManager.cpp` and
`ConnectionManager_fileTransfer.cpp` (it compares the body each object defines under a name with retail
at the address the ledger gives that name). Before: 7 `bytes` in ConnectionManager.cpp and 2
`flagged-transitive` in fileTransfer. After: 20 fit, 2 bytes (the string map's two names above).

Fixed (commit "ConnectionManager: bind retail's FileMaskMap and progress-map tree bodies"):
- **`map<unsigned short, unsigned char>` (FileMaskMap), 5 names.** Retail `processFileAnnounce` 0x004D2C8E
  calls the /O1 subscript 0x004D26E6, then 0x004D21EC insert(hint), 0x004D1F1A insert_unique(hint),
  0x004D1B6D _M_insert, 0x004D0FD4 _M_create_node: all already rowed byte-exact in
  `StlO1Instantiations.cpp` / `stlport_rb_tree_create_nodes.cpp`. ConnectionManager.cpp emitted its own
  frameless copies of the same five names (99 vs 72 B for the subscript). The unit now declares the
  subscript only (its existing decl-only block), so the only provider is the retail-exact one.
- **`map<unsigned short, int, Gen_lt_00940b40>` (file-progress maps).** fileTransfer's insert_unique
  (pinned 0x0046E31F) fit; its _M_create_node did not: `push 1 / call allocate` through a declared-only node
  `allocate` over `__malloc_alloc`, where retail 0x004DCC62 inlines the raw byte allocator
  (`push 0 / push 0x18 / call 0x004307F0`). The unit now builds with `/Ireference/shims/bfmealloc_alloconly`
  and no longer declares that `allocate`; its _M_create_node then reaches `_Construct<pair<const G,int>>`
  0x00469D1A as retail does. Byte gate 41/41, EH 7/7 exact.

The string map's remaining name is not a runtime defect: the anchor's chain has no retail caller, and our
operator[] reaches retail's /O1 chain (0x004D272E ...) through `map<int, Rva004D272ERecord>::insert`, so a
real link runs retail's code there. A fresh in-memory `tu_map` (tu_skeleton.map_rows, 2026-11-18) still gives
0x0016E310, 0x0016DF60 and 0x0016E330 no TU. After that approval, drop the anchor (keep lower_bound
0x001574F0 by explicit instantiation) and retire the 0x0016DF60 pin and its `code_identity_baseline.tsv`
key through `repair_queue.py retire identity`.
