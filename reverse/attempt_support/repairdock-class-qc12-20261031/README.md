# RepairDockUpdate decisions, qc-12
Base f48d8a67ae; queue5324; no source edit or adoption.
All eight queued attributes are resolved as follows from native evidence:
- inherited@0 and field@0: primary vfptrC51C80, not an ordinary data pointer.
- inherited@20 and field@20: secondary DockUpdateInterface vfptrC51C30.
Constructor4A118B calls58A290, then installs these and C51B20@C/C51D68@10.
- inherited@8: owner Object pointer. Native action4A12B6 is entered on this+20
and reads the owner from this-18; the full object's offset is8.
- name@4: module data, not m_owner. Native action accesses this-1C and then
uses data+10 for the full-heal duration. That distinguishes it from owner8.
- name@88: last repaired docker ObjectID; native action compares Object ID
against this+68 (full88), updates it for a new docker and clears it when full.
- name@8C: per-frame heal float; native ctor MOVSS zeroes full8C and action
uses this+6C in healing arithmetic. Existing m_lastRepair and
m_healthToAddPerFrame are appropriate structural names; no original target
member name is recovered merely from the donor's same-name fields.
Native factory-supported size90 and own fields88/8C retain the complete extent.

Real blocker: class:DockUpdate, which is not in canonical_classes.csv on this
base. Its native constructor58A290 (384bytes, attached) constructs the module
hierarchy and container members. It needs a canonical full layout and inherited
virtual provider closure before the derived header can be shared. Existing
RepairDockUpdateBehaviorCtor.cpp substitutes TU-local dummy addresses for four
vfptrs, while the action has only a 13-slot DockUpdateInterface prefix. Neither
is an honest complete base to promote. Coordinator's module-root/getter closure
boundary is honored; no root adoption or base default substitution attempted.
The action's secondary slot12 is at C51C30+30; byte matching its body alone
would not verify the other primary/behavior/update/dock slots.

ZH supplies the official header destination GameLogic/Module/RepairDockUpdate.h
and semantic donor leads only; native facts above come from the image. Both
served files are unchanged. No hatch, ledger or tool edits; zero adoption/byte/
link gain. Shared linking obstacle register is held elsewhere; this is its
proposed handoff entry.
