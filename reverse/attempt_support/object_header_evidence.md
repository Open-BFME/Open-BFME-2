# Object canonical header: evidence (draft, 2026-10-30)

Header: `Code/GameEngine/Source/GameLogic/Object/object.h` (BFME 1's path,
`game/GameEngine/Source/GameLogic/Object/object.h`). Not registered in
`reverse/canonical_classes.csv`: 335 of the 673 queued TUs have a donor with a
private Object view, and class_gate would refuse those merges. Units adopt it
one by one through `tools/header_adopt_lane.py adopt`, which never registers.

`tools/class_contract.py --class Object` decides by majority and says bases
`[]`, sizeof 604. Those are the private views' habits, not retail's; this
header does not use that contract.

## Target facts (retail bytes and the ledger)

- `??0Object@@QAE@PBVThingTemplate@@PBUCreateMask@@PAVTeam@@W4ObjectID@@@Z`,
  0x00298EA9, 3,525 bytes, matched (`ObjectConstructor.cpp`). `RET 0x14`: four
  arguments plus the hidden most-derived flag, so Object has a virtual base.
  It constructs Thing at +0 and every own member from +0x74 to +0x4CC. The
  member sizes come from the sub-object constructors it calls (GeometryInfo
  0x5C at +0xA8, WeaponSet 0x40 at +0x330 followed by a separate
  `bitset<128>` at +0x370, the 0x18-byte member at +0x468 followed by scalars
  at +0x480..+0x490).
- `??1Object@@MAE@XZ`, 0x00299CE4, matched (`ObjectDestructor.cpp`). Installs
  0x00BFC300 at +0x00, 0x00BFC2F0 at +0x60, 0x00BFC2D8 at +0x64, 0x00BFC2B8 at
  +0x6C, 0x00BFC290 at +0x70; the virtual base's 0x00BFC27C through the vbptr at
  +0x68 with a vtordisp at vbase-4; resets Snapshot's 0x00BBB554 at +0x60 and
  calls ~Thing 0x0030A120. Protected virtual (`MAE`).
- Layout engine (`tools/retail_layout.py`, commit e1cef4cdb7, bundle
  `build/fleet/inbox/layout-engine/`; report `build/fleet/layouts/REPORT.md`,
  `retail_layouts.json`), from retail bytes only: bases Thing@0
  (retail-ctor-call), Snapshot@0x60 (inlined base vptr), BfmeCtor001B3A20@0x64
  (retail-ctor-call to `??0BfmeCtor001B3A20@@QAE@XZ` 0x0028AADF; vbtable pointer
  at +0x68, table 0x7FC320), Rva005EEE6B@0x6C and Rva0028AB0D@0x70 (inlined base
  vptrs; their matched 9-byte constructors 0x005EEE6B / 0x0028AB0D store the
  same tables); one virtual base at +0x4D4 (vftable 0x7FC27C) via the +0x64
  vbptr. **sizeof 0x4D8**: `push 0x4D8; call operator new` at 0x0023CAF2 (call
  at 0x0023CB19) precedes the constructor call; the constructor's writes reach
  0x4D8. 0x4D0 is where the non-virtual part ends (own data +0x74..+0x4CC, the
  vtordisp at +0x4D0).
- Overriders named by the ledger: `?rva00290EE0@Object@@UAE?AVAsciiString@@XZ`
  (+0x64 slot 0), `?rva0028C037@...` / `?rva0028C08D@...` (+0x70 slots 0-1),
  `?getGeometryInfo@Object@@UBEABVGeometryInfo@@XZ` (+0x6C slot 0, gen-alias
  0x005FBE57), `?slot@Object@@UBEPAXXZ` (0x00299C99, the virtual base),
  `?loadPostProcess@Object@@UAEXXZ`, `?GetSnapshotName@Object@@UBEPBDXZ`,
  `?xfer@Object@@MAEXPAVXfer@@@Z` (Snapshot),
  `?reactToTransformChange@Object@@MAEXPBVMatrix3D@@PBUCoord3D@@M@Z` (Thing slot 5).
- Accessor mangling from the ledger: `getID` `QBE`, `getTeam` `QAE` (an
  out-of-line 7-byte copy at 0x0043A09D; consumers inline it),
  `getControllingPlayer` `QBE`, `testStatus` `QBE_NW4ObjectStatusTypes`,
  `setStatus` `QAEXW4ObjectStatusTypes@@_N`, `isEffectivelyDead` `QBE_N`,
  `getRelationship`, `getAbleToAttackSpecificObject`, `rva0028AF76` `QBEH`,
  `rva0028C197` `QBEPAX`.
- The header compiles to sizeof 0x4D8 with bases at +0/+0x60/+0x64/+0x6C/+0x70,
  the virtual base at +0x4D4 and every field at its commented offset (CodeView
  read on boat, class_layouts), agreeing with the layout engine.

### Layout-engine facts checked against retail bytes (2026-10-30)

The engine can read a member subobject's vptr store as a base and take sizeof
from an allocation a derived constructor owns, so its Object facts were checked
by hand in game.dat (capstone disassembly):

- **Bases at +0x6C and +0x70: verified bases.** In 0x00298EA9 the order is:
  vbtable 0x00BFC320 at +0x68 and the virtual base's vptr 0x00C078DC at +0x4D4
  (only under the most-derived flag), `call ??0Thing` (0x0030A188), Snapshot's
  vptr 0x00BBB554 at +0x60, `call ??0BfmeCtor001B3A20` (0x0028AADF, flag 0) on
  +0x64, then 0x00BFBC9C at +0x6C and 0x00BFBCBC at +0x70 (0x00298EF8,
  0x00298EFF): the tables `??0Rva005EEE6B` and `??0Rva0028AB0D` store. Only
  after these does Object install its own tables (0x00298F09..0x00298F2D:
  0x00BFC300 +0x00, 0x00BFC2F0 +0x60, 0x00BFC2D8 +0x64, 0x00BFC2B8 +0x6C,
  0x00BFC290 +0x70, 0x00BFC27C into the virtual base). Both stores fall in the
  base-construction phase, and Object then overwrites both slots with its own
  override tables, which a member subobject never receives. Member construction
  starts after that (0x00298F79 onward).
- **Virtual base at +0x4D4: verified.** Besides the direct store, the vbtable
  entry read through +0x68 gives 0x46C (`lea ecx,[eax-0x46C]` for the
  vtordisp), and 0x68 + 0x46C = 0x4D4.
- **sizeof 0x4D8: verified as the complete object.** At 0x0023CAF2 `push 0x4D8;
  call operator new` (0x0042FDA0); the result goes to ecx, then `push 1` (the
  most-derived flag) and the four arguments, and `call 0x00298EA9` at
  0x0023CB19. No derived constructor intervenes: 0x00298EA9 is the
  complete-object constructor the allocation flows into.

## Donor facts (Zero Hour, BFME 1)

- Zero Hour `Object.h`: names `m_id`, `m_producerID`, `m_builderID`,
  `m_drawable`, `m_name`, `m_status`, `m_geometryInfo`, `m_group`,
  `m_visionRange`, `m_shroudClearingRange`, `m_shroudRange`, `m_disabledMask`,
  `m_disabledTillFrame`, `m_firingTracker`, `m_behaviors`, `m_contain`,
  `m_body`, `m_ai`, `m_physics`, `m_radarData`, `m_experienceTracker`,
  `m_containedBy`, `m_xferContainedByID`, `m_containedByFrame`,
  `m_constructionPercent`, `m_team`, `m_originalTeamName`, `m_indicatorColor`,
  `m_healthBoxOffset`, `m_weaponSet`, `m_partitionData`, `m_privateStatus`;
  inline `getID`, `getContain`, `getBodyModule`, `getAIUpdateInterface` (const
  and non-const), `getContainedBy`, `isEffectivelyDead`
  (`m_privateStatus & EFFECTIVELY_DEAD`, bit 0). The constructor and
  destructor took these names where their statements match Zero Hour's.
- BFME 1 `ObjectDestructor.cpp` (0x001D4010): same base shape and statement
  order as BFME 2's destructor.

## Inferences (not proven)

- The bases past Thing and Snapshot have no recovered names. They take the
  placeholder names of their matched constructors, as the layout engine reports
  them (`BfmeCtor001B3A20`, `Rva005EEE6B`, `Rva0028AB0D`). The +0x64 base keeps
  its matched constructor's shape (a first base, then the virtual base); the
  engine reports the virtual base unnamed, so it keeps that source's placeholder
  `BfmeCtorVirtualBase001B3A20`. This settles the constructor/destructor
  disagreement in favour of the constructor's spelling. The slot declarations of
  the bases are Object's overriders from the ledger; the private views in
  `RvaSmallVtableCtors.cpp` and `BfmeCtor001B3A20.cpp` declare other slots there
  (a virtual destructor, `slot()`), which is open.
- +0x438 is `m_privateStatus` (unsigned char): `AITNGuardHasAttackedMeCondition`'s
  view tests its bit 0 as `isEffectivelyDead`, which is Zero Hour's body. The
  constructor's view had it inside a run of bools.
- Members whose class has no canonical header usable from every unit
  (AsciiString under its several include setups, GeometryInfo, WeaponSet,
  BitFlags, the STLport containers) are opaque storage of the constructor's
  size and alignment, with the type in a comment. Their offsets and sizes are
  target facts; their spelling here is not retail's.
- Remaining fields keep offset names (`m_80`, `m_1a4`, ...).

## Open questions

- `getGeometryInfo`: the ledger has it as the +0x6C base's virtual overrider,
  while consumer views (WorkerAIUpdateCtor, W3DRadar*) inline Zero Hour's
  non-virtual `return m_geometryInfo`. One of the two spellings is wrong.
- Thing slot 6 (`vslot6`): Object's overrider 0x0028B193 is rowed as the
  non-virtual `?rva0028B193@Object@@QAEXXZ`; the header does not declare the
  override.
- `?PartitionGetPlayerIndex@Object@@UBEHXZ` (0x0028E7F8) is a virtual of an
  undetermined base; not declared.
- The constructor and destructor TUs cannot adopt this header until the opaque
  members get their real types.

## Fresh-master adoption pass (2026-10-31)

Rebased the draft header onto origin/master 63a3af3ab6. Retail RVA 0x0049212B (78-byte matched PickupStuffUpdate::update, now in Code/GameEngine/Source/Common/PickupStuffUpdate.cpp) loads its Object pointer then `cmp dword ptr [ecx+0x258],0` at RVA 0x00492131. The matched source spells this as `obj->getAI()` with inline `AIUpdateInterface *getAI() const { return m_ai; }`. The canonical draft already places m_ai at +0x258. Added that accessor without a new data member or virtual slot.

`class_contract.py --class Object --sample 40 --jobs 8` reports class from bytes, sizeof 1240 (0x4D8) from retail-new, and Thing, Snapshot, BfmeCtor001B3A20, Rva005EEE6B, Rva0028AB0D plus the virtual base from retail-ctor; 40 views, zero uncompiled. The tool retains unresolved names for the three placeholder bases and virtual base, and a name tie at +0: these are not new name proofs. The draft retains five direct bases and its virtual base at +0x4D4. Object remains unregistered.
