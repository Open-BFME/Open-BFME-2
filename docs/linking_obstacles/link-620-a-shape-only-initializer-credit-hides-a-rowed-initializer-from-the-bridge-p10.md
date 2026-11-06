### LINK-620: a shape-only initializer credit hides a rowed initializer from the bridge (P10)

Status: open (fix in review). Updated: 2026-11-06; ancalgonn-swarm-link, branch
`swarm/link/p10-initializer-credit`. Related: LINK-236 (the initializer bridge), LINK-226 (P8 and P9).

**Crash P10.** Diagnostic images of `swarm/link/p8-vtable-names` (`3f603f990a`, receipt
`2026-11-06T192133Z-boot_smoke-684b2b69ae66`; `dc58e0ef6d`, receipt
`2026-11-06T201150Z-boot_smoke-6be965fdcae8`) get past P9 and exit with 666 after a first-chance
0xC0000094 (integer divide by zero) at image 0x1012464D:
`hashtable<AsciiString, Rva0002C9E7Value>::_M_find`+0x18, the `hash % bucket_count` of an empty table.
Retail's only direct caller of that `_M_find` is `INI::preprocessMacro` (0x0002D0A9), which searches
`BfmeINIMacroTableStorage` (0x009DF58C). Retail builds that table in the dynamic initializer 0x007ABBB3,
rowed matched as `?rva007ABBB3@Rva007ABBB3CtorInits@@SAXXZ`. The image holds that body, but no pointer
to it: it never runs, so the table keeps zero buckets.

**Cause (tool fact).** `image_report.initializer_report`'s weak pass credits an unidentified registration
to the first retail entry of the same shape. nullrobj.cpp's own `_$E1` (its loader static) has the common
`mov ecx, g; call ctor; push cleanup; call atexit` shape and took 0x007ABBB3, so `bridge_entries` counted
it registered and left the rowed body out of `retail_initializers.obj`. On the P9 object snapshot, 36 of
the 54 shape-only credits took a retail entry whose rowed body is kept code.

**Fix (narrow).** Master's report, credits and bridge entries are unchanged. `shape_credit_proof` adds a
shape-credited rowed initializer to the bridge only when both it and the crediting registration decode
fully with capstone (`image_report.construction`: every instruction classified, every relocation on an
operand, calls only to a constructor with a known `this`, atexit with a cleanup decoded the same way,
memset or a vector constructor/destructor iterator, or a destructor inside a cleanup), and what the rowed
body constructs is disjoint from what the crediting registration and every other native registration
constructs, and from every global an undecodable registration (or a cleanup it hands over) refers to.
The rest are listed with a reason. `exit_link`'s `initializer_bridge` keeps `shape_credit_bridged` and
`shape_credit_left` apart; the image report carries both.

**Measured on the P9 object snapshot** (run 42258145195's `image_objects`, ledger at `39bb28309b`):
`initializers_bridged` 673 -> 680, every master entry kept. Bridged: 0x007ABBB3
(BfmeINIMacroTableStorage), 0x007ACD90, 0x007ACDA0, 0x007AB830, 0x007AB846, 0x007ABB80, 0x007B3A22.
Left as on master (29): rowed body unresolved 20, crediting registration unresolved 7, constructs what the
crediting registration constructs 1 (0x007AC0FA, BfmeFontCharsCache, with W3DGameFont.cpp's `_$E6`), an
unresolved registration refers to what it constructs 1 (0x007ABBC9: INI_loadFile.cpp's `_$E1` registers
an inlined ~AsciiString of BfmeINICurrentFilename).

**Findings for later (not changed here).** Master already bridges four rowed initializers whose global a
native registration also builds, so the image builds each twice: 0x007B51EB (`Rva00A06858`
MappedImageCache; Rva005F0152ImageGet.cpp's `_$E1`), 0x007ABBE0 (`AsciiString::TheEmptyString`),
0x007ACD72 (`g_00DEE93C`) and 0x007AFC6B (`g_00E02EAC`, a Region2D). Retire them at the source, under
LINK-236, by rowing each native initializer and dropping its rowed copy.

**Next.** The stacked diagnostic image and the independent review; then the boot receipt past P10.
