# Apt array CRT header cleanup — 2026-11-04

Base: `301379c9f6`. Scope: `Code/GameEngine/Source/Common/Rva006D94A0AptCluster.cpp`.
Claim: `file:Code/GameEngine/Source/Common/Rva006D94A0AptCluster.cpp`.

Replaced the local memmove, qsort and atoi declarations with the real
`<string.h>` and `<stdlib.h>` declarations. TU-local `/D_CRTIMP=` keeps the
existing direct CRT entry-thunk calls under `/MD`; no pin, alias, class view,
ledger row or debt register changed.

Verification:

- Original and updated `./build.sh` runs: all 6 rows exact (949 bytes), all 3
  string references exact, float/import checks pass.
- `link_check.py --prepare-current`: strict reusable receipt preparation passes.
- `ms_header_audit.py check` and `git diff --check`: pass.
- Frozen-file checks before and after: all defined functions already matched.
- Microsoft-header audit `show`: clean; all three local declaration copies gone.
- Compared the original and updated COFF bodies through
  `build.read_object_symbol_bytes`: full section-tail bytes and named
  relocations identical for every row; undefined symbol sets identical.
  Direct REL32 CRT sites are listed below (offsets relative to each body).
- Current-index preview: LINKS, LINKED 949 -> 949 bytes; index
  `a62ac1c10b`, 2026-11-04 07:28. No new linked coverage claimed.
- Existing `BfmeAptValue006DCD20` header-queue row remains: its canonical
  field-offset mismatch is outside this declaration cleanup.
- The AptArray composition obstacle's class-view prerequisite is unchanged;
  no obstacle clearance or source recovery claim.

## Object comparison

```text
0x006D9CE0 ?rva006D9CE0@@YAPAVBfmeAptValue006DCD20@@PAV1@H@Z: body identical=True; relocations identical=True
CRT sites: [('0x40', 20, '_memmove')]
0x006D9F00 ?rva006D9F00@@YAPAVBfmeAptValue006DCD20@@PAV1@H@Z: body identical=True; relocations identical=True
CRT sites: [('0x59', 20, '_qsort')]
0x006DA0C0 ?rva006DA0C0@@YAPAVBfmeAptValue006DCD20@@PAV1@H@Z: body identical=True; relocations identical=True
CRT sites: [('0x49', 20, '_qsort')]
0x006D94A0 ?rva006D94A0@BfmeAptValue006DCD20@@QAEXXZ: body identical=True; relocations identical=True
CRT sites: []
0x006D9F70 _rva006DA0C0Comparator: body identical=True; relocations identical=True
CRT sites: [('0xa9', 20, '_atoi'), ('0xe3', 20, '_atoi')]
0x006D9E40 _rva006D9E40Comparator: body identical=True; relocations identical=True
CRT sites: []
Undefined names identical=True
```
