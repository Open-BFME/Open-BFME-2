# INIException / Respawn static data alias review

Read-only narrow header, register, tooling and policy inspection. No candidate/native RTTI graph verification, build, claim, network, source edit or ledger mutation. All tracked reads stopped before this report.

## Canonical facts and current ledger

`Code/GameEngine/Include/Common/INI/FieldParse.h:3,42-52` declares INIException with no virtual functions or bases: message pointer+0 and int field04+4, sizeof8. It declares varargs `(int,const char*,...)`, copy constructor, destructor and assignment; it declares **no default constructor**. Its target-fact comment binds ThrowInfo RVA008FE2FC, CatchableType008FE2D8 (size8/no base adjustment), destructor2BD30 and copy588C5 through assignment2F6D6. This supports the canonical class/API boundary; the parent separately verifies the candidate's emitted metadata graph and two DIR32 replacements.

`reverse/data_ledger.csv:16718` already has canonical name `__TI1?AVINIException@@`, kind rtti, status literal, source empty. The old `_respawnThrowInfoAnchor@Code/GameEngine/Source/GameLogic/Object/Update/RespawnUpdate.cpp` is only one TU-local alias token in its `names` cell. The row's2148 size is a heuristic upper bound to the next indexed address, not proof of the ThrowInfo extent. Its defs24/refs266 are cached aggregate diagnostics, not a new verified data claim. No exact8FE2FC/INIException ownership row or converged-address entry, and no Respawn static-anchor hatch/data-baseline key, was found in the narrow lookups.

Removing that old static binding does not rename the canonical ledger owner. It requires retiring a stale observed alias through the ledger's owning generation path; no second symbol/pin or hand alias is needed or supported.

## Supported tool path: regeneration, not a narrow alias-delete command

`tools/data_ledger.py:318-334` exposes only:

- `python3 tools/data_ledger.py --out build/respawn-parser-metadata-review-20261103/data_ledger.after.csv` — generate a scratch preview.
- `python3 tools/data_ledger.py` — regenerate the committed `reverse/data_ledger.csv` from present matched objects.
- `python3 tools/data_ledger.py --check` — compare the committed ledger against that generated result (nonzero if stale).

These commands were **not run** by this reviewer. No supported `--remove-alias`, `--source`, `--address` or scoped stale-alias cleanup option was found. `ledger_rows(bind,defs)` and `render(rows)` are generation primitives, not a scoped merge/removal policy. Hand-pruning the names cell through a generic writer would still be manual ledger editing, which the owning tool explicitly forbids.

Generation uses matched rows and their normal `build.row_object` paths. `collect()` memoizes from ledger rows plus object mtime/size, and `collect_uncached()` derives DIR32 bindings from the objects that exist. It does **not** establish current source/header receipts; missing objects are reported but the CLI still renders its result. Therefore the parent's private candidate alone cannot make a main-tree regeneration authoritative: the adopted source must have its normal current verified object, and broad regeneration requires review of unrelated stale/missing-cache effects. The scratch preview makes that broad diff reviewable; do not copy a selected manually edited line into the protected ledger.

The existing rename tool deliberately leaves a protected stale ledger spelling and instructs regeneration in a **Verifier-Change commit** (rename.py:4003-4006,4547-4550). Preserve that protected-ledger workflow and normal checks if regenerating. This trailer describes the index update; it never retires a separate debt key.

`tu_skeleton.unit_key_carry()` is not an alternative alias-retirement API. It transfers unit keys to actual definers for a split/shatter, deliberately leaves preexisting stale keys when the residual survives, and refuses a missing defining home. Here RespawnUpdate.cpp survives and the old static disappears; there is no destination for the alias to transfer to. The consolidation unit-key rules do not authorize deleting it by hand.

## Owning debt paths

Current RespawnUpdate.cpp has queued FieldParse, INI, INIException and MultiIniFieldParse header entries. Their supported commands are:

```
python3 tools/header_adopt_lane.py accept --class FieldParse Code/GameEngine/Source/GameLogic/Object/Update/RespawnUpdate.cpp
python3 tools/header_adopt_lane.py accept --class INI Code/GameEngine/Source/GameLogic/Object/Update/RespawnUpdate.cpp
python3 tools/header_adopt_lane.py accept --class INIException Code/GameEngine/Source/GameLogic/Object/Update/RespawnUpdate.cpp
python3 tools/header_adopt_lane.py accept --class MultiIniFieldParse Code/GameEngine/Source/GameLogic/Object/Update/RespawnUpdate.cpp
```

These are existing queue commands, not claims that the candidate passes acceptance. The parent owns application/verification. No source-specific data-check, identity, Microsoft-header or gate-baseline key was found by the narrow current lookup. If a real data-baseline key is encountered later, its route is `repair_queue.py retire data SOURCE` after a clean current build; that tool rejudges only keys no longer found. A data-ledger alias is not itself such a baseline line. Since the source survives, vanished-source Debt-Retired explanations are inapplicable.

Conclusion: canonical metadata already owns this data address. Exact stale-token cleanup has an owning full-generation route, but no narrow cleanup CLI/API was found. Keep the metadata proof, header acceptance, generated-ledger refresh and any actual debt retirement as distinct claims; no full RTTI/provider/image closure is supplied here.
