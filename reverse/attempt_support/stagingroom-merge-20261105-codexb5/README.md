# Blocked staging-room transfer merge trial, 2026-11-05

Parent: d7ec302b0b (LINK-562 transfer-view prerequisite).

The supported subsystem consolidation planner was regenerated after the view
repair. tu_skeleton rebuilt the current TU map in memory and accepted
StagingRoomGameInfo.cpp and GameSpyStagingRoomXfer.cpp, with no rejected donors.
It preserved both census-linked units through its link guard. The trial removed
one source file and kept all 82 matched rows in their approved retail TU. The mixed
stlport_pod_vector_bodies.cpp remains outside this batch. No assignment or
approval changed; only the transfer row's source column changed in tu_map.csv.
The commit-msg gate refused the trial, and every source/ledger change from the
merge was restored to the committed prerequisite. No file reduction is claimed.

Trial verification:

- ./build.sh on the merged TU: 82/82 exact, with 34 string literals, nine
  empty-string references and ten import references verified. No float literals.
- eh_verify.py: EXACT 15/15 graphs. find_declared_unmatched.py: all bodies
  matched. check_csv.py: OK (99471 functions, 9311 symbols, 2268 data rows).
- Current-object link preview LINKS for 6,182 bytes, preserving the original
  6,143 + 39 bytes against index c95fcfcfcd, 2026-11-05 05:17. The apparent
  per-source increase is repointing, not newly linked coverage or a census gain.
- [COFF comparison](symbol-delta.json): the original two objects' 139 external
  definitions and net external requirements are exactly preserved. The staging
  room vtable's bytes and relocations equal the verified prerequisite's.
  Neither source contains linker-alias pragmas; none are removed.
- data_check.py: zero shadow findings. The prerequisite hook reported two
  code-identity shadow findings on the seed's existing AsciiString::clear calls
  in its constructors; these calls are untouched and no debt key is retired.
- The supported transfer keeps the donor's GameSpyStagingRoom header-queue
  row, RVA and accept command attached to the destination TU. Its old compiler
  diagnostic is history, not a stale source owner. tu_skeleton's Microsoft-header
  refresh retains the destination's conflicting ABI finding (31 occurrences);
  header adoption and Microsoft-header repair remain separate work.
- Neither source owns a data/identity baseline key or hatch key. No protected
  debt is dropped. Existing destination header-queue rows remain.

Tooling compatibility audit across the complete outgoing source-path batch,
origin/master 0322121abe through this merge:

- ClickReactionBehaviorCtorThunk.cpp -> ClickReactionBehavior.cpp;
  GameSpyStagingRoomXfer.cpp -> StagingRoomGameInfo.cpp.
- Combined basename/full-path searches across tools, hooks, workflows, source
  and header includes, root/build configuration, docs and reverse registers
  find no active tooling/build/include consumer requiring either removed path.
  No active directory-based consumer assumption changes.
- Functions/TU-map columns name the current TUs; ClickReaction hatch keys were
  transferred by its supported merge. Staging-room header debt was transferred
  above. Doxygen and the other path-keyed registers have no removed-path owner.
- Remaining old paths occur in TU provenance comments, historical link_status.csv,
  old attempt/runtime-vtable evidence, a blocked name_agreed.csv explanation and
  the transferred header row's historical compiler diagnostic. Keep this history.
- Both destination TUs have current byte-verification receipts; the earlier
  ClickReaction merge's own handoff records its 11/11 exact rows, unchanged
  definitions/requirements and alias preservation. No tooling consumer changed.

Commit boundary and false rejection:

The pre-commit gate passed, including all byte rows, 15 EH graphs, census-linked
unit preservation and debt checks. Commit-msg then refused:

```
repair_queue: Code/GameEngine/Source/GameNetwork/GameSpy/GameSpyStagingRoomXfer.cpp: vanished unit (GameSpyStagingRoom) needs a transfer, deleted_rows coverage or per-key Debt-Retired trailer
COMMIT-MSG FAILED: disappearing debt has no accounting
```

The supported header_adopt_lane.transfer_sources preserved the donor row,
including RVA 0x004FDAC7, its failure and retry budget, and changed its source and
acceptance command to StagingRoomGameInfo.cpp. That destination already owns a
GameSpyStagingRoom row for 0x0007FAB3 / 0x004FDA17 / 0x004FDA3D / 0x004FDA42.
repair_queue._debt_transferred reduces rows to a set of (class, source), then
subtracts the old set. Thus the preserved donor row is invisible as an addition.
This conflicts with transfer_sources' explicit contract to keep individual rows
when donors owe adoption of the same class. The source's one ledger row also
followed the destination. No debt was retired, and no tombstone or retirement
trailer would honestly describe this operation.

Prior false-reject reports cover this same boundary: AptOnlineQuickMatch /
PlayerTemplate at 0x005BB3A1 and W3DShrubBuffer destructor at 0x000E9BAC.
Next step is a separate tooling repair that recognizes preserved individual
header-debt rows at an already-indebted destination while still rejecting actual
dropped debt; then retry the supported merge. No gate edit or bypass was made.

After restoring the trial, ./build.sh on the two original files again passed
82/82 rows and all string/import checks; declared-unmatched checks passed.
The outgoing batch audit at d7ec302b0b was INCONCLUSIVE: its index is at
c95fcfcfcd rather than outgoing base 0322121abe, and three affected source
objects lack census-grade current receipts (ClickReactionBehavior.cpp and both
staging-room files). This is not a clean affected-consumer verdict;
carry the batch into the next authorized census. The runner deferred publication
of the committed prerequisite because maintainers locked master. No complete
vtable, census improvement or runtime claim is made.
