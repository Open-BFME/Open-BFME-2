# Linking obstacle register

Required reading before selecting linking work; required updates with repairs
and attempt handoffs, and before ending a linking pass. Workflow:
[linking.md](linking.md#shared-obstacle-register). This is a shared handoff,
not an authoritative progress counter. Claim work through the normal claim tool.

Read the [linking target checklist](linking_targets.md) alongside this register
when selecting work. Update affected target rows with results, evidence and
remaining dependencies in the repair or handoff commit.

## Maintaining this register

- Update only the entries your evidence affects. Record the date, source revision,
  affected symbols/units, work completed, verification result, remaining blockers
  and next useful check. Link a repair commit or tracked attempt evidence. For
  previews, identify the index revision, current-input checks and measured scope;
  put detailed receipts in the repair's normal evidence location.
- Reuse an existing ID for the same cause; give a new cause the next unused
  `LINK-NNN` ID. If a broad entry is only partly repaired, keep it open and list
  the repaired subset or split off a narrower entry. Do not mark a whole family
  cleared because one consumer links.
- Use **Open** for an unresolved lead, **Blocked** with a named prerequisite,
  **Repair landed / awaiting verification** for an unconfirmed repair, and
  **Cleared** only with verification of the stated scope against current inputs.
  State separately whether a later census confirms it. A preview clearance does
  not change the headline; a source edit or provider's existence alone is not
  proof that its consumers now link.
- Keep cleared entries and their evidence. Reopen an entry with the new failing
  revision and evidence if it regresses. Preserve other agents' updates when
  rebasing. Do not repeat an unchanged failed trial without new evidence or a
  resolved prerequisite.

For a new entry, use this shape:

```text
### LINK-NNN: concrete cause and affected scope
Status: Open. Updated: YYYY-MM-DD; inspected revision: <SHA>.
Evidence / affected units: <symbols, files, tracked evidence, index revision>.
Completed: <repair or attempt, commit and measured result, or none yet>.
Remaining / next check: <specific dependency and how to verify it>.
Clearance: <scope, current-input verification and evidence, or pending>.
Census confirmation: <published measurement revision, or awaiting / not claimed>.
```

## Baseline for the initial entries

Seeded on **2026-10-25** from the investigation at `76efac458e`.
The historical census measured `d2636bb381` at **2026-10-25 09:42 UTC**;
its status was published by `b78c9ed16e`. It records **7,343,016 / 7,512,658
executable-game bytes (97.7419%)**, leaving 169,642 bytes and 385 blocked units.
Use the published status: the status file inside the measured commit itself
describes the preceding census.

The official provider index inspected had provider facts updated to `51fde01dff`
at **2026-10-25 13:53 UTC**, but retained the 09:42 census's blocker lists.
Index SHA-256:
`7225d4beb4d607e264bb010fef0dc8fdcb36d15b684d16fc7e654ee776a037ed`.
Thus the counts below are historical leads, not freshly measured failures on
master. Recheck current inputs before choosing work. The register's initial
entries claim no new census or current-master compile result.

Start by verifying landed repairs, then reconcile container identities and
shared headers/providers in coherent batches. Do not total overlapping units,
authored-byte previews or commit-title gains into a projected headline.

## Obstacles and handoffs

### LINK-001: landed repairs still appear in the historical census

**Status: Repair landed / awaiting verification. Updated: 2026-10-25.**

- **Evidence / scope:** the deleting destructor
  `??_EWeightInfoStruct@NamedPivotMapClass@@QAEPAXI@Z` blocked 34 graphics units;
  it was the sole blocker in 30, holding 45,189 authored nonpadding bytes
  (about 45 KB). The inspected provider index now has 33 retail-correct copies
  with identical digests. Provider evidence alone does not remeasure consumers.
- **Verified graphics subset (2026-10-25, `91fe970939`):**
  [the bounded verification](../reverse/attempt_support/weightinfo-verification-20261025/readme.md)
  passes 404/404 matched rows across all 34 units. Current-object inspection
  confirms 33 retail-correct copies and a correct selected body; W3DScene
  intentionally stopped emitting the incorrect copy. No destructor blocker
  remains in these 34 objects. The ordinary preview links all 30 historical
  sole-blocker units, covering **45,204 authored nonpadding bytes**. The other
  four retain unrelated dependencies, listed in that evidence. This graphics
  subset is **cleared in the bounded ordinary-preview scope**; census and
  closed-strict confirmation remain unclaimed. Strict receipt prerequisites
  found during verification are tracked separately as LINK-008.
- **Completed:** `51fde01dff` removed W3DScene's nonretail emission; its source
  was unchanged at investigation time. The earlier graphics gains overlap.
  Other landed repairs also have scoped evidence:
  [PlayerTemplate bucket copy](../reverse/attempt_support/object476-copy-link-20261025/readme.md),
  [record helpers](../reverse/attempt_support/asciistring-record-link-20261025/readme.md)
  and [narrow strings](../reverse/attempt_support/narrow-string-selective-link-20261025.md).
  Several historical `_Destroy` names already resolve to defined providers.
- **Remaining / next check:** check the next normal maintainer census for the
  verified graphics subset. Verify the other landed repair families' current
  consumers and providers before attempting another repair.
  Do not reopen a repaired name solely because `link_rank.py` still lists it.
- **Range-worker current-input check (2026-10-25, after `e302344089`):**
  [the paired range-worker proof](../reverse/attempt_support/range-destroy-link-20261025/readme.md)
  verifies 71/71 rows, 7 EXACT exception graphs and three strict receipts.
  The provider and both deferred-vector consumer files already preview cleanly
  with current alias handling, despite the historical unresolved names. One
  real whole-body C++ instantiation replaces its old alias and retires one
  hatch key; the paired before/after preview preserves all 2,978 authored
  bytes and claims no new linking gain. The other alias remains debt.
- **Stale string identity keys retired (2026-10-26, `fce2c6327a`):**
  [the forward-range caller check](../reverse/attempt_support/string-range-identity-retirement-20261026.md)
  confirms BfmeConv1486.cpp, BfmeConv1428.cpp and BfmeConv1438.cpp already bind
  the recovered insertion owner. All three whole callers remain exact
  (285, 42 and 47 bytes). After normal refresh of two newly consolidated
  upstream objects, the owning identity tool retires three stale keys, with
  zero remaining findings for each source. These callers are already
  census-linked; their existing code and the provider's separate closure
  work are unchanged. No C++ conversion or new linked-byte gain is claimed.
- **Stale vector-clear identity key retired (2026-10-26, `d75f6cf62f`):**
  [the overflow caller check](../reverse/attempt_support/vector-overflow-identity-retirement-20261026.md)
  verifies the unchanged 178-byte caller at 0x0048D48F and 75 rows in its
  construction/clear/destruction providers. The current scan classifies its
  0x000C060A call as a fold, with zero wrong bindings. The owning tool retires
  one stale identity key; ordinary preview is already clean (178 -> 178 bytes).
  No application identity or new linked-byte gain is claimed.
  After upstream `b85e569cee` moves the body to FlammableUpdate.cpp, the
  complete eight-row unit is reverified and the owning retirement tool
  removes the transferred key at its new path; one separate finding remains.
- **Clearance / census confirmation:** graphics ordinary-preview scope cleared
  at the revision above; other families and census confirmation remain pending.
  Keep individual repair previews separate from later census confirmation.
- **Sol prerequisite freshness handoff (2026-10-26, `73ffc391c4`):**
  [Radar, particle-bone and unit-crate receiver evidence](../reverse/attempt_support/consolidation-sol-prerequisites-20261026-codex.md)
  preserves matched bytes and existing object/binding facts; the outgoing gate
  passed 39 rows and eight EXACT EH graphs across eight sources. The new batch
  audit is **inconclusive**, not a clearance: provider index `51fde01dff` predates
  outgoing base `6cdb77c875`, and all eight objects lack accepted strict-current
  receipts (first: AnimatedParticleSysBoneClientUpdate.cpp). It returned before
  selected-provider/lost-byte analysis. No lost bytes were measured. Next check:
  claim the affected sources and use supported bounded `link_check.py
  --prepare-current` to establish strict receipts, diagnose any inventory
  refusals along LINK-008, then carry confirmation into the next normal census.
  No maintainer-only measurement or repeated batch audit was started here.

### LINK-002: distinct container element identities and exception contracts

**Status: Open. Updated: 2026-10-25.**

- **Evidence / scope:** equal-sized `BfmePod28` / `BfmePod32` views conflate
  native types with different constructors and copy operations. The
  [element-split handoff](../reverse/attempt_support/pod-element-split-20261023/readme.md)
  names the provider and consumers: the vector at `0x00541434` calls copy helper
  `0x005411C8`, while its current spelling resolves to `0x00215F38`; the vector
  at `0x0052C823` calls `0x0052C27E`, not `0x00421D28`.
- **Completed / failed trials:** the
  [vector exception-contract bank](../reverse/attempt_support/vector-587c40-construct-link-20261025/readme.md)
  shows that a throwing copy declaration preserves the 189-byte parent but emits
  the wrong helper; `throw()` fixes that helper while breaking the parent.
  Suppressing the control overflow definition also broke another matched row.
  These trials were restored; they are not repairs.
- **Remaining / next check:** reconcile element identity, native callees,
  ownership, shared declarations and EH contracts together. Verify every
  affected provider, consumer and emitted copy. Size equality and a renamed
  template do not prove a shared native type. Clearance and census confirmation
  remain pending.
- **AerialPathfinder concrete candidate (2026-10-25, `27b23d675b`):**
  [the native-list bank](../reverse/attempt_support/aerial-native-list-link-20261025/readme.md)
  identifies a conflation between the constructor's `BfmePod8` destructor pin
  at 002FECBC and this family's actual cleanup at 004EC395. Private adoption
  of the canonical subsystem base and the target query's polygon/height entry
  preserves the 75/59/28-byte parent/wrapper bodies and both exact EH graphs.
  No production repair was applied: required helper addresses 0014F3C4 and
  004EC395 were reserved by other workers. Resume through normal folded-body
  admission and current-input provider/consumer gates when claims permit;
  preserve the shared pin and do not equate unrelated equal-sized records.

### LINK-003: residual Zero Hour memory-pool interfaces

**Status: Open. Updated: 2026-10-25.**

- **Evidence / scope:** historical blockers include `MemoryPool::freeBlock`
  in 21 units and `allocateBlockImplementation` in 15; these sets overlap and
  predate later repairs. The inspected provider index has neither operation.
- **Completed:** `d7d2a0c653` changed the sweep `GameMemory.h` to BFME 2's native
  virtual destruction / global delete and global allocation contract. BFME 1
  and ZH interfaces remain reference leads, not proof of BFME 2 behavior.
- **Remaining / next check:** find residual imported declarations and callers,
  prove their native BFME 2 contracts, and repair the class/header family.
  [Scripts.cpp's handoff](../reverse/attempt_support/network-byte-setter-astra-s2-20261023/readme.md)
  records pool calls alongside ScriptGroup/OrCondition, signed-byte and parser
  ABI blockers. Removing a pool call does not clear those other dependencies.
  Verify the affected consumers together; clearance and census confirmation
  remain pending.

### LINK-004: missing or incompatible shared providers and declarations

**Status: Open. Updated: 2026-10-26.**

- **SpecialPowerCreate declaration prerequisite (2026-10-26):**
  [the bounded pool/callback repair](../reverse/attempt_support/consolidation-specialpowercreate-view-20261026-codex.md)
  shares the existing measured callback receiver with the pool-key consumer.
  Both strict-current objects retain every non-debug section, definition and
  code/data reference fact. Normal composition now accepts both donors, three
  rows / 136 bytes instead of only the pool's two rows / 79 bytes. This is a
  demonstrated prerequisite unblock; no merge or later Luna landing is claimed.
  The constructor still fails C2511, both mixed donors stay behind, and the
  pool's data register entries remain. No census or linked-byte gain is claimed.
- **Sway declaration prerequisite (2026-10-26):**
  [the scoped receiver and identity evidence](../reverse/attempt_support/consolidation-sway-receiver-20261026-codex.md)
  reconciles the seed, pool-key and transfer receivers. Ordinary composition now
  accepts all three sources (6 rows / 1,218 bytes), while the constructor still
  lacks a compatible declaration and the mixed getter stays behind. This is a
  demonstrated prerequisite unblock; no merge or later Luna landing is claimed.
  The separate visibility cleanup removes Sway's divergent seven-byte
  `Drawable::isVisible` COMDAT and preserves every retained section and code/data
  reference fact. The selected GameLogicInit copy remains the same. Identity
  register retirement is zero; scoped current-provider verification and its
  limits are recorded in the handoff. No census or linked-byte gain is claimed.
- **Evidence / scope:** recurring historical names include `AudioEventRTS`
  destruction, assignment and `setObjectID`; `UpdateModule::crc`;
  `DamageInfo` / `DamageInfoInput` / `DamageInfoOutput` transfer methods;
  `INI::scanIndexList`; `ParticleSystemManager::createParticleSystem`;
  `Object::setProducer` / `setStatus`; and `DISABLEDMASK_NONE`.
- **Completed:** the initial `link_rank.py --owner-gaps --top 12 --near 3`
  inspection found 23 unresolved names with matched-address candidates. This
  is an ownership lead, not a repair or identity proof.
- **Verified special-power subset (2026-10-25, inspected `777d0ff0aa`):**
  [current verification](../reverse/attempt_support/specialpower-dtor-verification-20261025/readme.md)
  confirms upstream `bcac7d81eb` removed the protected/public destructor
  mismatch for CashHack and Defector. Normal gates pass 14/14 rows across the
  two callers and two provider units, with 2/2 EH graphs EXACT; all four units
  have strict current receipts. Against index `51fde01dff` (13:53 UTC), with
  all four requested objects current, both callers preview cleanly for their
  already-counted 422 bytes. This binding/ordinary-preview subset is cleared;
  no new headline gain or census confirmation is claimed.
- **Historical special-power prerequisite:** the actual destructor's unit
  `SpecialPowerModuleDtor_Unresolved.cpp` still conflicts on the two
  BehaviorModule vtables and the SpecialPowerModule vtable (three first-copy
  COMDAT findings). Reconcile those native class/table definitions before
  claiming the family's closed-strict or executable closure; the scoped
  evidence above records the exact names. The broader entry remains open.
- **Follow-up verification (2026-10-25, after `aa31e9bac4`):** the dtor and its
  14 public-spelling consumers now preview cleanly (1,434 B). The constructor
  and WeaponMode consumer also need their local `BehaviorModule` destructor
  declared protected to bind the existing providers. Both corrected views
  byte-verify with exact EH; the constructor previews 340 B and WeaponMode
  retains its previously linked 112 B. See the LINK-014 follow-up below.
- **Native-interface/debt follow-up (2026-10-25, after `17d211067f`):**
  [the bounded zero-slot repair and ABI handoff](../reverse/attempt_support/behavior-zero-slot-hatch-20261025/readme.md)
  replaces one linker alias with a real, whole-body-verified C++ zero-result
  slot and consistent declarations in the constructor/companion units.
  All 9 rows, 3 EH graphs and 3 strict receipts pass; the enforced hatch
  register retires one alias. The 624 already-linked cohort bytes are kept,
  with the same three remaining provider-table conflicts. No new headline
  gain or family clearance is claimed. Native table inspection also shows
  that the indexed ZH-shaped 14/34-slot bases are not the retail contract:
  the primary native base has 12 slots, and the secondary run/signatures
  require reconciliation, including the class-contract queue's final slot.
  Use the handoff's exact table anchors before adopting shared declarations.
- **`AudioEventRTS` destruction/assignment subset (2026-10-25, inspected
  `b620cdb046`):**
  - The shared names are two pins:
    `??1AudioEventRTS@@UAE@XZ` -> `0x004EC395` (the folded STLport
    `_List_base` destructor) and `??4AudioEventRTS@@QAEAAV0@ABV0@@Z` ->
    `0x000366F0` (`StringBase<char>::set`).
  - `tools/name_dependents.py` finds 17 units, compiled against Zero Hour
    headers, whose objects reference them. Trial: drop both pins and build
    all 17. 15 units stay exact; exactly 2 rows fail:
    - `??4DynamicAudioEventRTS@@QAEAAV0@ABV0@@Z` (`0x00200BC0`, 25 B,
      `ThingFactory.cpp`). Retail copies only a `StringBase<char>` at +4 via
      `StringBase::set`, so this body is not an `AudioEventRTS` assignment.
      The masked-search placement is no identity proof.
    - `??1?$pair@VAsciiString@@VAudioEventRTS@@@_STL@@QAE@XZ` (`0x002A12E1`,
      `ThingTemplate.cpp`). Retail destroys `second` at +4 through the folded
      list destructor `0x004EC395`, then `first` through
      `StringBase<char>::~StringBase` (`0x00036410`), so the BFME 2 map value
      is not a 0x88 event.
  - These two pins block naming the canonical 0x88 class
    (`BfmeAudioEventPrefix136`, `Code/GameEngine/Include/Common/BfmeAudioEventPrefix136.h`)
    `AudioEventRTS`. The retail `AudioEventRTS.cpp` `__FILE__` string is
    referenced at `0x002D9ADC`, inside that class's translation unit
    (`0x002D94CE..0x002DAB18`). With the rename, its virtual destructor
    (`0x002D9A43`) would share a mangled name with the pin at `0x004EC395`.
    `pin_consistency` refuses that, and the link would select one body for
    both.
  - **Next check:** re-identify the two rows' real BFME 2 types (a
    {+0, `StringBase<char>` +4} class with assignment; a map value whose
    destructor folds with the list base). Retype them so they call those
    callees by their own names, then drop both pins. Re-run the 17-unit
    trial before the canonical rename.
- **GameWindow table prerequisite (2026-10-25, inspected `a0af8f5cb1`):**
  retail's table at RVA `0x0080BBCC` has 11 slots and ends at `0x0080BBF8`,
  the separately identified `Rva0031455E` table. `GameWindow.cpp` declares
  12 virtuals, including `winSetFont`; `GameWindowDtor.cpp` declares two,
  including a virtual `winDrawBorder` whose existing row is nonvirtual.
  The historical 249-byte dtor preview remains blocked. The next repair
  should reconcile both views with the native 11-slot table and its callees,
  then verify the table owner, parent bodies and consumers together.
  [Native slot evidence](../reverse/attempt_support/link-regression-clusters-20261025.md#gamewindow-native-table-prerequisite).
  No GameWindow source trial was applied during this follow-up.
- **INI bucket initializer repaired (2026-10-25, control `349db6dc10`):**
  [the scoped provider repair](../reverse/attempt_support/ini-bucket-provider-link-20261025/readme.md)
  makes INI emit the retail 59-byte initializer at `0x00148DDF` and applies its
  prime-search configuration before the relevant include. INI's wrong-binding
  count falls from one to zero. All 203 cohort rows and 13 EH graphs pass;
  the bounded ownership diagnostic clears INI's 2,989 authored bytes. Existing
  provider debt is recorded in the handoff. This subset is cleared in the
  scoped diagnostic; global closure and census confirmation remain pending.
- **INI repair's AI consumer checked (2026-10-26, `d7fa8a31bf`):**
  [the current-provider check](../reverse/attempt_support/ai-constructor-current-provider-20261026.md)
  verifies Rva00598E85Ctor.cpp's four rows and its INI/lower-bound providers
  (46 rows, six EXACT EH graphs). Index `f995f30157` still selects INI's old
  prime-search copy; including current INI makes the unchanged AI unit preview
  LINKS for 177 authored bytes. This confirms existing repair `0c7ebc35a7`,
  with no new source edit or census gain. INI's own ownership-overlay blockers
  remain outside this AI-only clearance; await the next census for confirmation.
- **GameLogic lookup header subset (2026-10-26, `8da4ac24ce`):**
  [the AITarget, indexed getter and audio owner adoptions](../reverse/attempt_support/gamelogic-lookup-header-adoption-20261026.md)
  replace private GameLogic/ObjectID declarations with the registered header.
  All eleven function rows and the data row remain exact, with one EXACT EH graph
  and unchanged 762-byte combined ordinary link-preview scope. The owning
  acceptance tool retires three header-queue rows; the shared header is unchanged.
  These already-linked consumers gain no census bytes. Other consumers and
  full class-layout reconciliation remain open.
- **AI Xfer header subset (2026-10-26, `a1ee5c1f39`):**
  [the flank-route, AIUpgrade and harvest-state adoptions](../reverse/attempt_support/ai-xfer-header-adoption-20261026.md)
  replace private Xfer declarations with the registered header. Seven function
  rows (772 bytes), the 68-byte state table and one EH graph remain exact.
  The route and harvest-state ordinary preview stays 518 -> 518 bytes against
  index `f995f30157`. A local operand-declaration include also preserves the
  supported 10-row flank TU merge dry-run, with no rejected donors; no merge
  was applied.
  AIUpgrade's two rows (254 bytes) and one EH graph also stay exact, but that
  source is absent from the index and has no ordinary-preview verdict. The
  owning acceptance tool retires three header-queue rows. Other Xfer consumers and
  class-wide closure remain open; no new census or matched-byte gain is claimed.
- **Vector Xfer header subset (2026-10-26, `6a57c22ccc`):**
  [the vector-transfer adoption](../reverse/attempt_support/vector-xfer-header-adoption-20261026.md)
  replaces the private classes in Rva003F2394Xfer.cpp and Rva0040E19DXfer.cpp
  with the canonical Xfer header. Both complete 204-byte bodies stay exact;
  each ordinary preview remains 204 -> 204. The owning tool retires two queue
  rows. A local operand include preserves
  declaration order and the temporary string-pointer lifetime needed for retail
  stack reuse. Shared headers and existing vector/exception identities are unchanged.
  Other Xfer consumers and class-wide closure remain open.
- **Remaining / next check:** resolve the real existing owner, parameter types,
  ABI and data ownership from native references; reconcile canonical headers
  with implementations and consumers as a batch. Verify all affected rows and
  selected definitions. Do not add a duplicate identity, stub or escape hatch
  to satisfy an old spelling. Clearance and census confirmation remain pending.

### LINK-005: units blocked by several incompatible dependencies

**Status: Open. Updated: 2026-10-25.**

- **Evidence / scope:** the historical blocker lists contain ConnectionManager
  (51 names), particle-module copy constructors (28), MapUtil (26), `texture.cpp`
  (21) and `ww3d.cpp` (20). These counts overlap the causes above and are not
  counts of independent missing implementations.
- **Completed:** the initial investigation grouped these as coordinated repair
  families; it made no source repairs or current-object measurements.
- **Remaining / next check:** refresh each unit's actual blockers, then reconcile
  shared string/map/vector views, destructors/vtables, signatures and graphics
  interfaces. Track resolved subsets and remaining names here or in a linked
  family handoff. A repaired dependency is partial progress until all blockers
  in the stated unit scope are checked. Clearance and census confirmation
  remain pending.

### LINK-006: compiler emission and the selected copy still disagree with retail

**Status: Open. Updated: 2026-10-25.**

- **Evidence / scope:** string erase/replace helpers and Render2D container
  destruction can resolve a symbol while retaining an incorrect selected body.
  Read the [prior linking handoff](../reverse/attempt_support/link-seat-20261025-final.md)
  and its referenced string/compiler banks before trying another emission shape.
  The vector parent/helper contract in LINK-002 is another concrete example.
- **Completed:** selective emission has repaired some other families, recorded
  under LINK-001; it does not establish a fix for these remaining cases.
- **FX-list constructor subset cleared in ordinary preview (2026-10-25,
  after `feb95824fa`):**
  [the full dependency proof](../reverse/attempt_support/fxlist-constructor-link-20261025/readme.md)
  restores allocator/forwarder visibility and replaces the sibling's wrong
  bucket-count emission with the retail copy. Normal gates prove the complete
  48/59/64-byte helpers, 19/19 cohort rows, four exact EH graphs and four strict
  current receipts. All four current units preview cleanly against index
  `51fde01dff`; the store constructor's 109 authored bytes are now included in
  that bounded clean scope. The paired evidence distinguishes actual source
  repair from alias-driven uncertainty in the old control. The broader
  value-layout and string/container entries remain open; census and executable
  closure are unclaimed.
- **Final FX-list provider scope:** the same proof also removes the constructor
  unit's wrong clear copy in favor of the existing 73-byte owner at 0060CFB6.
  Expanded verification passes 26 rows across five sources, four exact EH
  graphs, five strict receipts and zero new identity findings. FXList.cpp's
  clear operation is verified, while its whole 620-byte unit still has separate
  particle/terrain/drawable bindings, two nugget tables and list-lifetime
  blockers, detailed in the proof. Only the original four-unit ordinary-preview
  scope is cleared; the broader entry remains open.
- **Remaining / next check:** prove the native provider and inspect all emitted
  symbols, relocations, parent extents and EH graphs with current inputs. Merely
  suppressing a helper or changing an exception declaration can break a matched
  parent. Clearance and census confirmation remain pending for this scope.

- **FX-list obsolete-emission subset (2026-10-25, inspected `9edfc2834c`):**
  [the bounded cleanup and identity handoff](../reverse/attempt_support/fxlist-obsolete-emissions-20261025/readme.md)
  removes unused Zero Hour callbacks and retains the bone-position method out
  of line. All seven existing bodies and all their relocations are unchanged;
  normal byte/data gates and a strict current receipt pass. Against the fixed
  `ef9c691284` index, the obsolete drawable call and bone-position table conflict
  disappear. The 620-byte unit still does not link; no census gain is claimed.
  The two remaining list pins target StringBase operations (000365F0 and
  00036E70), and the 0052BD3A copy installs the existing one-string C61A20 table.
  Declaration-only suppression introduces unresolved references, so the next
  step is a coherent ownership/provider/consumer correction, preserving coverage.
  The separate particle table and legacy particle/terrain calls remain open.
  A supported identity-retirement attempt refused missing/stale provider evidence;
  no baseline was changed.

- **Map-metadata selected-copy subset (2026-10-25, inspected `d4cd9b535c`):**
  [the read-only cache-reference repair](../reverse/attempt_support/map-metadata-borrow-link-20261025/readme.md)
  stops SkirmishGameOptionsMenu.cpp from instantiating its shorter Zero Hour
  metadata copy and related tree-copy operations. Native positioning helpers
  independently show that the borrowed metadata and coordinates are read-only.
  Normal gates pass 56 rows across six current sources, 13 exact EH graphs and
  six strict receipts with independently checked object hashes. A fixed-facts
  paired ordinary preview clears four caller units (2,295 authored nonpadding
  bytes). This bounded subset awaits census confirmation; the legacy menu's
  other dependencies and MapMetaDataCopyDeferred's waypoint-tree identity/provider
  conflicts remain open. No whole-family or executable closure is claimed.

- **Decal unmatched-emission subset (2026-10-25):**
  The native check of `decalmsh.cpp` retains all six existing exact rows
  (326 bytes) while removing 18 explicitly unmatched Zero Hour function
  definitions. Five Texture-pointer vector members are emitted explicitly;
  the existing count getter keeps its directly proven receiver-field load,
  with no new vtable definition. The six unresolved legacy renderer calls
  disappear. Normal byte verification passes 6/6 before and after.
  Against the fixed `f995f30157` index (2026-10-25 21:36), the bounded ordinary
  preview changes this unit from blocked to clean (0 -> 326 authored bytes).
  No new C++ exact bytes, census headline or closed-strict result is claimed.
  Verification is the isolated native fork workflow; canonical class
  registration, data ownership, source claims and the actual file lease are
  checked before editing. The broader compiler/provider entry remains open.

  Removed hatch occurrences: 22; registered debt retired: 0. Unrelated register keys are preserved.

  Source blobs: original `11adf762e6f6e2a8296465286d1bb96364c58a02`, repaired `23f5050ee6df39dd0d5846c45f16427e153cc6a7`.
  Existing rows retained without ledger edits:

  | RVA | Bytes | Symbol |
  | --- | ---: | --- |
  | `0x00143E90` | 129 | `?Resize@?$SimpleVecClass@PAVTextureClass@@@@UAE_NH@Z` |
  | `0x00143F20` | 55 | `?Uninitialised_Grow@?$SimpleVecClass@PAVTextureClass@@@@UAE_NH@Z` |
  | `0x005508E9` | 7 | `?Decal_Count@RigidDecalMeshClass@@UAEHXZ` |
  | `0x00144910` | 40 | `?Resize@?$SimpleDynVecClass@PAVTextureClass@@@@UAE_NH@Z` |
  | `0x00144020` | 39 | `??0?$SimpleVecClass@PAVTextureClass@@@@QAE@H@Z` |
  | `0x001448D0` | 56 | `??0?$SimpleDynVecClass@PAVTextureClass@@@@QAE@H@Z` |

  Provider audit retains every mapped symbol through an equivalent or retail-correct provider; no linker alias is removed.
  Native receipt: https://github.com/McMickey93/Open-BFME-2/actions/runs/40240437884.

### LINK-007: incomplete data ownership beyond clean symbol resolution

**Status: Open; three storage subsets repaired. Updated: 2026-10-25.**

- **Evidence / scope:** the [linking handoff](../reverse/attempt_support/link-seat-20261025-final.md)
  identifies missing shader/filter root objects and the unowned 52-byte
  ScreenBWFilter group at `0x009B5B54`. Complete native objects and vtables are
  prerequisites; a symbol alone does not prove their storage or relocations.
- **Completed:** the [VP6 storage repair](../reverse/attempt_support/vp6-idct-storage-link-20261025/readme.md)
  proves the table's 548-byte allocation and records a fixed-comparison
  **17,413-byte placed closed-strict gain**. Those units already counted as
  linked in the headline. This is scoped closure evidence, not a new headline
  measurement of master; follow that lane's clean-room rules.
- **Filter adjacency repaired (2026-10-25):** the
  [modifier/pointer ownership proof](../reverse/attempt_support/vp6-filter-adjacency-link-20261025/readme.md)
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
  [the six-scaler ownership repair](../reverse/attempt_support/vp6-scale-tables-link-20261025/readme.md)
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
- **Remaining / next check:** shader/filter root-object ownership remains
  open. The [current witnesses](../reverse/attempt_support/vp6-scale-tables-link-20261025/remaining-witnesses.json)
  show InitPostProcessing still closure-blocked through GetProcessorFlags and
  CpuProbe_VendorSse2: the selected `__except_handler3` import twin lacks a
  confirmed map/object definition. UtilMachineSpecificConfig independently
  reaches FilterBlock2dBil's `g_bfmeTableC7E0` forward-map conflict. Prove those
  selected providers and native storage relationships; do not retry the cleared
  coefficient or filter-pointer splits. Verify storage
  extents, initial bytes, relocations and dependent closure through the existing
  gates. Family clearance and later census confirmation remain pending.
  Preserve the no-stubs/no-`/FORCE` runtime exit requirements.

### LINK-008: include inventories prevent strict reusable graphics receipts

**Status: Blocked on complete include inventories. Updated: 2026-10-25.**

- **Evidence / scope:** [graphics verification at `91fe970939`](../reverse/attempt_support/weightinfo-verification-20261025/readme.md)
  ran the normal gates successfully for 34 units, but its initial 17-unit
  `--prepare-current` run refused strict reuse. W3DShadowTextureCtor,
  W3DDebrisDraw, W3DDebrisDrawLegacy and W3DVolumetricShadow reported macro or
  parent-traversing include roots, or headers outside inventoried search roots.
- **Completed:** all 34 ordinary byte/receipt checks pass; 13 objects also have
  strict reusable receipts. The other 17 units were checked through the ordinary
  path; no claim is made that all of them are uncacheable. The refusal is retained
  in the evidence, and no gate was relaxed. LINK-001's destructor preview result
  does not establish strict closure.
- **Remaining / next check:** prove and make the actual include graph
  inventoryable under the existing gates, then repeat bounded strict preparation
  for all affected providers/consumers. A needed verifier repair follows the
  separate false-reject workflow. Do not substitute ordinary receipts for strict
  witnesses. Clearance and closed-strict confirmation remain pending; no census
  change is claimed for this inventory work.

### LINK-009: split-identity destructors; the alias route needs an admission path

**Status: Blocked on an identity merge or a maintainer admission decision.
Updated: 2026-10-25; inspected revision: `4e835ab16a6`.**

- **Evidence / scope:** constructors matched under one class name whose retail
  destructor is matched under a second, address-derived name, so the unit's
  `??1X` stays unresolved. Six units are affected, 661 authored bytes:
  GameSpyInfoCtor.cpp 280 B (`??1GameSpyInfo`), ExperienceTrackerAutoResolve.cpp
  113 B, Rva0022BD9ASubsystem.cpp 67 B, Rva0022C0CDSubsystemCtor.cpp 81 B,
  Rva0022BE0FSubsystemCtor.cpp 65 B and Rva0022BD25SubsystemCtor.cpp 55 B.
  Retail proves each pair: the unit's constructor installs a vtable whose slot 0
  deleting destructor calls the matched body, and two pairs are additionally
  anchored by address adjacency (`0x0041EFFF` + 67 = `0x0041F042`;
  `0x0041F913` + 55 = `0x0041F94A`). Banked detail and the per-class table:
  [split-identity handoff](../reverse/attempt_support/split-identity-dtors-20261024/readme.md).
- **Completed:** a full-form `/alternatename` trial on all six units re-verified
  28/28 rows and linked `LINKED 0 -> 661` bytes at census index 2026-10-24 10:28
  (`2fbdec0868`). It was reverted: the current rules forbid adding
  `/alternatename` by hand, hatch counts may rise only through an admitted tool,
  and the counter's own `--allow`/`--admit` is hand-adding. No admission tool
  covers this hatch, so the evidence is preserved as an attempt, not a repair.
- **Remaining / next check:** choose an admissible route. Preferred is an
  identity merge of the placeholder destructor class into the class the
  constructor/vtable prove, sharing one class view among every unit that emits
  the vtable; that is still blocked on `rename.py` support for a
  placeholder-to-real merge and on the class-view/COMDAT cases recorded in the
  handoff (GameLogic/SubsystemInterface slots, the ExperienceTrackerXfer vtable
  COMDAT, BaseHeightMapRenderObjClass and GlobalWeatherSystem whose rowed names
  are deleting destructors only). Otherwise a maintainer decision is needed for
  a scoped admission path. Do not repeat the unchanged alias trial.
- **Clearance / census confirmation:** pending; no census change is claimed and
  the alias trial was not published.

### LINK-010: folded STL table bases need the actual native predecessor

**Status: Blocked on supported native data-placement / ownership reconciliation.
Updated: 2026-10-25; inspected revision: `4f111811802`.**

- **Evidence / scope:** [the signed-reference handoff](../reverse/attempt_support/stl-tenscale-predecessor-link-20261025/readme.md)
  proves the full 640-byte tenpow and 160-byte twoexp arrays in
  `stlport_stl_atod.cpp`, all six native DIR32 references, and a normal 5/5
  body control. A read-only replay of `a7637e3b22` re-proves inputs and
  reproduces all 98,202 status rows and the fixed-comparison credit.
- **Completed:** the cause is narrowed beyond symbol visibility. Tenpow's
  folded -4/-8 references precede its own COFF contribution and collide with
  Initialize_get_float's digits literal in the measured image. Retail instead
  reaches the end/padding of the canonical `__hex_char_table_hi` at VA BBC910,
  owned by `stlport_write_integer_backward.cpp`. Twoexp's -2 reference already
  has a valid named predecessor and passes the existing before-symbol rule.
  Game source is unchanged; no new credit is claimed.
- **Remaining / next check:** reconcile real native data placement and the
  existing hex-table owner without duplicating or over-sizing that datum.
  Establish a fresh approved TU/ownership plan before any consolidation; the
  inspected committed map supplies no approved merge for these two units.
  Verify both predecessor and array, other consumers, and one-to-one maps.
  Do not repeat visibility-only or expression changes, add an artificial
  prefix, or weaken the check. Clearance and census confirmation are pending.

### LINK-011: provisional base classes and vtable mismatches in GameEngine subsystems and triggers

**Status: Repair landed / awaiting verification. Updated: 2026-10-25.**

- **Evidence / scope:** several GameEngine units used provisional `Rva...Base` classes
  that declared non-pure virtual functions (`unused()`, `~Class()`) without definitions,
  causing unresolvable vtable and destructor symbol references. In `PolygonTriggerCtor.cpp`,
  a secondary base declared `secondarySlot()` non-pure while `Rva002E3EB8Permuted` declared
  it pure virtual `slot() = 0`. In `Rva003BBAF0Ctor_Rva003FD199.cpp`, `BfmeBaseVNH` vtable
  `??_7BfmeBaseVNH@@6B@` was referenced without being defined. Total scope: 297 authored bytes
  across 4 units.
- **Completed:**
  - `SpecialPowerStore.cpp` (37 B): adopted canonical `SubsystemInterface` directly.
  - `EmotionSystem.cpp` (59 B): adopted canonical `SubsystemInterface` directly.
  - `PolygonTriggerCtor.cpp` (157 B): replaced ad-hoc secondary base with `Rva002E3EB8Base`
    declaring pure virtual `slot() = 0`.
  - `Rva003BBAF0Ctor_Rva003FD199.cpp` (44 B): defined `BfmeBaseVNH` vtable symbol.
  - Verification: `./build.sh` byte-matches all 4 units (5/5 rows); `tools/link_check.py`
    confirms all 4 link cleanly (`LINKED 0 -> 297` bytes).
- **Remaining / next check:** await confirmation in the maintainer's next link census run.
- **Clearance / census confirmation:** cleared in ordinary-preview scope; census confirmation pending.

### LINK-012: shattersystem.cpp's Zero Hour WW3D2 views emit divergent shared COMDATs

**Status: Open (partial repair landed). Updated: 2026-10-25; inspected revision: 70d32d864.**

- **Evidence / scope:** `Code/Libraries/Source/WWVegas/WW3D2/shattersystem.cpp` compiles
  against Zero Hour's `WWLib/Vector.H`, `WW3D2/matinfo.h` and the `meshmatdesclayout`
  shim, and emitted a 75-byte `DynamicVectorClass<VertexMaterialClass*>::Add` while
  retail's folded owner (0x001A3A60, 77 B) is what the six BFME 1-header units emit.
  The census (ef9c691284) kept shattersystem's copy, so every user of that `Add` failed
  `wrong_selected`: MeshLoadContextAddLegacyMaterial.cpp (2,714 B),
  MaterialCollectorDestructor.cpp (1,588 B), MaterialCollectorCollectMaterials.cpp
  (1,489 B), MeshModelReadVertexMaterials.cpp (270 B) and meshmdlio.cpp (352 B).
- **Completed:** shattersystem.cpp declares the `Add` specialization decl-only (before
  matinfo.h, whose inline `Add_Vertex_Material` instantiates it), so it emits no copy.
  `./build.sh` 1/1; `tools/link_check.py` with shattersystem.cpp and each consumer:
  all five consumers LINK (0 -> 6,413 B predicted).
- **Remaining / next check:** shattersystem.cpp still emits non-retail
  `MaterialInfoClass::Add_Vertex_Material` (out-of-line `Add` call where retail 0x00189670
  inlines BFME's `Add`) and `MeshMatDescClass::Peek_Single_Material` (material array at
  +0xA8 in the `meshmatdesclayout` view; retail 0x002C8ECF reads +0xA4). Those keep
  dynamesh.cpp (owner of both rows) and shattersystem.cpp itself from linking. The two
  `Add` bodies are textually identical, so the difference is the views' class layouts:
  reconcile shattersystem.cpp onto the BFME 1 WWLib/WW3D2 headers dynamesh.cpp uses,
  checking its 0x00074643 `Matrix3D::Scale` row.
- **Clearance:** preview scope only (current objects for the listed units).
- **Census confirmation:** awaiting the next census.

- **Mesh material I/O follow-up (2026-10-25, inspected `d7fa8a31bf3`):**
  [the bounded cleanup and provider control](../reverse/attempt_support/meshmdlio-hatch-cleanup-20261025-bce2/readme.md)
  confirms meshmdlio's eleven rows remain exact (352 bytes). Against the
  `f995f30157` index, checking the current shattersystem object alongside it
  clears the historical Add blocker before and after the cleanup. This is
  inherited repair, not new linking credit. The file's obsolete construction
  anchor and stale matched-destructor annotation are removed, retiring three
  hatch occurrences through the register tool. The RefCount optimization is
  retained after an independent removal trial changed Add_Ref's emission.
  Shattersystem's seven current unresolved/COMDAT/selected findings are
  unchanged and recorded in the evidence. Only this consumer's ordinary
  preview scope is cleared; family closure and census confirmation remain open.

### LINK-013: INI consolidation made a non-retail `set<AsciiString, BfmeStringNoCaseLess>::insert_unique` the kept copy

**Status: Cleared in the eight-unit ordinary preview; census pending. Updated: 2026-10-25; inspected revision: aa31e9bac4.**

- **Evidence / scope:** the census at f995f30157 lost the six units that call
  `_Rb_tree<AsciiString, …, BfmeStringNoCaseLess>::insert_unique` (row 0x0002C908, 153 B,
  owner `stlport_nocase_asciistring_set_insert.cpp`) to `wrong_selected`. Its index holds
  five copies:
  - non-retail (digest c5d4a74a154c): `INI.cpp` (object 576, first in link order since
    the INI merge) and `SidesListDataChunks.cpp` (object 2445)
  - retail (digest 46fbdb7211c9): `stlport_nocase_asciistring_set_insert.cpp`,
    `stlport_nocase_asciistring_set_touch.cpp` and `stlport_rb_tree_insert_unique_nocase.cpp`

  Before the merge a retail copy came first, so SidesList's copy was latent.
- **Completed:** both units declare the `insert_unique` specialization decl-only, so they
  emit no copy and bind the kept retail one. `./build.sh`: INI.cpp 39/39,
  SidesListDataChunks.cpp 91/91. `tools/link_check.py` against the f995f30157 index:
  - now LINK (0 -> 8,773 B predicted): SidesListDataChunks.cpp 6,726 B,
    Rva006047F3Family.cpp 1,659 B, the three WWLib owner units 388 B
  - INI.cpp itself still fails in that preview, on duplicate INI members (`~INI`,
    `INI::scanInt`, …) from `INI_ctor.obj` and `INI_scanInt.obj`. Those units were merged
    into INI.cpp after f995f30157, so these duplicates are stale-index artifacts, not this
    repair.
- **Current-provider verification:** the LINK-014 follow-up checks all eight
  insert_unique / _M_find units together and previews all 11,872 B clean,
  including INI.cpp. The historical duplicate-index and __lower_bound
  prerequisites below are cleared in that bounded check.
- **Historical remaining / next check:** the next census confirms the six units. INI.cpp's own link
  also depends on the separate `__lower_bound` provider repair.
- **Clearance:** preview scope only (five of six units against the f995f30157 index).
- **Census confirmation:** awaiting the next census.

### LINK-014: the census at f995f30157's other lost units (htree, SpecialPower, FX, BfmeE8, INI _M_find, BfmeConv499)

**Status: Open (partial repair landed). Updated: 2026-10-26; inspected revision: 65972bab0b.**

- **Evidence / scope:** 22 units linked in the census at ef9c691284 but not at f995f30157,
  for causes other than LINK-013 and the INI `__lower_bound` copy. Found by diffing
  `reverse/link_status.csv` (f995f30157 vs 763dc8759f) and reading the f995f30157
  index's blockers.
- **Completed** (each `./build.sh`-exact and previewed with `tools/link_check.py` against
  the f995f30157 index):

  | Unit(s) | Cause | Repair | Preview |
  |---|---|---|---|
  | `htree.cpp` | Merge af2f149baa dropped `/O1 /DNDEBUG`, so four unrowed Zero Hour definitions (`Create_Interpolated` ×2, `Create_Morphed`, `Vector3::Lerp`) called `_assert`, which retail does not import. | `/DNDEBUG` restored (35306cabab). | 0 -> 2,175 B |
  | 14 special-power ports | My landing of 83b2c3fa65 respelled `~SpecialPowerModule` protected after bcac7d81eb had bound the ports to the public spelling. | Public spelling restored (74fdf83172). | 0 -> 1,212 B |
  | `FXParticleSystemDefaultTemplateDtor.cpp` | My c81e10ce9d anchor made `FXParticleSystem.cpp` emit copies of the `DefaultModuleTemplate<2>/<3>` and Ortho dtors ahead of the owner. | Dtors declared in its views (d4fa3d06f2). | 0 -> 64 B |
  | Two `stlport_vector_e8_*` units | Once 289c748fb3 rowed `vector<BfmeE8>::_M_fill_insert`, their whole-class instantiations were non-retail copies first in link order. | Member declared decl-only; `__copy_backward` instantiated explicitly (1f6a6430ad). | 43/43 BfmeE8 users link, +950 B |
  | `_M_find` owner, `StlSweepR3Rva0002CB7D.cpp` | `INI.cpp`'s `_M_find<AsciiString>` called `vector<void*>::operator[] const` out of line. | Accessor forced inline as the owner does; copy now equals retail (f37ca79179). | +110 B |
  | `BfmeConv499.cpp` | 51cc7ed5dc dropped the alias for placeholder `bfmeDoBNH`. | Builds its handle base in place from `TextureAsset::Get`; orphaned pin dropped (65972bab0b). | 0 -> 27 B |

- **Ctor vtable reconciled (2026-10-26):** the ctor and dtor private views now
  declare the same named interface slots: `onSpecialPowerCreation` at slot 7,
  `pauseCountdown` at slot 9 and `startPowerRecharge` at slot 15. Both views now
  bind the same external definitions; this removes the ctor's pure slot 7 and
  the dtor's pure slots 9/15. `./build.sh` passes 7/7 rows across the two
  sources; `tools/link_check.py` against the 763dc8759f check index now links
  `SpecialPowerModuleCtor.cpp` for its 340 bytes (0 -> 340 B).
- **Dtor unit and 14 ports reconciled (2026-10-26):** the minimal
  `BehaviorModule` view in `SpecialPowerModuleDtor_Unresolved.cpp` shared the
  canonical class name, so it emitted two non-retail
  `??_7BehaviorModule@@6B...` COMDATs. Renaming that local, layout-only view
  `BehaviorModuleView` stops those false table owners without changing the
  `SpecialPowerModule` vtable or dtor bytes. `./build.sh` passes 5/5 rows;
  `tools/link_check.py` links the dtor unit for 222 B and all 14
  `??1SpecialPowerModule@@UAE@XZ` consumers for 1,212 B (0 -> 1,434 B).
- **Remaining / next check:** `OCLSpecialPower.cpp` still fails on its private
  protected dtor spelling, an unresolved `PartitionManager::findPositionAround`
  and a `FindPositionOptions` constructor copy. It was not one of the 14
  public-spelling ports.
- **Clearance:** preview scope only (the units listed above and the 14 ports).
- **Census confirmation:** awaiting the next census.

#### Current-provider follow-up, 2026-10-25

The [39-source verification](../reverse/attempt_support/link-regression-clusters-20261025.md)
at `aa31e9bac4` plus the two consumer access corrections confirms the six
historical regression clusters in ordinary preview. All eight AsciiString
units link (11,872 B), as do htree (2,175 B), all three E8 owners (928 B),
the FX template destructor (64 B), and BfmeConv499 (27 B). These are inherited
repairs verified together, rather than additional changes made by this pass.

The expanded check exposed two consumers of the public `BehaviorModule`
destructor formerly emitted by the minimal SpecialPower view:
`SpecialPowerModuleCtor.cpp` and `WeaponModeSpecialPowerUpdateCtorThunk.cpp`.
Their local views now declare that destructor protected, matching the 16
existing indexed providers. Normal verification passes 6/6 rows across both
consumers and a provider, with both consumer EH graphs EXACT. The constructor
links for 340 B; WeaponMode keeps its census-linked 112 B. No forwarding
implementation or new alias is retained.

The recorded combined result at that base is 32/39 clean units; six independent
candidates and the broader DumbProjectile provider unit were blocked as detailed
in the evidence. Concurrent upstream repairs in LINK-015 and LINK-016 supersede
the VectorClass<Vector3> and XferSave residuals from that snapshot.
OCL's protected SpecialPower destructor, findPositionAround and
FindPositionOptions remain open. Float-format's attempted active append
declaration triggers VC7.1 C1001; its alternate syntax fails C2768/C2244/C1506.
Both float trials were restored. Broader family closure and census
confirmation remain pending.

### LINK-015: naming `VectorClass<Vector3>`'s deleting destructor proved the consumers' inlined copies wrong

**Status: Repair landed / awaiting verification (two teardown units remain blocked). Updated: 2026-10-26; inspected revision: cf035cfb20.**

- **Evidence / scope:** 4e0bfa8260 named retail 0x000F1CF7 as
  `??_G?$VectorClass@VVector3@@@@UAEPAXI@Z` (34 B: vptr store, call to the kept
  `Clear` 0x000F0CD4, `pop ecx` after `operator delete`) and rowed it in
  `vector_class_vector3_ctor.cpp`. Once it had a retail address, the seven other
  copies were proven wrong: they inline `Clear` (/O2), and the /G7 ones clean up with
  `add esp, 4`. The first in link order, `collect.cpp`'s, was the one kept, so the
  census at ef9c691284 lost `pointgr.cpp`, `PointGroupClassRva0017A890.cpp`,
  `DX8SkinClearVisibleList.cpp`, `Rva007B7280Siblings.cpp` and `Rva007B73C0.cpp`,
  all linked at d2636bb381 (`reverse/link_status.csv` history). The owner's copy is
  only `unknown`, never `retail`: its DIR32 to `??_7?$VectorClass@VVector3@@@@6B@`
  (0x007CEFAC) has no data row, so no proven copy lets the wrong ones stand
  (retail-truth-3).
- **Completed:** `collect.cpp`, `mesh.cpp`, `DX8SkinClearVisibleList.cpp`,
  `PointGroupClassRva0017A890.cpp` and `pointgr.cpp` declare
  `~VectorClass<Vector3>` decl-only, so cl synthesizes neither `??_G` nor the
  `VectorClass<Vector3>` vtable there. Declaring `Clear` decl-only instead is not
  enough: the /G7 units still differ (`add esp, 4`), and `pointgr.cpp`'s
  `Rva00912CF0` inlines `Clear` as retail does. `pointgr.cpp` explicitly
  instantiates the virtuals the vtables used to bring: its rowed `ID(T const *)`
  (0x001298B0, /G7, retail-proven, now the first copy) and `ID(T const &)` and
  `operator==`, which the other units only declare. `vector_class_vector3_ctor.cpp`
  declares `ID(T const *)` decl-only: its non-/G7 copy (wrong) would otherwise be
  the first. `./build.sh`: 90/90 rows exact across the six sources.
  `tools/link_check.py` against the 763dc8759f index with all nine current objects
  (including `FXShaderRendererSkin.cpp`): `PointGroupClassRva0017A890.cpp`
  0 -> 11,964 B, `pointgr.cpp` 0 -> 10,565 B, `DX8SkinClearVisibleList.cpp`
  0 -> 1,613 B, `vector_class_vector3_ctor.cpp` 0 -> 194 B (+24,336 B);
  `FXShaderRendererSkin.cpp` keeps 937 B; `collect.cpp` and `mesh.cpp` keep only
  their earlier, unrelated blockers.
- **Remaining / next check:** `Rva007B7280Siblings.cpp` (353 B) and
  `Rva007B73C0.cpp` (59 B). Retail's teardowns inline both the destructor and
  `Clear`, so these /O2 units must keep both inlinable, and cl synthesizes their
  own inlined `??_G`, which loses while no copy is proven. Either a verified home
  for the 0x007CEFAC vtable that proves the owner's copy retail (retail-truth-3
  then lets the wrong copies stand), or consolidating the teardowns back into
  their retail TU, `pointgr.cpp`, would clear them. No source trial; no hatch
  (`#pragma optimize`) considered.
- **Clearance:** preview scope (the units above) on current objects.
- **Census confirmation:** awaiting the next census.

### LINK-016: folded bodies whose consumers declare them decl-only, with no provider

**Status: Repair landed / awaiting verification. Updated: 2026-10-26; inspected revision: 856b8bc032.**

- **Evidence / scope:** in the census at 763dc8759f, several units were
  unresolved only on an STL member or a global that they declare (decl-only, to
  avoid a non-retail COMDAT) but that no object defines under that name: retail
  ICF-folded the body under another instantiation's row. Found with
  `tools/link_rank.py --near 1 --json` (units whose only blockers are `U`) and
  each name's `reverse/symbols.csv` address.
- **Completed** (each `./build.sh`-exact; previewed with `tools/link_check.py`
  against the 763dc8759f index, passing the provider and its consumers together):

  | Unresolved name | Retail body | Provider (its flags already emit that shape) | Preview |
  |---|---|---|---|
  | `g_lgaKeyRecords` (0x00A02E50; it also carried two address names) | 16 B tree, ctor 0x007AF8CD | `Rva007B6880Thunks.cpp`: one zero-filled definition through an opaque tree view; Count, Merge and the initializer bind it (25f107697e) | unresolved gone from both LargeGroupAudio units |
  | key-tree `erase(iterator)` (`LargeGroupAudioKeyList.cpp`'s /O1 /Oy- copy was selected) | 0x00056BC3 | `stlport_asciistring_set_base.cpp` (3a828f7bea) | KeyList 0 -> 191 B |
  | `hashtable<pair<const int, Rva0060CF76Element>>::_M_initialize_buckets` | 0x00148DDF | `SelectionIDMap.cpp` (e80fae26b7) | XferSave.cpp 0 -> 1,060 B |
  | `_String_base<char>::_M_throw_out_of_range` | 0x00023A40 (empty /Od body) | `stlport_vector_voidptr_alloc.cpp` (357c8c8a3e) | four narrow-string units 0 -> 904 B |
  | `_Destroy<Rva002BBB96Element *>` | 0x002BB6A5 (BfmeAssignRecord52 loop) | `stlport_asciistring_record_bodies.cpp` (57b0571b72) | the two Deferred units 0 -> 2,925 B |
  | `/alternatename` onto an undefined `__copy<BfmeAssignRecord28 *>` | 0x003F6477 | the rowed `__copy<Rva003F6477Element *>` called directly; two hatches removed (856b8bc032) | VectorRangeEraseRva003F6975.cpp 0 -> 80 B |

- **Remaining / next check:** `LargeGroupAudioKeyMapBfmeAddKey.cpp` needs
  `vector<void*>::resize` (0x000E6D39, folded as BfmePowerCounts::resize). Its
  `_M_fill_insert` callee is 0x00233A5A, but `reverse/symbols.csv` puts
  `vector<void*>::_M_fill_insert` at 0x00029CA0, so a plain instantiation binds
  the wrong callee. Many `U` entries in the 763dc8759f index are stale: check
  with the defining unit's current object before working one (e.g.
  `~SpecialPowerModule` already resolves).
- **Clearance:** preview scope only (the units listed).
- **Census confirmation:** awaiting the next census.

### LINK-017: identity retirement does not resolve verified renumbered EH labels

**Status: Blocked on verifier reconciliation and current providers. Updated: 2026-10-26;
inspected revision: `2f9834aa34`.**

- **Evidence / scope:** [the DX8 retirement refusal](../reverse/attempt_support/dx8-identity-funclet-refusal-20261026.md)
  records 13 identity keys in dx8wrapper.cpp. Normal verification passes 228
  functions, 13 data rows and 21 EXACT EH graphs, including 72 renumbered funclets.
- **Completed:** no source or register edit. Retirement correctly refuses four
  stale providers and separately rejects old funclet labels already resolved by
  the byte gate. The latter is recorded as a false reject, not a debt repair.
- **Remaining / next check:** reconcile the retirement tool with verified parent
  EH resolution in a separate tooling change, refresh providers, then repair and
  judge the descriptor/vector bindings. Do not hand-change pins or labels.
- **Clearance / census confirmation:** none claimed.

### LINK-016: AIUpdate TU span combines weak propagation and disputed placement

**Status: Blocked on independent routing evidence and classification review.
Updated: 2026-10-26; inspected revision: `766153ce00`.**

- **Evidence / scope:** [the current-input routing handoff](../reverse/attempt_support/aiupdate-tu-approval-20261026/readme.md)
  separates 299 proposed rows from the seed's eight verified rows (241 bytes,
  one EXACT EH graph). The official plan has zero approved rows and one mixed
  file. No source, name, register or map was changed.
- **Completed:** six distant K-only assignments explain the broad span;
  the nonvirtual inline getter at 0x0026FF1E also extends it past Upgrade.cpp.
  A read-only diagnostic using the mapper's actual anchored roots still finds
  DisplayStringManager::link at 0x00262027 as a blocker after narrowing those
  bounds. Its WorldBuilder seed is not independent identity proof.
- **Remaining / next check:** prove that row's retail identity/ICF/placement,
  review weak propagation and inline classification separately, and retain
  genuine cross-TU anchors. The seed also retains its mixed rows and ordinary
  link blockers (17 unresolved, six COMDAT, five selected against f995f30157).
- **Clearance / census confirmation:** none. Neither a false reject nor a new
  matched, linked or debt-retirement gain is claimed.

## Investigation-specific validation limitation

The initial investigation preserved a pre-existing BFME 1 checkout at
`f5140c1cff6a58e16276fd6de6788186286953d4`, while BFME 2 pinned
`0bf534ea7ccde110c456edb9cd2dd5dae823c953`. Fetching the provider index succeeded,
but normal object import refused that mismatch. No check was bypassed and no
fresh local compile-based preview was claimed. This is a local input limitation,
not evidence that other agents or the whole repository are blocked. Use a
consistent verified checkout before taking new compile-based measurements.

The graphics follow-up above used a separate checkout with the pinned reference
and completed ordinary compile-based verification. The original checkout was
preserved; its mismatch did not block that isolated check. LINK-008 records the
separate strict receipt limitation encountered there.
