// cl: /MD
// Each class redeclares its public virtual destructor and defines it locally,
// which emits the scalar deleting destructor in this TU; the dtor call inside
// resolves through that destructor's own row (same pattern as spec_gdtor).

#include "../../Include/GameLogic/Module/DestroyDieModuleData.h"

struct EmitVtableTag;

// ??_GCreateObjectDieModuleData@@UAEPAXI@Z @0x485e50
class CreateObjectDieModuleData : public DestroyDieModuleData { public: CreateObjectDieModuleData(EmitVtableTag *); virtual ~CreateObjectDieModuleData(); };
// ?<CreateObjectDieModuleData::CreateObjectDieModuleData> absent-from-retail
CreateObjectDieModuleData::CreateObjectDieModuleData(EmitVtableTag *) {}

// ??_GCreateObjectDieIfEldestKindofModuleData@@UAEPAXI@Z @0x485e6c
class CreateObjectDieIfEldestKindofModuleData : public CreateObjectDieModuleData { public: CreateObjectDieIfEldestKindofModuleData(EmitVtableTag *); virtual ~CreateObjectDieIfEldestKindofModuleData(); };
// ?<CreateObjectDieIfEldestKindofModuleData::CreateObjectDieIfEldestKindofModuleData> absent-from-retail
inline CreateObjectDieIfEldestKindofModuleData::CreateObjectDieIfEldestKindofModuleData(EmitVtableTag *tag) : CreateObjectDieModuleData(tag) {}
// ?_bfmeCreateObjectDieIfEldestKindofModuleDataAnchor@@YAXPAVCreateObjectDieIfEldestKindofModuleData@@@Z absent-from-retail
void _bfmeCreateObjectDieIfEldestKindofModuleDataAnchor(CreateObjectDieIfEldestKindofModuleData *p) { p->CreateObjectDieIfEldestKindofModuleData::CreateObjectDieIfEldestKindofModuleData(0); }
