### LINK-624: addresses with two names and twice-registered initializers

Status: open (halilkkaya-sn3, 2026-11-07, from real link `1d41894d2a` image report
`duplicates.several` and `initializers.twice`).

When one retail global has two names in our objects the linked image holds two variables; code
that writes one and reads the other sees NULL. An initializer registered by two objects constructs
the same global twice. This entry records the addresses sn3 handled; lk42's LINK-623 holds the
wrong-globals lane.

**Fixed.**
- 0x00A08D3C `OSVersionExtraInfo` vs `g_rva00E08D3CString`; `initializers.twice` cpudetect.obj
  `_$E7` (0x007B54A0). The earlier note `reverse/attempt_support/data-00a08d3c-two-views-20261029-dd11.md`
  said cpudetect's object emits no initializer; it now emits `_$E7` (initializer) and `_$E8`
  (cleanup), in retail's order after ProcessorLog (0x007B5420) and CompactLog (0x007B5460).
  Rva00E08D3CString.cpp rowed the same two retail bodies. Fix: retract its two rows, delete the
  unit, readmit as cpudetect.cpp `_$E7` / `_$E8` (add_match). link_check cpudetect.cpp: LINKED
  8,761 -> 8,821.

- 0x009B5F88 `G00DB5F88` vs `WW3D::PrelitMode` (ww3d.cpp, initial value 1). ConstGlobalGetters2.cpp
  defined a second `int G00DB5F88 = 1`; GapBodiesGE25.cpp wrote it and meshmdlio.cpp read it. Now the
  getter and the setter reach `WW3D::PrelitMode` through the unit's WW3D view (private static, friend
  or accessor, `PrelitModeEnum` nested so the name mangles to `?PrelitMode@WW3D@@0W4PrelitModeEnum@1@A`),
  and meshmdlio.cpp switches on `WW3D::Get_Prelit_Mode()`. 65/65 + 31/31 exact; link_check unchanged
  (LINKED 190/427/6,452/4,980 for the four units, all LINKS).

**Skipped (done or held by another seat).** 0x00A1835C, 0x009E1F24, 0x00A0312C (lk42);
0x00A032E8 (GameLogic.cpp held); 0x009EBE0C/24 (lk42's note: retail-constructed copies in 4-byte
storage).

- 0x007AE806 Dict `g_Va00E00944` (VA 0x00E00944) `initializers.twice` (halilkkaya-sn4). Rva003B242CGet.cpp
  defines the Dict, and its object emits `_$E1` (Dict(0), atexit) and `_$E2` (cleanup) itself;
  Rva007ABEF3ArgCtorInits.cpp rowed the same retail initializer again. Fix: retract the ArgCtorInits row
  (deleted_rows.csv), drop its body, extern and the unused cleanup declaration, readmit 0x007AE806 as
  Get.cpp `_$E1` (add_match, exact). link_check: Get.cpp 59 -> 83 bytes, ArgCtorInits 472 -> 448, both LINKS;
  dir32_scope OK; find_declared_unmatched clean. Correction to the earlier lead: MapUtil `_$E33` (0x007AE5C2)
  builds `worldDict` at VA 0x00DFF140, a different global (retail bytes read `mov ecx,0xDFF140`), so there
  is no Dict duplicate on the MapUtil side. Not changed.

**Blocked: lk46's file claim on Rva007B6A00AtexitThunks.cpp and Rva007B6880Thunks.cpp (LINK-236).**
- Cleanup 0x007B7B14 (Rva007B6880Thunks.cpp `rva007B7B14`) is the same retail body as Get.obj `_$E2`; once
  the Thunks claim is free, retract it and readmit it as Get.cpp `_$E2` (until then Get.obj's `_$E2` is an
  unrowed body that its `_$E1` registers; the Thunks copy is orphaned, not registered).
- mixfile (0x007B54F0 / 0x007B9AB0): DONE (halilkkaya-sn5, 2026-11-07). mixfile.cpp's own object already emitted the
  initializer and cleanup for `_SimpleFileFactory`; the grab-bag CtorInits_Rva007ACC20 and AtexitThunks rowed
  second copies on an address-named `g_Va00E08D48`. Retracted both rows (deleted_rows.csv), dropped the bodies,
  externs, declarations and the two private SimpleFileFactoryClass views, removed the `g_Va00E08D48` definition,
  moved the data row at 0x00A08D48 to `?_SimpleFileFactory@@3VSimpleFileFactoryClass@@A` (mixfile.cpp), and
  readmitted as mixfile.cpp `_$E1`/`_$E2` (add_match, exact). Two address_global hatch lines retired.
  link_check: mixfile 655 -> 687 bytes, CtorInits_Rva007ACC20 132 -> 110, AtexitThunks 467 -> 457; all LINKS.
- 0x009FE490 `g_Va00DFE490` (AtexitThunks.cpp:136) vs `g_00DFE490` (ArmySummaryDescription.cpp, the
  data ledger's owner): drop the AtexitThunks definition (extern to the real global) and retire its data row.
