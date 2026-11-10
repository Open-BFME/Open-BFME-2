// cl: /MD
// ??_GSpellRechargeModifierUpgradeModuleData@@UAEPAXI@Z @0x004B606E 28B
// Deleting dtor slot 0 of vtable 0x008583E0; calls rowed ??1SpellRechargeModifierUpgradeModuleData@@UAE@XZ at 0x004B608A then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

// GeometryUpgradeModuleData derives from Rva00253487Base as GeometryUpgradeModuleDataCtor.cpp declares
// it, so this unit's copy of its 31-slot vftable (retail 0x00C589F0) equals that unit's copy instead
// of a one-slot one that link order would keep.
#include "../../Include/GameLogic/Module/Rva00253487Base.h"

class SpellRechargeModifierUpgradeModuleData : public Rva00253487Base { public: SpellRechargeModifierUpgradeModuleData(EmitVtableTag *); virtual ~SpellRechargeModifierUpgradeModuleData(); };
// ?<SpellRechargeModifierUpgradeModuleData::SpellRechargeModifierUpgradeModuleData> absent-from-retail
SpellRechargeModifierUpgradeModuleData::SpellRechargeModifierUpgradeModuleData(EmitVtableTag *) {}
// ??_GGeometryUpgradeModuleData@@UAEPAXI@Z @0x004B6F65 28B
// Deleting dtor slot 0 of vtable 0x008589F0; calls rowed ??1GeometryUpgradeModuleData@@UAE@XZ at 0x004B6F81 then rowed operator delete at 0x0002FD60.
class GeometryUpgradeModuleData : public Rva00253487Base { public: GeometryUpgradeModuleData(EmitVtableTag *); virtual ~GeometryUpgradeModuleData(); };
// ?<GeometryUpgradeModuleData::GeometryUpgradeModuleData> absent-from-retail
GeometryUpgradeModuleData::GeometryUpgradeModuleData(EmitVtableTag *) {}
