# ConnectionManager authentication string cleanup

Inspected 2026-10-28 at `b48e23b5d2`; ordinary link index `d92e7e6635`
(2026-10-28). Source:
`Code/GameEngine/Source/GameNetwork/ConnectionManager_processGameSpyStatsAuthKey_Rva004CFE24.cpp`.
The retained row is `?processGameSpyStatsAuthKeyCommand@BFMEConnectionManager@@QAEXPAX@Z`,
RVA `0x004CFE24`, 149 bytes.

## Selection and remaining placement work

The default picker claimed the proposed Common/BFMEConnectionManager.cpp scope
(25 rows across 16 files). The supported Common consolidation report was
regenerated. The current merger plan has zero approved rows and zero donors;
the proposed run interleaves Common and GameNetwork BFMEConnectionManager hints
with ConnectionManager anchors. This is unresolved placement evidence, not a
lost row. No TU map, row ownership or source path changes were made. Establish
the canonical class/TU relationship before approving or merging this family.
The authentication fragment was separately claimed for the bounded cleanup.

## Retained repair and evidence

The fragment now includes the existing canonical AsciiString header instead of
a private StringBase template disguised as AsciiString. Five alternate names
are removed by calling their existing ledger owners directly. Call-only views
do not establish complete class layouts or recovered class names. The +0x1C
getter retains the established CDDrive::getPath owner and uses a qualified
direct call; this does not identify the network message as a CDDrive.
The companion sendGameSpyStatsAuthKey source already uses that folded getter.

The previous private destructor reference at RVA `0x00036410` now names the
shared StringBase<char>::releaseBuffer worker. `repair_queue.py retire identity`
retired exactly one registered key and found zero remaining keys for this source.
`hatch_counters.py --update` supplied the five removed alias entries; unrelated
baseline sorting and stale-entry cleanup were excluded from this change.

Before/after objects have identical raw bytes for the parent and preserve all
three common external COMDAT bodies and relocation targets after resolving the
five old aliases and the corrected cleanup-worker name. No external COMDAT is
removed. The canonical header additionally emits AsciiString destruction,
AsciiString::getLength and StringBase<char>::validate helpers. This is scoped
object evidence, not a complete consumer or census verdict.

## Verification and limits

- Before and after `./build.sh` pass the sole 149-byte row and literal/import
  checks. Frozen-file checks pass before and after; class_gate passes.
- Strict `link_check.py --prepare-current` succeeds. Ordinary before and after
  previews both say LINKS, 149 authored bytes. No linked-byte increase claimed.
- `data_check.py --converged`: one source, 11 address edges, no second names or
  unjudged edges. Ordinary data check has zero findings.
- `eh_verify.py`: zero EH graphs in this fragment.
- The retirement tool initially refused 132 missing ledger objects. A normal
  `./build.sh` of those 132 sources restored them and passed all 1,256 rows,
  212 literals plus 11 empty strings, 75 float literals and 52 named imports.
  Retirement then succeeded through its supported tool.
- `check_csv.py`: 98,946 function rows, 9,415 symbols and 2,203 data rows pass.
- The staged-tree consumer audit is INCONCLUSIVE: its index predates the base,
  and affected consumer Common/0CreateAHeroManager21FE49.cpp lacks a current
  receipt. Complete consumer coverage and census confirmation remain pending;
  this report does not claim a clean batch audit.

Scratch observations are under `build/connection-auth-cleanup/` (before/after
objects, normalized comparison, restore-objects log and audit log). This
cleanup does not clear the wider ConnectionManager blockers in LINK-005.
No nightly, full census, runtime or smoke run was started. Source-file count,
TU approval and image ownership are unchanged.
