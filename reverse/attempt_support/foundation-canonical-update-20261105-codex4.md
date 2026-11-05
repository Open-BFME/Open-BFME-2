# FoundationAIUpdate canonical UpdateModule prerequisite

Inspected base: `0eb531811c` (2026-11-05). Scope: the approved
`Code/GameEngine/Source/GameLogic/Object/Update/FoundationAIUpdate.cpp` TU and
its three eligible donors. No source paths or function-ledger owners changed.

## Repair

`FoundationAIUpdateCtor.cpp` now includes the canonical UpdateModule header
instead of declaring a nonpolymorphic private copy. The constructor still
installs its existing retail-proven folded vtable providers at +0, +0x0C and
+0x10; the lvalues now address the canonical base slots directly. No alias,
pin, provider or escape hatch was added or removed.

The normal builder verified both original-source control and final source:
2/2 rows, constructor `0x004551B3` (107 bytes) and handler `0x00789EDC`
(10 bytes). `find_declared_unmatched.py` reports all definitions matched.
`header_adopt_lane.py accept --class UpdateModule` passed and retired exactly
one queue row through its owning workflow. No other debt register changed.

## Object and link checks

Original and final objects were produced only through `./build.sh`. Comparing
`class_cleanup.runtime_graph` snapshots finds five non-debug sections and one
external definition in each object. All section bytes, external definitions,
COMDAT policies and weak bindings agree. The only graph difference is the
REL32 target at offset 4 in `.text$x`:

- original: `??1UpdateModule@@QAE@XZ` (private nonvirtual view, unresolved);
- final: `??1UpdateModule@@UAE@XZ` (canonical virtual destructor).

The latter has the existing 25-byte matched owner at `0x0024A797` in
`Code/GameEngine/Source/Common/Rva0024A797DeletingDtor.cpp`. The updated
constructor's full EH graph is EXACT (`eh_verify.py`, one EH parent).
Ordinary `link_check.py FoundationAIUpdateCtor.cpp` reports LINKS and preserves
117 -> 117 bytes against census `c95fcfcfcd`, 2026-11-05 05:17. This is a
preview preservation result, not a new census or whole-game link claim.

## Consolidation boundary and next step

`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/`
produced a current planner snapshot with no missing inputs. The initial
`tu_skeleton.py --merge .../FoundationAIUpdate.cpp --dry-run` accepted no donors:
Xfer failed on an undefined UpdateModule base, Ctor on UpdateSleepTime ordering,
and Construct on missing Thing/ObjectID declarations in composed text.
The initial view plan additionally identifies:

- FoundationAIUpdate base clauses differ: the main/Construct views use
  UpdateModule plus Rva00C1A690Iface; Xfer uses FoundationTrailing; Ctor uses
  only UpdateModule with a stored trailing vptr.
- Rva00C1A690Iface slot 3 is named slot3 in the main view and gap3 in Construct.
- BfmeItemE63 is struct in the main source and class in Construct.
- Main/Construct retain canonical-header adoption prerequisites and Object
  member/layout dependencies. A proposed superset is evidence, not acceptance.

Only the constructor prerequisite above was changed and verified. The other
three sources are untouched. Reconcile those views in separately verified
changes before another merge attempt; never hand-merge rejected donors.

Generated cleanup `uw_00789ed4` remains in `Code/gen_small/uw_gen_011.cpp`.
The current TU map approves `0x00789ED4` for FoundationAIUpdate.cpp via the
constructor's retail FuncInfo at `0x00938408`. The constructor object emits
its cleanup as `$L820`, and the canonical destructor repairs its old callee
wall, but the split constructor source is not the approved destination TU.
Do not repoint the row to that split source. Merge the parent into the approved
TU first, then resolve the final compiler label from the exact parent EH graph.
No generated source was edited and no overlapping ownership was introduced.
