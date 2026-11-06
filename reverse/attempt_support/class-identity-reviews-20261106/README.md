# Existing-type identity reviews, the whole pending class queue (2026-11-06)

`name_lane.py reconcile` reports pending class names that collide with an existing
declaration and deliberately leaves the identity question open: it "changes no source,
votes or status and does not certify identity". This is one read-only verdict per key
over that entire queue, so the next worker starts from evidence rather than from the
collision message.

Nothing here was applied. No source, contract, header or vote changed in this pass.
`verdicts.json` beside this file holds all 267 verdicts with their evidence; its fields
are `key`, `proposed_type`, `verdict` (same/different/undecided), `confidence`,
`evidence`, `canonical_ref`, `next_step`, `shard` and `source_exists`.

## What the queue actually held

Of the 267 keys served, 66 named a one-function donor that the consolidation lane has
since merged into its approved TU and deleted - Rva00276223Leaf.cpp into Drawable.cpp,
BfmeConv1037.cpp into BfmeThingRE.cpp, FXParticleSystemLineSample.cpp into
fxpsemitterlinevolumemodule.cpp, and so on. Their placeholder went with the file, so
those keys could never apply; they are retired as stale by the commit "Retire 66
class-name keys whose source a TU merge absorbed", and the queue now serves 201.
Reviewers found them independently, reporting the empty-file hash in their packet
instead of a declaration to judge. Their verdicts are kept here because several cite
where the code went (Object.cpp, W3DShrubBuffer.cpp, AITargetHeuristicExpansionBase.cpp),
which is the starting point if one of those names is wanted at its new path.

- verdicts recorded: 267; on a source still in the tree: 201
- all keys: same 76 / different 35 / undecided 156
- live sources only: same 62 / different 30 / undecided 109

## How much to trust each verdict

The brief required positive evidence and said so: equal fields never prove identity, a
shared callee address is ICF folding rather than identity, and "undecided" costs
nothing while a wrong "same" corrupts a shared type for every consumer. 156 keys came
back undecided, which is the honest answer for a thin forwarder or a struct touched at
a single offset.

The ten packets were cut by stride from one pool, so they are statistically comparable,
but the share of "same" ran 15, 15, 19, 22, 22, 22, 30, 35, 48 and 58 per cent. Eight
cluster between 15 and 35; two sit well above. That spread is reviewer disposition, not
packet difficulty, so **a medium-confidence "same" here is a candidate, not a finding**.
The packets were disjoint, so no key received an independent second opinion; pairing two
reviewers on the same key is how to get one, and is the cheapest next improvement to
this lane.

Two high-confidence verdicts were re-checked by hand against committed files. Both held
exactly, which is why the high-confidence set below is worth acting on first:

- `Rva004A4214` -> StructureCollapseUpdate. `reverse/class_contracts/StructureCollapseUpdate.json`
  records retail vtable 0x852648 with slot 0 `??_GRva004A4214@@UAEPAXI@Z`, the stand-in's
  own deleting destructor, while slots 3 and 4 are already
  `?xfer@StructureCollapseUpdate@@MAEXPAVXfer@@@Z` and
  `?rva0004A429F@StructureCollapseUpdate@@SA?AW4NameKeyType@@XZ`.
- `Rva001E3647Result` -> PathfindCell. `PathfindCell.h` lines 51-53 read the packed dword
  exactly as the reviewer described: `getType() = (CellType)(m_0C & 0xF)`,
  `getLayer() = ((m_0C >> 4) & 0x3F)`, `getPinched() = ((m_0C >> 16) & 1)`.

## High-confidence `same`, live source (18): reconcile candidates

Each still needs what the lane requires before anything lands: layout, bases and ABI
compared against the registered contract, the declarations reconciled in their own
commit, then byte verification and the affected-consumer link check.

- **AIUpdateInterface** - `Code/GameEngine/Source/GameLogic/Object/WeaponRva002CB2D1Range.cpp`
  - The stand-in's Object+0x258 AI pointer is null-checked at +0x1F0. Canonical AIUpdateInterface (AIUpdate.h:60-61) names +0x1F0 as the current locomotor pointer read by getCurLocomotor, and its contract shows the retail ctor writing a dword at +0x1F0. The ledger ties Object+0x258 to AIUpdate (functions.csv row for rva004884B7). Offset and role both match.
- **CameraPath** - `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewCameraModLookTowardBfme.cpp`
  - The stand-in's W3DView member cameraPath is at +0x280, its numWaypoints at CameraPath +0x2070, cameraMovementMode at +0x2354 and doingRotateCamera at +0x1DD. The canonical CameraPath view in W3DViewCameraModFinalLookTowardBfme.cpp (lines 48-60 and 105-109) has the same offsets, and its Elem {Coord3D, AsciiString, Int} and Base layouts match. Both files implement the same cameraModLookToward waypoint heading on the same member.
- **DisplayString** - `Code/GameEngine/Source/Common/Rva00262045Unlink.cpp`
  - The stand-in is a linked node with m_next at +0xC and m_prev at +0x10, unlinked through Rva00262045::unLink (Rva00262045Unlink.cpp:25-37). The canonical DisplayString header declares m_next and m_prev at those offsets (Code/GameEngine/Include/GameClient/DisplayString.h:56-57), and W3DDisplayStringManager.cpp:66-67 and :160 use the same 0x0C/0x10 pair through the same rowed unLink. The contract's retail ctor writes at 0x0C and 0x10 agree.
- **GameResultsInterface** - `Code/GameEngine/Source/Common/GameEngineDeletingBaseDerived.cpp`
  - The stand-in's constructor 0x00419D18 is recorded in reverse/functions.csv with vptr 0x00C3AD08, which is the ??_7GameResultsInterface@@6B@ vtable, and deleted_rows.csv folds its dtor 0x00419CD4 and deleting dtor 0x00419CDF onto that same vtable. GameResultsQueueStartup_Unresolved.cpp declares GameResultsInterface with the same vtable 0x00C3AD08 and pure slots 14-21 (line 61), and GameResultsQueue's dtor 0x0041A644 tears down that vtable. The private view is empty because this file already declares class GameResultsInterface at line 129, so the stand-in is already the canonical name here.
- **IDirect3DVertexBuffer8** - `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DAptRendererBeginTriangleList.cpp`
  - The stand-in BfmeAptVertexBufferInterface (W3DAptRendererBeginTriangleList.cpp:34-42) has eleven placeholder slots followed by Lock(unsigned, unsigned, void**, unsigned) as slot 11, and the file calls it through deviceBuffer with (offset, size, &memory, flags). The vendored D3D8 layout is D3DRESOURCE_METHODS (11 entries: QueryInterface through GetType) followed by Lock at index 11 with (UINT, UINT, BYTE**, DWORD) (reference/shims/d3d8_shim_validated.h:206-224), so slot index and argument list both match IDirect3DVertexBuffer8.
- **LaserUpdate** - `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLaserDrawBfmeDoDraw.cpp`
  - The stand-in is fetched with findClientUpdateModule(NAMEKEY("LaserUpdate")) (W3DLaserDrawBfmeDoDraw.cpp:108-109). It uses m_startPos at +0x0C, m_endPos at +0x18, m_dirty at +0x24 and m_currentWidthScalar at +0x3C, which are the exact offsets of the canonical LaserUpdate members in GameLogic/Object/Update/LaserUpdate.cpp (base Rva0049B47C is 0xC bytes, then m_startPos, m_endPos, m_dirty, ..., m_currentWidthScalar). The canonical class is the LaserUpdate ClientUpdate module with that pool key. Four offsets and the key match, beyond field widths.
- **MeshModelClass** - `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBufferRva000E8365.cpp`
  - The stand-in reads int VertexCount at +0x28 and a Vector3 buffer through the pointer at +0x30 (W3DShrubBufferRva000E8365.cpp:51-59, with Get_Vertex_Count and Get_Vertex_Array accessors). The canonical MeshModelClass contract has VertexCount int at +0x28 and Vertex (ShareBufferClass<Vector3>*) at +0x30, and the accessor names are the WW3D MeshModelClass API.
- **PathfindCell**  [hand-checked] - `Code/GameEngine/Source/GameLogic/AI/PathfinderCellQueryPredicates.cpp`
  - The stand-in is the record returned by rva001E3647Pos, which the ledger describes as a Pathfinder pos-to-cell lookup ending in getCell (pathfinder.cpp, 0x001E3647). It reads only m_flags at +0x0C: low nibble tags 1, 2, 5 and 7 (PathfinderCellQueryPredicates.cpp IsBuildRestrictedCell), layer (flags>>4)&0x3F in GetGroundLayer, and bits 16/17. PathfindCell.h defines getType() as m_0C & 0xF, getLayer() as (m_0C>>4)&0x3F and getPinched() as bit 16 of m_0C at +0x0C (the m_0C field after m_info, field04 and m_zone). The bit layouts and the cell-type codes (CELL_WATER=1, CELL_BRIDGE_IMPASSABLE=5) match exactly.
- **PathfindCellInfo** - `Code/GameEngine/Source/Common/System/Rva002F1BD5Finish.cpp`
  - Rva002F1BD5Data is the PathfindCellInfo payload reached through PathfindCell+0x00 (m_info), with the obstacle ObjectID at +0x28, which matches the canonical PathfindCellInfo m_obstacleID at +0x28 (AIPathfind.cpp view). The argument is a PathfindCell: its +0x0C word masked with 15 equals 4, which matches PathfindCell::getType() == CELL_OBSTACLE (PathfindCell.h). Two canonical offsets and a canonical enum agree.
- **PlayerTemplate** - `Code/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorPrimarySlots.cpp`
  - The stand-in reads m_playerTemplate-chain bool m_isEvil at +0x1BC through Player+0x34 (GettingBuiltBehaviorPrimarySlots.cpp:67-77, 114). Canonical PlayerTemplate.h:120 declares bool m_isEvil at +0x1BC, and Player.h places m_playerTemplate at +0x34 directly before m_opaque38 at +0x38, so Player+0x34 is the PlayerTemplate pointer. Name, offset and type agree.
- **SpecialAbilityUpdateModuleData** - `Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdateSlot8.cpp`
  - The stand-in is the SpecialAbilityUpdate module data: vslot08 reads const SpecialPowerTemplate* at +0x38 (SpecialAbilityUpdateSlot8.cpp:52-56, 64-66). Canonical SpecialAbilityUpdateModuleData.h:37 declares const SpecialPowerTemplate *m_specialPowerTemplate at +0x38, the same name, type and offset.
- **StructureCollapseUpdate**  [hand-checked] - `Code/GameEngine/Source/Common/Rva0024A797Grandchildren.cpp`
  - The contract for StructureCollapseUpdate (reverse/class_contracts/StructureCollapseUpdate.json) records retail vtable 0x852648 whose slot 0 is ??_GRva004A4214 (this stand-in's deleting dtor) and whose slots 3 and 4 are StructureCollapseUpdate::xfer and rva0004A429F, so the stand-in's dtor sits in the canonical class's own vtable. Its second vptr at +0x20 matches the contract's secondary table at offset 0x20, and the stand-in's Rva004A4214_E1 slot fe is bound to StructureCollapseUpdate::onDie, the single virtual of DieModuleInterface, which is canonical base 2.
- **Team** - `Code/GameEngine/Source/Common/TeamInQueue.cpp`
  - TeamInQueue declares m_team as Team * (Code/GameEngine/Source/GameLogic/AI/TeamInQueue.h line 76), and the destructor casts that pointer to Rva004F05F0Flags to touch m_active at +0x5D and m_created at +0x5E. The canonical Team in Code/GameEngine/Include/Common/TeamBFME2.h declares m_active at +0x5D (line 202) and m_created at +0x5E (line 203), and its setActive() writes the same pair in the same order as the stand-in destructor.
- **ThingTemplate** - `Code/GameEngine/Source/GameClient/DrawableRva0027B18C.cpp`
  - The stand-in BfmeDamageTemplate puts the EVA fields at the exact offsets the canonical ThingTemplate header names: m_evaEventDamagedOwner +0x580, m_evaEventDamagedFromShroudedSourceOwner +0x584, m_evaEventDamagedByFireOwner +0x588, m_evaEventSecondDamageFarFromFirstOwner +0x58C, range (float) at +0x590 as m_evaEventSecondDamageFarFromFirstScanRange, delay at +0x594 as the TimeoutMS, and event598 at +0x598 as m_evaEventAmbushed. The file's Drawable::rva0027B18C reads these in the damage-EVA path, and the flags it tests at +0x10E and +0x118 fall inside the canonical m_kindof[7] words at +0x108.
- **ThingTemplate** - `Code/GameEngine/Source/GameLogic/AI/PathfinderCellQueryPredicates.cpp`
  - The stand-in reads the template at Object+4 and then m_slopeLimitIndex at +0x56C and m_canPathThroughGates at +0x634. Canonical ThingTemplate.h declares those members at the same offsets (lines 203 and 277), and canonical code reads them the same way (PathfinderSameCellRva002EE49B.cpp:159 uses m_slopeLimitIndex as the max layer; Object_isAbleToAttack.cpp:389 tests m_canPathThroughGates). The ledger row for the functor ctor also says the template is read at +0x634/+0x56C.
- **TurretInfo** - `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DScriptedModelDrawTurretInfo.cpp`
  - Rva000BBE86Rec (W3DScriptedModelDrawTurretInfo.cpp:26-33) is a 0x18-byte element of the vector at ModelSMConditionInfo +0xD0, with int keys at +0x00 and +0x04, an 8-byte pad, and ints at +0x10 (turretAngleBone, written as the output of rva000BBDDF) and +0x14. Canonical TurretInfo (W3DModelDrawConditionParsers.cpp:30-38) has the same int keys at +0x00 and +0x04, two Real art values at +0x08 and +0x0C (the stand-in's pad), and int bones at +0x10 and +0x14. W3DScriptedModelDrawTurretNames.cpp uses the same +0xD0 vector with the same 0x18 element size.
- **W3DModelDrawModuleData** - `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawDistanceOpacity.cpp`
  - The stand-in reads floats at +0x144 (outer fade radius), +0x148 (inner fade radius), +0x14C (alpha at inner radius) and an int at +0x158 (m_staticSortLevelWhileFading). Canonical W3DModelDrawModuleData (Code/Libraries/Source/WWVegas/WWLib/W3DModelDrawModuleData.cpp:210-216) names the same fields at the same offsets with the same meanings.
- **WeaponTemplate** - `Code/GameEngine/Source/GameLogic/Object/Made002CC5E1Rva005084FC.cpp`
  - The stand-in Rva005086CETemplate is reached as descriptor->parameters, where the weapon is cast to Rva005084FCWeaponView and parameters sits at weapon+0x04. Weapon.h declares m_template at +0x04 (a WeaponTemplate pointer) and m_ownerID at +0x08, and the file reads sourceID08 at +0x08 as the source object. The stand-in's bool at +0x140 and uchar at +0x141 land on canonical WeaponTemplate m_field140 and m_field141 (bool and uchar) in the header. The chain Weapon+0x04 to WeaponTemplate+0x140/0x141 is the positive evidence; the canonical names there are unrecovered.

## High-confidence `different` (12): proposals to drop

The cheapest result in the pass. Each name was proposed for a stand-in it does not fit,
so the stand-in needs a name of its own and the collision need not be re-litigated:

- **AudioEventInfo** is not `Rva006AD590Info` in `Code/GameEngine/Source/Common/Audio/AudioManagerAdjustPriorityAndVolume.cpp`
  - The file never defines Rva006AD590Info; its only class is Rva006AD590Entry, an AsciiString-keyed _Rb_tree map entry (m_map at +0x1B8, size 0x1C4) with find(int) returning a union slot, and it touches no audio event fields. The canonical AudioEventInfo views (AudioEventInfoPriority.cpp m_priority at +0x44) describe a different object, so nothing in this file supports the proposed name.
- **AudioManager** is not `Rva006AD590Owner` in `Code/GameEngine/Source/Common/Audio/AudioManagerAdjustPriorityAndVolume.cpp`
  - The stand-in name Rva006AD590Owner does not appear anywhere in the file. The file declares Rva006AD590Entry, a find() over an AsciiString-keyed _Rb_tree at +0x1B8 with size 0x1C4, plus a union Rva006AD590Slot. Nothing in the file touches AudioManager, its vtable, or its slot layout, and the AudioManager contract's only field is __vfptr at +0.
- **DynamicGameLODInfo** is not `Rva00201E2BLODInfo` in `Code/GameEngine/Source/Common/Rva00201DC4LODDefaults.cpp`
  - The stand-in Rva00201E2BLODInfo (Rva00201DC4LODDefaults.cpp:40-52) has four 4-byte members (minimumFPS, particleSkipMask, debrisSkipMask, slowDeathScale), and the file's own compile-time check at line 68 asserts sizeof 0x10, which matches the retail native stride 0x10 for the five-entry dynamic LOD array (comment near line 110). The canonical DynamicGameLODInfo (reference/shims/gamelod/Common/GameLOD.h:131-141) has six members including two ParticlePriorityType enums, so it is 0x18 bytes assuming 4-byte enums. Stride and size both rule it out.
- **GameWindow** is not `BfmeSubDEC` in `Code/GameEngine/Source/Common/BfmeConv679GoDEC.cpp`
  - BfmeConv679GoDEC.cpp:9-25: the stand-in is returned by BfmeThingDEC::bfmeFindDEC() and read as m_color at +0x134, inside the BFME1 bfmeGoDEC body (file header comment). It is a DEC sub-object of a different class, not a window. The GameWindow contract (reverse/class_contracts/GameWindow.json, size 536) has no retail access at 0x134.
- **Keyframe** is not `Rva0055B39CPair` in `Code/GameEngine/Source/GameClient/System/FXParticleSystem/Rva0055B39C.cpp`
  - Rva0055B39CPair is {unsigned frame at +0, float value at +4}, used as m_pairs[i].frame and .value with stride 8. The canonical Keyboard-style Keyframe is declared value first, then frame: FXParticleSystem.cpp and Rva0055B32BCtor.cpp both have float m_value at +0 and unsigned m_frame at +4, and the reference shim ParticleSys.h lists value before frame. The stand-in reads frame where canonical Keyframe has its value, so the field order is inverted.
- **LANPlayer** is not `Rva00809C60Player` in `Code/GameEngine/Source/GameNetwork/Rva00803730FeslAttrs.cpp`
  - Rva00809C60Player (Rva00803730FeslAttrs.cpp:97-106) is an element of LanGame::m_players, with an int pid at +0x10 compared to a pid argument and an int gid at +0x14. Canonical LANPlayer (LANPlayerClass.h:46-52; contract size 28) has a LANPlayer* m_next at +0x10 and BfmeNetAddress m_address at +0x14, and no pid or gid. The stand-in's +0x10 is an int where canonical has a pointer, and its m_i[0x20] at +0x18 runs to 0x38, past canonical's 28-byte size.
- **ProjectileUpdateInterface** is not `BfmeHostGI` in `Code/GameEngine/Source/Common/BfmeTwoHundredOne.cpp`
  - The stand-in is a host reached by this-4 from BfmeSubGI with vtable slots 0-2 as spare placeholders, slot 3 as doGI(void*) and slot 4 as askGI(void*). The canonical ProjectileUpdateInterface (reference/shims/update_modules_bfme2/GameLogic/Module/UpdateModule.h:230-240, and the Made002CC7DE.cpp view) has projectileLaunchAtObjectOrPosition at slot 0 and no void* slot at 3. Equal name only; the vtable layouts disagree.
- **RbTreeNode** is not `BfmeNodeEBD` in `Code/GameEngine/Source/Common/BfmeConv802.cpp`
  - BfmeNodeEBD (BfmeConv802.cpp:37-41) has an unsigned color at +0x00 and parent/left/right pointers at +0x04/+0x08/+0x0C. The canonical RbTreeNode (Rva00226883TreeFree.cpp:25-30) has char m_pad[8] at +0x00 and sibling/child pointers at +0x08/+0x0C, with no color word and no parent link. The layouts disagree at the pointer offsets, so they are not the same node type.
- **RefPtr** is not `Rva005F4C8ERef` in `Code/GameEngine/Source/Common/Rva005F4C8EFactory.cpp`
  - The stand-in Rva005F4C8ERef is a class template over T that calls pointer->addRef() and holds T *m_p, and it is instantiated with GameEngine interfaces (Rva005E6ED6Third, Rva005E5590Iface, Rva005CDE89Iface). The canonical RefPtr (WWVegas/WW3D2 MeshMatDescUniqueArrays.cpp and Rva0015b110Cluster.cpp) is a non-template class holding RefCountClass *m_ptr with Add_Ref/AddRef/Release, a different type and refcount protocol.
- **SpecialPowerModuleInterface** is not `Rva002AD661AI` in `Code/GameEngine/Source/Common/RTS/PlayerAddScience.cpp`
  - PlayerAddScience.cpp:109-121 declares the stand-in with getScienceProvider at +0x18, grantScienceToObject at +0x1C, setIntSink at +0x20 and setFloatSink at +0x3C, used at lines 200-213 for science granting. Canonical SpecialPowerModuleInterface (Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h) has slot 6 (+0x18) as getPowerName() returning AsciiString and declares no science-grant methods.
- **State** is not `Rva004A9617Level` in `Code/GameEngine/Source/Common/GapBodiesS3C.cpp`
  - The stand-in Rva004A9617Level is an 8-byte record {int m_00; unsigned int m_level at +0x04} with no vptr, read only through Rva004A9617Holder::level() as m_level->m_level. The canonical State (Code/GameEngine/Include/Common/StateMachine.h line 27) is a Snapshot-derived class with a vtable and virtual onEnter/onExit/update, none of which this file uses or can express.
- **StateMachine** is not `Rva004A9617Holder` in `Code/GameEngine/Source/Common/GapBodiesS3C.cpp`
  - GapBodiesS3C.cpp:297-306: Rva004A9617Holder is a non-polymorphic struct with an int at +0x00 and a Level pointer at +0x04, read through Rva004A9617 (+0xE0) and Rva004A6A81 (+0x04), not through any StateMachine method. The canonical StateMachine (reverse/class_contracts/StateMachine.json, size 24) has a __vfptr at +0x00 and m_currentState (State*) at +0x04 and m_stateMap at +0x08, so an int at +0x00 and a scalar read at +0x04 of the pointee are incompatible with it.

## Recurring reasons a key could not be decided

- the stand-in is a partial view with no vfptr, so no vtable or RTTI tie is available;
- the file touches one offset at one width, which any number of classes would satisfy;
- the second hop is unproven: the owner's member is typed by inference, so the
  stand-in's identity rests on a pointer whose own type is a guess;
- the canonical side is itself unsettled - ObjectDrawInterface has nine conflicting
  views, and the TAiData contract is sized 72 with fields only to +68, so it cannot
  settle a comparison until it is completed;
- a shared callee address is ICF folding, not identity, and was refused as evidence.

## Related

The same pass found the class-key rule deciding Coord3D from a majority of our own
ledger names; that is fixed in 2b6d25c8174, with the rename still owed and recorded in
`docs/linking_obstacles/region3d-header-adoption-needs-a-class-keyed-coord3d-and-a-pod-region3d.md`.
