# BIG archive reader CRT header cleanup

Inspected base: `b3417cdde8`. Published preview index: `d92e7e6635`,
2026-10-28 15:58. BFME 1 freshness receipt verified `001ccd8e27686e9887235b62ff797627f2dde7f5`
on 2026-10-26; no reference update was required.

## Change and evidence

`GameClient/Win32BIGFileSystemRva006046B0.cpp` replaces its strncmp macro
renaming and handwritten CRT declarations with string.h, mbstring.h and new.
The string header is included with _CRTIMP set to dllimport; _CRTIMP is then
restored to the unit's existing empty configuration before the other headers.
This preserves imported strncmp and direct _mbscpy/allocation calls.
The archive parser and nested-map implementation are unchanged. No donor
identity, source placement or naming claim is added.

## Verification

- Before/after normal builds: all nine function rows and the data row match;
  two empty-string references and the named import verify.
- Frozen-file checks pass before/after. The parent EH graph remains EXACT;
  all three generated funclets verify through their parent despite label renumbering.
- Strict provider preparation passes. Ordinary link preview retains LINKS
  for 606 authored bytes; this is no census-linked gain.
- All 104 external COMDAT byte-and-relocation fingerprints, three strong
  definitions, 19 undefined externals and the empty weak-binding set are
  unchanged. [Object comparison](bigarchive-ms-headers-object-20261028-codexb.json).
- Scoped data check reports zero findings. Microsoft-header audit reports
  clean; the two _CRTIMP configuration definitions are not local declarations.
  The owning refresh_queue API removes this source's four-finding queue entry
  while preserving unrelated rows.
- No pins, ledger rows, shared headers, source paths or census counters change.
  Runtime behavior is not newly tested.

## Queue rechecks before selecting cleanup

The default picker first served Rva00380200Getter.cpp and then
BfmeFVFDescriptorVertexDeclaration.cpp. Both already contain landed repairs.
Normal builds verify 7/7 and 6/6 rows respectively; ordinary previews report
LINKS for 914 and 1,820 authored bytes against the same index. Their claims
were released without source edits. The published-index fetch confirmed that
`d92e7e6635` is still the latest available index. These are rechecks of existing
LINK-132/LINK-133 repairs, not new linking progress.
The header picker also served reference/shims/sweep/wpaudio/altypes.h;
no Code source directly includes that unused sweep family. Its claim was
released without changing the shared shim, and cleanup selected the owned
archive reader instead.

Scratch backups and the explicit-source list are under
`build/bigarchive-ms-headers-20261028/`.

The staged-tree batch audit is INCONCLUSIVE (exit 2): index `d92e7e6635`
predates the base and affected consumer
`Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. Carry this
consumer and the unchanged archive-provider scope into the next scheduled
census. Full consumer closure is not claimed.
