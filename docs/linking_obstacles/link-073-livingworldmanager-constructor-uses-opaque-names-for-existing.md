### LINK-073: LivingWorldManager constructor uses opaque names for existing container and lifetime owners

Status: Class folded 2026-11-09; constructor members and the pure-slot table remain, see the end of this entry. Earlier notes describe the state before the fold.

Evidence / affected unit: `LivingWorld/LivingWorldManagerCtor.cpp` remains U5 against `d1f046749a`. Native calls reach the existing 31-byte `hash_map<int,Rva00213E11Element>` constructor at 0x00213E11 and 25-byte map constructor at 0x0033C432; the private member types instead reference `Rva002130CA`, `Rva00212379` and `Rva00211FA3` constructors. Its 0x0076DE66 cleanup reaches the seven-byte 0x00210CC5 setter under a destructor spelling. Native primary table slot 0 reaches the deleting destructor whose 691-byte lifetime owner is already `LivingWorldManager` at 0x00214405, while the constructor row retains `Rva0022B12DSubsystem`.

Completed: diagnosis only; all 19 assigned rows pass the byte gate. The named lifetime owner, both container providers and the setter provider remain LINKS in the same current-provider preview. Raw native calls and pin/owner lookups are in `build/c136-gui-w2/native-all.log`, `dependencies.log` and `final-all-with-providers.log`.

Remaining / next check: rename/reconcile the existing constructor row to `LivingWorldManager`, establish the actual container member types with their destructor owners, and reconcile the listener lifetime with the existing setter owner. Existing pins do not supply definitions to the census; adding another pin cannot resolve these names. No missing native body is established. Clearance: pending. Census confirmation: not claimed.


**2026-11-07 wall: the constructor's member types (swarm Link lane).** Real link `f98a8da771` still
reports `??1Rva0022B12DSubsystem@@UAE@XZ` (LivingWorldManagerCtor.cpp), and it is item 7 of LINK-627's
boot path. `rename.py class --fold Rva0022B12DSubsystem --into LivingWorldManager --dry-run` passes the
retail vftable proof and refuses only because LivingWorldManager is registered: GameEngineInit.cpp,
LivingWorldManagerCtor.cpp and SubsystemInterface.cpp must come in as `--prepared` units on the
canonical `LivingWorldManager.h` (rename.py accepts `--prepared` for a registered NEW). The prepared
constructor unit is what cannot be written yet:

- The constructor (0x00213EEF, 355 B, 17 rowed funclets and its `__ehhandler`) builds its members
  through private STL shims that exist only in LivingWorldManagerCtor.cpp: an `_STL::vector` whose
  default constructor always calls the folded `_Vector_base<GameWindow*>` constructor at 0x00211E58, and
  `_STL::hash_map` / `_STL::map` declarations whose constructors are the pinned bodies 0x00213E11 and
  0x0033C432. Those shims are what give each member's construction its exact callee and EH state.
- The canonical header cannot host them: it has 20+ consumers that include real STLport, which would
  see `_STL::vector`, `hash_map` and `map` redefined. With real STLport member types instead, each
  member's construction changes (its own `_Vector_base<T>` instantiation, inline hash/map
  construction), so the constructor body and its EH graph no longer match. The only precedent for the
  vector half is the ICF fold pins at 0x00211E58 in `symbols.csv`; pins are hatches and do nothing for
  the real link, and they would not cover the hash/map members, so they are not the route.
- LivingWorldManagerDtor.cpp compiles its own private `LivingWorldManager` view, whose third base is
  `LivingWorldObserver` (the canonical header's is `Rva00210CC5`); it defines the three
  `??_7LivingWorldManager` tables from that view. Its destructor (0x00214405) destroys the same members,
  so a full reconciliation brings the destructor unit onto the canonical header as well.

Candidate design (not tried): give the header the member types as wrapper classes that expose only
out-of-line or `dllimport __forceinline` constructors and destructors bound to the existing rows
(0x00212AEF/0x00212ED3, 0x00213E11 with 0x002130CA and 0x00212379, 0x0033C432 with 0x00211FA3, the
0x00211E58 vector base with 0x0021397C), so the STL shims stay private to the constructor unit and real
STLport consumers see only the wrappers. Then the prepared fold of the three units, then the destructor
unit's view. Claims released; nothing edited.

**2026-11-08 wall: the candidate wrapper design cannot spell the members without STL names or new
pins (seat halilkkaya-lk69, real link 42508219603 at `e834581c00`).** `??1Rva0022B12DSubsystem@@UAE@XZ`
is still the one unowned unresolved name. Its only referrer in LivingWorldManagerCtor.cpp's object is
the local `??_GRva0022B12DSubsystem@@UAEPAXI@Z`, which slot 0 of the unit's own
`??_7Rva0022B12DSubsystem@@6BSubsystemInterface@@@` reaches. The design above was checked against
retail and the ledger before any edit. Nothing was edited.

- Retail 0x00213EEF builds the members in this order. +0x14 calls 0x00212AEF. +0x204, +0x218, +0x26C,
  +0x280 and +0x294 call 0x00213E11. +0x234, +0x240, +0x24C, +0x258, +0x2A8 and +0x2CC each do
  `lea eax,[ebp-0Dh]; push eax; call 0x00211E58`: an allocator temporary, then the vector base
  constructor. +0x2B4 calls 0x0033C432. The EH state is stored only around throwing calls (3, 4, 0Ah,
  0Bh, 0Ch, 0Eh, 10h), so the six vector-base calls must be seen as non-throwing. The unwind funclets
  0x0076DE53..0x0076DF2D tail-jump to 0x001B4E74, 0x0049B47C, 0x00210CC5, 0x00212ED3, 0x002130CA
  (four members), 0x00212379, 0x0010F149, 0x0007FAB3 (five vectors), 0x0021397C and 0x00211FA3.
- Every name the ledger holds at 0x00211E58 is a `_STL::_Vector_base<T,allocator<T> >(const
  allocator<T>&)` row. The only row at 0x00213E11 is `_STL::hash_map<int,Rva00213E11Element,...>::hash_map()`
  (StlSweepW4Rva00213E11.cpp). The non-template spellings that reach them (`??0Rva002130CA`,
  `??0Rva00212379`; `??0Rva00211FA3` at 0x0033C432) are symbols.csv pins. So a byte-exact
  constructor must name `_STL` templates, or add new pins for non-template wrapper constructors.
  New pins are hatches.
- The canonical header cannot name `_STL` templates. 30 of its 41 consumers carry no `// stlport`
  marker, so `build.py` (`source_needs_stlport`) gives them no STLport include path. The 11 that do
  include real `<vector>`/`<hash_map>`, so a private `_STL` template there would be redefined.
- Wrapper constructors declared out of line in the header have no definition for the real link. Today
  the only definitions are the constructor unit's in-class `__declspec(noinline)` COMDATs:
  `??0Rva002130CA`, `??0Rva00212379`, `??0Rva00211FA3`, `??0Rva0021397C` and
  `??0?$vector@URva00390729Element...`, from the current object's symbol table. Those cannot stay
  in-class once the class lives in the header. An out-of-class definition is refused by
  `find_declared_unmatched.py` (no row), and retail has no such body except as the pinned ICF
  targets.
- The six slot names (`init`, `reset`, `update`, `loadPostProcess`, `GetSnapshotName` and `xfer`
  under LivingWorldManager; placeholders 0x00210D0D, 0x002123BE, 0x00210F27, 0x00214052, 0x00213D93)
  remain a separate prerequisite. Their renames would be pointless before the fold can land.

Not tried, and not recommended without a maintainer decision:
- Explicit `_STL` specializations for the placeholder element types inside the canonical header. That
  is a shim in the canonical header, seen by all 41 consumers.
- Dropping the declared destructor, so that the unit emits an implicit `??1Rva0022B12DSubsystem`.
  It would clear the name but hide the identity under a wrong local destructor, which is a fallback
  path.

Remaining: a decision on how the canonical header may express STLport member types for non-STLport
consumers, for example a `// stlport` marker policy for LivingWorldManager.h consumers. Alternatively,
row the wrapper constructors as fold-proved twins of 0x00213E11 and 0x0033C432 compiled in the
constructor unit, which retires the three pins. Then the slot renames, then the prepared fold.

**2026-11-09 the fold (swarm Link lane; reviewed by Codex for the swarm coordinator).** What it did: `Rva0022B12DSubsystem` folds into `LivingWorldManager` through `rename.py class --fold`, with `GameEngineInit.cpp`,
`LivingWorldManagerCtor.cpp` and `SubsystemInterface.cpp` prepared; `GameEngine::init` allocates the canonical class. It removes the real link's `??1Rva0022B12DSubsystem@@UAE@XZ`. Retail evidence: constructor 0x00213EEF and
destructor 0x00214405 install the same three tables, `GameEngine` allocates 0x2D8 and calls that constructor, and the name getter returns LivingWorldManager. 503/503 rows match.

Measured, images `afe630c454` and its exact base `3c5d07b6ca`: stubs 29 -> 28, bridged tables 4,088 -> 4,086, both stop at retail 0x37078. `image_iso` `vtable_slot` 150 -> 153 and unanalyzed slots 4,169 -> 4,166. Those 3 (`ParticleBufferClass` +48,
`HordeAIUpdate` +0, `Rva004C3108` +48) are not from the fold: with relocations masked each body has 0 differing bytes against the base. The verdict moved from unchecked to wrong because `code_equal` decodes inline jump tables as instructions, whose relocated
low bytes change with layout (`HordeAIUpdate` +0x10C holds 0x1048CDAF in one image and 0x1048CDDF in the other; `ParticleBufferClass` the same at +0xA0). `Rva004C3108` +48's body also calls retail-unmatched targets at +0x226, +0x25A and +0x28E in both images: that mismatch predates the fold.

**What it leaves, and what must not be removed first.** The constructor's own `??_7LivingWorldManager@@6BSubsystemInterface@@@` is 16 bytes against retail's 56, with `__purecall` in its last three entries. It is safe only while the vtable bridge wins. On the fold's image the constructor stores VA
0x109A3120, provided by `retail_vtables.obj`, 14 slots, none `__purecall` (0x10915B40); `exit_link.py` puts generated bridges before source objects. **So removing this bridge needs the class fixed first: bridge lane, read this before touching LivingWorldManager.** Suggested endpoint from the review: one
stable class definition with out-of-line construction wrappers and named overrides; byte match unproven. The two macros in the canonical header (`BFME_LIVINGWORLDMANAGER_CTOR_MEMBERS`, `BFME_LIVINGWORLDMANAGER_CTOR_PURE`) and its allocation-only form are accepted by the swarm coordinator as temporary on that basis.
`LivingWorldManagerCtor.cpp` stays out of the census on COMDAT differences (0 -> 0).

Stale until a regeneration, not to be hand-edited: `reverse/data_ledger.csv` rows `0x007E5220`, `0x007E5224`, `0x007E5234` and `0x007E7344` (the last gives one `image_iso` `no_object_retail_nonzero` entry), and `reverse/name_tiers.csv`.

**2026-11-09: listener destructor COMDAT cleared (seat Noro420).** The real link's `??1Rva0022B12DSubsystem@@UAE@XZ` blocker is gone with the fold above; `reverse/exit_link_blockers.tsv` (real link at `997413baa3`) predates it and still lists it until the next real link. `link_check.py` also reported `??1Rva00210CC5@@QAE@XZ` as "not retail's body": the unit defined it as a call to the `Rva00210CC5DwordImmSetter::apply` row. An empty destructor body now lets the compiler emit the vptr store itself, the same 7-byte shape retail has at 0x00210CC5, and `link_check.py` no longer lists it. The constructor's 19 rows still match. What remains for the unit is unchanged: the `??0Rva002130CA` and `??0Rva00212379` hash_map wrapper constructors (ICF-folded into 0x00213E11 in retail; the 2026-11-08 wall) and the short `??_7LivingWorldManager@@6BSubsystemInterface@@@` table.

**2026-11-09: the container wrapper constructors are gone (seat Noro420).** Retail's constructor calls 0x00213E11 and 0x0033C432 itself, so the members' own constructors were inlined and never existed out of line. `Rva002130CA`, `Rva00212379` and `Rva00211FA3` now declare no constructor. The constructor calls the rowed `_STL::hash_map<int,Rva00213E11Element,...>::hash_map()` (StlSweepW4Rva00213E11.cpp) and `_STL::map<unsigned char,int,...>::map()` (PersistentStorageThread.cpp) directly, with 19/19 rows still exact. That makes the three pins `??0Rva002130CA`, `??0Rva00212379` and `??0Rva00211FA3` obsolete, and they are removed. The compiler still emits unreferenced copies of the implicit wrapper constructors, but those names no longer have a retail address, so the census's `unreferenced` rule exempts them. `link_check.py` now reports only `??_7LivingWorldManager@@6BSubsystemInterface@@@` for the unit: the 16-byte constructor table differs from LivingWorldManagerDtor.cpp's private view, and retail's is 56 bytes. That needs the 14 slots named on both units, after the bridge-lane warning above. The 2026-11-08 header STLport question no longer blocks the constructor unit.

**2026-11-09: the primary table is retail's 14 slots in both installer units (seat Noro420).** Both LivingWorldManagerCtor.cpp and LivingWorldManagerDtor.cpp now include SubsystemInterface with `BFME_SUBSYSTEM_SLOTS` and declare `init`, `reset` and `update` as real overrides. Both compile the same 56-byte `??_7LivingWorldManager@@6BSubsystemInterface@@@`, and its slots line up with retail 0x00BE5234. `init` and `reset` are rowed in the constructor unit as verified ICF aliases of 0x00210D0D (`m_2C0 = false`, slots 1 and 9). `rename.py --to-class` refuses a body that sits in two slots, so the alias rows are the route. `update` is the old `?rva002123BE@Rva0021237E` row, moved by `rename.py function --to-class` (slot 10, Rva0021237EAudioEvents.cpp). 53/53 rows match, and `link_check.py` reports LINKS for all three units, the constructor going from 0 to 371 bytes. Still open: the Snapshot table 0x00BE5224 (`loadPostProcess` 0x00210F27, `GetSnapshotName` 0x00214052, `xfer` 0x00213D93; the `--to-class` dry runs refuse only because no installer compiles the slots yet) and the listener table 0x00BE5220 (slot00 against `OnSwapArmyMembers` 0x00211C68). The constructor unit keeps those slots pure. The vtable bridge still supplies the image's tables, so leave it in place until those slots are named.
