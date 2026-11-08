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
