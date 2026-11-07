### LINK-617: hand-built vtable arrays hold unrelocated retail slot addresses
Status: Partly repaired (5 of 12 sources fixed; the rest blocked on TU evidence or class identity; header lane). Updated: 2026-11-07; inspected revision: 35c0259989 (image 0a36813ed0, image_iso 35c0259989); repairs on 31e5d302162 and 10748c0b80c.

Evidence / affected units: `tools/image_iso.py` flags each word below as an `unrelocated_retail_address`
(`defects.tsv`, swarm packet P7b). Each constructor installs a vptr to an address-named `int`/`void *`/`char`
array whose initializer is retail's vtable as plain numbers. The bytes match retail, which loads at
0x400000 with no relocations. At our base (0x10000000) every slot points at the wrong memory, so any
virtual call through these objects jumps into garbage. The slot bodies are matched rows, but each is
rowed under a different placeholder class in another file, so no one class owns the vtable.

| Source | Array (retail VA) | Slots flagged | Slot rows (target facts) |
|---|---|---|---|
| Common/Bfme5ThirtyTwo.cpp | g_bfmeVtableCZ (0x00CE4A10, 19 slots + string bytes) | 19 | 0x68A160 BfmeThingVIH::bfmeDelVIH (BfmeConv1374.cpp), 0x7244B0 ICF twin, 16x __purecall, 0x68A130 Rva0068A130::rva0068A130 (Rva0068A130Cluster.cpp). Ctor 0x68A0E0 Gen_0081E480 here, dtor body 0x68A110 |
| Common/Rva000A217FCtor.cpp | g_00BC9020 (0x00BC9020) | 11 | FIXED 2026-11-07 (below). GameWindow-family slots (??_GRva0008FF3E, Rva000A260AWindow::input/system, Rva000A261CWindow::draw, GameWindow::vslot6/8/9, Xfer::IsCRC twin, ...) |
| Common/Rva004F599EClear.cpp | g_00C63254 (0x00C63254) | 4 | FIXED 2026-11-07 (below). ??_GObjectModule twin 0x4A10FD, ~Region2D twin 0xB3FD0, Rva004F59ACNamed::name, Rva004F599E::xfer |
| Common/Rva005C44A3Ctor.cpp | g_00C745D4 (0x00C745D4, char blob with trailing strings) | 4 | FIXED 2026-11-07 (below). 0x5C4537 (rowed ??_GRva004FA830), Rva005C44DF, Rva005C44C3::getName, Rva005C4352 |
| Common/R2ZeroingConstructors.cpp | R2Data010EC784 (0x00C61CA8), R2Data01085DBC (0x00C61C30) | 2 | ??_GRva004E194E, ??_GRva004E18A2; the ledger already lists ??_7Rva004E194E and ??_7Rva003B8610Record at 0x00C61CA8 |
| Common/R3ScalarFieldConstructors1.cpp | Gen00C1F470 (0x00C1F470) | 1 | FIXED 2026-11-07 (below). ScriptGroup; retail's table has 4 slots: ??_GRva003B4100, shared `ret` 0x4B3FD0, getter 0x3B40FA, ScriptGroup::xfer |
| Common/Rva007EB310Destroy.cpp | vftable_01129CB4 (0x00CE1514) | 1 | Rva007EB310Owner::destroy (ledger: ??_7Rva007EB2C0Object) |
| GameNetwork/Rva007EBAA0Create.cpp | g_bfmeVftTDA (0x00CE157C) | 1 | Rva007EB8B0Log::setFields_007EB760 |
| GameNetwork/Rva00800920FeslCtor.cpp | vftable_0112B89C (0x00C1C780) | 1 | __purecall (ledger: ??_7SecondaryModuleBase@FXParticleSystem; data row ??_7Rva003F498ACallback) |
| GameNetwork/ServiceHubImpl.cpp | vftable_01129CB0 (0x00CE1510), vftable_01129AF4 (0x00CE1354) | 2 | ??_GGen007EB140 (ledger: ??_7ServiceHubImpl), ??_GRva00657670 |
| GameNetwork/ServiceHubImpl_ctor.cpp | vftable_011296B0 (0x00CE0F20) | 1 | ??_GBfmeMsgVJH (ledger: ??_7Rva00808CB0LanGameEntry and six more) |
| WWLib/HordeMeleeAmoeba.cpp | g_00C6FF28 (0x00C6FF28) | 1 | FIXED 2026-11-07 (below). ??_GRva00587752Record, then 0x587F11 and 0x587217 |

ServiceHubImpl has four private class copies (ServiceHubImpl.cpp, ServiceHubImpl_ctor.cpp,
createServiceHubImpl.cpp, BuddyThreadClassThreadFunction.cpp). None is registered in canonical_classes.csv.

Completed (2026-11-07, seat halilkkaya-lk48, base 31e5d302162). Method for both: declare the
constructor's class with retail's slots (canonical Snapshot order: deleting destructor, loadPostProcess,
GetSnapshotName, xfer), let the compiler store the vptr, move the name getter into the class with
`rename.py function --to-class`, delete the address-named array. No row moved file; no hatch added.

- MissionStats (`Rva004F599E`, Player's stats member, ctor 0x004F599E): `ca6cc516556` declares it over
  canonical Snapshot.h (constructor-only surface); `da90fb79ddd` moves 0x004F59AC to
  `?GetSnapshotName@Rva004F599E@@MBEPBDXZ`. The ctor's +0 store now relocates to `??_7Rva004F599E@@6B@`
  (4 slots). Against retail 0x00C63254 by address: slots 2 and 3 equal; slot 0 is this unit's `??_G`
  (retail's 28-byte shape, calls ~Snapshot), slot 1 an inline `ret`; retail's slots 0/1 are ICF-shared
  bodies (0x004A10FD, 0x004B3FD0). g_00C63254 deleted. link_check: Rva004F599EClear.cpp,
  ModuleNameGetters.cpp, Rva004F599EXfer.cpp, PlayerCtorBFME2.cpp, PlayerDestructor.cpp,
  PlayerInitFromDict.cpp all LINK before and after, 6,479 B unchanged.
- ScriptGroup (Gen00C1F470): `33bfad6bf95` replaces the scripts_orcondition shim's Zero Hour ScriptGroup
  with BFME 2's 0x10-byte class (the list heads at +4 are a non-virtual base: both ctors build them
  before the vptr store) and renames ctor 0x003B40DF to `??0ScriptGroup@@QAE@XZ` by hand (ScriptGroup
  had no special member for the fold to key on); `68f3183be3e` gives the table's deleting destructor an
  inline noinline `~ScriptGroup` of retail 0x003B4100's 14-byte shape; `cc6eaa57545` moves 0x003B40FA to
  `?GetSnapshotName@ScriptGroup@@MBEPBDXZ`; `b5394d52a44` folds `Rva003529B0` (copy ctor 0x003B410E,
  clone 0x003B4147 and three dependent mangled names) into ScriptGroup by hand, because `class --fold`
  would token-rewrite Scripts.cpp's private view into a second ScriptGroup and refuses `--prepared` for
  an unregistered global NEW; `d5f36960c3f` deletes Gen00C1F470 and its data row. Both ctors now store
  `??_7ScriptGroup@@6B@` (Scripts.obj and Rva003529B0Clone.obj emit identical copies); slots 2 and 3
  equal retail by address. link_check over the eleven units naming ScriptGroup or its placeholders
  (Scripts.cpp, OpaqueScalarDeletingDtors.cpp, Rva003529B0Clone.cpp, SubsystemNameGetters4.cpp,
  R3ScalarFieldConstructors1.cpp, ScriptGroupXfer.cpp, ScriptListSubrecordAddRva003B7E39.cpp,
  ScriptEngineRva0020C3BBCallScript.cpp, ScriptGroupWriteGroup.cpp, ScriptList_WriteScriptsDataChunk.cpp,
  ScriptListDestructor.cpp): 11/11 LINK, 8,256 B, unchanged.
- Left for ScriptGroup: retail's destructor 0x003B4100 and `??_G` 0x003B4A20 stay rowed under
  `Rva003B4100` (OpaqueScalarDeletingDtors.cpp). `rename.py class --fold Rva003B4100 --into ScriptGroup`
  refuses because the destructor's only +0 store is 0x00BBB554 (canonical Snapshot's table, written by
  the inlined base destructor) and ScriptGroup's ctors call no Snapshot ctor; recorded as a false reject
  (`re_attempts.log`, `??1Rva003B4100@@UAE@XZ`). After a tooling fix: fold, then drop the inline
  destructor from the shim and Rva003529B0Clone.cpp's view. That also retires LINK-618's stale
  `??_7Rva003B4100@@6B@` name on 0x007BB554.
- Tooling fix landed, fold still blocked (2026-11-07, seat halilkkaya-lk50). f4fe1d2f893 lets `--fold` accept
  a `+0` store that is a registered class's own table: 0x00BBB554 is installed as its own by
  `??0Snapshot@@QAE@XZ` 0x000053A6. The dry run's evidence now passes. Two walls remain, both outside rename.py:
  1. Blast radius. The scripts_orcondition shim `Scripts.h` spells `Rva003B4100` in a comment, so the token
     fold rewrites it, and the shim's includers exceed 200 ledger sources (`--max-files 200` refused).
     Removing that mention first is a shared-shim edit (full gate).
  2. DIR32 identity. `tools/dir32.py` binds `??_7ScriptGroup@@6B@` to 0x00C1F470 (ctors 0x003B40DF in
     Scripts.cpp and 0x003B410E in Rva003529B0Clone.cpp) and `??_7Rva003B4100@@6B@` to 0x00BBB554 (the
     dtor in OpaqueScalarDeletingDtors.cpp). A token fold makes one symbol bind both, which the DIR32
     consistency gate refuses. Retail's destructor stores Snapshot's table, so the views must derive from
     BFME 2's Snapshot (canonical, reference/shims/moduledata/Common/Snapshot.h). Structural inference from
     retail's order: the heads base is declared before Snapshot (`class ScriptGroup : public Rva003B4071,
     public Snapshot`). MSVC then places Snapshot's vptr at +0 and the heads at +4. The ctor clears the heads,
     Snapshot's inline store is dead, and the class's own vptr is stored. The dtor's own store is dead, and
     ~Snapshot's store precedes the heads' `jmp clear`: retail's 14 bytes. The shim compiles Zero Hour's
     Snapshot.h, so this needs the header lane (shared shim, full gate). After that: fold, drop the inline
     destructor, and rehome the two rows into Scripts.cpp (their approved TU per its tu-skeleton marker).

Pass test for both: the next image_iso run no longer lists 0x00C63254 or 0x00C1F470's words in
`defects.tsv` (unrelocated_retail_address). Not claimed until that run.

Not fixed this pass, with what each needs:
- `Rva007EB2C0Object` (queue-ready lead a): no TU evidence. Retail 0x00658160 (createServiceHubImpl)
  pushes VA 0x00CE1534 `\views\feslbuild_main\jabba\fesl\source\hubsingle.cpp` (target fact), and the
  class's table 0x00CE1514 sits right before that string in .rdata, but `string_xrefs.tsv` lacks the
  xref: Ghidra made no function at 0x00658110/0x00658150/0x00658160/0x00658260. Measured over the
  image: 63 `__FILE__` path strings referenced from .text are absent from `string_xrefs.tsv`
  (hubsingle.cpp, FESL debug.cpp at 0x00658878/0x006588F4/0x006589A0, HordeMeleeAmoeba.cpp at
  0x0058846C, W3DScriptedModelDraw.cpp, ...). A scratch tu_map with F also read from retail operands
  (capstone-verified, owner rows only) finds 538 owners, 214 new, but withdraws 200 non-provisional and
  5,139 provisional approvals (W3DModelDraw.cpp's span holds W3DScriptedModelDraw.cpp strings): an
  owner decision, not a landable fix. Even with F at 0x00658160, rows 0x00658150/0x00658260/0x006582B0
  need a non-placeholder class name (U) or a second hubsingle anchor above 0x006582B0. Runtime risk is
  low: only destroy() stores vftable_01129CB4; ctor and dtor already store the compiler's table.
- CZ (lead b): rows 0x0068A0E0..0x0068A18B sit between approved VideoPlayer.cpp (Z) and
  CompressionManager.cpp (Z, 0x0068A190), so no C bracket agrees. The dtor 0x0068A110 calls 0x006891E0
  (VideoPlayer.cpp's approved span, a remove-from-list shape): a lead that CZ is that unit's stream
  class, not proof. Its `??_G` 0x0068A160 inlines the dtor, so both must share a TU. CZ is abstract (16
  `__purecall` slots): the array is live only during base construction and destruction.
- R2ZeroingConstructors.cpp (0x00C61CA8, 0x00C61C30): the classes' rows and approved TU are in
  SpawnArmy.cpp, file-claimed by another contributor on 2026-11-07; skipped. `??_7Rva003B8610Record`
  on 0x00C61CA8 is a stale data_ledger name (no unit defines it).
- g_bfmeVftTDA (FESL debug reporter): retail 0x00CE157C has 6 slots (setFields, the callback runner
  0x00658710, the variadic logger 0x00658820, assertFailed 0x00658890, errorFrom 0x00658930, a deleting
  destructor 0x006587E0 freeing 0x14 bytes); our array has one word, so slot-3 asserts read past it.
  Online only (created from createServiceHubImpl, called by BuddyThreadClass::Thread_Function).
- Rva005C44A3 (g_00C745D4, the "IncreaseCommandPoints" LivingWorld bonus template): the first
  `function --to-class` was refused because no slot of the installer's table resolved to a row (all three
  under other placeholders, slot 0's 0x005C4537 ICF-shared). CLEARED 2026-11-07 (seat halilkkaya-lk50):
  the tooling fix f4fe1d2f893 adds `--also RVA=NEW`, which moves the slots of one table in one plan, each
  judged by the others. One batch moved 0x005C44DF -> `?rva005C44DF@Rva005C44A3@@UAEPAVRva005C436E@@I@Z`
  (slot 1), 0x005C44C3 -> `?getName@Rva005C44A3@@UBE?AVAsciiString@@XZ` (slot 2) and 0x005C4352 ->
  `?rva005C4352@Rva005C44A3@@UAEXAAVMultiIniFieldParse@@@Z` (slot 3). The ctor unit declares the three
  overrides in retail's order, the compiler stores `??_7Rva005C44A3@@6B@`, and g_00C745D4 is deleted.
  Against retail 0x00C745D4 by address: slots 1-3 equal; slot 0 is this unit's `??_E` (retail's
  0x005C4537 is the ICF-shared `??_GRva004FA830`). Evidence: 20/20 exact; scoped DIR32 OK; link_check
  over Rva005C44A3Ctor.cpp, Rva005C44DFCreate.cpp, RvaAsciiStringNameGetters.cpp,
  Rva0052B5C6Factory.cpp and AsciiStringFoldDeleters.cpp: 5/5 LINK, 833 B unchanged;
  VslotSmallBodiesAG_Rva00131CF2.cpp does not link before or after (0 B). Pass test: the next image_iso
  run no longer lists 0x00C745D4's words in `defects.tsv`. Not claimed until that run.
- g_00BC9020 (Rva000A217F, a W3D gadget window): needs the canonical GameWindow (Bfme2GameWindow.h)
  reconciled with the BfmeAptScreenBase chain its base ctor 0x00104F8F uses; header lane. CLEARED
  2026-11-07 (seat halilkkaya-lk59, base 10748c0b80c), see the section below.

Completed (2026-11-07, seat halilkkaya-lk59, base 10748c0b80c): g_00BC9020, the combo box image window.
Target facts: the class chain is GameWindow (table 0x00C0BBCC, 11 slots) <- Rva0078D310Host (ctors
0x00104F32/0x00104F8F, dtor 0x00104E03, table 0x00BCF818; its member at +0x218 follows GameWindow's
0x218 bytes) <- Rva000A2137 (ctor 0x000A2137, table 0x00BC8FF4, the combo box window) <- Rva000A217F
(ctor 0x000A217F, table 0x00BC9020). Retail's 0x00BC9020: slot 0 0x0008FFC4 (ICF-shared ??_G calling
0x000A43C8, a `jmp 0x00104E03`), slots 1/2 Rva000A2137's 0x000A214F/0x000A2167, slot 3 0x000A261C,
slots 4-6/8/9 GameWindow's own rows, slot 7 0x000A219D (returns the factory Rva0008FABBCreate),
slot 10 0x0047A699 (`xor eax, eax; ret`, Rva0078D310Host's override; GameWindow's own is 0x0050B5C6).
- `b5c3e44baf0`: `rename.py function --to-class Rva000A2137` moves 0x000A214F (input) and 0x000A2167
  (system -> bfmeGoEHCb, the canonical slot-2 identifier) out of the placeholder Rva000A260AWindow.
- `7f047a8e50d`: hand renames (rename.py keeps parameters and moves only placeholder-class members)
  give Rva000A2137 its draw 0x000A260A (`?draw@Rva000A2137@@UAEHPAX@Z`, the canonical `draw(void *)`
  spelling) and slot-7 getter 0x000A2197 (`?fetchCreateInstance@Rva000A2137@@UAEPAXXZ`, was the free
  `?Rva000A2197Get@@YAHXZ`). Rva000A2137's own table, emitted by Rva0078D310HostCtor_Rva00104f8f.obj,
  goes from 1 slot to 4 (slots 1-3 equal retail).
- `5f01f968169` does the same for Rva000A217F (0x000A261C draw, 0x000A219D getter) and declares
  the chain over the canonical GameWindow in Rva000A217FCtor.cpp; the compiler stores
  `??_7Rva000A217F@@6B@` and g_00BC9020 is deleted. Against retail 0x00BC9020 by address: 9/11 slots
  equal (1-9). Slot 0 is this unit's `??_G` (retail's 28-byte shape) calling `??1Rva000A217F`, a
  `jmp ??1Rva0078D310Host` like retail's folded 0x000A43C8; slot 10 is an inline `return false`
  override on the Rva0078D310Host view (retail's 0x0047A699 is the ICF-shared `xor eax, eax; ret`).
  Evidence: 89/89 exact; find_declared_unmatched clean; scoped DIR32 OK; link_check over the nine
  units naming these classes (Rva000A217FCtor.cpp, W3DGadgetWindowDrawSlots.cpp, ConstIntGetters2.cpp,
  Rva0078D310HostCtor_Rva00104f8f.cpp, Rva0008F8EBFactories.cpp, W3DGameWindowManagerGadgets.cpp,
  ReplaceObjectUpdate.cpp, Rva00104E03Dtor.cpp, Rva0078D270GameWindowHostDtor_Rva00104f32.cpp): 9/9
  LINK before and after, 3,164 B unchanged. Pass test: the next image_iso run no longer lists
  0x00BC9020's words in `defects.tsv`. Not claimed until that run.
- Left for this family (LINK-514 short tables, not unrelocated words): `??_7Rva0078D310Host@@6B@` is a
  1-slot copy in all three of its definers (Rva0078D310HostCtor_Rva00104f8f.cpp,
  Rva0078D270GameWindowHostDtor_Rva00104f32.cpp, Rva00104E03Dtor.cpp; the latter two keep private
  GameWindow copies, header_queue rows), and `??_7Rva000A2137@@6B@` stops at slot 3, because that
  unit's base is a one-slot BfmeAptScreenBase view. Moving the three definers to the canonical
  GameWindow together (a ctor/dtor pair holds two copies of one table) completes both. The other 16
  gadget tables' draw rows in W3DGadgetWindowDrawSlots.cpp still spell `draw(WinInstanceData *)`; the
  canonical slot is `draw(void *)`, a parameter respelling rename.py cannot make.

Completed (2026-11-07, seat halilkkaya-lk59): g_00C6FF28, the HordeContain "Amoeba" melee behaviour
descriptor Rva005876D5 (constructor 0x005876D5, 0x70 bytes; HordeContainParseMeleeBehavior allocates
it for any MeleeBehavior name after Swarm, WaitForLeader and HoldGround). Target facts: retail table
0x00C6FF28 = [0x00587752, 0x00587F11, 0x00587217]; 0x00587752 is the deleting destructor ICF-shared
with Swarm's and HoldGround's, calling 0x00468A3F (`mov [ecx], 0x00C44890; ret`: the destructor of
the base whose table 0x00C44890 the HordeContainParseMeleeBehavior.cpp view models as
Rva004691B7MeleeBehavior). So the base class is that descriptor base; no new base was needed.
- One `rename.py function --to-class Rva005876D5 --rva 0x00587217 --new buildFieldParse --also
  0x00587F11=slot1` plan moves slot 2 (out of the placeholder Rva00587217, GapBodiesS3L.cpp, whose
  FieldParse table 0x00C6FE88 names Rva005876D5's own offsets) and slot 1 (the factory, out of
  Rva00587F11Factory, with its `__ehhandler$` row and funclet note). HordeMeleeAmoeba.cpp declares
  Rva005876D5 over the base view (slot 1 keeps the row's `Rva005D6FCC *` return) and the constructor
  stores `??_7Rva005876D5@@6B@`; g_00C6FF28 and its data row `?g_00C6FF28@@3HA` are deleted.
- Recipe: with a polymorphic base the constructor gained an EH frame (the base subobject has a
  destructor and the member constructor 0x00042526 may throw). Retail stores no EH state: declaring the
  member constructor `throw()` (it only zeroes 0x4C bytes) restores retail's 125 bytes.
- Against retail 0x00C6FF28 by address: slots 1 and 2 equal; slot 0 is this unit's `??_G` (retail's
  28-byte shape) calling the implicit `??1Rva005876D5`, which compiles to 0x00468A3F's 7 bytes (store
  the base table, ret). The unit now also emits the base's `??_7Rva004691B7MeleeBehavior@@6B@`, `??0`,
  `??1`, `??_G` and `buildFieldParse` COMDATs, each byte- and relocation-identical to
  HordeContainParseMeleeBehavior.obj's copies. Evidence: rename.py's ./build.sh 21/21 exact;
  find_declared_unmatched clean; scoped DIR32 OK (16 symbols); link_check over HordeMeleeAmoeba.cpp,
  GapBodiesS3L.cpp, HordeContainParseMeleeBehavior.cpp, InlineDtorDeletingDtors1.cpp,
  Disp0DwordImmSettersAddr.cpp, LargeGroupAudioAudioMap.cpp, HordeContain/HordeMeleeAmoeba.cpp,
  HordeMeleeAmoebaXfer.cpp, FamilyDeletingDtors_Rva00587F69.cpp and Rva00587F69Dtor.cpp: 10/10 LINK,
  8,520 B unchanged. Pass test: the next image_iso run no longer lists 0x00C6FF28. Not claimed until
  that run.
- Left: the base still has two placeholder names (Rva00468A46 in InlineDtorDeletingDtors1.cpp, ctor
  0x00468A36 and `??_G` 0x00468A46; Rva004691B7MeleeBehavior in the HordeContain views), and the
  HordeContainParseMeleeBehavior.cpp view still declares Rva005876D5's slot 1 returning `void *`. The
  emitter-only `??_GRva00587752Record` row and its `/alternatename` stay as they were.

Remaining / next check: for each array, reconcile the class. Give the constructor's class its real
virtual functions in retail slot order (a header via `tools/header_adopt_lane.py` where one exists),
rename the slot rows into that class with `tools/rename.py`, and let the compiler emit `??_7`, so the
vptr store relocates. Then delete the address-named array and its ledger alias. Verify with
`./build.sh` on every touched source and the next image_iso run (the words must leave `defects.tsv`).

Owner: the header lane, with TU evidence first (agreed 2026-11-06). A pilot in the static-defects lane
(about 50 minutes, nothing landed) found the same blocker in four of the twelve classes. A
compiler-generated `??_G` has to be emitted by its class's own TU, but none of these deleting-destructor
rows has an approved TU, and rows move only into an approved unit. Some classes also need a base class
identified first: HordeMeleeAmoeba's slot 0 at 0x587752 calls a base destructor at 0x468A3F and is
ICF-folded with two HordeContain destructors.

Queue-ready leads (TU evidence first, then the class):
- `Rva007EB2C0Object`: 0x658150 (ctor, Rva007EB2C0ObjectDestructor.cpp), 0x658260 (virtual dtor,
  same file) and 0x6582B0 (its scalar deleting destructor, rowed as `Rva007EB310Owner::destroy` in
  Rva007EB310Destroy.cpp with the hand-built vptr store). The class is already polymorphic and the
  compiler already emits its one-slot vtable. Once one TU is approved for the three rows, the row at
  0x6582B0 becomes the compiler's `??_GRva007EB2C0Object@@UAEPAXI@Z` in that TU, and
  vftable_01129CB4 and Rva007EB310Destroy.cpp's destroy() are deleted.
- The CZ class: 0x68A0E0 (ctor `Gen_0081E480`, Bfme5ThirtyTwo.cpp), 0x68A110 (dtor body
  `BfmeThingUC::bfmeResetUC`, BfmeThreeHundredFiftyFour.cpp, TU proposed BfmeThingUC.cpp), 0x68A130
  (slot 7 `Rva0068A130::rva0068A130`, Rva0068A130Cluster.cpp) and 0x68A160 (slot 0 deleting destructor
  `BfmeThingVIH::bfmeDelVIH`, BfmeConv1374.cpp, TU proposed BfmeThingVIH.cpp). These are four
  placeholder classes for one class with a 19-slot vtable (16 slots are `__purecall`; slot 1 is the
  ICF twin at 0x7244B0). The cluster sits directly before the approved CompressionManager.cpp
  (0x68A190), a lead for its TU.

Side fix landed separately: vftable_0112B89C (0x00C1C780, one `__purecall` slot, bound by name in about
50 FX particle files) now holds `(int)&_purecall` in Rva00800920FeslCtor.cpp. The array stays, because
those consumers name it.

Not pointers (left as they are):
- Huff.cpp `LZHLEncoderStat::symbolTable0`: henc.tbl packed {nBits, code} shorts (0x00B70008,
  0x00C30008, 0x00C70008).
- decodembs.cpp `defaultModeProbs`: byte probabilities (00 00 40 00).
- Two unattributed words: image RVA 0xA10ED0 is UTF-16 `L"LM"` after "Multiplayer_Human", and
  0xAD3EB4 sits in a run of int16 values (0x4D, 0x50, ...).

Clearance: pending.
Census confirmation: not claimed.
