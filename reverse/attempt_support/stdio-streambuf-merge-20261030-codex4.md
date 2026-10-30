# Narrow streambuf consolidation

Base: `5fc2f7fd56` (the fleet publisher rebased the prerequisite onto
`6e3f45976c`; none of the three streambuf sources or the shared header changed).
The supported `tu_skeleton.py --merge` absorbed
`Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_streambuf_xs.cpp` and
`Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_streambuf_snextc_aux.cpp`
into `Code/GameEngine/Source/Common/StdioStreambufBase.cpp`.

The current in-memory TU plan approves both moved rows at 0x0001C990 and
0x0001CBF0 under this provisional destination. The merge repointed two rows
in functions.csv and only their source columns in tu_map.csv; it did not
regenerate or change TU approvals. The three sources become one, preserving
all 12 matched rows. The tracked Code source count falls from 20,276 to
20,274 at this base. No original BFME translation-unit name is newly proven.

Verification:

- Normal build and strict provider preparation pass 12/12 rows. Both unwind
  rows remain bound to their parent; the parent EH graph is EXACT.
- Frozen-source checks pass. The Microsoft-header scanner finds zero local
  Microsoft definitions or declarations in the destination and shared header.
- [Object comparison](stdio-streambuf-merge-20261030-codex4.json) preserves
  all 18 distinct external COMDATs byte-for-byte including relocation
  fingerprints and sizes. The union of external definitions, references,
  unresolved names, weak symbols, aliases, inclusion roots and reference
  graph edges is identical before and after composition.
- The merger's census-linked guard accepts the composition. Ordinary preview
  reports the new TU LINKS with 555 authored bytes against index `12b9e7a7c0`.
  Its per-file historical 269 -> 555 display includes the absorbed providers
  and a prior seed repair; it is not a census linking gain.
- The staged-tree batch audit against `5fc2f7fd56` is INCONCLUSIVE: the index
  predates the base, and 16 source objects lack current receipts, beginning
  with `Code/GameEngine/Source/GameClient/Rva0055FB37Write.cpp`. Full consumer
  selection and loss verification remain pending the next scheduled census.

Consolidation audit, across all outgoing path moves from `origin/master`
through the staged tree: these are the only two removed source paths.
Combined old-path and basename searches found no active include, tool,
hook, workflow, build configuration or source-list consumer needing an edit.
The WWLib directory remains present; directory-based scans still apply.
Active function and TU-map rows now resolve to the destination. Neither donor
nor the destination owns code-identity, data-check, gate, pin-consistency or
header-queue debt. The merger refreshed the scoped Microsoft-header queue;
neither header queue has a remaining entry for these sources. The seed's
existing alternatename count remains one, with no donor hatch to transfer.
The merger's full hatch scan also removed an unrelated stale ShroudManager
entry; that incidental change was restored to keep this commit within scope.

Intentional old-path mentions are the merger's provenance comments, a codecvt
comment citing the old min-template precedent, the append-only attempt log,
the previous prerequisite evidence, and historical census/trial reports.
`stlport_trial.py queue_files` explicitly treats the report as historical lead
evidence and intersects it with the current ledger, so it will not re-serve
either removed source. No historical census or trial receipt is rewritten.

The uflow and xsputnc vendor-header donors still fail composition on the
partial locale declaration. Five mixed sources also remain outside this
merge. Carry the destination and its wider consumers into the next scheduled
census; no census or image-ownership improvement is claimed.
