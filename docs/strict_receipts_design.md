# Strict receipts on every compile (design, not scheduled)

Status: proposal for the owner to route. It changes `tools/build.py` and what the
hooks' compiles write, so it lands as its own reviewed `Verifier-Change` commit.
Evidence: [LINK-628](linking_obstacles/link-628-real-link-loss-audit-runs-in-report-mode-six-gaps-block-refuse.md),
measured on srv1 on 2026-11-07.

## Problem

`tools/link_batch_audit.py` proves an object current only with
`link_census.object_current`, which is `build.compile_is_current(strict=True)`:
a version-2 receipt whose include search inventory still matches the tree, or a
header-free version-1 receipt. Only two callers write version 2:
`link_census.py --build` and `link_check.py --prepare-current`. Everything else
writes version 1:

| Writer | Receipt | Why |
|---|---|---|
| `try_compile_source(inventory=False)`: `./build.sh`, the hooks' scoped gates, workers | v1 | no inventory taken |
| `_restore_object` (object store) | whichever variant is newest | no preference for v2 |
| `import_bundle` (`link_check --fetch-index`) | v1 | the bundle receipt carries no inventory |

So a source the pre-push hook has just byte-verified fails the audit
("N source object(s) lack current receipts", exit 2), and so does an unchanged
consumer compiled the same way ("affected consumer lacks current receipt").

Measured: worker seat5 had 337 version-2 receipts among 18,431 (1.8%), 5,004
header-free version-1 receipts (which pass) and 13,090 (71%) that fail strict.
The census cache had 16,400 of 22,802.

## Design

1. **Every compile records the inventory.** `try_compile_source` takes
   `inventory_before` and runs `_inventory_problems` for every `cl` compile, not
   only when `inventory=True`. The sidecar format is the existing version 2;
   nothing new is read. `input_proof` (census preprocessor witnesses) stays
   census-only, unchanged.
2. **The object store keeps working under (1).** Today
   `if not inventory and _restore_object(...)` skips the store whenever an
   inventory is wanted, and `compile_rows` skips `_restore_stale` for strict
   callers. Flipping (1) without this turns every restore into a compile.
   Instead:
   - `_restore_object(..., strict)` tries the entry's variants version-2 first
     (newest first within a version), installs one and keeps it only if
     `compile_is_current(strict=strict)` holds; a non-strict caller also prefers
     version 2, so a restore hands back a strict receipt whenever the store has one.
   - `compile_rows` restores for strict callers too, but not with `input_proof`
     unless the restored receipt passes strict currency, which needs no witness.
3. **One inventory walk per root per run.** Today a strict compile walks every
   search root twice uncached (before and after). Share one cache across a
   `compile_rows` call for the "before" inventory. Close the run with
   `_inventory_cache_still_current(cache)`, as `_strict_stale_chunk` already
   does. If a root changed during the run, the TUs compiled in it are written
   back as version 1 (or fail the run, as the strict stale check does).
4. **Bundles carry the inventory when it is host-neutral.** Export
   `version`, `inventory`, `retry_dirs` and `search_roots` when every search root
   is inside the repository (`_root_key` relative). Import writes them back.
   Strict currency recomputes the inventory locally anyway, so a mismatch only
   loses strictness, never soundness. This is what PC workers using
   `--fetch-index` need.
5. **Upgrade on demand, not by mass recompile.** A version-1 object that is
   otherwise current stays usable for ordinary gates. Where the audit needs a
   strict receipt, it already names the sources. A bounded strict prepare, like
   `link_check.py --prepare-current` (1..32 explicit sources), can recompile
   just those. That costs one `cl` per TU, and only for touched units.

## Cost

- **Compiles:** `search_inventory` is 0.07 s per TU uncached on srv1 (50 TUs).
  300 TUs sharing a cache took 7.1 s. Twice per compile uncached is about
  0.14 s against a 1–3 s Wine `cl`, so +5–10% on TUs actually compiled. With
  (3) it falls to about one walk per root per run. Current TUs cost nothing.
- **Strict currency checks:** these re-walk the roots per process (already
  cached per chunk), unchanged.
- **Disk:** none beyond the existing version-2 fields, a few hundred bytes per
  receipt.
- **No cache invalidation:** version-1 receipts stay valid for ordinary
  currency, so nothing recompiles at rollout.

## Expected effect

- Inventories survive master well. For 400 sampled TUs the in-repo roots'
  inventories were unchanged after 6 h, changed for 2% after 12 h and for 5%
  after 24 h (1,353 master commits in 48 h).
- So within a day of rollout, objects compiled or restored from the store
  should be strict-current at about the census cache's rate (72%) or better. A
  touched source is strict by construction.
- About 1% of TUs cannot be inventoried: 226 version-1 receipts with headers in
  the census cache, from macro or `..` includes or headers outside the roots.
  They stay unprovable outside a census and keep the audit inconclusive when
  touched. They are worth listing once and fixing at the source.

## Risks and checks

- **Build cache trap** (`docs/matching.md`): the change must not alter
  `_cmd_fingerprint` or object bytes. Only the sidecar gains fields, so the
  object store's keys and every existing receipt stay valid.
- **Tests:**
  - an ordinary compile writes version 2;
  - restore prefers a passing version 2 over a newer version 1;
  - a strict restore refuses a version 1 with headers;
  - a root changed mid-run downgrades or fails;
  - a bundle round-trip keeps strictness only for in-repo roots;
  - `tools/tests/test_gate_exploits.py` keeps every verdict.
- **Measure before and after:** the share of strict-current objects per seat
  (the counts above) and the audit's verdicts over a day of pushes. Pushes keep
  no log today, so the hook would need to append its audit verdict line
  somewhere durable.
