# Agent tool verbs

Agents call these fixed verbs rather than writing one-off scripts. Each verb takes
typed arguments (RVAs are hex, sizes are decimal bytes) and prints JSON with `--json`
(the `ghidra_refdb.py` verbs always print JSON). None of them writes the ledger.

| Verb | Answers |
|---|---|
| `python3 tools/ghidra_refdb.py fn DB RVA\|NAME` | Ghidra's function at or containing an RVA: boundary, body ranges, name, signature |
| `python3 tools/ghidra_refdb.py callers DB RVA` / `callees DB RVA` | call-graph edges |
| `python3 tools/ghidra_refdb.py xrefs-to DB RVA` / `xrefs-from DB RVA` | every reference, with kind and operand |
| `python3 tools/ghidra_refdb.py strings DB RVA` | strings a function references |
| `python3 tools/ghidra_refdb.py switch DB RVA` | jump-table targets in case order |
| `python3 tools/ghidra_refdb.py type DB NAME` | a Ghidra data type with members / enum values |
| `python3 tools/similar.py near RVA [--of GAME] [--json]` | the matched functions (any game) this body most resembles, with their sources |
| `python3 tools/next_work.py --tier similar` | an unclaimed function served next to its nearest matched neighbours |
| `python3 tools/variant_search.py SOURCE SYMBOL RVA SIZE` | model-proposed rewrites, compiled in parallel and scored by the gate |
| `python3 tools/model_routing.py route --size N` | which models may take this task, best first |
| `python3 tools/model_routing.py judge --model M` | whether M is on the protected judge list |
| `python3 tools/build.py SOURCE` | the byte gate: the only acceptance |

## Reference snapshots (Ghidra, read-only)

The analysed Ghidra project (BFME1, BFME2 and RotWK) is exported to one SQLite file
per binary with tables `functions`, `xrefs`, `strings`, `data`, `switches`, `types` and
`meta`. Snapshots are not committed. Local path: `build/refdb/<program>.sqlite`, for
example `build/refdb/bfme2_game.dat-442295.sqlite`. Published path: a GitHub release
tagged `refdb-YYYYMMDD` carrying `refdb-<program>-<content12>.sqlite`, where
`content12` is the first 12 hex digits of `meta.content_sha256`. Fetch it with
`gh release download refdb-YYYYMMDD -p 'refdb-*' -D build/refdb`.

Build one with:

    python3 tools/ghidra_refdb.py export --project <dir>/witchking.gpr \
        --program bfme2_game.dat-442295 --program rotwk_game.dat-c9e1ec

The exporter copies the project first and never opens the owner's copy. It needs
Ghidra 12.1 and JDK 21 (`GHIDRA_INSTALL_DIR`/`JAVA_HOME`, or under `build/toolchains`).
Two exports of the same project state give byte-identical files and the same
`content_sha256`. Check `meta.executable_sha256` against the repo baseline before you
trust its RVAs.

Snapshot names are Ghidra's. They are not identity evidence.

## Name sync into Ghidra

`ghidra_refdb.py sync-plan DB` lists the ledger names that may go into the canonical
project. A name qualifies only if it has evidence behind it:

- `export`: the PE export table names it.
- `ilt`: the ILT oracle confirmed it (an `ilt-verified=` note on a matched row).
- `reloc`: a byte-true call proved it (`reloc_names.csv`, `identity=real`).

A matched row on its own does not qualify, because the agent picked that name.
Placeholders never sync. Only `ilt` may replace a name that is not a placeholder.
`sync-apply` writes the plan into the canonical project with
`tools/ghidra/apply_names.java`, tagging each function `refdb-sync tier=...`.

## Similarity instead of BSim

`tools/similar.py` builds the cross-game index from masked instruction n-grams (2-
and 3-grams with registers and large constants masked, stop-words dropped, Jaccard
ranking) in about 25 s for 124k functions. It does not need the BSim database that
a full decompile of every function would require.
