# DieModuleDerived.cpp shape handoff (blocked attempt, 2026-10-31)

Claim: class:DieModule. To reclaim: `python3 tools/claims.py claim class:DieModule`.

## What the file holds

`Code/GameEngine/Source/GameLogic/Object/Die/DieModuleDerived.cpp`: ten opaque
MI destructor pairs (e.g. ??1Rva0045CE6D 0x0045CE6D 25B plus its deleting dtor
0x0045CF7F), each tail-calling DieModule::~DieModule (0x0045CE54), plus ten
`/alternatename` hatches tying each class's `B2::f2` vtable slot to the family
class's rowed onDie:

- Rva0045CE6D  = InstantDeathBehavior onDie
- Rva004851FE  = RefundDie
- Rva00485425  = CreateCrateDie
- Rva0048593D  = CreateObjectDie
- Rva00486136  = CrushDie
- Rva004864AA  = DestroyDie
- Rva00486579  = FXListDie
- Rva004869FC  = SpecialPowerCompletionDie
- Rva00486B56  = UpgradeDie
- Rva004C227A  = HeroDie

(Ties are vtable-slot proven only; the file's owner-identity comment still
calls them unproven — treat as leads, not recovered names.)

## Why the canonical-header trial byte-FAILs

The TU-local fake `DieModule` is 12 B (vptr + 8 pad) with two empty stand-in
bases (`MiBase1` at +0x0C, per-class `B2` at +0x10), i.e. three vptrs. The
canonical DieModule is already 0x14 with vptrs at +0x00 (primary),
+0x0C (BehaviorModuleInterface) and +0x10 (DieModuleInterface) — the same
three restores. Hypothesis (proven for the DamageFilteredCreateObjectDieDtor
sibling): the stand-in bases are scaffold for the canonical subobjects, and
the natural form is, per class,

```cpp
#include "../../../../Include/GameLogic/Module/DieModule.h"

class <FactoryClass> : public DieModule
{
public:
	virtual ~<FactoryClass>();
};
```

with NO extra bases and NO need for the per-class B2 alternatenames (the
+0x10 DMI slot-0 override IS the class's onDie from its own OnDie TU).

## What broke the trial and what to do next

1. Dropping the two stand-in bases changed the class size 0x24 -> 0x14 and
   every emitted `??_7..` secondary view digest, so link_check refuses units
   whose table copies disagree with the census's first copy. Verify each
   family class's census-table first-copy: its OnDie TU (defines onDie = key
   function) and its ModuleNameGetters TU (defines getModuleNameKey). Make
   every emitting TU's class-copy declare the same virtual set
   (getModuleNameKey, ~dtor, onDie, xfer where recovered) so the digests
   agree. Model commits: DamageFilteredCreateObjectDieDtor.cpp
   (canonical + Rva00C4AA84Iface) and CreateObjectDie_onDie.cpp.
2. The census shows these family tables' slot-2 f2 -> their rowed onDie rows
   VIA the alternatenames; removing a hatch needs the real virtuals accepted
   into the emitted tables AND the hatch counters adjusted
   (`tools/hatch_counters.py --update`), never hand-edited.
3. Revert each unit to its linked fake-shape baseline before landing partial
   work; the ctor sibling (DamageFilteredCreateObjectDieCtor.cpp) is logged
   partial for its diverging `??_7..@@6BDieModule@@@` Byzantine vtordisp
   emission (re_attempts.log, t=95).
