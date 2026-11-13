### LINK-006: compiler emission and the selected copy still disagree with retail

- **Unsigned/pointer tree destructor, already-landed repair verified (2026-11-13,
  inspected `b9047f2d164`):** the served missing tree-base constructor at
  `stlport_tree_dtor_00357C6A.cpp` was removed by `0e4b2640a11`, after measured
  commit `bd2310feee1`. Current strict object passes5/5 and references no tree-base
  constructor; scoped preview retains LINKS99 -> 99 against old index
  `aa7acf764d`. Source unchanged. Repair landed / awaiting authoritative
  verification; no census or whole-link gain claimed.
  [Object proof and measurement boundary](../../reverse/attempt_support/tree-base-current-object-20261113-root20.md).

- **MapMetaData cleanup (2026-11-05):** removing its declaration-only AsciiString destructor override preserves 16/16 rows, EXACT EH and the 320-byte LINKS preview; `repair_queue.py retire identity` clears both keys for `MapMetaDataCopy.cpp`. Deferred waypoint-tree obstacles remain; [evidence and scope](../../reverse/attempt_support/map-metadata-ascii-identity-20261105-codex.md).

- **Buddy status CRT declaration cleanup (2026-10-30, inspected `c790c01553`):**
  `Rva003896E7Permuted.cpp` now includes the real `stdlib.h` and binds its
  inline string cleanup to the existing `_STL::free` GameMemory provider.
  Native calls at 00389715/0038982E reach the rowed wrapper at 00030830.
  All three rows and strict compiler receipts pass; all fifteen external
  COMDAT bodies keep their bytes, with only the free-provider relocation name
  changing in two of them. The current ordinary preview retains LINKS,
  347 -> 347 bytes, against the 2026-10-30 04:25 index at `6fe1089c24`.
  The consumer audit is INCONCLUSIVE: that index predates the inspected base,
  and Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. Carry the
  source and affected consumers into the next scheduled census. Header-queue
  details and the retained prerequisites are in
  [the scoped evidence](../../reverse/attempt_support/buddy-status-crt-headers-20261030-codexb4.md).
  No census or runtime gain is claimed.

- **WindowVideo cleanup provider selection (2026-10-28, inspected `3aba05733d`):**
  the current preview reproduces the manager's wrong-selected hashtable
  destructor ahead of the verified WindowVideoHashtableDtor.cpp owner.
  Local declaration-only destructor/clear specializations remove exactly
  those two copies; the other 112 external COMDAT digests remain unchanged.
  All 43 rows byte-match, strict receipts pass, and eight EH graphs are EXACT.
  Against index `54b83e4f69`, both units now preview LINKS (2,206 and 134
  authored bytes). The two other indexed consumers retain LINKS (842 and
  331 bytes); the four-source cohort has eleven EXACT EH graphs.
  [Evidence and remaining prerequisites](../../reverse/attempt_support/window-video-cleanup-link-20261028.md).
  Identity retirement still refuses missing/stale provider receipts and
  existing bucket/AsciiString findings; all four keys remain. Clearance is
  limited to the four-source preview. Carry this cohort into the next census;
  no headline gain or full-image result is claimed.
  The post-publication batch audit is INCONCLUSIVE: index predates base
  `8c36c2edab`, and affected consumer Common/0CreateAHeroManager21FE49.cpp
  lacks a current receipt. Include that broader consumer scope in the census.

- **Font vector lifetime identity (2026-10-27, inspected `5a987437d9f`):**
  [the native lifetime and withdrawal evidence](../../reverse/attempt_support/font-vector-identity-link-20261027/readme.md)
  separates the constructor's actual BD3BE8/BD3B98 vector family from the
  BD0D68 base destructor. The wrong FontCharsBuffer dynamic-destructor
  admission and its dependent unwind are withdrawn in a reviewable commit;
  the remaining 12 rows and data row pass. Readmission of the existing
  Rva00155940Element specialization and parent-derived unwind follows.
  Readmission now passes all 14 rows through add_match without new pins.
  The official DIR32 check on 25 current rows passes 13 symbols with zero
  inconsistencies; the proved lifetime conflict is cleared in that scope.
  The paired three-source preview retains 1477 authored bytes, and the
  wider five-source cohort is 5/5 LINKS with 17790 bytes. No incremental
  census gain is claimed. Broader legacy template identities, the other
  native-gate conflicts and reference-refresh qualification remain open.
  Publication passed 78/78 rows in five sources and six EXACT EH graphs,
  but the outgoing linking-loss audit is **UNVERIFIED**: index 73061d9452
  predates base 1bce3761a21 and lacks per-object consumer names. Carry this
  source/consumer cohort to the next normal census; whole-batch closure and
  absence of losses are not established. See the tracked publication audit.

**Status: Open. Updated: 2026-10-27.**

**DefaultDraw table follow-up (2026-10-26, inspected `2a45addda1806342ac5c52757f63be902dcd428e`):** `T1Base005F3750Ctor.cpp` still disagrees with the first `DefaultDrawModuleInfo` table in `FXParticleSystem.cpp`. The native table at RVA 0081BAC0 has four slots (003A7ABD, 000B3FD0, 003A6127 and 00306A9B); the current first emitter has three slots, and T1's four-slot copy puts its name getter in slot 1 instead of slot 2. `build/c136-common2/provider-details.log` records the raw retail words and both COFF relocation lists. Matching the first emitter's shorter table would retain a non-retail contract, so no such trial was made. Next: reconcile the actual Snapshot interface and all emitting views, retaining every row, then recheck the family. The T1 destructor identity prerequisite remains separate under LINK-004. Clearance and census confirmation remain pending.

2026-11-05: four draw-info first emitters now have their exported, byte-verified transfer slot; T1's DefaultDraw COMDAT disagreement remains (ordinary preview 0 -> 0). Next: reconcile the post-load slot and other emitting views. [Evidence](../../reverse/attempt_support/fx-draw-transfer-20261105-codexb5/README.md).


**FX info post-load provider prerequisite (2026-10-30, base `a5c01ba2ba`):**
DefaultAlphaModuleInfo and DefaultColorModuleInfo now define their exported
empty `LoadPostProcess` callbacks as complete C++ ICF twins of B3FD0, replacing
two `v1` aliases to the coordinate destructor (alternatename -2). All 370
function checks, the data/string/float checks and strict preparation pass.
Of 680 retained COMDATs, only the two vtables change relocation names; both
edges retain native B3FD0. Ordinary preview retains LINKS against `85f6b7f40c`
(5,649 -> 5,650 authored bytes; zero unique native bytes gained).
The batch audit is INCONCLUSIVE on the older index and the missing current
CreateAHeroManager consumer receipt. Carry that consumer and this provider
into the next scheduled census. Complete Snapshot adoption still needs the
other seven post-load providers, nine DoXfer providers and reconciled four-slot
interfaces; its header-queue row remains. No census gain or complete consumer
closure is claimed. [Evidence](../../reverse/attempt_support/fx-postload-alias-cleanup-20261030-codex.md).

- **Old-reference full control (2026-10-27, frozen `47d8342e4c`):**
  [the completed control and native witnesses](../../reverse/attempt_support/bfme1-reference-08400aa3-20261027/readme.md)
  verify 98,522/98,522 function rows but finish with actual exit 1: six
  inconsistent vftable symbols plus one unproven camera data-size row.
  A read-only 304-row inspection reproduces all six table-base pairs at
  18 native operands. Several involve destructor `fold-proof` rows and their
  constructor/caller views; base/derived contracts and resolved data identity
  need verification before these folds can be accepted. The ProjectedShadow
  constructor views also need their actual table owners. These are versioned
  findings on the old inputs, not a current-master census or a proved
  replacement hierarchy. BFME 1 revision `08400aa3` was not adopted; the
  checkout remains `e74410b3`, the success stamp is unchanged and the claim
  is released. Check current master before repairing these sites; investigate
  the camera sizeof probe separately. No verifier, whitelist or source change
  was made and no new linked-byte gain is claimed.

- **Particle info lifetime prerequisite (2026-10-27, inspected `eba54d7587`):**
  [the bounded native/table handoff](../../reverse/attempt_support/particle-info-base-link-20261027/readme.md)
  tests the canonical Snapshot base for Rva0056224FCtor.cpp. All seven rows
  remain exact and the scoped DIR32 conflict clears, while the same-index
  ordinary preview preserves LINKS, 480 -> 480 bytes. The candidate's
  16-byte info table still emits three `__purecall` entries in place of native
  post-process, name and transfer handlers; its secondary emitter table also
  needs the actual overrides. The native getter returns
  `RenderObjectParticleUpdateModuleInfo`; a folded BoxEmissionVolumeInfo
  destructor name does not establish that constructor identity. The candidate
  is banked, production source/cache restored and claims released. Recover
  the complete class/table contracts and existing getter/transfer owners before
  retrying. This fixes no production unit and claims no new linking credit.
  **Update (2026-10-28, claudeb3, base 723bd233a1):** the full gate went red
  on DIR32 consistency (`??_7Rva0056224F@@6B@` bases 0x00BBB554/0x00C1D358).
  The canonical Snapshot base landed in production as the gate repair: 7/7
  exact, EH EXACT, `tools/dir32.py` one base each for `??_7Rva0056224F@@6B@`
  and `??_7Snapshot@@6B@`, link_check LINKS 473 -> 480 B. The 16-byte table
  still carries `__purecall` in the three Snapshot slots (the old view emitted
  a one-slot table, also not retail's); recovering the native post-process,
  name and transfer overrides remains open as above.

- **LivingWorldBattle traversal visitor (2026-10-28, claudeb3, base
  723bd233a1):** the same gate run found `??_7Rva003F498ACallback@@6B@` at
  0x00C1C780 and 0x00C37080: Rva003F6A91Dtor.cpp kept the visitor
  `Rva003F424F` novtable, so its inlined construction stored the interface's
  table name at the visitor's table. Target facts: 0x00C37080 = {0x003F55B6,
  0x003F4261}, the sibling 0x00C37064 = {0x003F5BBB, 0x003F4261}, and
  0x003F5BBB is already `Rva005FED52::invoke`. The slot-0 body is now
  `?invoke@Rva003F424F@@UAE_NH@Z` (VslotSmallBodiesL.cpp, same bytes), the
  visitor is an ordinary class in the dtor unit and RvaSmallVtableCtors.cpp
  shares its two-slot shape, so every emitter writes the same table and
  deleting destructor. Verified: 8/8, 195/195 exact; link_check
  Rva003F6A91Dtor.cpp 146 -> 153 B, VslotSmallBodiesL.cpp 165 -> 165 B,
  RvaSmallVtableCtors.cpp 2,669 -> 2,669 B; `tools/dir32.py` one base each for
  `??_7Rva003F498ACallback@@6B@` (0x00C1C780) and `??_7Rva003F424F@@6B@`
  (0x00C37080). Open: the folded deleting
  destructor 0x003F4261 is rowed only as `??_GRva005FED52`; the emitted
  `??_GRva003F424F` COMDAT has no row. Census confirmation pending.

- **Polygon renderer consolidation subset (2026-10-26, inspected cdf6e90a59):**
  [the scoped provider prerequisite](../../reverse/attempt_support/sol-b5-polygon-provider-20261026.md)
  found a 9/9-byte-exact merge changing the earliest scoped vector-constructor
  helper from 34 to 50 bytes. Keeping the existing optimization anchor in the
  TU's first include preserves the original 34-byte helper during composition.
  All nine rows, 12 selected scoped definitions/COMDAT flags, 18 references and
  five data bindings verify. The prerequisite is verified; the two-donor merge
  is left to Luna. Global selection and census confirmation are unclaimed.

- **Evidence / scope:** string erase/replace helpers and Render2D container
  destruction can resolve a symbol while retaining an incorrect selected body.
  Read the [prior linking handoff](../../reverse/attempt_support/link-seat-20261025-final.md)
  and its referenced string/compiler banks before trying another emission shape.
  The vector parent/helper contract in LINK-002 is another concrete example.
- **Completed:** selective emission has repaired some other families, recorded
  under LINK-001; it does not establish a fix for these remaining cases.
- **FX-list constructor subset cleared in ordinary preview (2026-10-25,
  after `feb95824fa`):**
  [the full dependency proof](../../reverse/attempt_support/fxlist-constructor-link-20261025/readme.md)
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
  [the bounded cleanup and identity handoff](../../reverse/attempt_support/fxlist-obsolete-emissions-20261025/readme.md)
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
  [the read-only cache-reference repair](../../reverse/attempt_support/map-metadata-borrow-link-20261025/readme.md)
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

- **Near-linking constructor scope (2026-10-26, inspected `896af216804e1f1e34de28bd318285fbbbfcc536`; index `d1f046749a`, retail-truth-4):** `BfmeConv881O1.cpp`, `RTS/PlayerRelationMapCtor.cpp`, `RTS/PlayerCtorBFME2.cpp`, `Rva00415704Ctor.cpp` and `StlSweepW4Rva001FEAB2.cpp` no longer replace three empty allocator/vector bodies with declaration-only specializations. The visible STLport bodies restore the native 64-byte hashtable-constructor shape instead of the former 77-byte shape. Removing only the allocator destructor declaration left 65 bytes; also revealing the vector constructor still left 65 bytes while its base stayed declaration-only. The complete change clears the corresponding ordinary-preview COMDAT/selected blockers. The sibling `StlSweepW4Rva001FEAB2.cpp` must change with PlayerCtor so their no-address copies agree; its 31-byte row remains exact and it still links. Raw paired previews, disassemblies, all six edited sources' byte/frozen/EH/data gates and the combined 149/149-row check are in `build/link-worker-w1/`; `build/link-report.md` maps each receipt. `comdat_verdicts.py` calls the resulting 64-byte copies `unknown`, so this is a cleared ordinary-preview blocker scope, not a full retail-body or census claim. Whole-unit blockers remain: two opaque XferSave element destructors, the PlayerRelationMap vtable, the 0x00415704 subsystem destructor, and PlayerCtor's existing UnitRevivalTracker/energy virtuals. Next check: reconcile those actual types and tables without restoring the three stale specializations. Census confirmation pending.
  - **`BfmeConv881O1.cpp` element types (2026-10-27, inspected `bcdd3415b2`):** still unresolved only on `??1Gen_t_009d80b0_p12cd`/`??1Gen_t_009d8120_p12cd`, emitted by this TU's +0x18 map unwind (retail funclet 0x007A6D28 jumps to the 5-byte hash_map dtor 0x0060D0AE). Target facts contradict the int-key/12-byte-mapped model: dtor 0x0060D0B3 tears +0x2C down through 0x0060CC99, whose clear 0x001DBCDC only frees nodes (trivial pair), and +0x18 through 0x0060D031, whose clear 0x0060CFB6 calls `_M_delete_node` 0x0060CF5A, which runs the 14-byte pair dtor 0x0007FAB3 on node+4 (frees the pair's *first* dword, i.e. a malloc-allocator `string` key). With XferSave.cpp's string-keyed (0x0060CAEA/0x0060D269) and `const char *`-keyed (0x0060CB2B/0x0060CDFD) finders, +0x18 is `hash_map<string, unsigned int>` and +0x2C `hash_map<const char *, int>`. Next check: retype both members, retarget the three `symbols.csv` pins (0x0060D06A x2, 0x0060CF76) to the new mangled names through `pin_admission.py`, and resolve the funclet's `~hash_map<string, unsigned int>` against the 0x0060D0AE owner (GapBodiesSeat10O1.cpp) by renaming that owner rather than adding a second name. Not attempted: the pin and owner-rename cascade outweighs the 138 B.
  - **Constructor cleanup / current boundary (2026-10-29, inspected `b6a65e10bf`):** removed 139 unused declaration lines from `BfmeConv881O1.cpp`. All four rows and its EH graph remain exact; 66 COMDAT fingerprints, 86 external symbol records and dependency edges are unchanged. Strict current preparation passes. Before/after ordinary previews against `840db2d676` retain the same two unresolved opaque-element destructors and zero linked bytes. The shared ctor/initializer identities, 0x0060D0AE owner and XferSave's clear/node provider family still require coordinated correction; `System/XferSave.cpp` currently calls the FXList-spelled clear. No retyping or pins attempted, no census gain claimed. [Checks and next prerequisites](../../reverse/attempt_support/xfersave-ctor-scaffolding-20261029-codexb4.md). Batch audit is INCONCLUSIVE: older index and no current receipt for affected consumer `Common/0CreateAHeroManager21FE49.cpp`; carry this scope into the next normal census.
  - **Finder consolidated (2026-11-02, base `0b27baa36db`):** the shared fold became available and the normal merge tool absorbs Rva0060D269 into XferSave: one fewer source file, all22 rows and EH3 exact, sole existing fold proof repointed. Strict receipts pass; ordinary preview retains the combined1294 bytes. 159 COMDAT copies are unchanged; three unrowed list helpers inline the same first-field cleanup (+7B each), with their existing selected owner retained in a bounded index overlay. No new retail-body claim for those copies. Registers/queues and active tooling path consumers audited; only historical references remain. Three direct consumer objects refresh30/30, but outgoing audit remains INCONCLUSIVE on older984a4cdc4d and missing current0CreateAHeroManager21FE49 receipt; carry this closure to the next scheduled census. Seven rejected donors, six mixed sources and constructor/type/provider prerequisites remain. [Application and audit](../../reverse/attempt_support/xfersave-finder-consolidation-20261102-bce2/README.md).
  - **Application held / publication boundary (2026-11-01):** a separate cleanup revision makes supported dry run accept XferSave plus Rva0060D269 (22 exact rows, link guard passes), but application writes nothing because shared fold7FAB3 is held by StarkillerHDX@fleet for AptMapPreview. No claim bypass or source move. The cleanup/accepted plan is preserved locally (commit2309a2c2941), with an evidence patch; publication retains only the two provider-preserving prerequisites. Restored cohort44/44 and EH8 pass. Outgoing audit is INCONCLUSIVE on older index0d24c60eef and missing current0CreateAHeroManager21FE49 receipt; carry that consumer/scope into the next census. No file or census gain. [Saved candidate, exact refusal and resume steps](../../reverse/attempt_support/xfersave-merge-held-20261101-bce2/README.md).
  - **String-node/iterator views (2026-11-01, base `0efa0eac7c8`):** the seed, finder and name writer now share the existing node/iterator spellings and payload-at10 contract. All 25 edited rows and 191 external COMDAT fingerprints/symbol sets are unchanged. Strict cohort44/44 and EH8 pass; eight of nine previews retain LINKS/2219, with the constructor's two opaque-dtor blockers unchanged. No source move or census gain. The finder gets past its composition declarations, but cached-object diagnostics locate a121vs128B miss at60D269: outlined string destruction replaces native inline cleanup. Test the seed's destructor specialization separately; other class/template/header/provider prerequisites remain. [Views, controls and exact composition boundary](../../reverse/attempt_support/xfersave-node-views-20261101-bce2/README.md).
  - **Fragment include context (2026-11-01, base `da2c4d00c25f`):** three XferSave fragments now take free from stdlib.h before STLport instead of declaring _STL::free. This clears their composition C2883; all seven edited rows, two EH graphs and three LINKS previews (627 bytes retained) pass. All 39 external section bodies/relocation shapes are unchanged after qualifying the sole free spelling change against native engine allocator30830. The supported merge still accepts no donor: node/iterator and XferSave views, open-writer adoption, byte and deque-provider prerequisites remain. No source-file or census gain claimed. [Controls and native call proof](../../reverse/attempt_support/xfersave-free-include-20261101-bce2/README.md).
  - **Private-view prerequisite cleanup (2026-10-30, base `758c0e2412`):** the seed, name writer and table helper now share the compiler-verified 16-byte finder view, preserving the helpers' `throw()` call contract. Unused helper declarations are removed; the block writer retains its existing node view to preserve its string `npos` provider. All 28 cohort rows remain exact; the four edited objects retain identical 101 COMDAT fingerprints, 148 external records and dependency graphs. Ordinary previews against `85f6b7f40c` retain six of seven linking units and the constructor's same two unresolved destructors. The constructor identity repair, include-context conflict, node/iterator views, open-writer layout/header adoption and bucket-number composition mismatch remain prerequisites. No merge or census gain claimed. [Verification and remaining work](../../reverse/attempt_support/xfersave-private-views-20261030.md). Strict provider preparation passes; batch audit remains INCONCLUSIVE on the older index and affected consumer `Common/0CreateAHeroManager21FE49.cpp` without a current receipt. Carry the scope into the next normal census.

**Assigned split-name/provider recheck (2026-10-26, inspected `896af216804e`):** `Rva006C3CC0Cluster.cpp`, `Rva006DE1A0Finish.cpp`, `Rva006F84C0DeletingDtor.cpp`, `AptPlayerTooltipMap.cpp`, `GameWindowManager_registerTabList.cpp` and `StateMachineDefineState.cpp` remain blocked against d1f046749a with current providers. No source change is retained. The allocator destructor calls the five-byte 0x00034D00 thunk, whereas its declared GeneralAllocator destructor pin targets the 309-byte 0x00033D50 owner; the real destructor/thunk identities need reconciliation without replacing a real destructor call by a placeholder. The pooled deleting destructor reaches the existing 37-byte `Rva006F8460` destructor, but its local complete-destructor definition is wrong; a folded-name/provider decision is required. The Apt value constructor retains the prior 15-slot hierarchy and split-class naming prerequisite; AptPlayer also needs its actual heterogeneous member types, the 68-byte `DetailedArchivedDirectoryInfo` destructor at 0x00224252 instead of `Rva00224C95`, and a complete table contract. The registerTabList call targets 0x002C54EE while the current list<GameWindow*> assignment row names 0x0046F0C2; State's eight-byte map still shares a falsely identified 16-byte-value `_M_insert` row at 0x0053479F. These are naming/ownership prerequisites, not missing bodies proven by an unresolved spelling. Preserve the earlier failed trials. Next: resolve each native identity before suppressing a copy or requesting a fold pin. Raw evidence and exact row homes: `build/link-worker-20261026-w2/dependencies2.log`, `native-rows.log`, `provider-paths.log` and `build/link-report.md`. No clearance or census claim.

- **Current-input string audit (2026-10-26, inspected `896af21680`, index `d1f046749a`):** `build/link-report.md` and `build/link-worker-20261026/` records fresh checks of both `Rva008312E0StringReplace.cpp` and `Rva008314E0StringReplace.cpp`, their BfmeConv providers, and all seven narrow forward-append emitters. The two replace units retain their four erase/replaceBase findings each; the documented frame and naming prerequisites are unchanged and were not retried. The append owner still emits its retail 254-byte body, while the first copy in `stlport_float_format.cpp` is an unproven 279-byte body; `urlBuilder.cpp` and `Rva001F9524Concat.cpp` remain blocked even when all seven current objects are supplied together. The recorded declaration and extern-template ICE trials were not repeated. Next check: establish an admissible retail copy or declaration strategy in the early emitter while preserving its rows, then recheck the entire seven-unit family. No string clearance or census gain is claimed.

- **String erase binding subset cleared in ordinary preview (2026-10-27, inspected `8a9e65cafe`):** Both replacement views now inherit the visible erase helper from a TU-local `basic_string<char>` specialization, binding their calls to the existing `0x00012150` owner. [Tracked repair evidence](../../reverse/attempt_support/string-erase-binding-20261027.md) records identical parent bytes, only the two intended relocation-name changes, 21/21 cohort rows, exact provider EH, and both identity-register retirements. Both obsolete erase pins are removed; no current object defines or references those spellings. Against fixed index `bf3dd31211` (2026-10-27 00:39), each caller loses its erase COMDAT/selected pair and retains only the replaceBase pair; the erase provider remains LINKS. This supersedes only the erase prerequisites in the earlier audits. The `0x0002A610` / `0x0002A730` replaceBase frame and owner-transition prerequisites remain open; next verify the banked template trial through an admissible row/name transition. No unit clearance or census gain is claimed.

- **String lead selection review (2026-10-28, inspected `a2002051b5`):** The picker served `Rva008312E0StringReplace.cpp`; current source already includes the erase-binding repair above. The documented replaceBase owner/signature prerequisite at `0x0002A610` is unchanged. No string source edit or repeated compile trial was made; claim released. The [selection review and independent header cleanup](../../reverse/attempt_support/20261028-list-owner-crt-header.md) record the scope. Next check remains an admissible owner transition before verifying the banked template trial; no clearance or census gain.

- **replaceBase template trial checked against link order (2026-10-28, inspected `5887b8bda4`, index `14dc3d2467`):** The owner transition is admissible: retract and re-add the row; `add_match.py` verifies the banked `BfmeConv1464.cpp` trial as `??$replaceBase@PAD@Rva008312E0String@@...` at 0x0002A610 (279 B). It still cannot land. In `link_check`, `BfmeConv1464.cpp` falls from 274 linked bytes to 0, and `Rva008312E0StringReplace.cpp` stays at 0. Two causes: (1) link order puts StringReplace first, because its lowest RVA is 0x000284D0, so its frame-0x44 replaceBase copy is the one kept; (2) BfmeConv1464 needs insertRange as an inline candidate, and its pick-any copy duplicates StringReplace's exclusive definition. Retail's own selection implies that 0x000284D0 and 0x0002AE50 come from different objects. Their file grouping, not frame codegen, is the remaining prerequisite, and tu_map gives these STLport rows no TU. Reverted; no clearance. Evidence: [link-order handoff](../../reverse/attempt_support/rva008312e0-replacebase-linkorder-20261028.md). Next check: TU evidence for either row, or retyping insertRange as STLport's member template in its own commit (row 0x000284D0 and five callers), which would let BfmeConv1464's conversion keep linking.

- **Clean C++ and insert-provider prerequisite (2026-10-30, base `574175bb6d1d`):** `BfmeS1155.cpp` now recovers the existing 279-byte forward replacement as clean C++, retaining its name, address and all twelve rows. The bank's real copy-length local restores the native 0xd4 frame in the merged header context. The insert owner uses `noinline inline`, preserving both row bodies while replacing its strong non-COMDAT definition with SELECT_ANY; the clean owner's copy is also ANY. The previous strong insert-definition conflict is cleared. Independent COFF comparison preserves all fourteen raw row bodies with only the deliberate binding to the existing real erase owner. Strict preparation passes 18/18 rows across both providers and four other direct callers. The six-source preview retains 5/6 LINKS and 2,070 authored bytes against `85f6b7f40c`; the range owner's separate replaceBase finding and grouping/identity prerequisite remain open. No census or unique-byte gain claimed. [Exact scope and proof](../../reverse/attempt_support/string-range-clean-cpp-20261030/readme.md). The outgoing audit exits 2 (INCONCLUSIVE): the index is older than the base and Common/0CreateAHeroManager21FE49.cpp lacks a current affected-consumer receipt. Carry the changed providers and wider consumer scope into the next scheduled census.


- **String lead selection review (2026-10-30, inspected `46af8b351c90`):** The default picker again served `Rva008312E0StringReplace.cpp`. The clean-C++ owner and insert-provider repair above are present; the remaining replaceBase selection/grouping prerequisite still stands, and neither range row has an approved TU. No string source edit or repeated compile trial was made. Body and file claims released; no clearance or census gain. [Selection scope and independent header cleanup](../../reverse/attempt_support/partition-allocator-release-20261030-codexb5.md).

**Waypoint-tree binding check (2026-10-26, inspected `2a45addda1806342ac5c52757f63be902dcd428e`):** `MapMetaDataCopyDeferred.cpp` remains L3/S3 against `d1f046749a` with the current `stlport_rb_tree_hint_00301883.cpp` provider. The emitted 165-byte tree copy constructor at 0x003025A5, 115-byte `_M_copy` at 0x00301F9B and 30-byte clone at 0x00301BBF have zero non-relocation byte differences. Their binding failures are concrete: the Coord3D clone pin names 0x00413E55 (also considered as 0x00013E55), whereas `_M_copy` calls 0x00301BBF; the node-creation pin names 0x0016D760, whereas the clone calls 0x003012CE; the header-base constructor pin names 0x0016D590, whereas the copy constructor calls 0x0030087C. The native clone and create operations already have the opaque-payload owners above. No pin, real type, row or shared header changed. Reconcile the typed owners and existing pins together; suppressing the only Coord3D-name definitions leaves no same-name provider. Raw byte/relocation diagnostics: `build/c136-gui-w2/map-native-targets.log`; all 21 assigned rows pass `final-assigned-build.log`. Clearance and census confirmation remain pending.

**Waypoint-tree selection recheck (2026-10-28, base `73a4520034`, index `41c28839bf`):** the current ordinary preview still reports the same three COMDAT and three selected-copy blockers, with 0 of the unit's 856 authored bytes linking. The typed node-creation and base-constructor names are already matched at 0x0016D760 and 0x0016D590 in `MapUtil.cpp`; the corresponding 0x003012CE and 0x0030087C targets belong to different existing owners. The clone pin still points to 0x00413E55. No source or ledger identity change was attempted: reconciling the distinct retail bodies and their consumers remains the prerequisite. No clearance or census gain is claimed. [Selection handoff](../../reverse/attempt_support/waypoint-tree-selection-20261028.md).

**Assigned record-family audit (2026-10-26, inspected `2a45addda1806342ac5c52757f63be902dcd428e`, index `d1f046749a`):** no source edit is retained in EvacuateDamageCtorModuleFactoryBody.cpp or ObjectCreationList.cpp. The Evacuate constructor's native EH cleanup reaches the existing 25-byte `Rva004B96CC` destructor, but two other rowed lifetimes in that source call the nocase-string tree destructor at 0x0002CC38 and the hashtable destructor at 0x0002CCC3. A declaration-only suppression would have no exact-name provider and would conceal those incompatible type identities. ObjectCreationList's rowed Payload vector construction reaches the existing 0x004F6A52 assignment worker, while destruction reaches the existing 0x005F85C8 stride-eight range worker. These are naming/type reconciliation prerequisites; no container reinterpretation, new pin or row change was attempted. Raw native references, exact owner names and the paired provider preview are in `build/c136-logic/`; all assigned sources pass the combined 118-row byte gate. The families remain blocked; no census clearance is claimed.

**Evacuate constructor recheck (2026-10-27, inspected `90b5ece91e`; index `73061d9452`):** the current ordinary preview still reports U1/L2/S2. The 0x0002CD7B destructor remains the misidentified INIMacroTable lifetime, and its current TU-map row is displaced with no approved destination. No source trial was repeated. Resolve the real macro-table member types and approved row ownership before changing this family; declaration-only suppression would still remove its only named providers. The [bounded recheck and independent CRT cleanup](../../reverse/attempt_support/tree-erase-crt-header-20261027.md) records the scope. Claims released; no clearance or census gain.

**Evacuate selection review (2026-10-28, inspected `38c5c62536`):** current
source, ownership map and prior handoffs retain the member-identity and approved
TU prerequisites above. No repeated source trial or fresh link preview; claims
released. The [selection record](../../reverse/attempt_support/mpgamesetup-crt-headers-20261028-codexb.md)
separates this blocked family from the independent header cleanup.

**Assigned W3D unmatched-emission cleanup (2026-10-26, inspected `2a45addda1806342ac5c52757f63be902dcd428e`; index `d1f046749a`, retail-truth-4):** `W3DRadar.cpp` drops eight unrowed donor methods and their private stealth helper, retaining every existing matched definition, the surface-value helper and the existing private-convention caller. No new body, pin, declaration spelling, shared header or ledger change is used. Radar is cleared in ordinary-preview scope; census confirmation pending. Raw baseline, paired current-object previews, matched-row checks, provider-removal audit and final gates are mapped by `build/link-report.md` under `build/link-worker-w5-c136/`. The retained Radar cleanup label is verified through its parent's exact EH graph after compiler renumbering. A separate w3d_dep scanner-removal trial was fully reversed after the wider current-provider check found a linking string-list consumer losing seven helpers (LINK-020); its smaller-scope LINKS result is not retained repair credit. The broader entry remains open; verify Radar in the next normal maintainer census.

**Assigned constructor/lifetime audit (2026-10-26, inspected `2a45addda1806342ac5c52757f63be902dcd428e`; index `d1f046749a`):** current paired providers preserve the earlier PlayerCtorBFME2 hashtable repair. The unit still lacks its declared virtual UnitRevivalTracker destructor and three Rva002B0F3CEnergy virtuals. The existing UnitRevivalTrackerCtorBFME2 view has a single xfer slot and a nonvirtual vector lifetime; the constructor's energy table instead reaches the existing Energy::xfer at 0x004DF290, name getter at 0x002AA3AF and empty slot at 0x000B3FD0. Correcting those declarations requires the complete lifetime/table contract, not a new destructor match inferred from the unresolved name. `Rva006CBF40Deferred.cpp` retains its seven nonretail complete-destructor emitters: the native deleting rows reach 0x006D1090, 0x006D6340, 0x006D63C0, 0x006E96D0, 0x006EB6A0 and 0x006FE460 under other existing owners. Neither source was edited. Raw evidence: `build/link-worker-w6/row-reference-witnesses.log`, `vtable-witnesses.log` and `paired-after.log`. Next check: reconcile the actual bases/member lifetimes with those row owners; no new fold pin has been proven. Clearance and census confirmation remain pending for these units.

**Player constructor checkpoint (2026-10-30, revision `50472e739d`, index
`12b9e7a7c0`):** ordinary preview retains the four unresolved names above.
The native 14-byte funclet at 0x00775E39 adjusts to Player +0x738 and calls
existing cleanup owner 0x002B0B8E. That eight-byte wrapper adds four and
tail-calls the existing vector destructor at 0x002B0B32; it does not perform
virtual destruction. This independently confirms the lifetime prerequisite,
without proving a second destructor body or an ICF alias. No source, ledger
identity or pin changed. Tracker cleanup identity and the three energy-table
bindings remain open; no clearance or census gain is claimed.

**Assigned FX and curve check (2026-10-27, inspected `97c23353111e60304b56434c02d20bee3465d83f`, index `5ce093a71a`):** `FXList.cpp` still has U2/L3/S2 with its current particle and hashtable providers. The earlier StringBase/list and one-string FXList-copy identity prerequisites remain; declaration-only list suppression was not retried. `curve.cpp` still has U3/L1/S1, and `find_declared_unmatched.py --fail` also refuses its unrowed curve implementations. Its three matched DynamicVectorClass lifetime rows remain exact. Removing the curve donor implementations would remove interfaces used by the currently linking `vehiclecurve.cpp` and `lookuptable.cpp`; no such removal was attempted. Reconcile the native curve/key and persistence interfaces before editing this frozen unit. No source change, clearance or census confirmation is claimed for either unit.


**GeneralAllocator destructor identity resolved in scoped proof (2026-11-03, base8661f15284):** the split-name paragraph's allocator prerequisite now has a genuine canonical destructor provider at34D00, replacing only its same-source address-placeholder row. Native normal6C3D08 and unwind7A7CF0 both reach34D00->33D50; exported MemoryPool allocator types independently prove the class spelling. The separate309B bool cleanup is preserved; its incorrectly addressed destructor pin is removed. Cluster adopts the canonical0x510 GeneralAllocator base with0x174 remaining padding, preserving member684. Normal22/22, parent EH EXACT, provider payload/properties preserved apart from the5B name; exactly1header queue retired through accept and1pin retired through owning refresh. Preview keeps provider LINKS111B and clears Cluster0->103B against23b85ddde5. No official linker/census/runtime clearance claimed. Rva006C1F60's own member-lifetime header surface and all unrelated split-name prerequisites above remain open. [Native, export, provider, consumer and retirement evidence](../../reverse/attempt_support/generalallocator-native-destructor-20261103/README.md). Prior8661f15284 batch audit remains INCONCLUSIVE (5receipt gaps, first DeferredWalkers; index23b85ddde5/based83ee506516b1e311c77658f28d1c40a6ad1bf90); carry recorded scope into the next scheduled census.


**Apt scalar-delete emission boundary (2026-11-06, base bd49217dc81, chat10 seat2):**
The identity queue serves Rva006CBF40Siblings.cpp's70A560 binding to existing
complete-destructor owner709B80. Removing the three local empty complete
bodies (70A530/560/590 names) preserves declarations/pins but suppresses all
three scalar deleting COMDATs: normal build fails symbol-not-found3/5,
other2 checks and data1 pass. Original source restored; all three debt keys
remain. No new famgen/tagged-constructor scaffolding, body, pin or alias was
added. This correct byte-gate refusal requires genuine class/emission
reconciliation before retrying; no preview, full-link or runtime gain claimed.
[Trial, exact scope and prerequisites](../../reverse/attempt_support/apt-sibling-emission-20261106-c10-seat2.md).
