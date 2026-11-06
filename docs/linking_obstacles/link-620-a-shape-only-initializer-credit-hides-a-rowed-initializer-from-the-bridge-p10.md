### LINK-620: a shape-only initializer credit hides a rowed initializer from the bridge (P10)

Status: open. The tool route is parked (2026-11-06, after three reviews); the lasting fix is real statics
in source. Updated: 2026-11-06; ancalgonn-swarm-link. Related: LINK-236 (the initializer bridge),
LINK-226 (P8 and P9).

**Crash P10.** Diagnostic images of `swarm/link/p8-vtable-names` (`3f603f990a`, receipt
`2026-11-06T192133Z-boot_smoke-684b2b69ae66`; `dc58e0ef6d`, receipt
`2026-11-06T201150Z-boot_smoke-6be965fdcae8`) get past P9 and exit with 666 after a first-chance
0xC0000094 (integer divide by zero) at image 0x1012464D:
`hashtable<AsciiString, Rva0002C9E7Value>::_M_find`+0x18, the `hash % bucket_count` of an empty table.
Retail's only direct caller of that `_M_find` is `INI::preprocessMacro` (0x0002D0A9), which searches
`BfmeINIMacroTableStorage` (0x009DF58C). Retail builds that table in the dynamic initializer 0x007ABBB3,
rowed matched as `?rva007ABBB3@Rva007ABBB3CtorInits@@SAXXZ` in `Rva007ABBB3CtorInits.cpp`. The image holds
that body, but no pointer to it: it never runs, so the table keeps zero buckets.

**Cause (tool fact).** `image_report.initializer_report`'s weak pass credits an unidentified registration
to the first retail entry of the same shape. nullrobj.cpp's own `_$E1` (its loader static) has the common
`mov ecx, g; call ctor; push cleanup; call atexit` shape and took 0x007ABBB3, so `bridge_entries` counted
it registered and left the rowed body out of `retail_initializers.obj`. On the P9 object snapshot (run
42258145195's `image_objects`, ledger at `39bb28309b`), 36 of the 54 shape-only credits took a retail
entry whose rowed body is kept code.

**Lasting fix (next).** Row the initializers in their own units so each global is a real static its TU
registers, under LINK-236; the bridge is scaffolding to retire, not to grow. For P10 that is
BfmeINIMacroTableStorage's initializer 0x007ABBB3 (today an address-named grab-bag, `Rva007ABBB3CtorInits.cpp`)
in the INI unit that owns the table. No P10 tool change is on master.

**Tool attempts and reviews (branch `swarm/link/p10-initializer-credit`, unlanded).**

1. `b8d5941ebb`: a shape credit never takes an entry rowed to kept code, unless the registration shares a
   relocation target with the rowed body. P9 snapshot: shape-only credits 54 -> 21, `initializers_bridged`
   673 -> 706. Review: not OK.
   - A shared relocation is no construction: two shape-identical initializers that both read an unledgered
     `rate` and build different globals let the native one consume the rowed credit, so the rowed global
     is never built.
   - Indirect construction gets a second registration: a rowed wrapper and a native one that both call a
     helper building the same global have no direct relocation to it; the rowed wrapper is bridged beside
     the native one. Static-local construction and COMDAT copies were not covered (unioning references
     across copies says nothing about the copy the link keeps).
2. `2c31eb20cd`: byte-pattern construction evidence (`mov ecx, offset g`, absolute stores, memset and
   vector-iterator arguments, deletes of a global's pointer, atexit resolved one level, a lone-`ret`
   cleanup as its own identity); same/different/unknown against the credit; `rowed_unresolved` and
   `rowed_built_natively` never bridged; globals written by several natives or several rowed bodies
   (theBlockParseList, 81 rowed BlockParse initializers) treated as shared accumulators. P9 snapshot:
   shape-only credits 54 -> 26, bridged 673 -> 692 (23 added, 4 dropped as double-built), 5 unresolved,
   4 built natively. Review: not OK.
   - A standalone `B9 <g>` counted as construction: `mov ecx, offset g; mov eax, [ecx]; ret` only reads g.
   - Any overlap suppressed the whole initializer: native {A} against rowed {A, B} leaves B unbuilt, and an
     unrecognized helper makes either set incomplete.
   - Dropping several-writer globals causes double construction: natives {G, A} and {G, B} against rowed
     {G, C} make the rowed one bridgeable once G is removed, so G is built again.
   - Byte matching ignores instruction boundaries: `B8 89 05 <g>` is `mov eax, imm32`, misread as a store;
     valid stores such as `DF /7` were missed.
   - Low: `exit_link` merged the two lists into one `unresolved`.
3. `fe6237aa9d` (narrowed at review's request): master's credits, report and bridge entries unchanged; a
   shape-credited rowed initializer added only when both it and the crediting registration decode fully
   with capstone and what it constructs is disjoint from the credit, every other native registration, and
   anything an undecodable registration or its handed-over cleanup refers to. P9 snapshot: bridged
   673 -> 680, every master entry kept; added 0x007ABBB3, 0x007ACD90, 0x007ACDA0, 0x007AB830, 0x007AB846,
   0x007ABB80, 0x007B3A22; 29 left (20 rowed body unresolved, 7 credit unresolved, 0x007AC0FA overlaps its
   credit, 0x007ABBC9 referred to by INI_loadFile.cpp's undecodable `_$E1`). Its diagnostic run
   42291189639 was cancelled while queued; no receipt. Review: not OK.
   - Undecodable natives are searched one call level deep only: native -> helper -> helper -> constructor of
     G escapes.
   - Additions are not checked against each other or against existing bridge entries.
   - Destination identity ignores addends, ranges and aliases at one address.
   - `mov cl, 4`, `pop` and `add esp` do not update the tracked ecx or push state.
   - Medium: relocation width and kind are not checked against the operand field.
   - Medium: COMDAT copies are compared by result sets, not instruction streams.

Each round found new static-analysis gaps; the route is parked rather than grown.

**Findings for later (not changed).** Master already bridges four rowed initializers whose global a
native registration also builds, so the image builds each twice: 0x007B51EB (`Rva00A06858`
MappedImageCache; Rva005F0152ImageGet.cpp's `_$E1`), 0x007ABBE0 (`AsciiString::TheEmptyString`),
0x007ACD72 (`g_00DEE93C`) and 0x007AFC6B (`g_00E02EAC`, a Region2D). Retire them at the source under
LINK-236: row each native initializer and drop its rowed copy.
