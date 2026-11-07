### LINK-617: hand-built vtable arrays hold unrelocated retail slot addresses
Status: Partly repaired (2 of 12 sources fixed; the rest blocked on TU evidence or class identity; header lane). Updated: 2026-11-07; inspected revision: 35c0259989 (image 0a36813ed0, image_iso 35c0259989); repairs on 31e5d302162.

Evidence / affected units: `tools/image_iso.py` flags each word below as an `unrelocated_retail_address`
(`defects.tsv`, swarm packet P7b). Each constructor installs a vptr to an address-named `int`/`void *`/`char`
array whose initializer is retail's vtable as plain numbers. The bytes match retail, which loads at
0x400000 with no relocations. At our base (0x10000000) every slot points at the wrong memory, so any
virtual call through these objects jumps into garbage. The slot bodies are matched rows, but each is
rowed under a different placeholder class in another file, so no one class owns the vtable.

| Source | Array (retail VA) | Slots flagged | Slot rows (target facts) |
|---|---|---|---|
| Common/Bfme5ThirtyTwo.cpp | g_bfmeVtableCZ (0x00CE4A10, 19 slots + string bytes) | 19 | 0x68A160 BfmeThingVIH::bfmeDelVIH (BfmeConv1374.cpp), 0x7244B0 ICF twin, 16x __purecall, 0x68A130 Rva0068A130::rva0068A130 (Rva0068A130Cluster.cpp). Ctor 0x68A0E0 Gen_0081E480 here, dtor body 0x68A110 |
| Common/Rva000A217FCtor.cpp | g_00BC9020 (0x00BC9020) | 11 | GameWindow-family slots (??_GRva0008FF3E, Rva000A260AWindow::input/system, Rva000A261CWindow::draw, GameWindow::vslot6/8/9, Xfer::IsCRC twin, ...) |
| Common/Rva004F599EClear.cpp | g_00C63254 (0x00C63254) | 4 | FIXED 2026-11-07 (below). ??_GObjectModule twin 0x4A10FD, ~Region2D twin 0xB3FD0, Rva004F59ACNamed::name, Rva004F599E::xfer |
| Common/Rva005C44A3Ctor.cpp | g_00C745D4 (0x00C745D4, char blob with trailing strings) | 4 | 0x5C4537 (rowed ??_GRva004FA830), Rva005C44DF, Rva005C44C3::getName, Rva005C4352 |
| Common/R2ZeroingConstructors.cpp | R2Data010EC784 (0x00C61CA8), R2Data01085DBC (0x00C61C30) | 2 | ??_GRva004E194E, ??_GRva004E18A2; the ledger already lists ??_7Rva004E194E and ??_7Rva003B8610Record at 0x00C61CA8 |
| Common/R3ScalarFieldConstructors1.cpp | Gen00C1F470 (0x00C1F470) | 1 | FIXED 2026-11-07 (below). ScriptGroup; retail's table has 4 slots: ??_GRva003B4100, shared `ret` 0x4B3FD0, getter 0x3B40FA, ScriptGroup::xfer |
| Common/Rva007EB310Destroy.cpp | vftable_01129CB4 (0x00CE1514) | 1 | Rva007EB310Owner::destroy (ledger: ??_7Rva007EB2C0Object) |
| GameNetwork/Rva007EBAA0Create.cpp | g_bfmeVftTDA (0x00CE157C) | 1 | Rva007EB8B0Log::setFields_007EB760 |
| GameNetwork/Rva00800920FeslCtor.cpp | vftable_0112B89C (0x00C1C780) | 1 | __purecall (ledger: ??_7SecondaryModuleBase@FXParticleSystem; data row ??_7Rva003F498ACallback) |
| GameNetwork/ServiceHubImpl.cpp | vftable_01129CB0 (0x00CE1510), vftable_01129AF4 (0x00CE1354) | 2 | ??_GGen007EB140 (ledger: ??_7ServiceHubImpl), ??_GRva00657670 |
| GameNetwork/ServiceHubImpl_ctor.cpp | vftable_011296B0 (0x00CE0F20) | 1 | ??_GBfmeMsgVJH (ledger: ??_7Rva00808CB0LanGameEntry and six more) |
| WWLib/HordeMeleeAmoeba.cpp | g_00C6FF28 (0x00C6FF28) | 1 | ??_GRva00587752Record, then 0x587F11 and 0x587217 |

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
- Rva005C44A3 (g_00C745D4, the "IncreaseCommandPoints" LivingWorld bonus template): the ctor view
  works (0x005C44A3 stays exact with the compiler's vptr store, three overrides declared in retail's
  slot order), but the first `function --to-class` (0x005C44DF, 0x005C44C3 or 0x005C4352) is refused:
  no slot of the installer's table resolves to a row yet (all three are under other placeholders and
  slot 0's 0x005C4537 is ICF-shared), so the tool cannot show the order. Recorded as a false reject
  (`re_attempts.log`, 0x005C44DF); the ctor attempt was reverted. Needs the tool to accept moving the
  three together, then the same recipe.
- g_00BC9020 (Rva000A217F, a W3D gadget window): needs the canonical GameWindow (Bfme2GameWindow.h)
  reconciled with the BfmeAptScreenBase chain its base ctor 0x00104F8F uses; header lane.

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
