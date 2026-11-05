### LINK-007: incomplete data ownership beyond clean symbol resolution

**Status: Open; scoped storage repairs verified. Updated: 2026-10-28.**

- **Module secondary-table storage (2026-10-28, base `7c98b18b59`):**
  [The two-source storage repair](../../reverse/attempt_support/module-secondary-table-storage-20261028-codex.md)
  replaces two integer stand-ins at RVA 0x0086157C with one complete table
  in Rva004DF324Dtor.cpp and an external reference in Rva004DF418Finish.cpp.
  The existing `_s_10` name is retained; all three slots name existing rowed
  functions. Six affected code rows, the 12-byte table and the constructor EH
  graph verify; the owning tool retires one duplicate-data key. Paired ordinary
  previews preserve LINKS and 189 authored bytes. The staged batch audit is
  INCONCLUSIVE because index `14dc3d2467` predates the base and lacks consumer
  names. Carry this scope to the next census. The separate folded table at
  RVA 0x007EFF90 and class identity remain prerequisites; no census or runtime
  gain is claimed.
  The normal hook for `ac22442be5` also reports the unchanged constructor
  funclet `uw_007917c3` targeting the 0x00268AFF forwarder through a member
  destructor name pinned to 0x00268902. Its member-lifetime identity needs
  separate reconciliation with PoolMemberRelease.cpp and other callers;
  byte/EH acceptance and the data retirement do not clear that shadow finding.

- **Shared random-seed storage (2026-10-28, control `87c6af16d4`):**
  [The seven-source binding repair](../../reverse/attempt_support/random-seed-storage-20261028-codex.md)
  exposes each existing seed owner under its unchanged C symbol and replaces
  seven duplicate arrays with declarations. All 12 code rows and 72 initialized
  seed bytes verify; current objects have one definition per seed and both data
  checks pass. The owning retirement tool removes seven registered keys from
  six sources. Three generated inventory rows now report one owner each.
  Paired ordinary previews retain 7/7 LINKS and 632 authored bytes against
  `14dc3d2467`. Original TU recovery and broader storage closure remain open;
  no census-linked, image-ownership or runtime gain is claimed.

- **E036 containment guard-index follow-up (2026-10-28, control `d67dec6909`):**
  [The scoped handoff](../../reverse/attempt_support/contain-e036-guard-data-index-20261028-codex.md)
  independently verifies twelve generated key/guard index rows after the E036
  clearer removal and accessor renames. The six sources retain 18/18 exact
  function rows, six EXACT EH graphs, zero data findings and paired LINKS
  previews (472 authored bytes, index `14dc3d2467`). Publication found that
  upstream `22ec257aa5` already retired all six keys; no additional six-key
  reduction is claimed. A further rebase picked up `978df9538b`'s HealContain
  guard-bound correction too, leaving no additional E036 index or retirement
  delta in this batch. Broader storage closure and census confirmation remain
  open; no runtime gain is claimed.

- **E038 update guard-index follow-up (2026-10-28, control `bd82c0156d2e`):**
  [The scoped current-owner check](../../reverse/attempt_support/update-e038-guard-data-index-20261028-codex.md)
  adopts nine changed generated key/guard index rows for six standalone update
  accessors after the earlier E038 clearer retirement and getter renames. All
  18 function rows, six literals and six parent EH graphs pass; both data checks
  report zero findings. Publication found that upstream `ed979c9e6b` already
  supplied all six source-key retirements and index changes; this check adds
  no further retirement. Ordinary previews retain 6/6 LINKS and 466 authored
  bytes against index `73061d9452`. Broader E038 storage closure and census
  confirmation remain open; no new linked-byte or image-ownership gain is claimed.

- **FX default-module guard index follow-up (2026-10-27, control `38e60a3ba930`):**
  [The current-owner check](../../reverse/attempt_support/fx-default-guard-data-index-20261027-codex.md)
  refreshes twelve generated guard-index rows left stale by the earlier
  standalone-clearer retirement. All 72 function rows and twelve parent EH
  graphs verify; both data checks pass with zero findings. The owning
  retirement tool removes all twelve source keys. Ordinary previews retain
  LINKS and 1,900 authored bytes against index `73061d9452`. This clears
  FXParticleSystemDefaults.cpp's registered data debt; broader storage closure
  and census confirmation remain open. No new linked-byte gain is claimed.

- **Shader filter storage and stale shutdown debt (2026-10-27, control c5dc2d6968):**
  [The three-unit binding check](../../reverse/attempt_support/shader-filter-data-identity-20261027-codex.md)
  binds the merged manager's two free helpers to its existing protected
  `m_currentFilter` static and removes the duplicate anonymous integer at
  RVA 0x009E1F5C. All six native references now relocate to the same owner.
  Two generated index rows reflect current providers; the owning retirement
  tool removes ten shutdown keys and one manager key. All 23 rows, five data
  rows, four EH parents and both data-check modes pass. Shutdown and
  startRenderToTexture preserve ordinary-preview LINKS (367 and 378 authored
  bytes). The manager still encounters deleted merge-donor objects in index
  73061d9452 (LINK-122); its filter-state duplicate finding is gone, but the
  remaining preview is inconclusive. Recheck in the next normal census.
  Other provisional shader storage remains open; no census gain is claimed.

- **FESL secondary-vtable anchor ownership (2026-10-27, control `eb4237832a`):**
  [The two-unit binding check](../../reverse/attempt_support/fesl-secondary-data-20261027.md)
  removes the destructor's private anchor at RVA 0x008E3F08 by exposing the
  existing constructor-owned symbol with external C linkage. Both matched rows
  pass, all eight executable sections preserve their bytes, and both sources
  have zero data findings. The owning tool retires two destructor data keys.
  Paired ordinary previews preserve LINKS for 200 authored bytes against
  `bf3dd31211`; no new census gain is claimed. This clears duplicate storage
  and binding debt only: the existing four-byte placeholder still needs the
  complete native secondary vtable and reconciled class identity before full
  data ownership can be claimed.

- **StatusBitsUpgrade / WeaponBonusUpgrade guard cleanup (2026-10-27):**
  [Exact parent EH ownership](../../reverse/attempt_support/upgrade-guard-rollbacks-20261027-codex.md)
  replaces the last two synthetic standalone clearers with their parents'
  emitted funclets, preserving both 13-byte ranges. The empty clearer source
  and six address-global hatch occurrences are removed. Four generated
  key/guard index rows now name their current parents; the owning retirement
  tool removes two stale data-debt keys. All 10 rows, both EH graphs and both
  data checks pass. WeaponBonusUpgrade preserves ordinary-preview LINKS
  (118 authored bytes) against bf3dd31211. StatusBitsUpgrade's preview retains
  the census's removed StatusBitsUpgradeConstructor.cpp as strong definer and
  sole owner after consolidation commit 6ff5daca29; next-census confirmation
  remains pending. Its constructor is unchanged and byte-verifies. Broader
  class/data closure remains open; no census-linked gain is claimed.

- **Nine-slot module interface follow-up (2026-10-27, control `139e5e9393`):**
  [The complete table repair](../../reverse/attempt_support/module-update-interface-data-20261027-codexb5.md)
  replaces Rva00492402Ctor.cpp's scalar owner at RVA 0x0084DFD4 with its full
  nine-slot native table. ModuleUpdateDtors.cpp references that shared owner
  and removes its duplicate scalar. All 29 function rows and three data rows
  verify; both sources have zero data findings. The owning retirement tool
  removes the destructor source's two remaining registered keys. The ordinary
  current-object preview preserves LINKS for both units and their 909 authored
  bytes against bf3dd31211. This clears only the stated storage/debt subset;
  original interface identities, other provisional storage, strict dependency
  closure and census confirmation remain open. No new census-linked bytes or
  image-ownership receipt is claimed.

- **SpecialDisguiseUpdate interface storage (2026-10-27, control `fb85f43469`):**
  [The native-table repair](../../reverse/attempt_support/special-disguise-interface-data-20261027-codexb5.md)
  replaces two scalar dummy owners with complete four-slot and 47-slot
  pointer tables, preserving their provisional names and using existing code
  owners for every entry. The constructor now shares both tables; it and the
  destructor owner also share the existing nine-slot provider. All 30 function
  rows and three data rows verify. The owning tool retires four constructor
  data-identity keys with zero remaining constructor findings; the owner's
  separate `s_dummyDFD4` keys remain. The three-object ordinary preview
  preserves all 1,005 authored bytes against `bf3dd31211`. Original interface
  and folded-method identities, wider storage closure and census confirmation
  remain open; no new census-linked bytes or ownership receipt is claimed.

- **WW3D window/default-sort bindings (2026-10-27, `0054abc1930e`):**
  [Scoped owner verification](../../reverse/attempt_support/ww3d-window-sort-data-20261027-codexb4.md)
  binds the screenshot/window getter and default-list reset to the existing
  initialization unit's globals. All 36 cohort rows and both EH graphs pass;
  all 78 consumer executable sections retain their bytes. Data findings fall
  from ten to six, with none outside the register; the owning retirement tool
  removes two window-storage debt keys. The six Movie/PixelCenter keys remain.
  Ordinary previews preserve the init owner's LINKS and the consumer's existing
  stale-provider obstacles (LINK-017). Only scoped data-debt reduction is claimed;
  census and image-ownership confirmation remain pending.

- **AllowBannerSpawnUpgrade local-static index repair (2026-10-27, `dbce5d0f8e`):**
  [The current-owner check](../../reverse/attempt_support/banner-poolkey-data-retirement-20261027-codexb4.md)
  refreshes two generated index rows after the existing getter rename and
  standalone guard-clearer retirement. All four function rows, the literal
  and the parent EH graph verify. The owning tool retires one data-debt key
  with zero remaining findings; ordinary preview preserves LINKS at 113
  authored bytes against index `bf3dd31211`. This subset's index repair is
  verified; broader storage closure and census confirmation remain open.
  No new linked-byte or image-ownership gain is claimed.

- **Sorting-renderer alias cleanup (2026-10-27, control `25d156a07f`):**
  [The scoped verification and storage prerequisite](../../reverse/attempt_support/sorting-renderer-data-aliases-20261027-codexb4.md)
  replaces three data aliases with existing DX8Wrapper declarations and removes
  four alternatename occurrences. All 26 rows and the parent EH graph pass;
  all 77 non-label code symbols retain identical bytes. Ordinary previews
  preserve LINKS and 13,227 authored bytes against index `bf3dd31211`.
  The owning retirement tool refuses on five pre-existing outside-register
  findings: three static-storage duplicates with sortingrenderer.cpp and two
  list identities. All five original data-baseline keys remain. Next reconcile
  shared sorting storage and the native list owners before retrying retirement.
  Only hatch reduction is claimed; broader storage closure and census
  confirmation remain open.

  Update 2026-10-29 (ea153f2145): five scalar state values now have one external
  owner in sortingrenderer.cpp; all 20 initializer bytes and compiler sizes
  verify. Both changed units retain 37 rows; the restored list reader brings
  the checked scope to 52/52. Four static-storage findings disappear; the two
  list identities per renderer remain, and no baseline key is removed. A full
  list-sharing trial failed five rows and was restored. Reconcile its private
  alias/visibility contract or approved TU composition before retrying retirement.
  [Verified scalar storage and rejected list patch](../../reverse/attempt_support/sorting-renderer-shared-state-20261029-round2.md).
  Census and image-ownership confirmation remain pending.
  The outgoing gate passes 75 rows, but its batch-link audit remains
  INCONCLUSIVE: Eva.cpp and WWLib/thread.cpp lack reusable receipts, and
  strict bounded preparation refuses their untraceable include roots.
  Carry both additional consumers into the next normal census too.
  Update 2026-11-05: [existing-vptr owner casts](../../reverse/attempt_support/sorting-list-owner-cast-20261105-codexb/README.md) retain 10/11 bodies but fail Deinit even with local references; restored 11/11 plus five data rows. Full list backing and visibility still need reconciliation.

- **DetachableRiderBody local-static index repair (2026-10-27, `408c38abc0`):**
  [The current-owner check](../../reverse/attempt_support/detachable-rider-poolkey-data-retirement-20261027-codexb4.md)
  refreshes two generated data-index rows left stale by the existing method
  rename and guard-clearer retirement. The verified parent now owns both its
  cached key and compiler guard in the index. All three function rows and the
  parent EH graph pass; the owning tool retires one registered data-identity
  key with zero remaining source findings. The ordinary preview preserves
  LINKS (79 authored bytes) against index `bf3dd31211`. This subset's index
  repair is verified; broader data closure and census confirmation remain open.
  No new linked-byte or image-ownership gain is claimed.
  A shard-2 trial for the ctor and field-parse donors passed bytes and LinkGuard
  but was restored: `tu_ownership.py --staged` routes two EH rows to
  `ImmortalBody.cpp` and rejects private `ActiveBody`/`UpgradeMux` bodies.
  Resolve those routing and canonical-header prerequisites before retrying.
  [Checks and remaining blockers](../../reverse/attempt_support/consolidation-shard-2-2026-11-04-session5.md).

- **RiderChangeContain local-static index repair (2026-10-27, `67587e56fd`):**
  [The current-owner check](../../reverse/attempt_support/rider-poolkey-data-retirement-20261027-codexb4.md)
  refreshes two tool-generated data-index rows after the existing method rename
  and standalone guard-clearer retirement. The current parent owns its cached
  key and compiler rollback guard; all three function rows and the parent EH
  graph verify. The owning retirement tool removes one stale data-identity key
  with zero remaining source findings. Its ordinary preview preserves LINKS
  against index `bf3dd31211`; no new census gain is claimed. The broader
  consolidation remains blocked on private class views and native containment
  interfaces; no unchanged broad composition trial was repeated.

- **Draw cached-key index follow-up (2026-10-27, control `8b5a8a815e`):**
  [The current-object verification](../../reverse/attempt_support/draw-poolkey-data-index-20261027.md)
  refreshes twelve standalone draw getters' key/guard index entries after the
  already-landed guard cleanup and getter renames. All 36 function rows,
  twelve literals and twelve EH graphs pass. The owning tool retires twelve
  stale data-debt keys with zero source findings; ordinary previews preserve
  all twelve units' 946 authored bytes against index `bf3dd31211`. This is debt
  retirement only; no census or image-ownership gain is claimed. PropDraw's
  separate ModuleData/DrawModule prerequisites (LINK-102) remain open.

- **Special-power cached-key index follow-up (2026-10-27, control `afd6ba6febe2`):**
  [The current-object verification](../../reverse/attempt_support/specialpower-guard-data-index-20261027-codex.md)
  refreshes eight getters' generated key/guard index entries after the existing
  standalone clearer retirement and five getter renames. All 24 function rows,
  eight literals and eight EH graphs pass. The owning tool retires eight stale
  data-identity keys with zero source findings; ordinary previews preserve all
  eight units' 629 authored bytes against index `73061d9452`. This subset's
  index repair is verified; broader data closure and census confirmation remain
  open. No new census or image-ownership gain is claimed.

- **Update-module cached-key index follow-up (2026-10-27, control `b76477cafd`):**
  [The current-object verification](../../reverse/attempt_support/update-poolkey-data-index-20261027-codex.md)
  refreshes nineteen standalone update getters' key/guard index entries after
  the existing E039 guard-clearer retirement and getter renames. All 57 function
  rows, nineteen literals and nineteen EH graphs pass; enforced and converged
  data checks report zero findings. Ordinary previews preserve all nineteen
  units' 1,493 authored bytes against index `73061d9452`. The owning tool retires
  nineteen stale data keys. AssaultTransportAIUpdate's separately held unit and
  mixed sources stay outside this repair. Broader data closure and census
  confirmation remain open; no new census or ownership gain is claimed.

- **DX8Caps work-string ownership (2026-10-27, control `f3d49bea73`):**
  [The lifetime-preserving repair](../../reverse/attempt_support/dx8caps-work-string-ownership-20261027.md)
  binds cleanup `007B7070` to dx8caps.cpp's existing StringClass at `009EE938`,
  replacing the cleanup TU's unsigned placeholder and registering the real
  four-byte storage. All 932 cohort function rows and 22 data rows pass; the
  owning tool retires both DX8Caps data keys with zero remaining source findings.
  One address-global hatch key (three occurrences) retires. Ordinary previews
  preserve DX8Caps's 8,058 authored bytes and the cleanup TU's separate
  LargeGroupAudio provider prerequisite. Its other data findings remain open.
  This subset's storage and lifetime binding is verified; strict closure,
  census and image-ownership confirmation remain unclaimed.

- **Buffer-slot FVF table identity (2026-10-27, control `1710ea0aea`):**
  [The current-owner repair](../../reverse/attempt_support/buffer-slot-fvf-data-20261027-codexb4.md)
  replaces the slot allocator's private table with the existing unsigned-array
  owner in W3DBufferManager_ReAcquireResources.cpp. All sixteen cohort rows and
  both slot-unit EH graphs pass; all ten executable sections retain their bytes.
  The owning retirement tool removes one data-identity key with zero findings.
  Paired ordinary previews preserve all three sources' 1,268 authored bytes
  against index `bf3dd31211`. This subset's binding is verified; wider storage
  closure, census confirmation and image-ownership receipts remain unclaimed.

  Recovery batch audit (2026-10-27, outgoing base `e1a73387fd`): the push-hook
  dry run passes 70/70 function rows, two data rows and eight EXACT EH graphs
  across eight sources. The link batch audit is INCONCLUSIVE: its index is
  `bf3dd31211`, older than the outgoing base, and seven source objects lack
  current receipts (first Rva0025DDD2Float.cpp). Selected-provider and lost-byte
  conclusions are unavailable for this batch; carry this freshness scope into
  the next census. This does not extend the earlier paired-preview clearance.

- **Particle-editor loader ownership (2026-10-26, control `665f50f7cf`):**
  [The scoped repair](../../reverse/attempt_support/particle-editor-owner-20261026.md)
  replaces the cleanup TU's four-byte placeholder with a reference to the
  existing twelve-byte `TheFXParticleEditor` owner and registers its complete
  storage. All 950 affected function rows, 22 data rows and both EH graphs
  pass. The owning tool retires four stale ScriptEngine debug-DLL keys with
  zero findings in either ScriptEngine source. Thunk retirement remains
  refused on unrelated findings. Paired ordinary previews preserve the three
  clean initializer/ScriptEngine units; the thunk unit still requires the
  LargeGroupAudio storage provider omitted from this bounded control.
  No strict closure or census gain is claimed.

- **Dynamic vertex-buffer storage trial (2026-10-26, control `1429c156108`):**
  [The scoped handoff](../../reverse/attempt_support/dynamic-vertex-buffer-data-20261026.md)
  records five existing-owner extern trials blocked by changed constructor,
  destructor and sorting-allocator bytes. All failed edits were restored; the
  ten registered data keys remain. Retail TU and alias-contract reconciliation
  are still prerequisites. The separate SDK declaration cleanup preserves all
  46 rows, 14 EXACT EH graphs and every emitted code section/relocation.
  Ordinary preview against census index `5ce093a71a` retains all 6,860 bytes;
  no census gain or storage-ownership closure is claimed.
  The normal shadow identity warning on `uw_00765c90` is also reproduced in
  the saved control object: the local reference-count destructor's target
  00072892 already belongs to `RefCountClass::~RefCountClass`. That existing
  class-identity prerequisite remains open; no register key was added.

- **Texture-statistics scalar subset (2026-10-26, control `d831bc24031`):**
  [The scoped ownership repair](../../reverse/attempt_support/texture-statistics-data-20261026-bce2/readme.md)
  binds recording mode and seven reporting counters to their existing
  `statistics.cpp` owners, retiring sixteen data-register keys through the
  owning tool. All 51 cohort rows, four EH graphs and three strict preparation
  receipts pass; all 79 emitted code definitions retain their bytes and code
  references. Both consumers keep their 1,780 ordinary-preview bytes against
  index `47e030bafc`; the provider's existing findings are unchanged. The
  reporting-mode extern trial changed scheduling and was restored. Current-frame
  counters need the claimed reset provider; vector/handle/string storage needs
  full extent and initializer/teardown reconciliation. No family closure,
  census gain or image-ownership receipt is claimed; LINK-017 still applies.
  Its normal push gate also passes the automatically included Eva dependent
  (45/45 rows, seven EXACT EH graphs). The batch audit is inconclusive on the
  older index and Eva's missing strict receipt; bounded preparation refuses
  Eva's macro/parent-traversing include inventory, the LINK-008 prerequisite.
  No verifier or include-path change is made in this scalar repair.

  Follow-up (2026-10-27, control `83f299b390`): the reset provider and both
  consumers now share six current-frame counters through their existing
  data-ledger definitions. [Scoped evidence](../../reverse/attempt_support/texture-current-frame-data-20261027.md)
  records twelve owning-tool retirements, 31/31 matched rows, four EXACT EH
  graphs and all 58 executable sections unchanged in bytes and relocation
  names. Three strict preparation receipts pass; ordinary previews preserve
  all 2,502 authored bytes against `bf3dd31211`. Sharing record/change counters
  changes the recording parent's load ordering; both failed trials were
  restored. Those two counters and vector/handle/string lifetime ownership
  remain prerequisites. This clears only the six-counter binding subset,
  without family closure, census gain or an image-ownership claim.

  Reporting-counter follow-up (2026-10-28, control `c5dcd40bdf`):
  [the bounded two-unit repair](../../reverse/attempt_support/texture-report-counter-data-20261028.md)
  shares record/change counters between the reset owner and reporting consumer,
  retiring two reporting duplicate-def keys through the owning tool. All 21
  rows, both EH graphs and all 38 emitted executable sections retain their
  bytes and symbolic code references. Enforced data checking finds no new
  keys. The recording function's known alias/load blocker and its private
  counters remain; reporting mode and lifetime storage also remain open.
  Census index `73061d9452` predates this control revision; no family closure,
  new census-linked bytes or image-ownership result is claimed.

- **Evidence / scope:** the [linking handoff](../../reverse/attempt_support/link-seat-20261025-final.md)
  identifies missing shader/filter root objects and the unowned 52-byte
  ScreenBWFilter group at `0x009B5B54`. Complete native objects and vtables are
  prerequisites; a symbol alone does not prove their storage or relocations.
- **Completed:** the [VP6 storage repair](../../reverse/attempt_support/vp6-idct-storage-link-20261025/readme.md)
  proves the table's 548-byte allocation and records a fixed-comparison
  **17,413-byte placed closed-strict gain**. Those units already counted as
  linked in the headline. This is scoped closure evidence, not a new headline
  measurement of master; follow that lane's clean-room rules.
- **Filter adjacency repaired (2026-10-25):** the
  [modifier/pointer ownership proof](../../reverse/attempt_support/vp6-filter-adjacency-link-20261025/readme.md)
  preserves native `g_bfmeDeringModifiers+0x100 == g_bfmeFilterLimit` in one
  verified 260-byte owner. The six-unit control passes 13/13 bodies (5,862
  bytes); all 13 affected data relocations keep their native targets. The
  authoritative fixed comparison `026edbcbcc` to `a7637e3b22` changes exactly
  four of 23,460 canonical objects and gains **2,369 placed closed-strict
  bytes** in seven rows, with no losses. All seven former unit failures are
  self-strict; six are also closed-strict, together with the FilterBlock2d
  caller. The independent closure report reproduces all 98,202 status rows.
  This is scoped closure evidence, not a new census headline.
- **Scaler coefficients repaired (2026-10-25, inspected `d0c913e6dde`):**
  [the six-scaler ownership repair](../../reverse/attempt_support/vp6-scale-tables-link-20261025/readme.md)
  gives the five shared native coefficient addresses one owner each instead of
  22 private copies. Normal controls pass 6/6 bodies (1,739 bytes), all five
  eight-byte data owners and all 64 native DIR32 targets. The authoritative
  fixed comparison `a7637e3b22` to `7124e772c5` gains **1,739 placed
  closed-strict bytes** in the six scalers, with zero losses. All five datum
  nodes pass; exactly five of 23,460 canonical objects change. Independent
  reconstruction reproduces all 98,202 status rows and the 1,700,931-byte
  credit. This scoped
  scaler repair is **cleared in the fixed comparison**; no current census
  headline change is claimed. Native alignment padding remains unowned.
- **Generic filter scratch cleared in the fixed comparison (2026-10-26,
  source base `684d224e847`):**
  [the scratch ownership proof](../../reverse/attempt_support/vp6-filter-scratch-link-20261025/readme.md)
  replaces two four-byte scalar claims with the independently bounded
  352-byte buffer at DFDA58; its second-pass row is buffer+32, not a second
  datum. All 5 control bodies (821 bytes), the complete data owner and all
  6 native DIR32 targets pass. A plain zero-based eight-column loop preserves
  native pointer induction after the correct array declaration. The authoritative
  comparison `7124e772c5` to `f012cbcc5e` gains **2,747 placed closed-strict
  bytes** in five rows, with zero losses. It clears both bilinear bodies, their
  two filter callers and the unchanged debug row's scratch/counter forward-map
  conflict. Exactly two of 23,460 canonical objects change. Independent closure
  reconstruction reproduces all 98,202 rows and the 1,703,678-byte credit.
  The interrupted first run was preserved; the resumed process exits zero after
  2,992 seconds with no final drift or new unresolved references. Publication
  controls also pass against the rebased reference inputs. This is scoped closure
  evidence, not a new current-master census headline.
- **Quantizer endpoint layout cleared in the fixed comparison (2026-10-26,
  source base `0044debbb5`):** the
  [native layout proof](../../reverse/attempt_support/vp6-quantizer-layout-link-20261026/readme.md)
  puts the existing 256-byte scan table directly after the correction array,
  preserving the biased correction+260 end comparison at BD8464. The final
  order keeps the scan table at its previous section offset 272 and its own
  biased end at 532, with unchanged contribution size and alignment. Normal
  controls pass the complete 945-byte parent, all 16 initializers and all 26
  native data references; the expanded two-body control also preserves the
  unchanged 185-byte quantize.cpp caller. The authoritative comparison
  `f012cbcc5e` to `d8d65b08cc` gains **1,538 placed closed-strict bytes** in
  VP6_init_quantizer (945), VP6_UpdateQC (93) and VP6_quantize_c (500), with
  zero losses. Exactly one of 23,460 canonical objects changes. Independent
  reconstruction reproduces all 98,202 rows and the 1,705,216-byte credit;
  25 roots are additionally re-proved. The process exits zero after 3,626
  seconds with no final drift or new unresolved references. The unchanged
  quantize.cpp caller loses its old backward-map failure but still has the
  forward-map failure on scan+260 toward the separate IdentityIndex owner;
  its actual witness is retained. No new name, pin, header or data value is
  introduced. This subset is cleared in the fixed comparison; whole-chain
  clearance and a current-master census remain pending (LINK-008/017).
- **Huffman-table extent repair (2026-10-27, control `9d6c94a6fe`):** the
  [native table-layout proof](../../reverse/attempt_support/vp6-huff-table-layout-link-20261027/readme.md)
  places the existing 48-byte token-minimum definition directly before its
  native band-map successor. This removes the four mismatching zero bytes
  from the inferred minimum contribution; the band's new four-byte tail
  agrees with native padding. All three complete data contributions, 440
  initializer bytes and four native DIR32 targets are verified. Normal
  controls retain all three bodies (1,829 bytes). Source work finalized at
  t=8 minutes with no new coverage, name, pin, value or source-path change.
  The authoritative fixed comparison `d8d65b08cc` to `dc81d055af` gains
  **2,877 placed closed-strict bytes** in 3 rows, with zero losses.
  Exactly one of 23,460 canonical objects changes; independent reconstruction
  reproduces all 98,202 rows and the 1,708,093-byte credit, with 25 forced roots.
  The process exits zero after 3471 seconds, with zero final drift or new
  unresolved references. This subset is cleared in the fixed comparison;
  no current-master census or runtime gain is claimed (LINK-008/017).
- **Context coefficient initialization (2026-10-27, control `fd9943a126`):**
  [the native coefficient proof](../../reverse/attempt_support/vp6-context-coefficients-link-20261027/readme.md)
  replaces the existing owner's zero-filled storage with its fifteen native
  slope/bias pairs. All 120 initialized bytes and eleven data-reference targets
  agree with retail; the same symbol, type and bound are retained. Normal
  controls pass the 331-byte context function and its unchanged 556-byte
  entropy-decoder caller, plus six data rows. Source work finalized at t=8
  minutes with no new function coverage, name, pin or alias. The authoritative
  fixed comparison `dc81d055af` to `a150087a1c` gains **887 placed closed-strict
  bytes** in 2 rows, with zero losses. Exactly one of 23,460 canonical objects
  changes; independent reconstruction reproduces all 98,202 rows and the
  1,708,980-byte credit, with 25 additional forced roots. The process exits
  zero after 3437 seconds, with zero final drift or new unresolved references.
  This coefficient subset is cleared in the fixed comparison. Other motion-vector
  storage prerequisites and current-master census confirmation remain open.
- **MV update-table bytes and endpoint handoff (2026-10-27, `b8e318a126`):**
  [the native/coff proof](../../reverse/attempt_support/vp6-mv-table-link-20261027/readme.md)
  corrects two copied probability values (flat 13: 250 -> 254; flat 31:
  254 -> 251), restoring all 34 native bytes on the same owner. The complete
  331-byte function and six data operands remain exact; non-debug allocation
  and relocation layout is unchanged. End comparisons at table+35/+36/+43
  still require native padding/defaultMvShort provider reconciliation.
  That table's decodembs.cpp scope was held by davidrazidlo-claude and was not
  edited. The stale TU map is not move approval. Ordinary preview against
  `bf3dd31211` preserves 330 -> 330 bytes; no additional strict credit,
  current-master census gain or whole-MV closure is claimed. Source work
  finalized at t=13 minutes. Resume through approved storage ownership without
  artificial prefixes, extra rows, new pins or verifier exceptions.
- **LargeGroupAudio key-tree follow-up (2026-10-26, `e5c5a1787c`):**
  [the whole key-list repair](../../reverse/attempt_support/largegroup-keylist-erase-link-20261026.md)
  preserves its 191-byte parent and verifies all 15 rows of the native erase
  provider. Calling that existing owner removes the nonretail COMDAT and
  wrong selected-copy blockers; current identity has four owner bindings and
  zero wrong bindings. Ordinary preview remains 0 -> 0 against `f995f30157`
  because `g_lgaKeyRecords` is unresolved. Its address has two separate
  four-byte definitions under other spellings, plus an initializer and cleanup
  that need one complete storage owner. Prove the extent and reconcile all
  consumers before clearing this additional storage subset; no census gain
  or register retirement is claimed.
- **Key-tree storage follow-up (2026-10-26, after `5611c263e4`):**
  [the six-source ownership repair](../../reverse/attempt_support/largegroup-keylist-storage-link-20261026.md)
  replaces those split allocations with one verified twelve-byte backing store
  under the existing `g_lgaKeyRecords` identifier. The native initializer and
  cleanup use the same symbol as all readers. All 938 function rows, the 23
  existing data rows, the new data row and five EH graphs pass. The six-object
  ordinary preview is 5/6 clean, retaining 10,184 bytes and adding KeyList's
  191 authored bytes; AddKey retains an unrelated unresolved vector resize.
  The owning tool retires two data keys, and the hatch tool retires five
  address-global occurrences. Thunk retirement remains refused on other
  findings. This storage subset is cleared in the stated current-object
  scope; full convergence, strict closure and census confirmation are unclaimed.
- **Key insertion resize follow-up (2026-10-26, after `d453de7462`):**
  The same evidence records the direct native resize-owner call. AddKey's four
  rows (324 bytes), data row and two EH graphs remain exact; the final six-unit
  ordinary preview is 6/6 clean, 10,184 -> 10,689 authored bytes (505 gained).
  This clears the stated ordinary-preview cohort, not its strict or census
  status. Identity retirement still refuses a separate AsciiString-destructor
  binding in the static accessor; its existing identity key is retained.
- **Canonical string follow-up (2026-10-26, after `3a6521d528`):**
  AddKey now uses the registered BFME 2 string header. All four rows, its data
  row, two EH graphs and the six-unit ordinary preview are preserved. The
  owning tool removes its registered destructor-binding key and no longer
  finds the separate accessor-destructor issue. One insert-unique key at
  `0x003ED8B1` remains; no class-wide identity clearance is claimed.
- **Native insert follow-up (2026-10-26, after `97e5e68584`):**
  The same handoff proves the existing record-tree owner at `0x003ED8B1`
  and the caller's scalar offsets. AddKey now uses that specialization;
  its four rows, data row and two EH graphs remain exact. The owning tool
  retires its final identity key with zero remaining source findings. The
  six-unit ordinary preview remains 6/6 clean at 10,184 -> 10,689 bytes.
  No wider class identity, strict closure or census clearance is implied.
- **Stale streak-clear data keys (2026-10-26, `2edd747b85`):**
  [Whole-file verification](../../reverse/attempt_support/streak-clear-data-retirement-20261026.md)
  confirms `Rva0012641FClear.cpp` already uses the two existing pointer globals
  since `0bb6eb81be`. Three wrapper/owner rows and both four-byte data rows
  pass; the owning tool retires two obsolete names with zero remaining source
  findings. The wrapper's ordinary preview remains 20 -> 20 bytes. This is
  stale debt retirement only, with no new binding or census gain. Upstream
  `462ffdd1f8` subsequently retired the same two keys; the rebase preserves its
  register and does not count this historical work again in the current PR.
- **Remaining / next check:** shader/filter root-object ownership remains
  open. The [current witnesses](../../reverse/attempt_support/vp6-filter-scratch-link-20261025/remaining-witnesses.json)
  show InitPostProcessing, PostProcMachineSpecificConfig and
  UtilMachineSpecificConfig still closure-blocked through GetProcessorFlags and
  CpuProbe_VendorSse2: the selected `__except_handler3` import twin lacks a
  confirmed map/object definition. UtilMachineSpecificConfig's previous scratch
  witness is cleared. Prove the selected import provider and remaining native
  storage relationships; do not retry the cleared
  coefficient or filter-pointer splits. Verify storage
  extents, initial bytes, relocations and dependent closure through the existing
  gates. Family clearance and later census confirmation remain pending.
  Preserve the no-stubs/no-`/FORCE` runtime exit requirements.

- **Filter-root current-input audit (2026-10-26, inspected `896af21680`, index `d1f046749a`):** `build/link-report.md` and `build/link-worker-20261026/` confirms `W3DShaderManagerScreenBWFilterInit.cpp` remains unresolved on `screenBWFilter` and `screenBWFilterDOT3`; native DIR32 operands select VA `0x00DB5B54` and `0x00DB5B5C`. `Rva000FDCD7Get.cpp` still selects VA `0x00DB5BD4` for `W3DFilters[9]`. The old 144-byte inferred interval beginning at `0x009B5B88` is not storage proof for that filter: the current data register owns only the four-byte swap counter at its start. No artificial storage or alias is introduced. Next check: independently bound and recover complete filter objects and their initialized vtables before registering their ownership. Clearance and census confirmation remain pending.
  Rechecked 2026-10-30 at `5e645d88d7` against index `12b9e7a7c0`
  (10:11 UTC): ordinary current-object preview still reports 0/101 authored
  bytes and exactly the two missing globals above. The declaration scan passes;
  no source or storage change was attempted. The complete-object/vtable
  prerequisite remains open; this is an unchanged blocker, not a new regression.

  Native-object follow-up (2026-11-01, control `59e3f8f825`, index
  `0d24c60eef`): the [target-byte and provider inventory](../../reverse/attempt_support/bw-filter-objects-20261101/readme.md)
  bounds two candidate eight-byte objects, their separate seven-slot tables
  and the already-rowed 13-byte constructors. The current whole-file preview
  still reports 0/101 bytes with exactly the two global providers missing.
  Several table members and both constructors currently belong to different
  neutral class views; trivial slots also share existing ICF owners. Reconcile
  those identities and the four-word BFME 2 post-render ABI before defining
  complete native globals and verifying all fourteen table relocations. No
  incomplete class object, alias, pin or data ownership was added. This records
  a concrete prerequisite inventory, without clearance or census credit.

**Assigned table-data audit (2026-10-26, inspected `2a45addda1806342ac5c52757f63be902dcd428e`):** `Rva002D22CAInit.cpp` remains blocked by its seven existing address-named table declarations. The matched row's DIR32 references agree with `reverse/data_ledger.csv` at RVAs 0x009BC890, 0x009BC998, 0x009BC9C0, 0x009BCAC8, 0x009BCBAC, 0x009BCBC4 and 0x009BCBDC, but every ledger entry is unowned. `build/link-worker-w6/row-reference-witnesses.log` records the individual native references. No alternative existing global definer was found and no data definition or hatch was added. Next check: recover and admit those table owners through the data lane. Clearance and census confirmation remain pending.

**Split GameSpy pinger data repair (2026-10-27, inspected `67098f8d8b`, index
`bf3dd31211`):** peerPing.c and pingerMain.c now share eight globals through
their existing data-ledger definitions instead of defining private duplicates.
All 19 rows remain exact, both ordinary previews remain LINKS (2,770 authored
bytes total), and `repair_queue.py retire data` removes eight duplicate-definition
keys. The [scoped evidence](../../reverse/attempt_support/gamespy-pinger-shared-data-20261027.md)
records the retained owners and two reversed piSettingData trials. Its remaining
duplicate changes store scheduling in piProcessTrip2 when made extern; the four
piNextID keys need reconciliation with RvaSmallLeafTransfers.cpp's existing union
owner. Those five keys remain registered. Clearance is limited to the eight
duplicate-definition keys; no census or image-ownership gain is claimed.

**Pinger compiler-contract follow-up (2026-10-27, `bb2acc05b2`):** the
[additional alias trials](../../reverse/attempt_support/pinger-alias-contract-20261027-codexb4.md)
retain no source change. VC7.1 rejects a restrict-qualified socket-address
parameter with C4235; an inline scalar-argument callback helper changes
piProcessTrip2's frame from 24 to 28 bytes and fails its byte check. Both
sources are restored and all 19 rows pass again. The existing mixed-width
counter owner and all five registered keys remain prerequisites. No new
clearance or linking gain is claimed.

**piNextID owner resolution (2026-10-27, `claude`):** the mixed-width counter
owner is pingerMain.c itself. Its unchanged static `piGetNextID` byte-matches
0x006B2150/29 in a probe compile (all three DIR32 operands select VA
0x00E0C0EC), and both `_piGetNextID` and `_piNextID` are COFF static symbols
there, so RvaSmallLeafTransfers.cpp's `Rva006B2150` and its `g_00E0C0EC` union
are a second copy of SDK code. The repoint is blocked by tooling: add_match's
one-name rule sees peer's global `_piGetNextID` at 0x006A0010, and
`ledger_io.same_function_name` scopes only `_$E<n>` and funclet labels per TU.
Recorded as a false reject in `reverse/re_attempts.log`. Next check (tooling
seat): admit TU-scoped C static function names, repoint the row, delete the
union owner and retire the four piNextID keys. No clearance is claimed.

**Pinger decoder follow-up (2026-11-05):** [Additional volatile-copy and pointer-expression trials](../../reverse/attempt_support/pinger-decoder-alias-boundary-20261105-codex4.md) restore the alternating payload copy under `/Ow` but still change pointer scheduling and magic validation; whole-input volatility changes the caller too. All trials restored, 19/19 rows exact; next check must preserve those decoder details or establish approved TU placement. No keys retired.

**piNextID extern trial (2026-11-04, `claude`):** making pingerMain.c's counter
external (peerPing.c extern, Rva006B2150 through a view) breaks `_pingerPing`
and `_piProcessTrip1`: retail's dword counter load needs a TU-static `uint16`.
Next step is therefore the pinger TU approval and merge of peerPing.c's pinger
rows, plus the TU-scoped C-static row names above (`re_attempts.log`, `_piNextID`
0x00A0C0EC). Reverted; no clearance is claimed.

#### Debug dialog flag ownership follow-up (2026-10-28)

The shared external-flag trial remains blocked at base `2451819902`.
Line-first formatting snapshots, an inline formatter and an aggregate snapshot
preserve CrashDone's size and flag-store position but change four register
encoding bytes. All trials were reverted; the paired original sources pass
2/2 rows and retain their initial 2,078 authored ordinary-preview bytes.
The duplicate-def and wrong-name keys remain. [Trial details and the banking refusal](../../reverse/attempt_support/debug-dialog-data-20261028-codexb.md).
Next: reconcile the approved Debug TU or a new argument-evaluation model;
no source, debt or census gain is claimed for this attempt.

The default GameEngineInit pick still reports the documented LINK-132
Object-pointer vector-destructor selection blocker and an unresolved
TheThreatFinderManager name against index `41c28839bf`. No source edit or
repeated AIBuilder trial was made; the claim was released.

At base `1f13ae3586`, a refreshed preview against index `d92e7e6635`
still reports the selected non-retail `vector<Object *>` destructor as the
sole blocker for GameEngineInit (9,424 authored bytes). The earlier provider
trials were not repeated. Provider reconciliation or an approved census rule
decision remains necessary; census clearance is not claimed.

**Pinger flag alias boundary (2026-11-04):** `/Ow` permits the shared flag with 18/19 rows exact; only `_piBytesToPing` scheduling remains. All trials restored and 19/19 reverified; [evidence and next check](../../reverse/attempt_support/pinger-settingdata-alias-flags-20261104-codexb.md).
