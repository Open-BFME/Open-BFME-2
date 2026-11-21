# Native Item014: STLport POD-vector migration prerequisite review

Result: **known whole-file ABI/ownership blocker remains; no unchanged compiler probe**. Confidence: **sicher** for current row counts, declarations and exact recorded history; the old global provider/consumer selection remains **unknown-current**. No Code/tool/header, ledger, claim, Git or shared build-cache mutation; no compiler.

## Actual scope before compilation

Root's native seat holds only `file:Code/Libraries/Source/WWVegas/WWLib/stlport_pod_vector_bodies.cpp`. The complete current source is 1,385 lines and owns **160 rows / 157 unique RVAs / 8,181 row bytes**, not three rows. `CURRENT-ROWS.json` is a filtered streaming read of those rows only. `ACTUAL-SCOPE.json` gives every unique RVA and the 17 precise old const-allocator symbols/addresses/sizes for future central planning; this is not an additional claim request.

The three rows in `reverse/stlport_trial.csv` are **library-copy** samples from upstream `facets_byname.cpp`, with `header_46=not-sampled`:

| RVA | Bytes | Library sample |
| --- | ---: | --- |
| 00307641 | 63 | _Vector_base<char> ctor, mismatch |
| 00307C43 | 51 | vector<char> count ctor, match |
| 004598CC | 21 | mutable byte __uninitialized_copy, match |

The queue's two successes /72 bytes describe those samples only. Its sentence 'unit itself was never compiled under4.6' is generated for a library lead from that report kind, **not a history-aware finding**. `tools/repair_queue.py:stlport_items` appends that sentence when `entry['lead'] != 'unit'`. It conflicts with the existing recorded native whole-file attempts, rather than revealing a new compilation opportunity. No check was changed or bypassed.

## Existing evidence rules out an unchanged repeat

All four exact source-prefixed migration history entries were captured with native log line numbers in `MIGRATION-HISTORY.json`:

- 98307: supported4.6 marker+18 const adjustments and proxy/hint adaptations tried;34/157 failures.
- 99170: complete160-row adapted candidate;124 normal exact,160 only under explicitly diagnostic const-twin relocation translation. Seventeen QBE providers and outside consumers require coherent migration.
- 125690 / Nov19 prerequisite check: normal unchanged160/160 control then passed at2d3b37d310; the same17 old const providers remained; a missing dependency had been restored; old claim contention was no longer asserted.
- 133197: marker-only port again fails due to4.5.3-specific proxy definitions and nonconst allocator API. No new independent lever.

The original detailed evidence is `reverse/attempt_support/stlport-pod-migration-20261103/README.md`, candidate.cpp.txt and provider-consumers.{md,json}; their present hashes are in `INPUT-HASHES.json`. The original complete160-row masked diagnostic success **was never a normal admission or selected-link proof** and is not promoted here. No diagnostic const-twin translation was used in a new probe.

Current source still explicitly instantiates all17 allocator<T>::allocate(... )const rows, with QBE names. Current4.5.3 `reference/shims/bfmealloc/stl/_alloc.h` declares its primary allocate const. Pristine4.6 `_alloc.h` declares allocate nonconst; its existing supported BFME allocation patch preserves that nonconst signature. These exact checked-in inputs still substantiate the API-name incompatibility. Current source also contains the old _STLP_alloc_proxy<char*> allocate/deallocate specializations, the previously observed incompatible declarations.

The complete source contains many real/nontrivial element forwarding, destruction and growth contracts: BuildListInfo, WeaponTemplateSetHead, CreateAHeroManager::CreateAHeroSubClass, CarryoverUnit and documented neutral element views. An allocator symbol rename alone is not proof that all these callers retain the correct selected implementation. No application class rename, API edit or canonical-header repair is proposed by this scout.

## Narrow next action, if centrally reopened

Do not reserve three sample RVAs or run the already refuted marker-only trial as a whole-file success. A real migration would first need a **fresh selection-aware audit** of all17 old-name providers and actual consumer relocations, followed by lawful authoritative placement and a complete central claim set. The historical audit found16 outside consumer files /46 runtime call or tail-jump edges and19 alternative provider copies, but its index was984a4cdc4d and two receipt exceptions existed. Those numbers and old claim holders are not asserted current. A same-name or identical provider is not approval to rehome a row there.

Only after that fresh evidence and explicit scope could the known normal4.6 API adaptation be applied without arbitrary flags/header hacks or aliases. Every affected file must pass all its rows, full raw+relocation/weak/COMDAT/data/EH footprints and joint provider/consumer link selection before the normal add_match migrated markers. No partial160-row move, no fake compatibility provider and no new source variants are recommended now.

`find_declared_unmatched.py` was inspected but not executed in this read-only pre-claim stage: its current source-prover path can call `build.compile_rows` if a strict-current receipt is missing (lines451-456), which would violate the no-shared-compilation assignment. Root may run the normal guard when the operation is properly scoped.

**0 migrated rows, 0 new bodies/bytes, 0 commits.** No current whole-file compile, full-link or runtime result is claimed by this supplementary review. Input and result hashes are closed in MANIFEST.json.
