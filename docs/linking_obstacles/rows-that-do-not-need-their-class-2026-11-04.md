### Rows that do not need their class: two repairs for the real link's blockers (2026-11-04, seat ancalgonn-ops-srv1)

**Status: Open as a method. Applied to the units below; the next real link measures them.**

Most of the real link's unresolved names come from a compiler vtable: a rowed constructor or
destructor makes the unit emit its class's table, and the table names members no unit defines.
Two repairs remove those references without new row names, and both keep the row byte-exact.

**1. The unit is a Zero Hour port of a class retail does not have.** Test it first: game.dat has no
string naming the class, and no other unit uses it. Keep the file and its rows and delete the
class's bodies. A row can stay without the class:

- a non-inline row stays an ordinary definition;
- a non-virtual inline stays by explicit instantiation or a pointer anchor;
- a virtual inline or a constructor stays through a file-local function nothing runs that calls it
  directly (`object->Class::slot()`, or a local of the type), with an extern pointer holding that
  function. `#pragma inline_depth(0)` around the function, or `/Ob0` on the unit, keeps the call out
  of line. Use neither when the row's own body needs an inline: `Matrix3D(bool)` needs its inlined
  `Make_Identity`, so `JetAIUpdate.cpp` relies on `/O1`, which keeps the constructor out of line.

This answers "cannot be anchored", recorded in LINK-072. Examples: `DumbProjectileBehavior.cpp`,
`JetAIUpdate.cpp`, `RailedTransportDockUpdate.cpp`, `WW3D2/collect.cpp`, `WWSaveLoad/twiddler.cpp`.

**2. The class is real but its virtuals are not all named yet.** The constructor stores retail's
tables itself, and each table is filled from retail's words with the ledger row at each slot's
address (`extern "C" { void __identifier("<row>")(); }`, then `(const void *)&__identifier("<row>")`).
Either give the class no virtuals of its own (`Rva005BA1FDCtor.cpp`) or, when a real base needs the
derived class to stay derived, mark it `__declspec(novtable)` so the constructor emits no table
(`Rva0008EF3FProductCtor_Unresolved.cpp`). Name the tables plainly: the compiler reserves a class's
`??_7` names as soon as the class is defined. This also makes the table retail's length.

**3. A leftover Zero Hour body nothing else references.** Some files in the real class still carry
`present-unmatched` bodies, and those bodies are what reference the missing names. Scan every object's
undefined symbols and read which function each relocation falls in. A body with no outside user and no vtable
slot can go. The build then reports any row it alone made the unit emit; keep those with a direct call as in
repair 1. Examples: `ThingFactory::parseObjectDefinition`, `ModelConditionInfo::validateCachedBones` and `::clear`.

**4. A base class named from retail's unwind.** When a missing `??1` belongs to a placeholder base, read the
parent's funclet in retail: its `jmp` lands on the real destructor, and the row at that address gives the name
for the local view. The same holds for a base constructor's call target. Examples: `AptValueGC` from funclet
0x007A8DA0 in `Rva006DE1A0Finish.cpp`; `BfmeThingSJ` from the call to 0x001320D0 in `BfmeConv901.cpp`. A
name with a canonical header must use that header; `tools/class_gate.py` refuses a private copy.

**5. A name the ledger pins to a row spelled differently.** The real link does not honour pins, so a pinned
name is missing even though its address is known. `reverse/symbols.csv` gives the address and
`reverse/functions.csv` the row there. Have the caller reach that row: declare a local view of the row's class
and cast, or give the local class a thin out-of-line member that forwards to it. Forwarding keeps the caller's row
byte-exact, because call targets are masked. `__declspec(noinline)` or `/Ob0` keeps the forwarder from inlining.
Examples: the `StlSweepW4` element operations, and `LivingWorldManagerCtor.cpp`'s members. Read retail's own
call first when the row looks unrelated: a fold shares one body under an unrelated name, and an old pin can be wrong.

Pinned names still missing at `181e4a4e7b`, with the row at each address. Some rows are folds, so these are leads,
not verified targets:

| Address | Missing name | Referenced from | Row at the address |
|---|---|---|---|
| `0x00007850` | `??0BFMENetworkState@@QAE@XZ` | `BFMENetwork.cpp` | `??0?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ` |
| `0x000120C0` | `??4?$vector@UPrereqUnitRec@ProductionPrerequisite@@V?$allocator@UPrereqUnitRec@ProductionPrerequisite@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z` | `ThingFactory.cpp` | `?assign@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@ABV12@@Z` |
| `0x0002CCC3` | `??1PB_DeepBase@@UAE@XZ` | `EvacuateDamageCtorModuleFactoryBody.cpp` | `??1?$hashtable@URva0002CCC3Record@@U1@U?$hash@URva0002CCC3Record@@@_STL@@U?$_Identity@URva0002CCC3Record@@@3@U?$equal_to@URva0002CCC3Record@@@3@V?$allocator@URva0002CCC3Record@@@3@@_STL@@QAE@XZ` |
| `0x000366F0` | `??4AudioEventRTS@@QAEAAV0@ABV0@@Z` | `ThingFactory.cpp` | `?set@?$StringBase@D@@QAEXABV1@@Z` |
| `0x0004254E` | `??0W3DAnimationInfo@@QAE@ABV0@@Z` | `W3DAnimationInfoVectorInsert.cpp` | `??0Region2D@@QAE@ABU0@@Z` |
| `0x00130FCE` | `?rva00130FCE@Rva00130FCE@@QAE_NXZ` | `VslotSmallBodiesAG_Rva00131CF2.cpp` | `?bfmeGoURB@BfmeThingURB@@QAEHXZ` |
| `0x001B4E63` | `?baseConstruct@BFME2NativeNetwork@@QAEXXZ` | `AerialPathfinder.cpp` | `??0SubsystemInterface@@QAE@XZ` |
| `0x001EC3B5` | `?removeAllTerrainBibs@BaseHeightMapRenderObjClass@@QAEXXZ` | `W3DTerrainVisual.cpp` | `?onCurrentMissionWon@LinearCampaign@@QAEXXZ` |
| `0x002C9BC3` | `?getRelativeAngle2D@PartitionManager@@QAEMPBVObject@@PBUCoord3D@@@Z` | `AIUpdate.cpp` | `?rva002C9BC3@Rva002C9BC3Owner@@QAEMPAX0@Z` |
| `0x002CF21B` | `?newDrawable@BFMEThingFactory@@QAEPAVDrawable@@PBVThingTemplate@@W4DrawableStatus@@H@Z` | `W3DGameClient.cpp` | `?newDrawable@ThingFactory@@QAEPAXPAXHH@Z` |
| `0x003F60C8` | `??1EvaMessageInfo@@QAE@XZ` | `EvaMessageVectorAssign.cpp` | `??1BfmeStringRecord00111ACF@@QAE@XZ` |
| `0x0046A9AB` | `?lower_bound@Rva0046A9ABMapLowerBound@@QBEPAU?$_Rb_tree_node@U?$pair@$$CBGVAsciiString@@@_STL@@@_STL@@ABG@Z` | `ConnectionManager.cpp` | `?_M_lower_bound@?$_Rb_tree@GU?$pair@$$CBGE@_STL@@U?$_Select1st@U?$pair@$$CBGE@_STL@@@2@U?$less@G@2@V?$allocator@U?$pair@$$CBGE@_STL@@@2@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBGE@_STL@@@2@ABG@Z` |
| `0x0047A69C` | `?buildFieldParse@Rva005C4352Base@@QAEXAAVMultiIniFieldParse@@@Z` | `VslotSmallBodiesAG_Rva00131CF2.cpp` | `?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z` |
| `0x0047A69C` | `?m@Gen_003bcb40@@QAEXH@Z` | `VslotSmallBodiesAG_Rva00131CF2.cpp` | `?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z` |
| `0x004D272E` | `?insert@Rva004D272EMapHintInsert@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBGVAsciiString@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBGVAsciiString@@@_STL@@@2@@_STL@@U23@ABU?$pair@$$CBGVAsciiString@@@3@@Z` | `ConnectionManager.cpp` | `?insert@?$map@HURva004D272ERecord@@U?$less@H@_STL@@V?$allocator@U?$pair@$$CBHURva004D272ERecord@@@_STL@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHURva004D272ERecord@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHURva004D272ERecord@@@_STL@@@2@@2@U32@ABU?$pair@$$CBHURva004D272ERecord@@@2@@Z` |
| `0x004EC395` | `??1AudioEventRTS@@UAE@XZ` | `ThingTemplate.cpp` | `??1?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAE@XZ` |
| `0x0052B7B3` | `??1Rva0052B7B3Dtor@@QAE@XZ` | `Rva007B6880Thunks.cpp` | `?j_0052b7b3@@YAXXZ` |
| `0x0052BB9A` | `??0Elem003AF9E0@@QAE@ABU0@@Z` | `PAVectorEraseRangeFamily003AF.cpp` | `??0Rva003A6360Record@@QAE@ABV0@@Z` |

**Limits.** Neither repair helps when the missing names are base destructors an EH unwind calls by name
(`Rva0057621ACtor.cpp`), or with real virtual inheritance (`Rva005F422CDtor.cpp`). A hand table is a
step toward linking, not the final source: when the class's members get real names, go back to the
compiler's table. Repair 1 removes retained COMDATs, so read the push hook's `link_batch_audit` and the
next real link for any provider a consumer loses.

**Evidence.** Each unit's rows byte-verified by `./build.sh` at the time of its commit. Real link: 271
unresolved at `fe50b7af7a`, 168 at `4a114fcaf5` after repairs 1 and 2, with three new names from providers the
removals lost: `??0UpdateModuleData`, `Get_Native_Screen_Size` and `getDisabledTypesToProcess` spelled
`BitFlags<13>`. All three are repaired since. Later runs: 151 at `7f8c3eb144`, 146 at `6686dd4790` (the first
authoritative link), 124 at `181e4a4e7b`, each including other workers' commits.
