# ObjectCreationList declaration reconciliation

Inspected revision: `868eff29fe`; worker: `yasinschroeder-codex`.

The default picker selected consolidation into
`Code/GameEngine/Source/GameLogic/Object/ObjectCreationList.cpp`. The supported
planner was run under `Code/GameEngine/Source/GameLogic/Object/`; its report
identified declaration, include, compiler-context and routing prerequisites.
These are investigation leads, not approval to move mixed sources.

`tu_views.py` reconciled the two private `ObjectCreationList` declarations in
`GenericObjectCreationNuggetCanCreate.cpp` and `ObjectCreationNuggetParse.cpp`.
The resulting view retains both existing methods, with their original types;
it adds no field, method implementation, pin or alias. The forward declaration
of `ObjectCreationNugget` supplies the parser's existing parameter type.

Verification:

- `./build.sh` on both changed files: 8/8 rows match; three data rows and the
  string-reference check pass. Two compiler-renumbered funclet labels resolve
  through their existing parent EH data.
- `find_declared_unmatched.py` on both files: all definitions already matched.
- `link_check.py` on both files: 2/2 LINKS; 719 + 241 authored bytes preserved.
  The preview uses census/index `c95fcfcfcd`, 2026-11-05 05:17. This is no new
  census, linking gain or source-file reduction.

The class-view report still refuses the broader family: constructor import
attributes differ for `ObjectCreationNugget`; `AttackNugget` has differing
`novtable` declarations; `GenericObjectCreationNugget` has incompatible base
clauses; `Object` has incompatible field partitions at +0x38; and the store's
views overlap at +0xC. `FireWeaponNugget` and `ApplyRandomForceNugget` also have
different inline-constructor spellings. These require separate, byte-verified
prerequisite repairs. No incompatible class was forced into a shared view.

No source paths move in this prerequisite change; protected debt registers,
header queues and historical native-vector evidence remain with their owners.

## Completed merge comparison

The applying `tu_views.py` run completed its normal pre/post
`tu_skeleton.py --merge ... --dry-run` comparisons: **0 accepted donors before,
0 after**. No source file was absorbed. The independent direct dry run queued
after this completed comparison was cancelled as redundant; it supplies no
verification verdict.

Representative remaining compile refusals:

- `AttackNuggetCreate.cpp`: NameKeyGenerator must precede the short Subsystem
  view; `GenericObjectCreationNuggetCanCreate.cpp`: ThingFactory must precede
  that view.
- `AttackNuggetDtor.cpp`: ObjectCreationNugget vftable type-modifier conflict.
- Generic nugget constructor, positional-create and really-create donors:
  the composed declarations use GenericObjectCreationNugget before its
  declaration; waypoint donor lacks its `rva001F21E8` method.
- Store destructor donor: the retained store class lacks `m_vec24`.
- Vector-copy donor: explicit-specialization conflict for STLport `__copy_aux`.

The seed also receives a link-guard refusal for not defining
`?Rva0076B063ClearFlag@@YAIXZ`, which the older index still references. Current
ledger row `$L2093` at 0x0076B063 belongs to AttackNuggetCreate.cpp's native EH
graph and explicitly replaces that standalone clearer. This is a stale-index
prerequisite, not evidence that this declaration-only change lost a provider.
Use a published index incorporating that native-funclet repair before judging
the seed's provider loss; keep the normal guard enabled. The separate compile
prerequisites still need repairs even after that index refresh.
