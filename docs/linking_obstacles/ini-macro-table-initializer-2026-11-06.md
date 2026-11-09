### LINK-621: the INI macro table's retail initializer never runs (P10); lasting fix and why the triage routes are closed
Status: Open. Updated: 2026-11-06; inspected revision: 4b2bb61eb1.
Evidence / affected units: with P8 and P9 fixed, the game exits on a divide by zero in
`hashtable<AsciiString, Rva0002C9E7Value>::_M_find`+0x18 from `INI::preprocessMacro`: the bucket
count of the global macro table `BfmeINIMacroTableStorage` (RVA 0x009DF58C, owner
`Code/GameEngine/Source/Common/System/INI_loadFile.cpp`) is 0 (receipt
`2026-11-06T201150Z-boot_smoke-6be965fdcae8`, branch image `dc58e0ef6d`). Retail builds it in the
initializer 0x007ABBB3 (`mov ecx, 0xDDF58C; call ??0INIMacroTable 0x0002DC3C; push 0x007B6A6E; call
atexit`), which our ledger holds as the placeholder static function
`?rva007ABBB3@Rva007ABBB3CtorInits@@SAXXZ` that nothing registers. The image report's shape credit
gives that retail entry to `nullrobj.cpp`'s native `_$E1` (history: LINK-620).
Findings (target facts, this pass):
- 0x0002CD7B is `INIMacroTable`'s destructor, not `??1EvacuateDamage@@UAE@XZ` (the row's name, from
  a masked search; re_attempts.log line 85297): retail destroys +0x14 (the set) then +0 (the
  hash_map) inside an EH frame, and its only caller is the atexit thunk 0x007B6A6E.
  `EvacuateDamage.cpp:249` defines a real `~EvacuateDamage`, so the rename needs care.
- The global is `unsigned BfmeINIMacroTableStorage[8]` (`?BfmeINIMacroTableStorage@@3PAIA`); retail's
  shape is an `INIMacroTable` object. Declared as `extern unsigned ...[8]` in INI/INI.cpp,
  Rva007ABBB3CtorInits.cpp, Rva007ABBB3CtorInits_Rva007ADCAE.cpp and Rva007B6880Thunks.cpp.
- `nullrobj.cpp`'s `_$E1` builds `NullLoaderClass _NullLoader` (nullrobj.cpp:64), a Zero Hour static
  retail does not have: retail .text has no `mov eax, 0x750; ret` (NullLoaderClass::Chunk_Type), and
  its only three loader-shaped initializers (0x007AB8A0, 0x007AC15D, 0x007B37CE) are rowed and build
  other loaders. Nothing in Code/ references `_NullLoader`.
Completed: none. Routes closed by the hard rules: a compiler-native static needs 0x007ABBB3,
0x007B6A6E, 0x0002CD7B and 0x0075C9F7 in one unit with the global, and tu_map approves none of them
(tu empty; 0x0002CD7B `displaced`); rowing nullrobj's `_$E1` as a retail initializer has no target.
Remaining / next check:
- Naming/identity: respell 0x0002CD7B (and its EH handler 0x0075C9F7) as `??1INIMacroTable@@QAE@XZ`.
- TU evidence: approve one unit for the global, 0x007ABBB3 and 0x007B6A6E (the global's owner
  INI_loadFile.cpp is approved into INI/INI.cpp; the INIMacroTable ctor 0x0002DC3C is proposed for
  INIMacroTable.cpp).
- Then define `INIMacroTable BfmeINIMacroTableStorage;` there (data row respelled to
  `?BfmeINIMacroTableStorage@@3VINIMacroTable@@A`, consumers' externs retyped, byte-neutral), and repoint
  0x007ABBB3 and 0x007B6A6E to the compiler's `_$E1`/`_$E2` (`object-symbol=_$E<n>`, hatch rule 9).
- Independently, removing nullrobj's non-retail `_NullLoader` static would end the shape credit; it
  needs an owner decision (Zero Hour donor code), not done here.
Clearance: pending.
Census confirmation: not claimed.

Update (2026-11-06, swarm crash-triage, base 4b2bb61eb1 + nullrobj trial): removing the
non-retail `NullLoaderClass _NullLoader` static (coordinator-approved) builds clean (`./build.sh` 3/3,
find_declared_unmatched passes, nullrobj.obj then emits no `_$E1`/`_$E2`) but does not bridge
0x007ABBB3. `image_report.bridge_entries` over the ledger and seat2's 17,973 current objects: 672
bridged entries with the old nullrobj object, 673 without `_$E1`, 0x007ABBB3 in neither. The
initializer report then gives 0x007ABBB3's shape credit to the next tie in retail order,
`particle_emitter_read_props.obj`'s `_$E4`; `by_shape_only` holds 35 such credits. Removing one
unrowed static only moves the credit, so the trial was reverted and not landed. 0x007ABBB3 needs
either the compiler-native static above (TU approvals and the 0x0002CD7B respelling) or the shape
credit to stop crediting ties, which is the parked tool route in LINK-620.

Update (2026-11-07, swarm crash-triage): 0x0002CD7B is now rowed as `??1INIMacroTable@@QAE@XZ` (with
its EH handler 0x0075C9F7) in its existing file, and the atexit thunk 0x007B6A6E names it; the
`EvacuateDamage` misidentification is retracted with tombstones. TU evidence (read-only, tu_map
rebuilt in memory): every INIMacroTable body lies inside `Code/GameEngine/Source/Common/INI/INI.cpp`'s
approved span (0x0002C9A6 and 0x0002DC1D are approved there by T; 0x0002CD7B and the ctor 0x0002DC3C sit
between approved INI.cpp rows), and the table's owner INI_loadFile.cpp is approved into INI.cpp. So
INIMacroTable belongs in INI/INI.cpp, not a separate INIMacroTable.cpp: the naming-convention hint
`INIMacroTable.cpp` is what leaves 0x0002CD7B and 0x0002DC3C only `proposed` (noncontiguous) after the
rename. Approving them needs a TU-evidence rule that folds an unanchored class hint into the one
anchored unit whose span holds all of its rows; 0x007ABBB3 and 0x007B6A6E need an initializer rule
(I is unpromoted and unanchored). Both are tooling, not done here.

Update (2026-11-07, swarm crash-triage, P10 family fix): the shape-credit family is classified in
seat2 `build/drift_review/swarm/p10_family.md` (36 shape-only native registrations: 0 A, 7 B, 6 C,
23 D). Four C entries, the Zero Hour W3D loader statics `_AggregateLoader`, `_BoxLoader`, `_NullLoader`
and `_ParticleEmitterLoader`, are removed (no Chunk_Type body for them anywhere in retail .text; no
consumers). With them gone the existing bridge registers 0x007AB8A0, 0x007ABB80, 0x007ABBB3 and
0x007ABBC9 (672 -> 676). `_DistLODLoader` stays: retail keeps its Chunk_Type (0x00064825) as
unreferenced code, which this unit only emits through the static's vtable.
Accepted debt, retire with the TU-approved fix above: 0x007ABBC9 (bridged, retail's initializer of
`BfmeINICurrentFilename`, VA 0x00DDF5B4) and INI_loadFile.obj's native `_$E1` both register that
AsciiString's cleanup. Checked on the matched bodies: the bridged initializer runs in the bridge block
ahead of every native registration, before WinMain, and is the only constructor call (the native `_$E1`
calls no constructor, only atexit); no other initializer references 0x00DDF5B4; the constructor
0x00326BE6 is `mov eax, ecx; and dword [eax], 0; ret` (empties, no allocation); both cleanups reach
`StringBase<char>::releaseBuffer` 0x00036410, which stores 0 after releasing and skips the release when
the pointer is 0, so the second cleanup only takes and drops the lock. Same pattern as LINK-616's
`TheFXParticleEditor`.
Caveat (independent review): both cleanups take `releaseBuffer`'s shared string lock, so the double registration assumes that lock is still valid when the second (bridged, earlier-registered, so later-run) cleanup runs at exit; retail runs that same bridged cleanup at the same point.
