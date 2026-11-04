### Globals constructed into storage smaller than retail's object (2026-11-04, seat ancalgonn-ops-srv1)

**Status: Open. A runtime risk the linker cannot see; `image_report.py` now counts it (`constructed_undersized`).**

Many address-named globals are defined as `unsigned int g_Va...;`, 4 bytes, while an initializer constructs a
whole object there: `Rva007AC6DDGlobalInits.cpp` placement-news a 52-byte filter into `g_Va00DEC140`, and
`g_Va00DEDC80` has a 656-byte gap. The link succeeds and the object's constructor then overwrites whatever
follows it in our image, during startup. `image_report.py`'s byte comparison misses this because it bounds each
comparison by our own symbol's extent, so it lists these separately (`undersized_rows`).

**Measured 2026-11-04 on the census's objects:** of 3,247 globals an object defines, 963 are smaller than the
ledger's gap to the next known symbol, 406 of those at exactly 4 bytes. The gap is an upper bound on the true
size, so that figure is not a count of bugs. The hard subset: 44 names that source visibly constructs in place
(`new (&g_...)` or a cast-and-construct) and that are smaller than their gap, 22 of them in
`Rva007B6880Thunks.cpp`.

**Repair, for a name with no data row:** keep the mangled name every other unit declares and give the definition
the ledger's extent, for example `extern "C" { unsigned int __identifier("?g_Va00DEC140@@3IA")[13]; }`. The braces
matter: without them `extern "C"` only declares, and the object is undefined at link. Byte verification is unaffected,
because references are masked. Too large wastes bytes; too small corrupts memory, so the gap is the safe choice until
the class's real size is known.

**Repair, for a name with a data row:** `tools/data_rows.py` measures `sizeof` of the plain name and refuses a macro,
and a mangled scalar cannot be larger than its type. So make it a real array in every file that names it,
`unsigned int g_X[N];`, and change the row to `?g_X@@3PAIA` with size `N * 4`. Uses that take `&g_X` compile unchanged.

**Check the gap against the object first.** It is only an upper bound, and two names here show why. `g_Va00DFF0C4` has
a gap of 12 and holds a 4-byte `UnicodeString`: it needs nothing, and retyping it renumbered `GameText.cpp`'s EH labels.
`g_Va00E06634` has a gap of 12 and another row inside it, below.

**Done, data-rowed names, as arrays:** `g_Va00E065EC`, `g_Va00DF2984`, `g_Va00E06620`, `g_Va00DEBC64`,
`g_Va00E06360`, `g_Va00E08D48`, `g_Va00E0631C`.

**Found by `constructed_undersized` and read against retail's constructor, 2026-11-04:**

- `g_aptDateInterpreter`: 12 bytes, and retail's constructor at 0x006FE980 zeroes words out to +0x3C. Sized to the 72-byte
  gap in `AptDate.cpp`, which has no other member names to give it.
- `g_registryAtE02E88`, `g_00E04424`, `g_00E044F0`: 1-byte `Rva002B7250`, and constructor 0x003818F4's base 0x00330757 writes
  +0xC. Each now has 16 bytes through a storage member in the class that defines it.
- `g_00E06734`, `g_00E06748` (20) and `g_Va00E06710` (12): arrays, as above.

The array and storage sizes are the ledger's gap, an upper bound. Each constructor's writes reach at least the last word of
that size except `g_aptDateInterpreter`, whose last proven write is +0x3C.

- `g_00DFE7A8`: one byte, and retail's constructor at 0x0023DBF9 writes out to +0x88. It takes 0x98 bytes in
  `Rva003B9EC4.cpp`, keeping the name its byte readers declare. Its data row claimed a one-byte object retail does not have,
  and `tools/data_rows.py` measures the plain name, so the row was removed. The gap of 8 was far below the true size: the
  ledger's next name is a field of the same object, so a small gap does not mean a small object.

- `g_Va00E06360`: first sized to its 20-byte gap, wrongly. Constructor 0x0057AA45 writes out to +0x20. The ledger's
  `g_00E06374`, `g_00E06378` and `g_00E0637C` were its words 5 to 7, so `StrategicHUD.cpp` read ints nothing wrote.

**An object recorded as several globals.** The ledger knows addresses, so a field used on its own looks like a separate
global, its gap is too small, and code reads the wrong memory. So the gap is not a safe size: read the constructor.
`constructed_undersized` compares against the gap and misses these once sized to it. A one-off scan of 71 constructed
globals against their constructor's highest store found only `g_Va00E06360` and `g_Va00E06634`, but it cannot see a class
whose name differs from its constructor's row, as `g_00DFE7A8`'s does. No check enforces this yet. Leads with close
neighbours to read: `g_Va00E032E8`, `g_Va00E048C4`.

**False alarm, read against retail:** `g_00E02EAC` is a 16-byte `Region2D`; the gap of 20 is padding.

**Done, in `Rva007ABD4BGeometryInits.cpp` and `Rva007B401CButtonNameInits.cpp`:** the names those files construct.

**Done, all in `Rva007B6880Thunks.cpp`:** seven filter objects (`g_Va00DEC018`, `g_Va00DEC080`, `g_Va00DEC0E0`, `g_Va00DEC140`,
`g_Va00DEC174`, `g_Va00DEC1CC`, `g_Va00DEC1DC`), `g_Va00A1F4E8`, `g_Va00DFDD0C`, `g_Va00E0669C`, `g_Va00E06778`, `g_Va00DE2008`,
`g_Va00E03168`, `g_Va00DF29B4`, `g_Va00DFF494`, `g_Va00E04508`, `g_Va00E04938`, `g_Va00E03174`, `g_Va00E06E60`, `g_Va009F6F30`
and `g_Va00DEDC80`.

**Open:**

- `g_Va00E06634` (16 bytes; the ledger's gap of 12 is short): one object recorded as two globals. Retail's constructor at 0x005D00A6
  stores 1000 at +8 and +0xC, so the row `?delay@Rva005CF9FF@@2IA` at 0x00E0663C, in
  `StrategicInGameUIBattleResolver.cpp`, is this object's +8. Ours is a separate zero, so the battle resolver's wait never
  happens, and the constructor writes past 4 bytes. Fix: make it an array with `delay` as `[2]`, retiring that row. The
  hatch register counts `g_Va00E06634` per file, and that file has no allowance for the name, so it needs a real name first.
- `g_Va00E01E08` (gap 16): `AIBurningDeathStateUpdate.cpp` names it and another worker held that file. It has no data
  row, so the first repair works without touching that file.
- `g_Va00E02FF8` (gap 20): has a data row, so it needs the array form, and `BfmeConv1292DeferredWalkers.cpp` names it. That
  file is frozen (`PointerSJATable::_M_bkt_num_key` and `::_M_delete_node` have no rows), so remedy those first.
- `g_00DFE7B0`: the ledger's name for +8 of the object at `g_00DFE7A8`, typed as a string. It should be read against that
  object now that the object has its storage.

The measured figures predate these repairs. `constructed_undersized` in the next real link's `image_report.json` gives
the current count; the source pattern only sees direct construction, so it can miss others.

#### Object pools, repaired 2026-11-04

`g_freelistPool00DBA5E0` and `g_freelistPool009BBD2C` (VA 0x00DBBD2C) were 1-byte zero-filled views. Retail's images are 24 bytes: 0x80, 0, 0, the allocate function at 0x0042FFC0, the free function at
0x0042FFE0, 0. `grow` (0x001EAEF9) calls through +0xC and `pop` (0x002393E2) reads the head at +8, so ours would have called
through neighbouring memory the first time a pool grew. The heads were also recorded as
`DrawableListFreeNodes` and `g_00DBBD34`, so `pop` and the code naming a head used different memory. Each is now one
object, as `36c6b5aa26` did for `g_freelistPool00DB8FEC`; the head names are per-file macros over the pool's +8 field.
Evidence is retail's bytes and the matched pool code. No build has run with this yet.

`g_freelistPool` (VA 0x00DA60E8, 1,459 references) had the same fault and got the same repair in `b83078ec2e`, with its head
`g_freeList` at 0x00DA60F0.

2026-11-04 scoped preview: the current `g_Va00E06E60` provider resolves the old blocker in all three selected filesystem consumers; the provider's separate `g_Va00DF2984` index blocker remains ([evidence](../../reverse/attempt_support/chat-header-adoption-20261104-codex5.md)); no census confirmation claimed.


#### Existing E06E60 provider rechecked, 2026-11-04, run1242

The picker still cites the older missing-global artifact, but the recorded
forty-byte E06E60 provider is present. The unchanged Rva0060147B source now
predicts LINKS with177 ->177 bytes. No new datum, identity, alias or link-census
credit is taken; the pending official whole-image result remains separate.
[Scoped review](../../reverse/attempt_support/link-picker-review-20261104-1242.md).
2026-11-04: current-object preview confirms the two DEC1CC/DEC1DC consumers ScreenFilterRva000FC63DSet.cpp and Rva007AC9B0FilterInits.cpp link with the existing providers; broader thunk unit still has an unrelated DF2984 array-name blocker ([evidence](../../reverse/attempt_support/screenfilter-link-header-20261104.md)).

2026-11-04: BridgeBehavior allocator shim now accesses the repaired pool's +8 head instead of the removed standalone `g_freeList`; 51/51 rows byte-match and the scoped preview links, with official real-link confirmation pending ([evidence](../../reverse/attempt_support/bridgebehavior-pool-head-20261104-codexb.md)).
