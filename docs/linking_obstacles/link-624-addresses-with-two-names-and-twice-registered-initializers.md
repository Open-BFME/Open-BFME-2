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

**Skipped (done or held by another seat).** 0x00A1835C, 0x009E1F24, 0x00A0312C (lk42);
0x00A032E8 (GameLogic.cpp held); 0x009EBE0C/24 (lk42's note: retail-constructed copies in 4-byte
storage).

**Not yet handled / notes.** mixfile.obj `_$E1` (0x007B54F0), Rva003B242CGet.obj `_$E1`
(0x007AE806), MapUtil `_$E33` (0x007AE5C2): see below if investigated.
