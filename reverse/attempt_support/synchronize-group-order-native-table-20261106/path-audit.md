# Planned SynchronizeGroupOrder path audit

Read-only audit, 2026-11-06. Inspected HEAD: `faee62b0b26c48462b513f1b528a570d55da011d`.
The merge has not been applied or admitted by this audit. Its exact accepted
donor set and the normal merge/link guard remain the root operator's decision.

## Planned paths

All three donors are under `Code/GameEngine/Source/GameLogic/AI/`:

| Planned absorbed source | Destination |
| --- | --- |
| `SynchronizeGroupOrderDtor.cpp` | `SynchronizeGroupOrder.cpp` |
| `SynchronizeGroupOrderSlot4.cpp` | `SynchronizeGroupOrder.cpp` |
| `SynchronizeGroupOrderXfer.cpp` | `SynchronizeGroupOrder.cpp` |

No directory is moved. No original EA path string is implicated. The destination
retains its existing path. This report audits these three planned removals, not
any unrelated path change that might enter the outgoing batch later.

## Search scope and result

One combined family search covered the old full paths, case-insensitive donor
basenames with and without `.cpp`, and encoded COFF-object basename forms. It
covered `tools/`, `.githooks/`, `.github/`, `Code/` (including include directives),
`reverse/`, `docs/` including `docs/doxygen/`, `vendor/`, and all root files:
`.gitattributes`, `.gitignore`, `.gitmodules`, `AGENTS.md`, `build.ps1`,
`build.sh`, `LICENSE`, `PLAN.md`, and `README.md`. Hidden/ignored files in those
named scopes were included in the final active-consumer search. Searches did
not traverse `build/`, its worktrees, `.git/`, baselines or the reference tree.
Historical attempt directories were searched separately by filename mentions.

No hard-coded donor path or basename was found in active tools, hooks,
workflows, source/header includes, build/configuration files, vendor files,
doxygen source inputs, or active documentation. No tool special-case, glob or
directory-derived assumption specific to the donors was found. The directory
remains in place, so existing generic AI-directory scans keep their scope.

## References that must follow the supported merge

* `reverse/functions.csv` currently has six donor-owned code rows: Dtor 2 rows /
  87 bytes, Slot4 3 / 104, Xfer 1 / 68; total 6 / 259. Their `source` cells must
  move to the approved destination through `tu_skeleton.py`.
* `reverse/tu_map.csv` has the six corresponding `source` cells. Their existing
  approved destination is already `SynchronizeGroupOrder.cpp`. Repoint only
  source cells; do not regenerate the map or change approval evidence.
* The destination's six `// tu-skeleton:` comments name those donors as not yet
  merged. The normal composition consumes/replaces them; provenance comments
  describing absorbed fragments may legitimately keep old paths afterwards.

No donor key was found in data rows, body owners, pins/fold proofs, naming basis,
header queue, Microsoft-header queue, DX/STLport queues, flag overrides, gate /
identity / data / hatch baselines, data ledger, whitelist, exit-link blockers,
or doxygen source inputs. Normal merge transfer/refresh machinery still decides
and verifies register changes at application time.

`tu_skeleton.repoint_all` handles `rename.PATH_COLUMNS`, naming provenance,
fold-proof tokens and doxygen inputs. `refresh_reports` transfers header scope
and refreshes Microsoft-header reports. No missing active path registry was
identified; no tooling edit is recommended.

## Intentionally preserved measured/history references

| Location | Classification and handling |
| --- | --- |
| `reverse/link_status.csv` (three donor rows) | Published census at `d707d2f53b`, 2026-11-06 11:04. Historical measurement; keep unchanged until its owning scheduled census refreshes it. A merge does not authorize hand-changing measured linking status. |
| `reverse/vtable_bridge_queue.tsv` (SynchronizeGroupOrder table `0x0086A314`) | Queue measured by real link `6e5fe55db8dc5d05854f35d462aa911f13699d5c`. Its source field names the surviving destination; embedded JSON names the old destructor owner/object as measured evidence. Preserve that evidence; the next real link must establish whether this refusal clears. |
| `reverse/deleted_rows.csv` (four historical family-reconciliation reasons) | Tombstone prose names the then-current donor owners. Preserve history. |
| `reverse/attempt_support/synchronize-group-order-container-20261104.md` | Historical four-source container repair and blocked-merge evidence. Preserve. |
| `reverse/attempt_support/aispecialpower-xfer-consolidation-20261104/README.md` | Historical broader outgoing audit lists these units as missing receipts. Preserve the original audit scope. |
| `reverse/attempt_support/runtime-vtable-survey-20261105.tsv` | Dated survey evidence, not a live source registry. Preserve. |
| `reverse/attempt_support/synchronize-group-order-native-table-20261106/full-view-proof.json` and `full-normal-closure.json` | Current prerequisite repair receipts name the pre-merge sources. Preserve as before-state proof; acquire new destination proof for the actual composition. |

No old donor basename was found in `reverse/re_attempts.log`; relevant older
consolidation verdicts instead name the surviving TU.

## Publication boundary

This audit identifies no independent active consumer needing a path edit.
The root still needs the supported approved merge, destination byte/EH/data /
frozen-file checks, protected-register transfer verdicts, current merge/link
guard, and publication audit. Do not reuse donor compiler receipts as proof of
the merged destination. Carry the old census/bridge evidence into the next
scheduled measurement; no new runtime or headline gain is asserted here.

Reuse this audit only while these planned paths and relevant consumers remain
the entire path-changing scope of the outgoing batch. Reaudit if a different
donor/path or an affected active consumer is added.
