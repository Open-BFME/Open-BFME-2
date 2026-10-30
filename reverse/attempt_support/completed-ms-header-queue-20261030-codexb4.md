# Retire two stale Microsoft-header picker entries

Base: `0fa815229e`. This changes queue bookkeeping only; the source repairs
were already committed. No source, ledger, header contract or verifier changes.

- `Code/Libraries/Source/Apt/AptDate.cpp` already takes `sprintf` and `abs`
  from `<stdio.h>` and `<stdlib.h>` (repair `b241683ae3`). Its queued two
  local definitions no longer exist.
- `Code/GameEngine/Source/GameLogic/Object/Update/WoundArrowUpdateUpdate.cpp`
  already takes `sqrt` from `<math.h>` (repair `91a3a60aa2`). Its queued
  local definition no longer exists.

For each claimed source, `find_declared_unmatched.py` passes and the current
`ms_header_audit.scan_text` / `classify` result is clean. The existing
`ms_header_audit.refresh_queue` helper removes exactly these two entries,
preserving every unrelated queue row. The queue falls from 936 to 934 files;
three stale declaration findings are removed, with no new source recovery
or header-adoption gain claimed.

Verification on the current tree:

- `./build.sh Code/Libraries/Source/Apt/AptDate.cpp`: 45/45 matched, one data
  row verified, 17 string literals and one float literal verified. The two
  renumbered funclet labels resolve through their parent EH data.
- `./build.sh Code/GameEngine/Source/GameLogic/Object/Update/WoundArrowUpdateUpdate.cpp`:
  1/1 matched (347 bytes), one float literal verified.
- Both builds used current dependency-cache receipts; no source changed.

The default link selection was also stale: `stlport_LocaleWctomb.c` and
`stlport_LocaleFacets.cpp` both preview LINKS against index `85f6b7f40c`
(6,205 authored bytes). LINK-139 records this limited confirmation of the
previous repair; scheduled census and full consumer checks remain pending.
