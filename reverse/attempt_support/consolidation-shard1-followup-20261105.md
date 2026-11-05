# Mechanical consolidation shard 1 follow-up (2026-11-05)

Continued the allocated shard at RunOffMapBehavior and moved to later eligible
TUs after each blocked trial. No merge or split was applied; no claims were
taken. Each candidate passed `consolidation_queue.py --check-tu`. Scoped planner
snapshots were regenerated after the first RunOffMap scan reported stale inputs;
the refreshed snapshots passed `name_lane.py consolidate --check`.

## RunOffMapBehavior.cpp

`tu_skeleton.py --merge .../RunOffMapBehavior.cpp --dry-run` accepted no donors.
The constructor donor failed because its constructor signature is absent from
the class view; the slot donor's `getModuleNameKey` is undeclared. Required
class reconciliation is for `RunOffMapBehavior`.

Inspected all three mixed files with `--split` and `--split ... --for ... --dry-run`:

- `BehaviorModuleDataBuildFieldParse.cpp`, row `0x0046216A`: byte matched, but
  LinkGuard rejected the split because both census-linked objects would stop
  linking and it introduced duplicate AimWeaponBehaviorModuleData providers.
- `ConstIntGetters4.cpp`, row `0x004621AC`: byte matched, but LinkGuard rejected
  the moved `RunOffMapBehavior` string COMDAT without matching private/weak-free
  context.
- `Rva0049B47CThreeVptrDerived.cpp`: no row is approved for this TU.

## Later allocated candidates

- `BloodthirstyUpdate.cpp`: constructor donor failed on a vtable declaration;
  module-data constructor failed on an undeclared compiler-generated member;
  destructor donor failed LinkGuard with unresolved `UpdateModule::crc` and
  `BloodthirstyUpdateIface` methods; module-data destructor had a byte mismatch.
  Mixed `ModuleDataBuildFieldParse.cpp` row `0x0044E099` byte matched but failed
  compilation because `BloodthirstyUpdateModuleData::m_filter` is undeclared.
- `SupplyWarehouseCripplingBehavior.cpp`: constructor donor failed because its
  signature is absent from the class view. Mixed field-parse row `0x00483A7A`
  byte matched but failed compilation on an undeclared compiler-generated
  `SupplyWarehouseCripplingBehaviorModuleData` constructor.
- `AutoFindHealingUpdate.cpp`: constructor donor failed because its signature
  is absent from the class view. Mixed field-parse row `0x00495128` byte matched
  but failed compilation on an undeclared compiler-generated
  `AutoFindHealingUpdateModuleData` constructor.
- `AptAnimData.cpp`: donor failed compilation because `map` is undeclared in the
  combined TU.
- `AiOrdersManager.cpp`: patrol donor failed compilation on an incomplete
  `Rva0054840A::ObjectID` declaration cycle.

These are code/header declaration prerequisites outside the mechanical lane.
Do not retry unchanged dry runs or repair declarations here. Later allocated
TUs remain available; the shard is not exhausted.
