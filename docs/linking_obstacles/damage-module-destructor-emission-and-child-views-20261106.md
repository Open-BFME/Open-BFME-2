# DamageModule destructor emission and child views

Status: Blocked on a genuine deleting-destructor emitter and complete child views.
Updated: 2026-11-06. Inspected base:6d19e6b1f0.

EvacuateDamageCtorModuleFactoryBody.cpp passes9/9 matched bodies but remains
unlinked: its implicit DamageModule destructor is not retail's and references
PB_DeepBase::~PB_DeepBase. The INIMacroTable destructor identity has already
been corrected; the remaining parent/child lifetime work is independent of it.

The supported ReflectDamage child fold now identifies native4BAB36/4BABDE from
the table also installed by constructor4BABB4. Both sources retain7/7 rows.
[Identity evidence](../../reverse/attempt_support/reflect-damage-identity-20261106/README.md).
This removes one naming prerequisite for adopting the real callback surface,
while the private parent/interface projections and old aliases remain debt.
