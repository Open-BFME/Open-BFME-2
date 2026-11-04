# Horde model module-data view reconciliation, 2026-11-04

Starting revision: bbe99a9103. Scope: the existing manager TU and
W3DHordeModelDrawModuleDataCtor.cpp, claimed by yasinschroeder-codex.

The initial consolidation dry run accepted no donor. The constructor trial
failed because the kept module-data declaration appeared after HordeGroupNode,
and the destination represented its base as padding. Reconciled these two
private views using the constructor's existing base declaration and the
manager's existing HordeLodEntry array. No class or field identity is newly
inferred: the existing target ctor stores and getters establish the same
0x188 base extent, three 0x14 records, and total size 0x1C4.

Compiler layouts agree in both sources: W3DModelDrawModuleData at offset zero,
size 0x188; m_lods at 0x188, size 0x3C; derived size 0x1C4. The original
constructor vtable binding and all destination aliases remain unchanged.

Verification: ./build.sh on both sources passes 72/72 function checks, both
data rows, string/float/import checks, and three parent-generated EH funclets.
find_declared_unmatched.py reports every defined function matched;
link_check.py --new-variants passes for both objects; git diff --check passes.
No row, pin, hatch or protected debt key is removed. The naming planner's
current Common report retains provisional placement and mixed-row blockers;
it does not independently prove a retail path.

Next: regenerate the planner after the view edit and retry tu_skeleton's
normal merge/link guard. Other donors retain STL/container view, placement-new,
byte-shape and allocator-provider prerequisites. The manager's two private
container views at +0xC disagree (list<string> versus list<vector<unsigned>>);
that conflict is deliberately unresolved here.
