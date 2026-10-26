# INI lookup parser: native C++ exceptions

Base `2808663ede`, 2026-10-26. The claimed whole source is
`Code/GameEngine/Source/Common/System/INI_scanLookupList.cpp`.
Its sole matched body is `INI::scanLookupList`,
`0x0002BD85..0x0002BDF1`, 108 bytes.

The preceding consolidation rejected this donor because its artificial
default-constructed `INIException` did not agree with the seed's real exception
declaration. The source manually invoked the variadic constructor and
`_CxxThrowException`, passing a zero-filled throw-info anchor.

Retail has two error paths: a missing/empty lookup table and an unsuccessful
case-insensitive lookup. Both construct the exception in the same eight-byte
stack slot and join the throw tail at `0x0002BDE3`. The successful lookup returns
the adjacent integer without constructing an exception.

The reconstruction now expresses both failures as ordinary
`throw INIException(...)`. Its class declaration retains the native two-member
layout and the existing constructor/copy/destructor ABI used by INI.cpp and
INIExceptionCtor.cpp. The artificial default constructor, explicit throw-runtime
declaration, direct runtime calls and zero-filled anchor are removed. The name,
row boundary, lookup loop, error codes, format strings and compiler flags stay
unchanged. No new pin, alias or counted hatch is introduced.

Verification:

- Normal whole-file build before and after: 1/1, all 108 bytes exact.
- Both format literals and the `_strcmpi` import verify; frozen-file checks pass.
- Code identity: three references, all owner bindings, zero wrong bindings.
- Data check: zero findings. EH verification has no EH-frame rows for this
  function, as expected; this is not a claim about a new full-image run.
- Ordinary preview against `763dc8759f` remains clean, 108 -> 108 authored bytes.

Logs: `build/codex-cleanup-20261025/iteration19-lookup-{before,after,identity,link}.log`.
This replaces manual exception machinery with verified C++; matching coverage
is unchanged. A new composition trial must still prove the donor can be absorbed.

The preceding merge's normal full commit gate completed successfully:
98,252 function rows, 2,216 data rows, all reference checks, the no-op image and
converged-data enforcement over 23,033 sources. A follow-up flag proposal proves
the inherited SSE override is still needed for two INI rows. Its measurement
count will be refreshed once for the final consolidated TU; no override is
retired by this parser change.

## Approved composition follow-up

At base `468141e4c7`, a fresh supported TU plan and `tu_skeleton.py --merge`
accept the repaired lookup donor. Its unchanged 108-byte body joins INI.cpp;
the resulting TU preserves 53 rows / 3,945 matched bytes. Across the two merges,
seven whole donors are absorbed and 14 existing rows / 906 bytes are repointed.
This is consolidation, not new matched coverage.

The owning tool transfers the one function row, one existing TU-map source cell
and one data-ledger source reference, then refreshes the MS-header queue.
The data-ledger `names` entry still spells the old, now-unused
`_scanLookupListThrowInfoAnchor` catalogue name; only its source path moves.
Its canonical name, literal status and ownership do not change. This stale
catalogue spelling is not an active emitted anchor or a new data-ownership claim.

Normal verification accepts all 53 rows, 54 strings plus one empty string,
one float and nine imports. The INI/Get comparison cohort has 178 references
(149 owner, 19 alias, eight EH and two fold bindings), zero wrong bindings,
zero data findings and eight EXACT EH graphs. Frozen-file and ledger checks
pass. Read-only review found no source or register blocker.

Ordinary preview against `763dc8759f` retains seven duplicate and five selected
findings in INI.cpp; Get stays clean at 154 bytes. The additional lookup pair
has the same stale-index cause: its owner remains donor object 581 while the
selected definition now belongs to merged INI object 576. Post-merge closure
still requires a current provider audit or census and is not claimed here.

Eleven whole donors remain unchanged. The new trial reports missing INI member
or type declarations in initFromINIMulti, Clear, ParseLine, Get, mixerFieldEdit,
loadWithParse, loadDirectory and parseAsciiString, and overlapping private
string/allocator/vector views in readLine, getNextTokenOrNull and
parseAsciiStringVectorAppend. These are first trial diagnostics, not proven
independent root causes. The original byte-matched bodies remain intact.

Logs: `build/codex-cleanup-20261025/iteration19-{dry-run,merge,merged-build,merged-identity,merged-link}.log`.

## Final flags and path-consumer audit

After rebasing on `origin/master` at `561f16348d`, the owning
`flag_defaults.py propose` tool measures the final 53-row TU. The existing
`-O1 -arch:SSE` override remains necessary: the region default loses two rows.
Only the measured row count changes from two to 53; effective compilation
flags do not change. Log: `iteration19-flags-final.log`.

The complete source-path delta in `561f16348d..37dc9e234d` removes exactly the
seven donors listed above and in the preceding consolidation handoff. A single
combined search of their full paths and basenames across active tools, hooks,
workflows, source/header files, build configuration, registers and documentation
finds no active consumer requiring another path change. INI-specific directory
and glob checks likewise find no dependency on those retired files. Existing
generic source discovery and source-keyed register transfers use the new TU.

Remaining old-path mentions are source/provenance comments, immutable attempt
evidence, append-only attempt history and the saved census's `link_status.csv`.
Those historical records are intentionally retained. No include, hook, active
function/data owner, override, header queue or tooling path still requires a
deleted donor. Audit log: `iteration19-path-consumers.log`. Recheck this audit
only if a later change adds another move or alters a relevant consumer.
