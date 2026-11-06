### LINK-622: Wrong globals in the real link's image report

Status: Open. Updated: 2026-11-07 (seat halilkkaya-lk42); inspected: `image_report.json` of real link `1d41894d2a`
(2026-11-06 20:05 UTC), tree at `88ce76fc444`.

Evidence / affected units: the `globals` section of `tools/image_report.py` over the kept objects. Every address below is
a retail RVA unless marked VA; retail bytes are `game.dat`'s.

#### No object defines it, and retail's data is not zero (483)

The counter counts ledger rows of kind `global` for which no kept object defines any of the row's names as an external
data symbol, and whose retail bytes are not all zero. Read against the kept objects at `88ce76fc444` (the same 17,967
objects; the count reproduces at 483):

| Class | Rows | What it means |
|---|---:|---|
| Defined as a TU-local static | 296 | The object holds the data under a static symbol (`_MIN_OMEGA`, `__Stl_tenpow`, `_default_dayname`, ...). `scan_objects` reads external symbols only, so it neither finds them nor compares their bytes. Present in the image, contents unchecked. |
| Neither defined nor referenced | 183 | No kept object names them. The names come from `reverse/data_ledger.csv`, which is stale (a regeneration changes about 27,000 lines). For 118 of them `reverse/data_rows.csv` has a row at the same address under another name, which `data_ledger.load()` prefers but `image_report.py` (reading the CSV itself) does not; the subtitle table below was counted for the same reason. Not an image defect by itself. |
| Referenced, never defined | 4 | Resolved by `/alternatename` or COMMON storage, which the report cannot see. Read one by one, below. |

The four:

- `_vtbl_00BD4688` (`DynamicVectorBfmeHandleCtor.cpp`) and `_vtbl_00C4D5A0` (`ArrowStormUpdateModuleDataCtor.cpp`):
  `/alternatename` to the compiler's `??_7` of the same class. Hatches, but the right table.
- `?Rva0081D7C0FieldParseTable@@3QBUFieldParse@@B` (VA 0x00CE43B0), read by `parseSubtitle` in `SubtitleEntry.cpp`:
  **a wrong global, repaired.** A link-cycle repair (`d36a83efbfa`) aliased it to the string literal `"0"`
  (`??_C@_01GBGANLPD@0?$AA@`), so `INI::initFromINI` read the subtitle fields from the bytes of `"0"` and what follows
  it. Retail's table is five 16-byte entries (FontName, FontPitch, SubTitleType, SubTitle, LineTable) and a null
  terminator, and the tree already defines it byte-verified: the data row `?g_00CE43B0@@3QBUFieldParse@@B` in
  `INIThinFieldParsers2.cpp`. `parseSubtitle` now names that owner and the alias is gone (one `/alternatename` fewer).
  The ledger row lists only the old name, which is why the report counted it.
- `_static_qr2_rec` (0x009DB710, 280 bytes, `GameSpy/qr2/qr2.c`): retail initializes the first word to `INVALID_SOCKET`
  (`ff ff ff ff`, the rest zero); ours is a zero COMMON definition, because the carrier's initializer is commented out.
  Online hosting only.

#### One address, several names (23)

Two definitions for one retail datum link as two objects: one side writes, the other reads its own copy. Read
against retail and the readers:

- 0x00A1835C: **repaired.** `Rva006FB960Cluster.cpp` defined `g_bfmeFrameStackAtE1835C = 0` for the Apt frame stack
  that `AptScriptFunction.cpp` defines as `AptScriptFunctionBase::spFrameStack` and the interpreter sets. Retail's
  `Rva006FBE80::find2` (0x006FBE80, `8b 35 5c 83 e1 00`) reads that one pointer, so ours always took the scope fallback
  and never saw a script frame's variables. It now declares the owner as `Rva006FBED0Cluster.cpp` does.
- 0x009E1F24: **repaired.** `W3DShaderManager.cpp` defined both `W3DShaders[2]`, which init (0x000F5B43) fills, and
  `g_00DE1F24[1]`, which only `setShader` (0x00075655) read. Retail's `setShader` indexes 0x00DE1F24, so ours never
  reached a shader's `set` and always returned 0. It now reads `W3DShaders` through the same volatile view.

Remaining / next check: regenerate `reverse/data_ledger.csv` (a separate decision; LINK-619 measured the same staleness)
and re-read this counter; most of the 183 should then name their current owners.

Clearance: pending. Census confirmation: not claimed.
