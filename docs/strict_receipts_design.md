# Strict receipts on every compile (design: only step 0 has landed)

Status: only step 0, the verdict logger, has landed (e2b22f90d4, 104cd6d6a8).
Steps 1 to 5 are not scheduled. The owner will revisit them once the log has a
real sample of INCONCLUSIVE rates to judge them by; on 2026-11-08 it held 9 real
lines, 3 of them inconclusive, which is too few; on 2026-11-09 it held 233, none
of them a judged batch, and receipts are not the only wall (LINK-651). If scheduled, they change
`tools/build.py` and what the hooks' compiles write, so they land as their own
reviewed `Verifier-Change` commit. Revised 2026-11-07 after the Link lane's
review; checked against master at 3b141964e7 on 2026-11-08. Evidence:
[LINK-628](linking_obstacles/link-628-real-link-loss-audit-runs-in-report-mode-six-gaps-block-refuse.md),
measured on srv1 on 2026-11-07 unless dated otherwise.

## Problem

`tools/link_batch_audit.py` proves an object current only with
`link_census.object_current`, which is `build.compile_is_current(strict=True)`:
a version-2 receipt whose include search inventory still matches the tree, or a
header-free version-1 receipt. Only three callers compile for version 2:
`link_census.py --build`, `link_check.py --prepare-current` and `link_cycle.py`
(`compile_rows(strict=True)`). Everything else writes version 1:

| Writer | Receipt | Why |
|---|---|---|
| `try_compile_source(inventory=False)`: `./build.sh`, the hooks' scoped gates, workers | v1 | no inventory taken |
| `_restore_object` (object store) | whichever variant is newest | no preference for v2 |
| `import_objects` (`link_check --fetch-index` bundles) | v1 | the bundle receipt carries no inventory |

So a source the pre-push hook has just byte-verified fails the audit
("N source object(s) lack current receipts", exit 2), and so does an unchanged
consumer compiled the same way ("affected consumer lacks current receipt").

Measured: worker seat5 had 337 version-2 receipts among 18,431 (1.8%), 5,004
header-free version-1 receipts (which pass) and 13,090 (71%) that fail strict.
The census runner's cache had 16,400 of 22,802.

That cache's figure depends on when it is read, because the runner's follower
cycles write to it too. On 2026-11-08 one follower restored 6,746 TUs from the
object store, nearly all as version 1 with headers, leaving 9,645 version-2 of
22,804 and 6,991 version-1 with headers. Step 2 is about exactly this.

## Design

Step 0 describes what landed. Steps 1 to 5 are the unscheduled proposal.

0. **Verdict logger (landed).** It went first, so that any later change can be
   compared before and after.
   - **Format:** after its verdict, `link_batch_audit.py` appends one JSON line
     to `<git common dir>/link_audit_verdicts.jsonl`, as `class_gate.shadow_log`
     does for `class_gate_shadow.jsonl`.
   - **Fields:** `utc`, `base`, `tip`, `verdict` (`clean`, `failed`,
     `inconclusive`, `crashed`, or `exit-N` for any other exit code), `reason`
     for an inconclusive run (`missing-receipts`, `consumer-receipt`, `no-index`,
     `non-exact-base`, else `other`), `exit`, `sources` (the scope), `exact_base`
     (null when the run returned before comparing), `judged` (the batch's objects
     were read through to a verdict), `shadow` (below),
     `real_link_findings`, and `lines` (the first 12 output lines, each cut to 300
     characters). There is no missing-count field; that count is only in the text
     of `lines`.
   - **No behaviour change:** the hook's output and exit code don't change, and
     a failing write loses the line, never the push. A run the hook's time cap
     kills writes no line. One clone's file is that clone's pushes; the seats on
     srv1 share one common dir, so they share one log.
   - **Started lines:** each run first writes a line with `verdict: started`. A started tip with no verdict line after
     it is a run the hook's cap killed, so count those as lost, not as absent.
   - **`shadow`:** what a gap-aware audit would say, measured beside the exit, which only `audit()` decides. `would_be` is
     `clean`, `failed`, `unknown` with `reasons`, or null when there is nothing to judge. `possible_losses` and `real_link`
     count losses even when `unknown`, and those counts are the base rate. Its objects are the seat's, so a cold seat reads
     `gap-object-unavailable`. It never prints and runs inside the hook's budget (`out-of-budget`).
   - **Reading it:** drop lines with `"base": "a"` and `"tip": "b"`. They are
     fixtures `tools/tests/test_link_batch_audit.py` wrote into real logs
     (2026-11-07 on; 6 of srv1's first 8 lines), and a clone running the suite from
     before its fix (1ec1e0a27a) can still add more. The live log is left as it is.

1. **Every compile records the inventory.** `try_compile_source` takes
   `inventory_before` and runs `_inventory_problems` for every `cl` compile, not
   only when `inventory=True`. The sidecar format is the existing version 2;
   nothing new is read. `input_proof` (the census's preprocessor witnesses)
   stays census-only and unchanged.

2. **The object store keeps working under (1).** Today
   `if not inventory and _restore_object(...)` skips the store whenever an
   inventory is wanted, and `compile_rows` skips `_restore_stale` for strict
   callers. Flipping (1) without this turns every restore into a compile.
   - **Order:** `_restore_object(..., strict)` tries the entry's variants
     version-2 first, newest first within a version.
   - **Check before install:** a variant's receipt is judged against the source
     and tree (the `compile_is_current` predicate over a candidate receipt)
     before anything is installed.
   - **Atomic install:** copy both files of the chosen variant to private
     temporaries, rename the current `.obj`/`.deps.json` pair aside, rename the
     temporaries in, and drop the aside pair only once the installed pair passes
     `compile_is_current(strict=strict)`. Any failure renames the aside pair
     back. The output pair is always both-old or both-new, and a refused variant
     leaves the previous pair byte-identical (`docs/matching.md`, "The build
     cache trap"). Today's restore removes both outputs when the post-install
     check fails.
   - **Non-strict callers:** they also prefer version 2, so a restore hands back
     a strict receipt whenever the store has one. That can restore an older
     version-2 variant over a newer current version-1 one, which is harmless:
     both are current for the same source, command and headers, and are the
     same object.
   - **Census:** `compile_rows` restores for strict callers too. With
     `input_proof` (the census), a restored variant counts only if it passes
     strict currency, which needs no witness; otherwise the census compiles as
     today.

3. **The inventory is taken once, in the parent, before compiling.**
   - **When:** `compile_rows` takes the inventory of every search root its stale
     TUs use in the parent process, before any compile starts, never lazily in
     a worker. Under `BUILD_POOL` each worker would otherwise see the tree at a
     different moment, and a root that changed between workers could pass as
     unchanged.
   - **How workers use it:** each compile is handed its roots' inventories and
     writes them as its "before".
   - **The close check:** after the last compile, the parent takes the same
     inventories again (`_inventory_cache_still_current`, as `_strict_stale_chunk`
     does). Every TU whose search roots include a root that changed mid-run is
     written back as version 1, or the run fails, as the strict stale check
     does. The downgrade is per TU over that root, not per directory entry:
     which file appeared does not matter.
   - **Cost:** one walk per distinct root per run, instead of two per TU.

4. **Bundles carry the inventory only when it is host-neutral.**
   - **The problem:** the toolchain's INCLUDE roots break neutrality.
     `build.vc71_root()` honours `VC71_ROOT`, so a PC worker with VS2003
     installed elsewhere has different root paths and would never match.
   - **Keying:** toolchain roots are keyed by toolchain identity (a digest of the
     toolchain's include trees, the files under `Vc7/include` and
     `Vc7/PlatformSDK/Include`) rather than by path. In-repo roots keep their
     repo-relative `_root_key`.
   - **Export rule:** a receipt is exported with `version`, `inventory`,
     `retry_dirs` and `search_roots` only when every root is one of those two
     kinds; any other root (an absolute path outside the repo and the
     toolchain) exports version 1 as today.
   - **Import:** writes the fields back. Strict currency recomputes the
     inventory locally, so a mismatch only loses strictness, never soundness.
     This is what PC workers using `--fetch-index` need.

5. **The strict rebuild stays opt-in.** A version-1 object that is otherwise
   current stays usable for ordinary gates.
   - **Hook unchanged:** the hook does not rebuild strictly on its own. When the
     audit says INCONCLUSIVE, the pusher may run
     `link_check.py --prepare-current` (1..32 explicit sources) on the sources
     it names and push again.
   - **Header pushes stay inconclusive often:** at most 16 of master's 57 scoped
     header commits in the 48 h measured (28%) recompile a TU whose search cannot
     be inventoried (an upper bound, see "Measurements" below). Those pushes stay
     INCONCLUSIVE whatever the pusher does. The median scoped header push recompiles 4 sources, the largest 1,285, and 3 of 60
     header commits ran the full gate.
   - **Two other causes:** a consumer the push does not recompile still needs a
     strict receipt of its own until caches turn over, and a census index that
     is not at the pushed base keeps findings provisional.
   - **Lowering that floor:** fixing those TUs at the source is what lowers it.

## Cost

- **Compiles:** `search_inventory` is 0.07 s per TU uncached on srv1 (50 TUs);
  300 TUs sharing a cache took 7.1 s. With (3) it is one walk per distinct root
  per run, a few seconds on a full build and well under a second on a scoped
  one. Today's strict path walks every root twice per TU, about 0.14 s against a
  1–3 s Wine `cl`. Current TUs cost nothing.
- **Strict currency checks:** they keep re-walking the roots per process,
  cached per chunk, unchanged.
- **Disk:** none beyond the existing version-2 fields, a few hundred bytes per
  receipt.
- **No cache invalidation:** version-1 receipts stay valid for ordinary
  currency, so nothing recompiles at rollout.

## Expected effect

- Inventories survive master well. For 400 sampled TUs the in-repo roots'
  inventories were unchanged after 6 h, changed for 2% after 12 h and for 5%
  after 24 h (1,353 master commits in 48 h).
- Within a day of rollout, objects compiled or restored from the store should
  be strict-current at about the runner cache's 2026-11-07 rate (72%) or better.
  A touched source is strict by construction unless its search cannot be
  inventoried.
- Source-only pushes should then mostly turn conclusive. Header pushes keep the
  floor from (5), at most about 28%.
- The logger from (0) measures both against its pre-change baseline.

## Tests

- **Cache identity:** `_cmd_fingerprint` and the object bytes are unchanged.
  Compile one TU before and after the change and compare the store key
  (`_objstore_dir`) and the object's bytes; only the sidecar gains fields.
- **Writes and freshness:**
  - an ordinary compile writes version 2;
  - a header content edit after the compile fails strict (and ordinary)
    currency;
  - a header added to an earlier search root fails strict currency only.
- **Restore:**
  - the store prefers a passing version 2 over a newer version 1;
  - a strict restore refuses a version 1 with headers;
  - a refused restore rolls back: a version-2 variant that fails the check
    leaves the previous `.obj`/`.deps.json` pair byte-identical;
  - an install interrupted between the two renames leaves either the old or
    the new pair, never one file of each.
- **Parent inventory:**
  - under a multi-worker `compile_rows` (`BUILD_POOL` > 1), every worker's
    receipt carries the inventory the parent took before the first compile;
  - a root changed after the parent's walk but before a worker compiles
    downgrades (or fails) every TU over that root.
- **Bundles:** a round-trip keeps strictness for in-repo and toolchain-identity
  roots, and drops it for any other root (a VS2003 install at another path
  still matches by identity).
- **Gate exploits:** `tools/tests/test_gate_exploits.py` keeps every verdict.

## Measurements behind the numbers

- **The TUs whose search cannot be inventoried:** not settled. The runner cache's
  version-1 receipts that record headers were read as these, since the census
  compiles with `inventory=True` and such a receipt there failed
  `_inventory_problems` (macro or `..` includes, or headers outside the search
  roots). That gave 226 and later 265 on 2026-11-07, but follower cycles write the
  same kind of receipt (6,991 on 2026-11-08), so both are upper bounds and the
  count cannot be repeated that way. Run `_inventory_problems` over the TUs before
  relying on it. A header outside the checkout, the toolchain and a trusted link
  no longer compiles at all (include confinement, `docs/matching.md`).
- **The 28%:** master's header-touching commits in the 48 h before 2026-11-07
  21:00 UTC, with each push's recompile set from `header_dependents.py --range`,
  against the 265, so it is an upper bound too.
- **Seat counts:** the `build/match` sidecars of seat5 and of the census runner
  on srv1, on 2026-11-07.
