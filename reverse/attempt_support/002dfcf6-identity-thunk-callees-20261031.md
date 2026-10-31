# Code-identity callee groups after the hashtable pass (seat halilkkaya-cid-o4, 2026-10-31)

Follows seat cid-o3's table of open callee groups (findings outside
`reverse/code_identity_baseline.tsv`). Counts are from scoped re-scans with
`allowed_symbols.scan` over the named sources. Target facts (retail bytes,
ledger rows) are kept apart from the structural inferences that fix them.

## Landed in this batch

| Callee group | Retail fact | Fix | Findings |
|---|---|---|---|
| `~DrawableList` at 0x00239BAB | 0x00239BAB is `jmp 0x00239AF4`, rowed as `list<Drawable *>::~list`; 0x00239AF4 is `_List_base<Drawable *>::~_List_base` | stack lists typed `list<Drawable *>` in 17 units; decl-only `~_List_base` (throw() where retail stores no EH state) | 18 |
| `_List_base<int>::~_List_base` at 0x00200667 (+ `_List_base<CameraMarker>` at 0x00295983) | both are 5-byte `jmp` thunks rowed as `list<T>::~list` | members typed `list<T>` in 9 destructor units | 11 |
| tree views at 0x00383567/0x0038356C/0x00383571 | 5-byte thunks = `map<unsigned char, int/short/float>::~map` | private `map` specializations holding the tree views; one ICF row at 0x00383567 | 19 |
| `_M_erase` of the region-record multimap (0x005025DB) | calls the pair destructor 0x0050174A out of line | `~Rva00501656()` declared in both instantiating units; ICF row | 2 |
| `_M_erase` at 0x0026C238 and 0x00501F2D | value destructors 0x000796BC (frees a vector at +4) and 0x005011B4 (`add ecx,4; jmp` the rowed vector destructor 0x00500E3D) | the sweep records hold that member; ICF rows for the pair destructor and `_M_erase` | 2 |
| `_M_insert_overflow<const UpgradeTemplate *>` at 0x002DFCF6 (step 1 of 2) | retail expands `max<unsigned>` | dllimport + `__forceinline` max in HordeContainApplyUpgradeMask.cpp; leaves `allocate` 0x00068E15 and `fill_n` 0x0007E48F rowed | 0 (prerequisite) |

The rule behind the first three rows: an unwind funclet (and the eh vector
destructor helper) always takes the member or local type's own destructor.
When a view type makes the normal path call the right address, the funclet
still names the view. Type the object as retail's container and keep the base
destructor declaration-only so the normal path stays out of line.

## Blocked or left

- **0x002DFCF6 row.** One ICF row clears the 5 UpgradeTemplate `push_back`
  findings (the allowed_symbols simulation certifies it):

      python3 tools/add_match.py '?_M_insert_overflow@?$vector@PBVUpgradeTemplate@@V?$allocator@PBVUpgradeTemplate@@@_STL@@@_STL@@IAEXPAPBVUpgradeTemplate@@ABQBV3@ABU__true_type@2@I_N@Z' 0x002DFCF6 140 Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainApplyUpgradeMask.cpp --icf-owner '?_M_insert_overflow@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@IAEXPAPBVModuleData@@ABQBV3@ABU__true_type@2@I_N@Z' --notes "ICF twin;fold-proof=Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainApplyUpgradeMask.cpp;compiler-emitted body a code-identity reference reaches at this retail address: this unit keeps the copy link.exe selects and it equals retail in bytes and resolved relocations;no unique coverage added"

  `claims.py claim 0x002DFCF6` was refused all session: its lock file
  ScriptEngineDoXfer.cpp is held by a TU-merge seat.
- **The 141-byte `_M_insert_overflow` copies** (`Rva005C4230*`,
  `Rva002C5EF0*`, `Rva004DD489*`, `const SpecialPowerTemplate *`,
  `Rva004DC920*`; 7 chain findings): each kept copy differs from 0x002DFCF6
  only in `call [__imp__free]` where retail calls free directly. The keeping
  units (Rva0052B278Permuted.cpp, LivingWorldBuildPlotIcon.cpp, ...) lack the
  `/D_CRTIMP=` the 140-byte providers use. They also need rows at
  0x002DFCF6, so they wait on the same claim.
- **PlaceEventTranslator.cpp** (1 DrawableList finding): the same retype
  swaps two spilled locals' frame slots in translateGameMessage. Recorded
  in re_attempts.log.
- **Held files with the same fix:** ProductionUpdateQueue.cpp (2 DrawableList),
  ScriptEngine_dtor.cpp (10 `_List_base<int>`), PlayerDestructor.cpp (2).
- **Remaining `_M_erase` findings (13).** Each sweep record spells a key or
  value retail does not have:
  - 0x00206593/5C8/5FD/632/69C/6D1 (StlSweepR3Rva002075F3 ... 00207761): the
    value destructor 0x002046BB is `jmp` to pair<const AsciiString,
    AsciiString>::~pair (offset 0), so the key is not an int. These need a
    retype and rename, not a destructor.
  - 0x0023FBDB: a set<Rva00439862Element> spelling where retail destroys
    pair<const int, Rva004393D6> values (0x0023D377).
  - 0x0060421C (ThingTemplate.cpp): the value at +4 has a destructor.
  - 0x002A13DB, 0x00056CC3, 0x000A7941: AsciiString members (strings fleet).
  - 0x004D9B4B, 0x00256FB5: full-body value destructors; they need real
    layouts.
  - 0x0028614C: 55 bytes with no destructor call; a different difference.
- **Next direct groups (same funclet rule, wrapper identity still to prove):**
  0x002F0F02 (`jmp` the tree destructor ??1Rva002EE9B7 at 0x002F0B52; 6 units),
  vector<Rva0007BB16Record> at 0x0007C632 (8 units), 0x0022CA3B,
  0x001FE065, 0x0021DA13, 0x0029A21F.
