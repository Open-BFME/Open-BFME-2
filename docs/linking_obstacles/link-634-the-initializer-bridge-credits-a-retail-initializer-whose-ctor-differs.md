### LINK-634: the initializer bridge credits a retail initializer when the owner's initializer calls a different ctor

**Status: Open (check gap). Updated: 2026-11-08; inspected revision: fb69867e93 (diagnostic image; tools at
02e12bcd22) (crash-triage seat2, P36). Family:
[LINK-630](link-630-a-byte-matched-row-whose-calls-bind-to-local-unrowed-comdats.md).**

- **Gap:** `tools/image_report.py` `initializer_report` maps each pending `_$E` registration (a compiler-local
  initializer with no row in its own object) to a retail `.CRT$XCU` entry by masked shape, then by
  `relocation_votes`. A relocation counts only when the ledger places its target; a target it does not place (an
  unrowed local ctor) is neutral. So the common `mov ecx, g; call ctor; push cleanup; call atexit` shape is credited by
  its global and `atexit` alone (two agreeing votes, no disagreement, one best entry: the strong pass), whichever
  ctor it calls. The credited retail entry counts as registered, so the exit link's bridge
  (`tools/exit_link.py` `initializer_table`) leaves it out, and its rowed body is never run. The report carries no
  sign of it: the entry is not in `by_shape_only`, `not_registered` or `plain_functions`.
- **Case (P36, crash):** the image-type cache global 0x00E06858 (`?Rva00A06858@@3VMappedImageCache@@A`, owner
  `Code/GameEngine/Source/Common/Rva005F0152ImageGet.cpp`, a plain-data view). Retail's initializer 0x007B51EB
  (`?rva007B51EB@@YAXXZ`, rowed in `Rva007AC6DDGlobalInits.cpp`) is `mov ecx, 0xE06858; call 0x005F005B; push
  0x007B99B5; call atexit`; 0x005F005B (`??0Rva005F00FB@@QAE@XZ`, rowed) builds the 'TypeImages' field object
  (base 0x00221635 inserts it into the function-local-static registry 0x002213D9, guard 0x00DFE4B8; vtable 0x00C78A78).
  The owner's `_$E1` (image XCU slot 685) calls the unrowed local `??0MappedImageCache@@QAE@XZ` instead, which
  registers nothing; the strong pass credited it with 0x007B51EB, and `?rva007B51EB@@YAXXZ` is absent from the
  image's XCU. StrategicHUD.ini then fails on 'TypeImages' (receipt
  2026-11-08T052156Z-boot_smoke-c9a2802ab59a, image fb69867e93). Replay: `build/triage/p36_bridge.py IMAGE_DIR` (seat2
  scratch) runs `initializer_report` on an image's recorded inputs.
- **Not an initialization-order defect:** the registry is order-safe, so a retail link order (P32) does not fix it.
- **Repair (P36, crash-prevention lane):** unify `MappedImageCache` with `Rva005F00FB` (ctor 0x005F005B, dtor
  0x005F00FB, getters 0x005F0152 and 0x005F0185; the two views disagree on the cache arrays, 13 slots against 10 zeroed,
  in a 112-byte global) and make the owner's initializer retail's 0x007B51EB. Test-only diagnostic (never lands):
  694c71b4fc on `swarm/triage/p25-p35-p36-test`, where `MappedImageCache`'s ctor runs the rowed retail ctor in place.
- **Proposed check:** compare the constructor the image's initializer calls with retail's. For each `REL32` relocation
  in a pending registration, read retail's call target at that offset; when the ledger rows that address under a
  different name than the relocation's target (here `??0Rva005F00FB@@QAE@XZ` against `??0MappedImageCache@@QAE@XZ`),
  count a disagreement instead of skipping it. A registration that matches a retail entry on everything but its ctor
  is then not credited: retail's entry stays unregistered (the bridge runs its rowed body, or it is reported as a
  `plain_function_row`), and the registration is listed as "builds <global> with <ctor>, retail with <ctor>" so the
  identity defect surfaces before a boot does. A regression case: this registration against 0x007B51EB.
- **Repair of the P36 case (2026-11-08, crash-prevention, seat4, branch `scan/p36-fix`, not landed):**
  `rename.py class --fold` gains the initializer route, which made `Rva005F00FB` and `MappedImageCache` one class. The
  owner now declares the constructor, so its `_$E1` and `_$E2` run the rows 0x005F005B and 0x005F00FB; they agree with retail's
  0x007B51EB and 0x007B99B5 outside relocations. `function --to-class` moved 0x005EFFA6 into the class, so the compiled table
  has retail's two slots. The rows 0x007B51EB and 0x007B99B5 stay in their units as plain functions: those addresses have no
  approved unit, so they cannot move, and `Rva007AC6DDGlobalInits.cpp` and `Rva007B6880Thunks.cpp` now declare the real
  members and match (953/953 across the 8 sources). The owner's `_$E1` does the construction, and the bridge's credit of
  0x007B51EB to it is now true. No link or boot has run on this yet. The bridge gap itself is still open: the check below is
  not built.
- **Scan of the whole table (2026-11-08, diagnostic image c1a124cccc, ledger at that commit, static only):** of retail's 1166
  initializers, 348 have the shape `mov ecx,&G; call X` (pushed arguments and a tail `jmp` included). Findings:
  `reverse/attempt_support/link-634-initializer-scan-c1a124cccc.tsv`.
  - 318 match: the same constructor on the same global.
  - 5 run retail's constructor on a global the map cannot place, so the global itself is unconfirmed.
  - 18 differ by symbol. 0x007B51EB (P36) really differs. 13 have no differing address operand (12 `vector` globals and
    `Random3Class`). 0x007ACC20 (`render_state`) makes the same stores inline.
  - **Judgement, read by hand, not proved:** the other three, 0x007AC818, 0x007AC832 and 0x007AC0FA, are own template copies
    of the same shape whose slots match retail's by name or family.
  - 7 have no image initializer for G; all have rowed bodies that are not in the image's table, and the replay shows 5 of them
    as shape-only credits to an unrelated `_$E`:
    `_Loc_init` 0x007AB830 and `CPUDetectInitClass` 0x007B54E0 (the constructor still runs from another entry);
    `g_vec00200D38` 0x007ABB96 and `g_videoTable` 0x007B6610 (zeroed storage reads as an empty vector, a reading of STLport not
    checked against retail's constructor; their atexit destructors do not run);
    `CAtlBaseModule` 0x007B559D and `CAtlWinModule` 0x007AB81A (the constructors never run; only initializer and atexit thunks,
    and ATL's own `Term`/cleanup, refer to that storage); and 0x007B6760, a real defect of this family with a different global
    (P39: the shape credit goes to `StringPool.cpp`'s `_$E1`, which runs `EAStringC`'s constructor on 0x00E18650, also
    `gpGlobalGlobalObject`, while 0x00E177D4 stays null; read as no boot stop, with exit-time risk, unverified by any run).
- **Unchecked by the scan:** the replay reports 294 shape-only credits, each keeping a retail body out of the bridge, and only
  those among the 348 were checked. The 818 initializers of other shapes were not compared at all (mostly constant setup) and
  could have lost bodies the same way. The proposed check should judge every shape and report on every image.
