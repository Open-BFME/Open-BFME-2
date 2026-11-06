# Assisted builder / constructor-funclet owner audit

Audit scope: pending working-tree batch after parent-supplied base
`ef649c78a7`, limited to these two row-owner changes. No source is deleted.

| Body | Old source | Destination | Observed status |
|---|---|---|---|
| buildFieldParse, RVA 0x486E7C/17 | ModuleDataBuildFieldParse.cpp | AssistedTargetingUpdate.cpp | Applied |
| ctor cleanup, RVA 0x78C15D/8 | Code/gen_small/uw_gen_011.cpp | AssistedTargetingUpdate.cpp | Applied: $L6272 |

All three sources remain. Final inspection confirms the mixed builder source
has 80 matched rows, uw_gen_011 has 201 and the destination has 16. functions.csv
now owns 0x78C15D/8 as `$L6272` in the destination, notes
`gen-funclet;parent=??0AssistedTargetingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z`.
The old generated ledger row is gone; its generator source remains untouched.

**No active hardcoded consumer or stale protected target key was found for
either applied row-owner change. No tooling change is indicated.** The parent
reports the final constructor's unmasked 84-byte body and EH graph exact, with
current label `$L6272` and the full eight-byte cleanup's sole +4 REL32 resolving
to the existing UpdateModule destructor. This final audit adds no new build.

## Searched scope

Case-insensitive literal searches covered the exact builder decorated name,
`486E7C`, `78C15D` and `uw_0078c15d` across active tools/, .githooks/,
.github/, Code/ includes/source/config content, reverse/ ledgers/registers/
queues, docs/ and remaining root build/config/source registries. Generic old
source references and doxygen configuration were checked separately. Owned
reference/shims were searched for target-specific bindings. Broad searches
excluded build scratch/worktrees, .git/ and vendor/external reference inputs.
Large ledgers were narrowly filtered/streamed, never loaded wholesale.

## Applied builder and data ownership

functions.csv and tu_map.csv name the destination for 0x486E7C, with approved
Z/S/N TU evidence. Only the destination defines this registration body. The
FieldParse[5] owner at RVA 0x84AFE8/80 also names the destination in data_rows;
the residual source retains only an external declaration of the real table.
The factory's callback reference is symbolic and remains valid.

No affected identity/header/MS-header/data-check/gate/hatch/unclaimed key names
the moved body/RVA under the old source. Generic keys for the residual source
remain valid and must not be retired just because one row moved.

The inferred table's completed name_data_requests/name_basis/name_agreed owner
paths moved to the destination. The original user-source hash and line in the
request are preserved historical admission evidence; the record has an agreed
and a landed data admission, and is not a current code/provider binding. Do
not refresh those immutable original caller facts by hand.

## Applied generated funclet

The supported add_match admission now records the actual final label `$L6272`
and destination parent. No active tool/config/registry hardcodes the old uw
symbol or this RVA to uw_gen_011.cpp. No protected key retains the old target.
tu_map's approved Assisted assignment via constructor 0x486E8D / FuncInfo
0x93B754 remains correct; its source cell still names the former generated
owner, a stale generated projection. Let owning tools rebuild that map in
memory from current inputs; do not hand-edit or commit a regenerated map from
this lane. The current functions.csv row is the observed source ownership.

The generator reads its source files generically and recognizes scaffolds by
the row's complete generator shape. A recovered real-parent row no longer
qualifies as generated scaffolding. uw_gen_011.cpp and its remaining rows stay;
leave its uncredited orphaned harness body untouched. No source deletion,
generic source-list removal or generated-source edit follows from the repoint.

No fold-proof token names uw_gen_011.cpp or depends on the moved builder
remaining in ModuleDataBuildFieldParse.cpp. Existing generic consumers of both
old files remain valid.

## Intentional references and final handoff

fieldparse_tables.tsv records native tokens/callback RVAs without a source
binding. Factory comments, re_attempts records, immutable native/proof JSON,
old generated-label history and destination tu-skeleton provenance are retained
as evidence. The destination still has the old `not merged yet` placeholder
comment for uw_0078c15d; this is stale generated commentary, not a code/provider
binding. The banked pre-admission move audit under attempt_support is historical
and intentionally retains its then-pending status. Census snapshots remain
measurement-owned. None is a broken path consumer. No raw EA path string
requires rewriting.

Final ownership and counts have been observed after admission. Parent retains
the ordinary final byte/EH/link/ledger checks and separate native-cleanup commit;
the supported builder split is already committed as 577b865365. This audit does
not claim publication of the cleanup before the parent's push.

Only this untracked scratch audit was written. No tracked/index changes,
builds, claims, network operations or publication were performed.
