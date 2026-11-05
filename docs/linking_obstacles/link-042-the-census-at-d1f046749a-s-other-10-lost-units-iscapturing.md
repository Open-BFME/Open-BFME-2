### LINK-042: the census at d1f046749a's other 10 lost units (IsCapturing respelling and four TU merges)

**Multiplayer seed follow-up (2026-10-28, `d5843cec`, index `d92e7e6635`):**
native layout/table reconciliation retains the explicit out-of-line color-copy
declaration, exact pair/getColor rows and LINKS/97-byte prediction. Removing
donor-wide includes drops only data COMDATs already selected from the unchanged
FiringTrackerXfer provider; the native VCI provider also remains selected.
This preserves the pair-copy fix and prepares LINK-009's later lifetime merge;
it does not clear the whole register or claim a new census result.
[Independent evidence and limits](../../reverse/attempt_support/multiplayer-settings-layout-20261028.md).

**Status: Open (partial repair landed). Updated: 2026-10-26; inspected revision: e9bab0ff07.**

- **Evidence / scope:** the units besides LINK-041's 23 that linked in the census at
  47e030bafc (or were linked before their merge) and not at d1f046749a, 3,997 B in all.
  Blockers read with `tools/link_check.py --census-only`; causes traced to the commits below.
- **Completed:** 397acb4f2e moved `IsCapturing` under `public:` in five WW3D class views to
  match the ledger's unowned `?IsCapturing@WW3D@@2_NA`, but `ww3d.cpp` defines it private
  (`?IsCapturing@WW3D@@0_NA`). Reverted ("Revert 397acb4f2e"): `WW3DBeginRenderBFME2.cpp`,
  `WW3DStartMovieCapture.cpp`, `WW3DShutdownRenderDevice.cpp`, `WW3DStopMovieCapture.cpp`,
  `GapBodiesGE41_Rva00118610.cpp`; `./build.sh` 8/8, preview 0 -> 818 B.
- **Capture-owner ledger follow-up (2026-10-27, base `6f7952d716`):** the five
  consumer fixes are already upstream. The existing private one-byte owner is
  now recorded separately, with seven native DIR32 operands and the zero
  initializer verified. The current six-source cohort passes 31 function rows
  and five data rows. [Current evidence](../../reverse/attempt_support/ww3d-capture-data-owner-20261026.md)
  preserves the historical preview separately; no new census gain is claimed.
- **Remaining** (all four came from `tools/tu_skeleton.py --merge`, which accepts a donor and
  chooses the `// cl:` line by matched rows only, not by whether the target still links):
  - `GameFont.cpp` (1,758 B), bdf96f6de4: absorbed `StlSweepR3Rva00218E09.cpp`, which never
    linked (3 unresolved `Rva00218E09Record` members, pinned non-retail `__median` /
    `__unguarded_partition` copies). Next: give the record its real type (the copy ctor is
    already bound to `MixFileCreator::FileInfoStruct`'s) so its members resolve.
    **Repaired 2026-10-26 (b5c5d490a1, agent K9):** the record now carries
    `FileInfoStruct`'s 16-byte layout (CRC, Offset, Size, `AsciiString` Filename) with an
    inline signed-CRC `operator<` (the compare the rowed partition 0x00217AB0 does). The
    implicit dtor and copy-assign are inline, so the three unresolved members disappear,
    and the emitted `__median` / `__unguarded_partition` copies are retail's.
    `./build.sh` 26/26; `tools/link_check.py` (d1f046749a index): `GameFont.cpp`
    0 -> 1,758 B; `MixFileCreatorFileInfoStructAssign.cpp`, `stlport_int_algorithm_bodies.cpp`
    stay linked. The copy ctor still binds through the file's existing `/alternatename`
    (renaming the record to `MixFileCreator::FileInfoStruct` would retire it; not done).
    **Identity cleanup 2026-10-27:** the current scan already accepts `bfmeEachQR`'s
    copy binding as a fold. Its source-wide retirement was blocked by two opaque
    sort-helper bindings. An explicit STLport introsort specialization now calls
    the existing 0x00217AB0 partition and 0x00218BD4 partial-sort owners. All 26
    GameFont rows (38 with the partition provider) still byte-match; identity is
    63 references, zero wrong bindings. The owning tool retired one registered
    identity key; two no-longer-emitted helper pins were removed and their hatch
    counts lowered. Preview at bf3dd31211 stays 1,758 + 357 B, with no new census
    gain claimed. The existing copy alias and opaque record name remain.
    [Evidence](../../reverse/attempt_support/gamefont-sort-identity-20261027.md).
    **Header prerequisite 2026-11-05:** three FontLibrary private views adopt the existing canonical header (68/68 rows exact; three queue rows retired; preview 4,278 -> 4,278 B); the lookup merge now reaches byte comparison, while the parser needs its Rva002186EB container view reconciled. [Evidence and remaining merge blockers](../../reverse/attempt_support/gamefont-fontlibrary-header-adoption-20261105.md).
  - `statistics.cpp` (986 B), 01a7f0d9ba: absorbed `Rva001296F0Destroy.cpp`, which never
    linked (`extern "C" textureStatisticsString`, while the string is a file static in
    `DebugStatisticsRecordTextureEnd.cpp`; non-retail `??1Rva001880D0Dtor` copy).
    **Repair landed / awaiting census (2026-10-26, K5, 320523b560):** the body now forwards
    the ledger's `texture_statistics_string` (defined in this file, 0x009EE91C) to the
    0x001880D0 row `Rva001880D0StringCleanupForward::cleanup`; `./build.sh` 33/33,
    `link_check statistics.cpp wwstring_free_string.cpp dx8wrapper.cpp ww3d.cpp` predicts
    0 -> 986 B, partners unchanged (index d1f046749a). Census confirmation: awaiting.
  - `CrateSystem.cpp` (259 B), aab36803a7: the donors were `/O1 /G6 /D_STLP_NO_EXCEPTIONS`;
    under the TU's flags the emitted `list<Rva0035CBB2Element>::insert` (pinned 0x0035CB8D)
    is not retail's. Declaring it only leaves it unresolved (a pin does not satisfy the
    census), so the copy itself has to match.
    **Repaired 2026-10-26 (aa04b88683, agent K9):** 0x0035CB8D is the matched row
    `list<crateCreationEntry>::insert`, so the two absorbed rows (0x0035CBB2
    `_M_insert_dispatch`, 0x0035CC18 range `insert`) are `list<crateCreationEntry>` members.
    Instantiated over `crateCreationEntry` instead of `Rva0035CBB2Element`/`Rva0035CC18Element`,
    the TU emits retail's insert copy; the two `symbols.csv` pins that bound the placeholder
    callees were dropped. `./build.sh` 5/5; `tools/link_check.py` (d1f046749a index):
    `CrateSystem.cpp` 0 -> 259 B, `CrateCreationEntryListInsert.cpp` stays linked.
  - `MultiplayerSettings.cpp` (97 B) and `MultiplayerColorDefinitionCopy.cpp` (79 B),
    b93c4b507b: the merge dropped `/FIzh_ascii.h /DNDEBUG /DWIN32 /D_WINDOWS
    /D_STLP_USE_MALLOC /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE` (unresolved
    `AsciiString::freeBytes`, non-retail `~MultiplayerColorDefinition`), and the absorbed
    `pair` copy (0x00380DA3) now emits the implicit `MultiplayerColorDefinition` copy ctor,
    which clashes with `MultiplayerColorDefinitionCopy.cpp`'s. Restoring the flags fixes the
    first two blockers but fails the `pair` row (it inlines the copy ctor); tu_map already
    places 0x00380D30 in this TU, so merging `MultiplayerColorDefinitionCopy.cpp` here is
    the likely fix.
    **Repaired 2026-10-26 (c923d4c567, agent K9):** restored the dropped flags and replaced
    the ZH header include with a TU-local copy of its view whose `MultiplayerColorDefinition`
    declares (does not define) its copy ctor, so the `pair` row calls 0x00380D30 out of line
    and nothing re-emits it; no merge needed. `./build.sh` 2/2; `tools/link_check.py` on the
    d1f046749a index: `MultiplayerSettings.cpp` 0 -> 97 B, `MultiplayerColorDefinitionCopy.cpp`
    0 -> 79 B. Census confirmation pending.
- **Process note:** before applying a merge, `tools/link_check.py` the target TU and refuse
  the merge when a target that linked stops linking.
- **Guard (2026-10-26, 40bf8d4d7a, 1d3eaaf01f, 01e0e3a952):** `tu_skeleton.py --merge` now
  does this itself (`LinkGuard`). When the target or a donor links at the census, every
  candidate text is judged as one object against the census index (`link_check
  check_object` and `new_variants`, the absorbed units removed). A donor that would leave a
  linked unit not linking is rejected; a merge it cannot judge (no index, a linked unit
  missing from it, a link position it cannot model) is blocked. Dry run on real data:
  `W3DRopeDraw.cpp` refuses the never-linked `W3DRopeDrawCtor.cpp` (unresolved
  `__node_alloc::deallocate`, two losing COMDATs). Initial gaps: the split lane
  (covered by the follow-up below), merges in which no unit links, and changes
  to other units since the census.
- **Moved providers (2026-10-27):** with 790 commits since census bf3dd31211, the
  guard blocked unchanged seeds: `Recorder.cpp` read `unresolved ??0Rva0060C5FA`
  (its one census definer `Rva0060C5FACtor.cpp` went into `Xfer.cpp`, 0eff857b88)
  and `ControlBarScheme.cpp` `unresolved ??0INI` (`INI_ctor.cpp` into `INI.cpp`,
  ee70325db0). `LinkGuard.moved_provider` now excuses an unresolved name only
  when every census definer is a gone unit and a matched ledger row puts it in a
  unit outside the merge that the next census links. Other staleness (a live
  unit's own changes since the census) remains a gap; the next census confirms.
- **Split protection (2026-10-26):** `tu_skeleton.py --split` now compares a
  freshly compiled original mixed file and existing destination against the
  residual/destination pair, at their actual post-carve link positions. The
  existing byte checks remain. New blockers, a clean destination inheriting
  donor debt, missing outside providers, changed alias routes, new outside
  duplicates/COMDAT losers and changed selected implementations refuse the
  candidate before application. Existing debt remains visible. Moved unknown
  copies require matching raw relocation context and stable outside referents;
  changed `/MAP` exceptions need measured evidence. Regression fixtures use
  real COFF readers and the census rules, including accepted cross-file calls,
  COMMON providers, unchanged debt and dry runs. The scope is the two affected
  compiled units plus the census's outside-provider evidence; changes elsewhere
  since that census remain a limitation. No game source or census was changed.
  Verification: 259 tests and 17 subtests passed, with one existing skip. One
  Windows CRLF-writing split-ledger fixture was deselected after reproducing
  its LF-refusal on the original HEAD tooling; ledger validation stays enforced.
- **Guard false reject (2026-10-27):** the PR115 INI merge preserves its existing
  21-byte `rts::equal_to<AsciiString>` copy and its precedence over ThingFactory,
  but the trial view forgets that ThingFactory already lost before the merge.
  [The pre-merge evidence](../../reverse/attempt_support/ini-linkguard-premerge-baseline-20261027.md)
  distinguishes unchanged debt from newly broken outside units. A separate
  verifier repair and a fresh guard after rebase remain prerequisites; no
  source workaround, census gain or linking clearance is claimed.
  The separate verifier repair is now tested against authenticated old object
  bytes and the real before/after order: 228 tests and 11 subtests pass (one
  existing skip), and the bounded eight-object INI replay reports no problems.
  Missing raw proof, private/weak/alias context, a changed selected body or a
  newly referenced losing copy remain refused. The final guard after rebase
  and census confirmation are still pending.
- **Census confirmation:** awaiting the next census.


- **Bounded duplicate follow-up (2026-10-26, inspected `896af216804e1f1e34de28bd318285fbbbfcc536`; index `d1f046749a`):** `MultiplayerColorDefinitionCopy.cpp` still collides with MultiplayerSettings.cpp's implicit copy constructor. The explicit 79-byte body is retail-correct; the merged provider's implicit copy is not. No repeat of the failed flag trial and no source edit were made. Preventing that implicit copy requires the shared MultiplayerColorDefinition declaration to declare the out-of-line copy constructor, or the separately approved TU reconciliation; this seat forbids shared-shim edits and row moves. The raw index providers, ordinary previews and unchanged byte gate are in `build/link-worker-w1/`. No clearance claimed.

- **INI integration guard verified (2026-10-27, base `72327e6ccf`):**
  [the current integration receipt](../../reverse/attempt_support/ini-publication-current-provider-audit-20261026.md)
  passes 57/57 current rows and the fresh eight-object pre-merge guard with
  authenticated census-object evidence, `problems: []`. Seven whole donors
  move 14 existing rows / 906 bytes. The outgoing path audit finds no active
  removed-path consumer, and the unrelated HeaderTemplate queue row is
  preserved. This clears this INI consolidation guard only; the broader
  obstacle, official census and runtime confirmation remain open.

**Guard provider-index prerequisite (2026-10-26, inspected `442a92e102`,
rebased through `6c583e82f0`):** MetaEvent's unchanged merge trial accepts
nothing against index `5ce093a71a`. The guard removes obsolete
GameMessageIntWideArgs/GetArgument objects but does not refresh their
replacement definitions in MessageStream.cpp, leaving integer append and
argument access unresolved in the seed. The current provider verifies 18/18
rows; the six fragments preview cleanly at 1,389 authored bytes. Including the
provider in the ordinary preview instead exposes its duplicates against the
obsolete objects, so whole-image closure is not established. The
[bounded handoff](../../reverse/attempt_support/consolidation-metaevent-prerequisites-20261026-codex4.md)
records both results and independently verified canonical base/string
declaration cleanups. Next: a coherent fresh provider index or a separate
verified guard-freshness repair, then reconcile the remaining reference-header
conflicts. No merge, guard workaround, link gain or census clearance is claimed.
The preceding publication's batch-link audit was also inconclusive against
the older index and its receipt requirements; carry this into the next census.
