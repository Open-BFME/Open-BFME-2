# Assisted builder / constructor-funclet owner audit

Audit scope: pending working-tree batch after parent-supplied base
`ef649c78a7`, limited to these two row-owner changes. No source is deleted.

| Body | Old source | Destination | Observed status |
|---|---|---|---|
| buildFieldParse, RVA 0x486E7C/17 | ModuleDataBuildFieldParse.cpp | AssistedTargetingUpdate.cpp | Applied |
| ctor cleanup, RVA 0x78C15D/8 | Code/gen_small/uw_gen_011.cpp | AssistedTargetingUpdate.cpp | Pending admission |

All three sources remain. At inspection, the mixed builder source has 80
matched rows, uw_gen_011 has 202 and the destination has 15. The generated row
is still `uw_0078c15d`, notes `gen-funclet;object-symbol=$L10886`. This report
does not claim the prospective funclet repoint has landed or verified.

**No active hardcoded consumer or stale protected target key was found for
the applied builder move. No tooling change is indicated for the planned
funclet repoint.** Parent must confirm its application and final normal proof.

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

## Pending generated funclet

tu_map already approves 0x78C15D for the destination via the native constructor
0x486E8D / FuncInfo 0x93B754. The prior read-only receipt identifies its exact
EH-owned cleanup and existing UpdateModule dtor callee; compiler label numbers
must be refreshed from the final object before supported add_match admission.
No active tool/config/registry hardcodes this RVA to uw_gen_011.cpp.

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
as evidence. Census snapshots remain measurement-owned. None is a broken path
consumer. No raw EA path string requires rewriting.

Before finalizing, parent must confirm the generated row has been replaced by
the actual final parent-emitted label with `gen-funclet;parent=...`, and normal
byte/EH/link/ledger checks pass. Its current old-owner ledger/TU-source entries
are expected pending state, not an already repaired result.

Only this untracked scratch audit was written. No tracked/index changes,
builds, claims, network operations or publication were performed.
