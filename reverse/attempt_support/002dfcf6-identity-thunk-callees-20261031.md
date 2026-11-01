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
| `set<int>::~set` at 0x00073116 | `jmp` the int-tree destructor 0x000730DE | `set<int>` specialization holding the tree view in 4 units | 4 |
| `ModuleInfo::~ModuleInfo` at 0x0033CF2F | `jmp` the record-vector destructor 0x0033CD02 | ThingTemplate's four module-info members typed ModuleInfo | 4 |
| `~Rva0021DA13` at 0x0021DA13 | `jmp` the name-set destructor 0x0021D5D5 | the save-file name sets typed Rva0021DA13 (as AptSaveLoadRva0043684C.cpp does) in 4 units | 4 |
| `PlayerStorage::~PlayerStorage` at 0x002BBD4D | `jmp` the battle-record vector destructor | the battle records typed PlayerStorage in LivingWorldBattle and LivingWorldAIArmyMover | 3 |
| `_M_insert_overflow<const UpgradeTemplate *>` at 0x002DFCF6 (step 1 of 2) | retail expands `max<unsigned>` | dllimport + `__forceinline` max in HordeContainApplyUpgradeMask.cpp; leaves `allocate` 0x00068E15 and `fill_n` 0x0007E48F rowed | 0 (prerequisite) |

The rule behind every row but the `_M_erase` and `_M_insert_overflow` ones: an unwind funclet (and the eh vector
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
  vector<Rva0007BB16Record> at 0x0007C632 (8 units; the owner
  ??1Rva0007C632Dtor is a strong definition, so a COMDAT wrapper would
  collide), 0x0022CA3B, 0x001FE065 and 0x0029A21F (their owners are
  method-named forwards, so the wrapper destructor needs its own ICF row),
  PlayerStorage in LivingWorldLogic.cpp ($L26855), and the deque holder
  0x000581F0 (MilesAudioManager.cpp, 4).

## Seat halilkkaya-cid-o5 (2026-11-01)

| Commit | Group | Findings |
|---|---|---|
| fe2e5d759c | `_List_base<int>` (0x00200667): ScriptEngine_dtor.cpp's ScriptIntList and Player's +0x700/+0x704 typed `list<int>` (the eh vector destructor iterator over ScriptEngine's 20-list arrays takes it too) | 13 |
| a0e899119e | Player's +0x288/+0x294/+0x2A8/+0x2D0 typed as wrappers Rva001FD85E/Rva001FE065/Rva001FD863 (implicit destructor = retail 5-byte `jmp` to the container destructor); ICF rows at 0x001FD85E, 0x001FE065, 0x001FD863 beside the method-named forwards | 4 |
| 553805e859 | AptPlayer's +0x5C/+0x70/+0x90 typed as wrapper Rva002239AD over Rva0022366C; ICF row at 0x002239AD | 3 |

Wrapper rule: when the funclet's retail target is a 5-byte `jmp` to the
destructor it names, the member is a wrapper. Type it with an implicit
destructor and row the emitted `??1` as an ICF twin at the thunk.

Open, with the blocker:

- **BfmeObject476Copy.cpp** (9 funclets, $L13041-3/$L14089-91/$L14298-300):
  the same three wrappers. Their rows now exist, so retyping the members
  needs no new row. Held (StarkillerHDX@fleet).
- **AptShapeContainer.cpp** (13 callers of 0x002888D4): the only copy of
  `hashtable<pair<const NameKeyType, ArmorTemplate>, ...>::_M_find<NameKeyType>`
  is kept from this unit. Its decl-only `vector<void*>::size()/begin()`
  specializations (lines 584-586) make the copy call them out of line, where
  retail inlines them. Held.
- **`??_F` vector closures at 0x00256646** (11): keptplan finds them FIXABLE
  with ICF rows for `vector<T>::vector(const allocator&)` at 0x004F710A in
  Rva0007517FCtor_Unresolved.cpp, SlowDeathBehaviorModuleDataCtor.cpp (2),
  FXShaderParameterBinder.cpp, StrategicVeterancyAutoResolveCtor.cpp,
  BfmePod248.cpp and StrategicInGameUIDynamicAutoResolveDialogImpl.cpp.
  `claims.py claim 0x004F710A` is held through other fleets' files.
- **ScriptEngine_dtor.cpp map funclets** (6, thunks 0x00207BDA..0x00207BF8):
  ScriptEngine.cpp defines the thunks as strong out-of-line destructors
  (`??1Rva00207BDAMap` ...), so a COMDAT wrapper would collide. The
  handoff above notes that the key is not int.
- **PlayerDestructor.cpp**: uw_00775f1d targets 0x002AE76B, rowed only as
  the gen-thunk `j_002ae76b` with pin `??1Gen_uwm_002ae76b`. uw_00775e89
  targets the base-vptr reset 0x002A983D (certify unknown).
- **AptPlayerDtor.cpp** (7 left): FileInfoTree/TargetSet are `_Rb_tree`
  views where the funclets take map/set thunks (0x002241D1, 0x0022424D,
  0x0006C94B).
- **More thunk groups** (scan of 2026-11-01): 0x002F0F02 (6 units),
  0x0022CA3B (5), 0x0029A21F (4), 0x0007E7DD (4), 0x000B0560 (3),
  0x0008B4CD (3), 0x00550634 (3), 0x000411BC (3), and 0x000581F0
  (MilesAudioManager.cpp, held).
- **`?xfer@Locomotor` at 0x00341E2D is a wrong identity** (re_attempts.log,
  identity-suspect). Locomotor's table 0x00BDE888 has slot 3 = 0x001E525A
  (`?xfer@Rva001E3E43`). 0x00341E2D is slot 3 of the WaterRenderObjClass,
  GODupBase and Rva00341E22 tables. Fix: retire LocomotorXfer.cpp's row,
  then run `rename.py class Rva001E3E43 -> Locomotor`, keeping LocomotorCtor
  (395 B) linking. class:Locomotor is held. `canonical:string` was refused,
  so a basis is still needed.
