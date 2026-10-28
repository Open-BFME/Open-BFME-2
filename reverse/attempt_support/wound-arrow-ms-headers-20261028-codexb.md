# WoundArrowUpdate math header cleanup — 2026-10-28

Base: `7dce1ebcf1`; preview index: `d92e7e6635` (2026-10-28 15:58).
Source: `Code/GameEngine/Source/GameLogic/Object/Update/WoundArrowUpdateUpdate.cpp`.

Replace the handwritten sqrt prototype with `<math.h>`. Explicitly promote
the float expression to double to select the original CRT overload; otherwise
the real header selects its inline float overload and changes the body. Keep
the existing outer parentheses required by the documented x87 scheduling.
No row, extent, name, compile flag, class layout or source path changes.

Verification:

- `./build.sh`: 1/1 row exact (RVA 0x004C6A20, 347 bytes), including its
  compiler floating literal; frozen-file check clean before and after.
- `link_check.py --prepare-current`: strict reusable receipt and normal
  byte gates pass. The first run overlapped a comment edit and rejected its
  stale receipt; the final unchanged-input run passes.
- Ordinary link preview: LINKS, 347 authored bytes, before and after.
- All five external COMDAT byte/relocation fingerprints, one strong definition,
  eight undefined references, weak bindings and the reference graph unchanged;
  see [object receipt](wound-arrow-ms-headers-object-20261028-codexb.json).
- Scoped data check: zero findings. Microsoft-header audit: clean. Its scoped
  queue refresh removes only this source's single sqrt finding.

No new census-linked coverage or runtime result is claimed.

The staged-tree batch audit is INCONCLUSIVE (exit 2): the index predates the
base, and affected consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a
current receipt. Carry this consumer and the unchanged WoundArrowUpdate
provider into the next scheduled census; full consumer closure is unverified.
