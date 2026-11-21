# ReflectDamage vtable bridge (0x008597F8 and siblings) — handoff

Target facts (retail): primary table 0x00C59CBC, BehaviorModuleInterface table
0x00C597F8, DamageModuleInterface table 0x00C59CB0; constructor 0x004BABB4
(Common/ReflectDamage.cpp), destructor 0x004BAB36 (Common/Rva004B96CCDerived.cpp).
Primary slots: 1 = 0x00497805 (ICF fold, loadPostProcess), 2 = 0x004BAB4F
(GetSnapshotName), 3 = 0x0045CE8C (ICF fold, xfer), 4 = 0x004BAB55 (rowed
getModuleNameKey). +0x10 table: onDamage 0x004BABFA (rowed), 0x0047A69C, 0x000D1407.

Done (landed): canonical header `Code/GameEngine/Include/GameLogic/Module/ReflectDamage.h`
registered, contract `reverse/class_contracts/ReflectDamage.json`; the factory,
friend_new, onDamage and getModuleNameKey units adopt it.

Remaining: `owner-and-dtor-units.patch` adopts the header in the two units that emit
the vtables and adds the folded loadPostProcess/xfer/onHealing/onBodyDamageStateChange
bodies (all 325 rows still byte-matched with it). It then needs:

1. Slot 2 named: 0x004BAB4F is rowed `?name@Rva004BAB4FNamed@@QBEPBDXZ`
   (ModuleNameGetters3.cpp). `rename.py function --to-class ReflectDamage --new
   '?GetSnapshotName@ReflectDamage@@MBEPBDXZ'` refuses without a name_lane approval
   for slot key `Code/GameEngine/Include/GameLogic/Module/ReflectDamage.h|slot|ReflectDamage@0x00C59CBC|2`
   (`--approval-base REV`); the within-class `?name@C` shortcut and `class --fold`
   (no ctor/dtor row under the placeholder) do not apply. Once approved, prepare
   ModuleNameGetters3.cpp line 130 as `BFME_SNAPSHOT_NAME_GETTER(ReflectDamage, "ReflectDamage")`.
2. ICF rows (add_match `--icf-owner`, BoneFXDamage's rows as precedent) for
   `?loadPostProcess@ReflectDamage@@MAEXXZ` 0x00497805, `?xfer@ReflectDamage@@MAEXPAVXfer@@@Z`
   0x0045CE8C, `?onHealing@ReflectDamage@@UAEXPAVDamageInfo@@@Z` 0x0047A69C,
   `?onBodyDamageStateChange@ReflectDamage@@UAEXPBVDamageInfo@@W4BodyDamageType@@1@Z` 0x000D1407.

Note: a unit that includes object.h must `#define BFME_SNAPSHOT_NAME_SLOT` first, or
the Snapshot shim spells slot 2 `crc` (fixed in ReflectDamageOnDamage.cpp, 601a257fec).
