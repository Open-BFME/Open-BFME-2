# Canonical UnicodeString adoption

Base inspected: `1efc3f6a40`. The default queue served
`Common/System/WideConcatPair.cpp` for the UnicodeString header lane.

## Wide concat helpers

Replaced the unit's private StringBase and UnicodeString declarations with
the registered UnicodeString header. The two friend grants already present
in the private StringBase move to the shared declaration within its existing
BFME_STRINGBASE_PUBLIC_DTOR mode; its fields and function bodies are unchanged.
That mode preserves this unit's public destructor and by-value StringBase return.
These are compatibility changes to evidenced BFME 2 views, not a claim to
have recovered original class names or donor source.

Verification on the pinned BFME 1 input `0bf534ea7c`:

- `find_declared_unmatched.py` passes for the source and shared string_base.h.
- Normal `build.sh` passes 167/167 rows across 16 files: all ten sources
  defining that existing mode, RecorderCopyCurrentRecording,
  RecorderCopyReplayFileRva0037D96B, AptSaveLoadOnButtonSave,
  AptSaveLoadRva00435819, PlayerInitFromDict and WWLib/Rva000A7E9E.
  WideConcatPair contributes 13 rows (484 bytes). The four extra concat
  consumers define the type with `struct` and check that ordinary consumers
  retain their declarations without the new helper names.
- `eh_verify.py` reports all nine EH graphs in WideConcatPair,
  PlayerInitFromDict and WWLib/Rva000A7E9E EXACT. Funclets are
  verified through their parent graphs despite compiler label renumbering;
  no ledger labels, pins or aliases were added or changed.
- Ordinary `link_check.py` against index `ef9c691284` (2026-10-25 18:23 UTC)
  reports all five files linking, preserving 2,926 authored bytes. The
  WideConcatPair subset stays 441 -> 441; this count excludes compiler rows
  that are included in the 484-byte row total above.
- `header_adopt_lane.py accept --class UnicodeString` passes and retires the
  source's single queue entry. No census or executable-closure gain is claimed.

The complete gate rejected the initial unconditional friend declarations:
they changed PlayerInitFromDict code generation and renumbered AudioFileCache's
bare `object-symbol=$L7618` cleanup to `$L7620`. The helper names are now
restricted to the existing by-value lifetime mode, so ordinary consumers keep
their previous declarations and code generation. The tests above cover both
regressions and every source opting into that mode. Neither consumer nor its
ledger was changed; no verifier, pin or alias was adjusted to hide the failures.
The AudioFileCache cleanup at 0x00760BC6 remains a future metadata-cleanup lead:
its exact parent graph binds it to freeUnusedSamples at 0x000A81BE.

Before rebasing, the wide-concat change on base `1efc3f6a40` passed the
complete normal hook: 98,252 function rows,
2,210 data rows, all reference checks and the no-op image check. The enforced
converged-data audit also passed all 23,127 sources for its ten registered
addresses. This is verification evidence, not a new link census.

## Other string consumers

- `OptionPreferences_getGameSpyIPAddress.cpp`: removed the unused private
  BfmeStringData and wide StringBase/UnicodeString declarations and included
  the registered UnicodeString header alongside AsciiString. The 194-byte
  online-address body passes its normal byte/reference gate; its EH graph
  is EXACT, the frozen-file check passes, and ordinary preview preserves
  194 -> 194 authored bytes against the same index. The header lane accepts
  and retires this source's one queue row.
- `OptionPreferences_getLANIPAddress.cpp`: the same canonical-header adoption
  removes the private wide-string declarations. Both rows (194-byte body and
  10-byte handler) pass the normal gate, the parent EH graph is EXACT and the
  frozen-file check passes. Ordinary preview preserves 204 -> 204 authored
  bytes, and header-lane acceptance retires its one queue row.
- `Rva001EB15ACopy.cpp`: includes both canonical string headers and uses
  AsciiString for the member at +0x10. The existing Rva001EB15A view in
  `Common/RTS/UnitRevivalTracker.cpp` already uses UnicodeString at +0xC and
  AsciiString at +0x10; the record name remains provisional. The 89-byte copy
  constructor, 22-byte default constructor and 10-byte handler all pass the
  normal gate, the copy's EH graph is EXACT and the frozen-file check passes.
  Ordinary preview keeps 121 -> 121 authored bytes; the header lane accepts
  and retires its queue row.

Batch result: four accepted header-queue retirements, with all 19 existing
rows (1,003 bytes) preserved in the four changed source files. No new body,
source ownership, original name or census gain is claimed.

Publication was synchronized to `16119d3948`. Upstream did not change the
four sources or the shared string headers; the obstacle-register conflict
retains both the upstream INI repair and this adoption record.

## Reference freshness check

Official BFME 1 `d80f952c24` was fetched and tested at unchanged BFME 2
`feb95824fa`. Full verification passed 98,249/98,249 function rows, all
reference/identity checks, 2,210 data rows and the no-op image check.
The first run finished with only an environment failure (missing disassembler);
after installing Capstone locally, a new complete run exited 0. The original
run was allowed to finish without stopping or restarting it.

The official reference scope was subsequently found held by another worker
performing the old/new-input comparison. This patch therefore leaves the
committed reference pointer unchanged, releases its duplicate fork scope,
and uses the pinned input for the source repairs. No successful freshness
stamp was written for the old pointer. Reference publication remains with
that owner; the full-gate result above is scoped to its stated revisions.
