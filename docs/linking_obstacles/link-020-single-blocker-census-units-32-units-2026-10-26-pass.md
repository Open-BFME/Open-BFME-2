### LINK-020: single-blocker census units (32 units, 2026-10-26 pass)
Status: Open. Updated: 2026-10-26; inspected revision: 655f117955; census 2026-10-26 08:28 at 47e030bafc.
Evidence / affected units: `link_rank.py --json` listed 32 census units with exactly one blocker
(14 U, 8 L, 6 S, 3 A, 1 D). Two seats rechecked every one with `link_check.py --fetch-index` and
`--refresh`. Neither committed a change.
Completed:
- Already link on current master (the census entry is stale; verified with `--refresh`, no edit):
  `XferSave.cpp` (1,060 B), `VectorRangeEraseRva003F6975.cpp` (80 B), `stlport_float_format.cpp`,
  `stlport_narrow_stringbuf_overflow_setbuf.cpp`, `stlport_narrow_ostringstream_dtor.cpp` (429 B),
  `urlBuilder.cpp` (868 B), `StlportNarrowAppendCStr.cpp` (58 B), `Rva001F9524Concat.cpp` (160 B).
- A trial declare-only `basic_string::append<const char*>` specialization in the STLport narrow-string
  units hit C1001 at `_string.h(573)`. It was reverted, and those units link without it.
Remaining / next check (each needs a decision, a row or a shared change; none is unit-local):
- `_String_base<char>::_M_throw_out_of_range` (U in `stlport_narrow_string_copy`, `_substring_ctor`,
  `_erase_count`, `_substr`): cleared upstream by 1e45b8be0f, which supplies the body from
  `stlport_vector_voidptr_alloc.cpp`. All four units LINK when `link_check.py` is run together with that
  provider (LINKED 0 -> 904 B). Run alone, a stale provider object still reports them as unresolved.
  The provider's 4.6 migration preserves 31/31 rows and its 3,902-byte preview; with the current
  provider, all four consumers retain their combined 904-byte preview against index `85f6b7f40c`.
  Carry the provider and consumers into the next census; no new census gain is claimed.
- `_Destroy<Rva002BBB96Element*>` and `_Destroy<Rva004758F4Element*>` (U in
  `StlportVectorDtorDeferred.cpp` and `StlportVectorClearRva00475F2A.cpp`): pins only (0x002BB6A5,
  0x00470398); the owners are `__destroy_aux` rows with a two-argument push. This needs a `_Destroy`
  owner row or a caller rewrite.
- `vector<PrereqUnitRec>::operator=` (U in `StlSweepW5Rva0042830DAssignTwin.cpp`): a wrong premise.
  Retail 0x0042816E calls 0x000120C0 twice, the rowed 41 B narrow `basic_string::operator=`, so the
  element holds two strings, not vectors. The twin now uses two `basic_string<char>` members and LINKS
  (0 -> 33 B). `ThingFactory.cpp`'s `ProductionPrerequisite::operator=` row at the same address still
  declares the vector layout; reconcile that view separately.
- `AcademyStats::recordSpecialPowerUsed` (U in `SpecialPowerModule.cpp`): the call comes from the
  present-unmatched ZH `initiateIntentToDoSpecialPower`. Retail's 0x004946F3 makes no AcademyStats call,
  so there is no retail body to recover. Find a retail caller of the stat, or drop the ZH call from the
  unmatched body.
- `g_00DB5BD4` (U in `Rva000FDCD7Get.cpp`): the old inferred 144-byte
  `data_ledger.csv` interval at `0x009B5B88` does not prove storage for this
  filter. The matched data row at its start owns only the four-byte
  `BfmeScreenTransitionSwapCounter`. Rechecked 2026-10-28 at `ee6402fcd2`,
  ordinary index `d92e7e6635`: the caller remains byte-exact (26 B), with this
  filter object its sole unresolved reference. Recover the complete object
  and initialized vtable before registering ownership, as LINK-007 requires;
  a ledger split alone cannot clear it.
  [Evidence](../../reverse/attempt_support/filter-slot9-owner-20261028-codex3.md).
- `latest_texture` (U in `DebugStatisticsTextureShutdown.cpp`): a file-static in
  `DebugStatisticsRecordTexture.cpp`; the thunk belongs in that TU (consolidation).
  Cleared in ordinary-preview scope, 2026-10-28: the recording unit now owns
  the shared handle and vector, with reset/shutdown fragments declaring that
  storage; the reporting consumer also shares the vector with its vptr restored.
  All 941 rows, including both initializers and shutdown callbacks, remain exact;
  the shutdown unit changes from unresolved to LINKS. Six data-debt keys and
  five address-global hatch occurrences are retired. TU consolidation remains
  separate. [Storage evidence and preview limits](../../reverse/attempt_support/texture-statistics-storage-20261028-codexb.md).
  Census confirmation is pending. The large thunk unit retains the same
  unrelated unresolved freelist-clear reference in both previews; its current
  FreelistPool.cpp provider is absent from this census index.
  Publication reconciliation: upstream `fc5da7fbc2` independently landed the
  shared storage with C++ linkage and the compiler-owned _$E5 shutdown row.
  The replay keeps those definitions and retains the earlier investigation
  as evidence only; its debt reductions are already upstream, not additional.
- `@_RTC_CheckStackVars@8` (D in `RtcStack.cpp`): also defined by the vendored msvc71crt lib. This needs
  an owner decision.
  Rechecked 2026-10-28 at `51fa553a3c`, ordinary index `41c28839bf`: the
  duplicate remains the sole blocker (86 authored preview bytes). The native
  member supplies the rowed `__RTC_CheckEsp` sibling; moving the clean checker
  back to the archive is forbidden, and neither address has approved TU
  placement for a source move. No repeat of the failed inline trial or source
  change. [Ownership prerequisite and checks](../../reverse/attempt_support/rtc-stack-owner-20261028-codex.md).
- `ChunkLoadClass(FileClass*)` (U in `w3d_dep.cpp`): retail's constructor takes `BFMEChunkInput*`
  (row 0x00614EF0). The unit also has six unresolved `__imp_` STL names.
- `BridgeScaffoldBehavior.cpp`: the unresolved `UpdateModule::loadPostProcess` is gone on current
  inputs, but duplicate-definition blockers (ctor, `update`, `xfer`, interface getter) remain.
- `??_7Debug@@6B@` (L in `DebugDestructorThunk.cpp`): **2026-11-01 correction:**
  retail has46 slots, not the previously stated37; destructor remains at16.
  Constructor38440 and dtor38710 installBBE810; distinct command-interface ctor38670
  installs the next tableBBE8C8, proving the184-byte boundary. The shared shim
  still emits35. Native bool/int64 stream slots9/4/3 retain nonvirtual row spellings;
  `rename.py function --virtual` currently refuses operators before their evidence.
  Correct overload selection is a tooling prerequisite; adding only a dtor slot
  does not recover this interface. Original preview12902e9e1b retains ctor418 and
  debug_debug2295 while dtor99 code bytes still fail. No source/pin/header changes
  or clearance. See `reverse/attempt_support/debug-vtable-native-20261101/readme.md`;
  the older37-slot handoffs are retained as superseded history.
  **Tooling follow-up:** exact bool/int64 operator virtual planning is now covered
  by131 passing targeted tests (one empty fixture set skipped), and real slots9/4/3
  pass dry-run planning. The21 broader failures reproduce on the untouched module.
  No game source/row changed; native prefix/provider/table recovery remains open.
  See `reverse/attempt_support/debug-stream-virtual-tooling-20261101/readme.md`.
  **Provider source follow-up:** all3 actual UAE stream bodies now match privately
  and normal verification passes18/18 own plus1345/1345 dependent rows (49 sources,
  57 data rows). The final unstaged-dependent guard correctly refuses because
  debug_debug.cpp's duplicate-emitter cleanup is outside the rename Plan.after
  footprint. Metadata and all3 source files are restored. The next change must
  journal/claim/stage/verify owned C++ preparations in the normal transaction,
  retaining that guard. No linking clearance or gain; exact candidate and full
  refusal: `reverse/attempt_support/debug-stream-providers-20261101/readme.md`.
  **Preparation API follow-up:** owned CPP edits can now enter the same in-memory
  plan, claims, normal verification, staged footprint and rollback.177 targeted
  tests pass; the broad21 failures reproduce the unchanged control. No Code/row
  change yet. Retry the exact provider candidate through this API; the unstaged
  guard is unchanged. See `reverse/attempt_support/rename-source-preparation-20261101/readme.md`.
  **Applied provider follow-up:** the normal joint transaction now qualifies all3
  existing operators as native UAE members and removes exactly their competing
  unrowed definitions. Default checks pass18/18 own and909/909 dependent rows
  (25 sources,29 data rows); frozen checks and CSV pass. Ordinary index12902e9e1b
  preview retains2909 bytes across bool/long/main/ctor; dtor99 still fails.
  These196 existing bytes add0 unique coverage and no census credit. Full46-slot
  recovery and AddOutput/interface ownership remain open; outgoing consumer
  auditing and the next census must cover the changed provider identities.
  Evidence: `reverse/attempt_support/debug-stream-providers-20261101/readme.md`.
  **Outgoing audit boundary:** b169014cc7 passes normal hooks. Bounded strict
  preparation of ctor/long/main passes19/19; the consumer audit still returns2
  (older index12902e9e1b; first strict receipt missing in
  Common/0CreateAHeroManager21FE49.cpp). Its ordinary bytes passed, which is not
  strict closure proof. Carry changed providers, ctor/dtor and their transitive
  consumers to the next scheduled census; no general consumer clearance.
- `??_7GameWindow@@6B@` (L in `GameWindowDtor.cpp`): the 0x0080BBCC table is shared with
  `BfmeAptScreenBase`. This needs a class-view reconcile.
- `VectorClass<Vector3>` deleting destructor (S in `vector_class_vector3_ctor.cpp`): see LINK-015.
- `PartitionData::updateCellsTouched` (S): the kept body is a 426 B SSE method, but retail 0x73AD90 is
  a 1,158 B x87 body. Resolved in `PartitionData_friendUpdateCellsTouched.cpp` via native `ShroudManager::Data::UpdateCellsTouched` (LINK-037).
- `WeaponTemplate::getName` (S in `Weapon_getName_Thunk.cpp`): an ICF alias at 0x28F940, shared with
  `NetCommandMsg::getContentsAsAsciiString`. This needs an owner decision.
- Pod28/Pod32 vector copy and `_M_fill_insert` (S in `Rva00541913CopyCtor.cpp`,
  `Rva0056616BCopyDeferred.cpp`, `stlport_pod28_vector_resize_value.cpp`): see
  `reverse/attempt_support/pod-copy-link-20261024/readme.md`.
- `ConstIntGettersAddr.cpp` and `ConstIntGetters2Addr.cpp` (A): the flagged values are returned
  constants, not addresses; there is no global to bind. This looks like a heuristic false positive.
Clearance: the 8 already-linking units preview LINKS against index 47e030bafc with current objects.
Census confirmation: awaiting the next census.

- **Assignment current-input audit (2026-10-26, inspected `896af21680`, index `d1f046749a`):** `build/link-report.md` and `build/link-worker-20261026/` supersedes the earlier already-linking append observation for this fixed index: the seven current append emitters still block the two assigned consumers, as detailed in LINK-006. `RtcStack.cpp` retains the native-library duplicate; a noinline-inline trial previewed LINKS only because its matched symbol disappeared, so the failed byte check forced reversal. The final 90-byte row is exact and still duplicate-blocked. The `Weapon_getName_Thunk.cpp` native callee at `0x0028F940` is the existing `NetCommandMsg::getContentsAsAsciiString` row: it ignores `this` and constructs from the empty-string global, so changing a shared WeaponTemplate accessor to fit it would require first settling the wrapper identity. The Debug vtable and file-static latest-texture ownership prerequisites remain unchanged; no forbidden shared-header, row-move or pin trial was made. Next checks: resolve the CRT owner policy, establish the weapon-wrapper identity, reconcile Debug slots, and recover the texture thunk in its proper owning TU. No clearance or census gain is claimed for these units.

- **Current address-blocker clarification (2026-10-26, inspected `896af216804e1f1e34de28bd318285fbbbfcc536`; index `d1f046749a`):** the ordinary preview still reports A=1 for `ConstIntGetters2Addr.cpp` and A=1042 for `ConstIntGettersAddr.cpp`. The former's 0x00424F58 literal is inside a rowed string body and its meaning remains unasserted. The latter now contains large FieldParse/data initializers as well as getter immediates, so the earlier blanket false-positive explanation does not establish the meaning of its current findings. No literal, row or data ownership was changed. Raw before/after previews and the successful 149-row combined byte gate are in `build/link-worker-w1/`; classify actual datum ownership before changing these values or the heuristic. Clearance remains pending.

**2026-10-26 current-provider recheck, inspected `896af216804e`:** the d1f046749a index still reports one append COMDAT blocker for each of `StlportNarrowAppendCStr.cpp`, `stlport_float_format.cpp`, `stlport_narrow_ostringstream_dtor.cpp` and `stlport_narrow_stringbuf_overflow_setbuf.cpp` when the four are checked alone. Supplying current `stlport_narrow_string.cpp` and `stlport_narrow_string_append.cpp` in the same call makes all six LINKS. The former changed since the index and now emits the native const/mutable append bodies. This is inherited repair, verified without any string-source edit or repeated C1001 trial. Repeated 40-unit before/after previews preserve all four results; all assigned rows byte-verify. Raw evidence: `build/link-worker-w5/before-all.log`, `before-strings-current.log`, `before-cohort.log`, `after-cohort.log` and `all-assigned-build.log`. These four units are cleared in ordinary-preview scope; census confirmation pending. Their preview bytes are not new repair credit for this worker.

**W3D dependency scanner follow-up (2026-10-26, inspected `2a45addda1806342ac5c52757f63be902dcd428e`; index `d1f046749a`):** the `ChunkLoadClass(FileClass*)` and six imported STL references in `w3d_dep.cpp` belong to its unrowed donor scanner. Removing that scanner preserves its equality row and previews LINKS, but the wider 618-unit current-provider check makes previously linking `stlport_list_string_erase_00424363.cpp` lose `_S_merge`, `_S_sort`, `_S_unique`, allocator-proxy `swap`, the string-list `_List_base` constructor/destructor and `_M_create_node`. The entire scanner-removal trial was reversed, and the restored consumer links again. Raw evidence: `build/link-worker-w5-c136/final-before-cohort.log`, `final-after-cohort.log`, `terminal-w3d-restored-preview.log`, `terminal-w3d-restored-build.log` and `terminal-after-cohort.log`. The earlier cached-object audit found no external reference only because that consumer object was stale; it does not override the freshly compiled result. Next check: recover those exact current string-list provider dependencies together before removing the donor scanner, potentially retaining the required existing primary-template instantiations explicitly. This seat stops on the demonstrated consumer regression. No w3d_dep edit, clearance or census gain is retained. **Update (2026-10-29):** the consumer now emits those helpers itself and the scanner is removed; see LINK-143.
