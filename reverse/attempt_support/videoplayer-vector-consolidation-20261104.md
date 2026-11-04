# VideoPlayer vector destructor consolidation

Inspected base: `074ded58448006a7e7d23fd0d3d1afdb2f0a8e08`.

## Compiler-context prerequisite

`VideoPlayer.cpp` suppressed instantiation of the record vector destructor with
an explicit specialization declaration. Removing that declaration allows the
existing destructor donor's explicit instantiation to compile in the TU.
The donor requires `/EHs`: `/EHsc` omits the retail destructor's EH state -1
store before deallocation. These are target byte/codegen observations, not
evidence of an original source spelling or external donor layout.

The prerequisite changes the TU from `/EHsc` to `/EHs` and removes only the
specialization declaration. `./build.sh Code/GameEngine/Source/GameClient/VideoPlayer.cpp`
passes all 34 existing rows. `find_declared_unmatched.py` reports all defined
functions matched. Isolated `tu_skeleton.Verifier` builds before/after have
identical normalized `link_census.object_facts`: 73 COMDAT copies, 10 defined
symbols, 29 undefined symbols and one weak alias; no added, removed or changed
facts in any of those sets. No link-wide alias is removed.

The supported merge dry-run accepts `Rva00689DB0Finish.cpp` with these changes.
It checks the destructor at 0x00689DB0 against its 103 retail bytes, with the
donor's EH rows at 0x007A7BA0 and 0x007A7BA8 carried with their parent.
The remaining donors are rejected for flag overrides, conflicting
SubsystemInterface definitions, or the element destructor's pointer view.
No census increase is claimed.

## Applied merge and verification

After the prerequisite commit, `tu_skeleton.py --merge` absorbed only
`Code/Libraries/Source/WWVegas/WWLib/Rva00689DB0Finish.cpp` into
`Code/GameEngine/Source/GameClient/VideoPlayer.cpp`. The tool moved all three
ledger rows, refreshed header/MS-header reports without changes, and repointed
only the three existing TU-map source fields (no map regeneration). One source
file is removed. Its local duplicate element declaration is replaced by the
destination's existing declaration; the explicit destructor instantiation is
retained. That instantiation has no local/parameter bindings to clarify.

Checks on the applied unit:

- `./build.sh Code/GameEngine/Source/GameClient/VideoPlayer.cpp`: 37/37 rows
  exact, string/float/import references passed; the moved funclet is located
  through its parent EH data despite compiler label renumbering.
- `find_declared_unmatched.py` reports all defined functions matched.
- `eh_verify.py`: four EH graphs EXACT, zero exceptions or missing objects.
- `link_check.py --prepare-current`: one explicit safe provider byte-verified
  with a strict reusable receipt; no census/index/status update.
- Ordinary `link_check.py` preview: the resulting TU LINKS, 1,976 authored
  bytes versus the indexed seed's 1,863. The additional 113 bytes already
  belonged to the census-linked donor; this is consolidation, not linked gain.
- The supported merge's LinkGuard accepted the composition against index
  `f6d845ecd4`, updated 2026-11-04 13:15 UTC, census `3a8028f34e` at 11:27 UTC.
  This guards selected COMDATs, external code/data facts and affected bindings;
  the index predates the inspected base, so scheduled census confirmation is
  still required and no current full-game link result is claimed.

The complete path-change batch is the one donor-to-TU move, following the
already published compiler-context prerequisite. A combined full-path/basename
search covered `tools/`, `.githooks/`, `.github/`, source/header includes,
`build.sh`, `reverse/` and `docs/`. There are no filename-dependent active
tool/build consumers. Remaining mentions are the merge provenance comment,
the historical symbol/handler-row evidence, census-owned `link_status.csv`,
and previous attempt evidence. Those are intentionally preserved. All ledger
source fields and three TU-map source fields name the destination.

Neither absorbed source has a data/code-identity baseline key to transfer;
existing destination header debt and its two hatch keys remain unchanged.
The merge tool's report refresh and hatch rescan produced no register diff.
No debt is retired and no `/alternatename` is removed.

Remaining merge prerequisites: Add/Get/Remove flag overrides, the destructor
thunk's conflicting SubsystemInterface definition, and the element destructor's
`void *` versus `Rva00688980 *` ownership view. Reconcile each in a separate
byte-verified prerequisite before retrying the supported merge. Carry the
destination and the absorbed donor provider scope into the next scheduled
census; the older 2026-10-29 consumer-receipt obstacle is not declared cleared
by this bounded preview.
