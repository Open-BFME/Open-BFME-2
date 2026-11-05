### LINK-008: include inventories prevent strict reusable graphics receipts

**Status: Blocked on complete include inventories. Updated: 2026-10-27.**

- 2026-11-05: [Camera timestep consolidation](../../reverse/attempt_support/camera-timestep-consolidation-20261105-codex4.md) preserves 17/17 rows and supplies strict receipts for the destination and W3DCamTransform; the older-index consumer audit still lacks Common/0CreateAHeroManager21FE49.cpp's current receipt, so carry this shared-list cohort into the next scheduled census/current-index audit.

- 2026-11-04: [Emission constructor adoption](../../reverse/attempt_support/emission-info-header-adoption-20261104-codex4.md) retires nine header rows with strict receipts for both providers and 865/865 ordinary preview bytes preserved; the older-index consumer audit still lacks Common/AIBaseBuilder.cpp's current receipt, so include this cohort in the next scheduled consumer check.

- 2026-11-03: [AIStatBase consolidation and AIGameTeam reconciliation scope](../../reverse/attempt_support/aistatbase-consolidation-20261103.md) preserves ordinary previews; the older-index batch audit lacks three strict receipts (first AIGameTeam), so carry this additional cohort and consumers into the next scheduled census.

- **Eva/thread subset repaired (2026-10-29):**
  [explicit native include operands](../../reverse/attempt_support/consumer-include-roots-20261029/readme.md)
  remove the two macro-include ambiguities without changing the resolved
  header sets. Both supported strict preparations pass with version2
  reusable receipts,38 matched rows and2 data rows;2/2 ordinary previews
  preserve3471 authored bytes. This clears only these two recurring
  publication consumers, not the graphics cases or whole-batch closure.
- **Evidence / scope:** [graphics verification at `91fe970939`](../../reverse/attempt_support/weightinfo-verification-20261025/readme.md)
  ran the normal gates successfully for 34 units, but its initial 17-unit
  `--prepare-current` run refused strict reuse. W3DShadowTextureCtor,
  W3DDebrisDraw, W3DDebrisDrawLegacy and W3DVolumetricShadow reported macro or
  parent-traversing include roots, or headers outside inventoried search roots.
- **Completed:** all 34 ordinary byte/receipt checks pass; 13 objects also have
  strict reusable receipts. The other 17 units were checked through the ordinary
  path; no claim is made that all of them are uncacheable. The refusal is retained
  in the evidence, and no gate was relaxed. LINK-001's destructor preview result
  does not establish strict closure.
- **Dynamic vertex-buffer header cleanup publication (2026-10-27,
  `c2ec6b636d`):** the normal push gate passed 84/84 rows and 18 exact EH
  graphs across four sources. Its link audit remains inconclusive: index
  `bf3dd31211` predates outgoing base `324eb34f54`, and four scoped objects
  lack current receipts (first `Code/GameEngine/Source/GameClient/Eva.cpp`).
  Carry this publication scope and LINK-106's dynamic-buffer caller cohort to
  the next normal census/current-index audit; complete strict receipt
  prerequisites before strict reuse. The separate three-source ordinary
  preview remains LINKS; it does not clear this current-master audit.
  [Publication evidence](../../reverse/attempt_support/dynamic-vertex-buffer-header-20261027-codex.md).
- **Coordinate-checker backlog publication (2026-10-27, `028575016a`):**
  the normal hook passes 47/47 function rows, two data rows and eight EXACT
  EH graphs across its eleven-source scope. Its batch audit remains
  INCONCLUSIVE: index `73061d9452` predates outgoing base `4346b5248b`, and
  eleven objects lack current receipts, first
  `Code/GameEngine/Source/Common/Rva0033BD50Free.cpp`. Linking is explicitly
  UNVERIFIED. Carry this batch into the next scheduled census/current-receipt
  audit; no selected-provider or lost-byte verdict follows from its byte
  checks. [Scope and qualification](../../reverse/attempt_support/coord2d-companion-adoption-20261027.md#previous-batch-publication-qualification).
- **BFME 1 refresh publication scope (2026-10-27):** three rebased pre-push
  gates passed for 1,301, 1,314 and 1,322 sources, including upstream header
  consumers since the local pre-rebase full-gate receipt `6803d7df5b`. This
  batch itself changes no game source. The link audits remain inconclusive: index
  `5ce093a71a` predates outgoing bases `9d6c94a6fe`, `fa8f0a9db4` and
  `bf3ce2314b`; respectively 1,296, 1,309 and 1,317 objects lack current strict
  receipts, first `Code/GameEngine/Source/Common/AIHarvestPrepareSiteState.cpp`.
  No selected-provider or lost-byte conclusion follows. Carry this freshness
  scope into the next normal census; successful byte checks do not clear it.
  Each transfer was rejected because master moved during verification. The
  [reference evidence](../../reverse/attempt_support/bfme1-reference-e74410b3-20261027/readme.md)
  preserves the separate fixed-input comparison; no census or ownership gain
  is claimed.
- **Non-graphics publication control (2026-10-26, source `cc68e92bcd`,
  evidence `b3bd2d6351`):** the
  [VP6 scratch publication audit](../../reverse/attempt_support/vp6-filter-scratch-link-20261025/publication-audit.json)
  passes all 32 ordinary rows across the two repaired units and the conservatively
  included `Eva.cpp` control, one complete data owner, four exact EH graphs and
  converged-data enforcement. The mandatory batch audit is nevertheless
  inconclusive: index `47e030bafc` predates outgoing base `6e852991684`, and
  `Eva.cpp` lacks a current strict reusable receipt. No selected-provider or
  lost-byte verdict against current master follows from that audit. The separate
  immutable fixed comparison proves the scoped 2,747-byte gain with zero losses;
  it does not supply a current-master census. Carry this cohort to the next
  normal census and inventory Eva's include graph before strict reuse.
- **Quantizer publication cohort (2026-10-26, first candidate `71b55f3f7a`):**
  [the retained normal-hook audit](../../reverse/attempt_support/vp6-quantizer-layout-link-20261026/publication-audit.json)
  passes 39/39 bodies, 18 data rows, four exact EH graphs and converged-data
  enforcement across InitQuantizer.cpp, Eva.cpp, ThreadClassLifecycle.cpp and
  thread.cpp. The shadow batch comparison is inconclusive against index
  `d1f046749a`: its outgoing base was `ced3615d0f3`, and all four scoped
  objects lacked current strict receipts (first Eva). No selected-provider or
  current-master lost-byte verdict is claimed. Carry these exact four paths
  to the next normal census/current-index check. The independent immutable
  comparison proves the separate 1,538-byte gain with zero losses. The first
  push was rejected solely because master advanced; the existing commits are
  rebased and retried without repeating any match or full measurement.
- **Huffman publication cohort (2026-10-27, first candidate `6cec0a4f41`):**
  [the retained normal-hook audit](../../reverse/attempt_support/vp6-huff-table-layout-link-20261027/publication-audit.json)
  passes 41/41 bodies, five data rows, four exact EH graphs and converged-data
  enforcement across HuffTokens.cpp, Eva.cpp, ThreadClassLifecycle.cpp and
  thread.cpp. The mandatory comparison is inconclusive: index `d1f046749a`
  predates outgoing base `3e1e5f6d6a5`, and three objects lack current strict
  receipts (first Eva). No selected-provider or current-master lost-byte verdict
  follows; carry these four paths to the next normal census/current-index check.
  The separate immutable comparison proves 2,877 placed closed-strict bytes
  with zero losses. The first push was rejected because master advanced;
  only the existing commits are rebased/retried, without repeating any match
  record or full measurement.
- **Context-coefficient publication cohort (2026-10-27, candidate `3beaccdb21`):**
  [the retained normal-hook audit](../../reverse/attempt_support/vp6-context-coefficients-link-20261027/publication-audit.json)
  passes 39/39 bodies, three data rows, four exact EH graphs and converged-data
  enforcement across ConfigureContexts.cpp, Eva.cpp, ThreadClassLifecycle.cpp
  and thread.cpp. The post-rebase controls also pass against the incoming
  `e74410b373` reference. The batch audit is inconclusive: index `d1f046749a`
  predates outgoing base `094c0f30686`, and three objects lack current strict
  receipts (first Eva). No current-master provider or lost-byte verdict follows;
  carry these four paths to the next normal census/current-index check. The
  separate immutable comparison proves the 887-byte gain with zero losses.
  The first push was rejected because master advanced; only normal rebase/retry
  follows, without repeating any match record or full measurement.
- **MV probability repair publication (2026-10-27, `777a841df1`):**
  [the enforced batch audit](../../reverse/attempt_support/vp6-mv-table-link-20261027/publication-audit.json)
  passes 39/39 ordinary bodies, three data rows and four exact EH graphs across
  ConfigureMvEntropyDecoder.cpp and the additional Eva/thread control cohort.
  Its index `bf3dd31211` predates outgoing base `fb85f434697` and lacks the
  per-object consumer names required by the new loss-enforcement audit.
  The result is explicitly **linking unverified**, not clean: no current-master
  provider-change or lost-byte conclusion was reached. Preserve the source
  cohort for the next maintainer-published current-format census index;
  do not bypass enforcement or reclassify this as new linking credit.
- **Remaining / next check:** prove and make the actual include graph
  inventoryable under the existing gates, then repeat bounded strict preparation
  for all affected providers/consumers. A needed verifier repair follows the
  separate false-reject workflow. Do not substitute ordinary receipts for strict
  witnesses. Clearance and closed-strict confirmation remain pending; no census
  change is claimed for this inventory work.

- **Full publication (`98500fc347`, 2026-10-26):** the next normal push passes
  all 98,252 function rows, 2,218 data rows, reference checks and the no-op
  image. Its final EH audit retains 24 registered exceptions beside 11,876
  EXACT graphs. Converged-data enforcement passes for 22,962 sources with no
  second names or unjudged rows. The shadow link audit does not finish within
  the hook's limit and still compares against an older census index; it gives
  no new provider-change/lost-byte verdict. Prior strict-input prerequisites
  remain unclosed. [Receipt and follow-up](../../reverse/attempt_support/skirmish-game-info-data-owner-20261026.md#publication-and-following-file-cleanup).

- **Outgoing-batch audit follow-up (2026-10-26, published `0edae3a354`):**
  The new pre-push audit is [inconclusive for this batch](../../reverse/attempt_support/material-collector-anchor-cleanup-20261026.md#publication-audit-qualification):
  its index `f995f30157` predates outgoing base `a5cb102c02`, and nine objects
  lack strict current receipts. Normal publication verification passes 47
  functions, one data row and nine EH graphs. Read-only witnesses for the
  material collector and the first reported upstream particle-update unit
  confirm ordinary cache validity but no strict include inventory. No selected
  provider or lost-byte verdict was reached. Carry the batch into the next
  census with current input proof and an appropriate comparison baseline;
  no regression, clearance, false reject or new linking gain is inferred.

- **INI publication follow-up (2026-10-26, published `7d17532afb`):**
  [The expanded batch audit](../../reverse/attempt_support/ini-lookup-clean-throw-20261026.md#publication-audit-qualification)
  has strict reusable proofs for 135 explicitly prepared sources; the push
  hook verifies 1,375 functions, three data rows and 195 EXACT EH graphs over
  138 sources. Its only missing strict receipt is the additional Eva.cpp
  dependency. A focused supported preparation refuses unknown macro or
  parent-traversing include search roots. The index `763dc8759f` also predates
  outgoing base `0edae3a354`. No provider-change/lost-byte verdict, false reject
  or closure is inferred; complete include inventory and a suitable comparison
  baseline remain prerequisites.
  The subsequent `5994f7c59a` publication passes 85 functions and 12 EXACT EH
  graphs in three sources, but its audit reaches the same Eva.cpp prerequisite.
  The failed strict preparation is not relaunched without new include evidence.

- **Later bounded publication (`f8aefae21a`, 2026-10-26):**
  [All 54 changed objects have strict receipts](../../reverse/attempt_support/ini-publication-current-provider-audit-20261026.md).
  The full normal gate passes 98,252 functions and 2,216 data rows, followed by
  116 EXACT EH graphs. This scope excludes Eva and does not clear its inventory
  prerequisite. The audit completes with 89 retired objects, 287 provisional
  disappeared-provider reports and 30 possible-loss lines against the older
  `763dc8759f` index. No aggregate loss, global clearance or census gain follows.

2026-11-04: ScreenFilterRva000FC63DSet.cpp ShaderClass adoption now reaches the inactive `Ole2.h`/`macname1.h` inventory blocker after an unused-macro trial; trial reverted, no debt retired ([evidence](../../reverse/attempt_support/screenfilter-link-header-20261104.md)).
