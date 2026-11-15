## Tables the vtable bridge does not cover: survey at e9c6c9136fa (2026-11-15)

Seat halilkkaya-vt. Inputs: a full `./build.sh` (FULL GATE: OK) at e9c6c9136fa,
`tools/vtable_bridge.plan()` over exit_link's own inputs called as
`exit_link.py` calls it, and the CI image a9c23eeaef's `vtable_bridge.json`.
Nothing was linked or run. Method notes at the end.

### Counts

| Group | a9c23eeaef (CI) | e9c6c9136fa | after 13f6c235f5d, b189a76a5ac |
|---|---|---|---|
| refused: strong-definition | 18 | 18 | 18 |
| refused: target-not-winning-provider | 6 | 6 | 6 |
| refused: unsupported-selection | 2 | 2 | 2 |
| bridged names with no kept definition | 23 | 23 | 21 |
| bridged tables (all) | 3,130 | 3,129 | 3,127 |
| already correct | 2,402 | 2,403 | 2,403 |
| vftable names with no retail address (never judged) | 691 | 691 | 691 |

A plan built without `image_report.retail_function_spans()` shows one more
refusal, `unrowed-target` on `??_7AptSpellStore@@6BGameWindow@@@` (0x0083D7F8):
the word after its 14 slots is the string "dds" (0x00736464), which reads as a
.text address. `exit_link.py` passes the spans (fdd0d06a747), so the real plan
bridges that table and refuses 26, not 27.

### What each group does to the image

**strong-definition (18).** The link keeps the hand-built array. For all 18
every slot relocates, DIR32 without addend, to a name the ledger binds only at
retail's slot target, the array is as long as retail's table, and every slot
target resolves to the verified provider that wins the link
(`Targets.resolve`, which the planner skips once it refuses). The image's
table equals retail's. Sixteen are also matched `reverse/data_rows.csv` rows;
the two `??_7Rva003AECE6@@6BRva003AECE6Slot0/1@@@` arrays (LINK-636) have no
data row. The defect sits beside them: where a compiler-named table is bound
at the same address (16 of the 18: `??_7Rva00253E19@@6BUpdateModule@@@`
beside `_vtbl_00BF17F8`, and so on) it is a short or wrong placeholder copy,
so no existing compiler table can replace an array; each needs its class.

**target-not-winning-provider (6).** The link keeps the first COMDAT copy of
the table, whose slot 0 names a deleting destructor that two units compile to
different bodies; path order puts the unverified one first.

| Table | Path-order winner (bytes) | Ledger body (bytes) | Difference |
|---|---|---|---|
| `??_7?$VectorClass@H@@6B@` 0x007BB5AC | Render2DSentenceAllocateSurfaceBFME2.obj (71) | vector_class_resize.obj (34) | winner inlines `Clear` |
| `??_7?$VectorClass@VVector3@@@@6B@` 0x007CEFAC | Rva007B7280Siblings.obj (71) | vector_class_vector3_ctor.obj (34) | winner inlines `Clear` |
| `??_7?$VectorClass@VStringClass@@@@6B@` 0x007D0D80 | INIStatsRecordTextures.obj (34) | dx8wrapper.obj (93) | owner inlines `Clear` |
| `??_7?$basic_ios@DV?$char_traits@D@_STL@@@_STL@@6B@` 0x007BBCEC | Rva003A5DA0Write.obj (28, /O1) | stlport_narrow_ostream.obj (30, /O2) | `pop ecx` against `add esp,4` |
| `??_7Bucket@@6B@` 0x007D3564 | BucketDtor.obj (30, /O2) | NameKeyGenerator.obj (28, /O1) | `add esp,4` against `pop ecx` |
| `??_7Rva005E3AE1@@6BRva0007DF07@@@` 0x00877C70 | Rva005E3AE1Dtor.obj (38) | SBServer.obj (42) | winner keeps `this` in ecx across the call to its own unit's `??1` |

Each pair does the same work; the image holds non-retail bytes for that
destructor, not another behaviour. Two tables also carry slots that name
template members with no ledger row (retail folds them into other
instantiations): VectorClass<Vector3> slots 1, 3, 4, 5 and
VectorClass<StringClass> slot 5. The image runs the unit's own instantiations
there, unverified against retail.

All six are artifacts of the default link order. Under
`exit_link.retail_object_order` (`--order retail`) the ledger owner's object
precedes the path-order winner in all six (ranks: 30 before 3,224; 72 before
9,403; 2,603 before 17,633; 3,946 before 13,475; 593 before 3,096; 15,573
before 15,851).

The same offline plan with `exit_link.ORDER = "retail"` (b189a76a5ac's
objects; a plan, not a link, and it says nothing about what else moving
copies costs):

| | path order | retail order |
|---|---|---|
| refused | 26 | 22 |
| target-not-winning-provider | 6 | 2 |
| already correct | 2,403 | 2,408 |
| bridged | 3,127 | 3,128 |
| mismatching source slots | 34,417 | 34,363 |

The six clear: VectorClass<int>, basic_ios<char>, Bucket and Rva005E3AE1
become correct, VectorClass<Vector3> and VectorClass<StringClass> become
bridged (their unrowed template slots). Two new wrong winners appear, both on
slot 0: `??_7?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY...`
(0x0081C2E4, was correct; FXParticleSystemFactories.obj before the owner
VectorDeletingDtorsV06.obj) and `??_7Rva0058AD7A@@6B@` (0x0087091C;
Rva0058AD7ACtor.obj before the owner Rva0058AD7ABase.obj). One correct table
turns bridged (`??_7AODCrushCollideModuleData@@6B@`, 0x0085A350) and three
bridged turn correct (AutoDepositUpdateModuleData, StructureToppleUpdateModuleData,
RespawnBodyModuleData).

**unsupported-selection (2).** Not defects. `??_7_com_error@@6B@` is a /GR
table (SELECT_LARGEST, RTTI locator before the symbol) as retail has it;
`??_7type_info@@6B@` has a second definition in the runtime archive under
another selection. In both the kept copy's slots equal retail's.

**bridged, no kept definition (23, now 21).** A unit stores an address-named
extern (`_vtbl_00BF36C0`, `?g_Va00CE4918@@3DA`) that nothing defines. The
bridge's generated copy is the only definition, so the exit image is right
and holds a second copy of that retail table beside the compiler-named one.
Without the bridge: each of the 21 left has one `/alternatename` to a
compiler table, and the store falls to that table. It is correct for 3
(`_vtbl_00BC6F20`, `_vtbl_00BD4688`, `_bfmeVftYX`) and short or wrong for 18
(VideoPlayer 1 slot of 29, Rva0098477 1 of 15, the two ModuleData tables 3
slots pure of 31). The two repaired names were the other kind: one had an
`/alternatename` to a correct table, one had none and was unresolved.
`link_check` reports 25 of the 26 units that name one as linking; only
Rva003AE017CopyCtor.cpp did not (repaired, b189a76a5ac).

**never judged (691 names).** Compiler vftables no matched body stores, so no
retail address is known. No function that stores one has a row in that
object. 324 are stored only by `EmitVtableTag` scaffold constructors, which
game code never calls; 292 only by other constructors and destructors; 75 by
something else as well (deleting destructors, `famgen*` factories, `*_Anchor`
helpers, and a few real bodies such as the W3D `Load_W3D` loaders,
`AABTreeNodeClass::Partition` and `initSubsystem<T>`). Whether any of those
367 stores runs was not analysed.

### Repaired

- 13f6c235f5d, `?g_007CE338@@3QBQBXB` (0x007CE338): MeshMatDescInstallUVArray.cpp's
  UVBufferClass stores its own table.
- b189a76a5ac, `...6BSecondaryModuleBase@1@@` (0x0081BFB4): Rva003AE017CopyCtor.cpp
  names the defined table; the unit links (0 -> 38 bytes).

### Blocked, with the remedy each needs

- `_vtbl_00BD4688` and `_vtbl_00BC6F20`: `reverse/re_attempts.log` (2026-11-15).
  A unit whose own view declares the class polymorphic cannot name that
  class's table through an extern (C2373), and dropping the hand store makes
  the unit emit a short table or a base vptr store retail lacks.
- `_bfmeVftYX`: FramGrab.cpp's storing body `BfmeOwnerYX::bfmeCleanupYX` is the
  destructor of `BfmeThingTXA`, whose table the unit already emits correctly;
  it needs `rename.py function --to-class`, then the store is the compiler's.
- `_vtbl_00C40818` (6 x `__purecall`): ToppleUpdateCtor.cpp could take
  `??_7CollideModuleInterface@@6B@` (target fact: FireWeaponCollide.cpp's
  matched store binds that name at 0x00C40818; donor fact: Zero Hour's
  ToppleUpdate derives from CollideModuleInterface, six pure virtuals), but
  Rva005C48D0Ctor.cpp's class is unidentified, so the name stays referenced.
- The other 17 need the class behind the table (their `/alternatename`
  targets are the short copies): the storing constructor's
  class declared with retail's virtuals, the slot rows renamed into it with
  `tools/rename.py`, the hand store dropped.
  Reach, most to least: VideoPlayer 0x008E4918 (boot), Rva0098477 0x007C8298
  (boot subsystem), ModuleData 0x007F36C0 / 0x007F3740 / 0x0083B988 (INI
  load), ShdDefFactoryClass 0x0087C584 and Rva007B6880Thunks' three tables
  (static initializers), DllHandle loader 0x007E3994, window transitions
  0x00816530 / 0x00816574 / 0x00816594 (menu), FX 0x0081D2C0 (match),
  FunctorNotSet 0x007D3B54 (thrown only), FESL 0x008E3AE4 / 0x008E3AE8
  (online).
- The six wrong winners: a link-order decision (`--order retail`), or per
  table the first provider compiling the ledger's body
  (`bucket-dtor-profile-20261111.md` for Bucket).

### Method

`plan()` was called with `image_report.Retail(exe, retail_function_spans())`,
exit_link's inventory, omitted set, archives and source map; for each refusal
the per-slot `Targets.resolve` verdict was added, and for each unbound name
the code relocations that store it. The two COMDAT bodies of each wrong
winner were read from the objects. The CI figures are from
`vtable_bridge.json` of image a9c23eeaef. Reach is inferred from unit and
class names except where a row or initializer address is cited.
