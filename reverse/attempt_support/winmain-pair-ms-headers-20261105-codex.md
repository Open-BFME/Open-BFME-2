# WinMain title-pair Microsoft headers

Inspected revision: `4b5df6d8cf`, 2026-11-05.
Scope: `Code/GameEngine/Source/Main/WinMainPairUnicode.cpp` only.

Replace the local CRT prototypes, HKEY forward declaration/typedef and registry
root constants with VS2003 `<string.h>`, `<new>` and Platform SDK `<windows.h>`.
Enable the per-TU Platform SDK include path and `/MD`. The real string header
declares `wcslen` dllimport under `/MD`, preserving initWide's IAT call, while
its x86 `memcpy` and `strlen` declarations remain direct calls. The toolchain's
non-native wchar_t typedef is the same unsigned-short ABI this source uses.
No shared header, row, pin, alias, class layout or source path changes.

Verification:

- Original and final `./build.sh` pass all 46 rows, two nonempty string
  literals, one empty-string reference and one named import. All 19 compiler
  funclet rows remain verified through their parent EH data after label changes.
- Original and final COFF comparison using `link_census._comdat_sections` and
  `_coff_symbols`: all 45 name/digest/size COMDAT fingerprints and all 66
  external name/value/definition records identical; neither object has weak
  externals. This includes the per-body CRT relocation targets. `/MD` changes
  the default CRT library directive; no executable body or external binding
  changes.
- `find_declared_unmatched.py`: all defined functions matched, before and after.
- `ms_header_audit.py check` passes; scoped `scan --write-queue` reports zero
  local Microsoft declarations and removes the file's nine-name queue entry.
- `link_check.py --prepare-current`: strict reusable provider receipt, 46/46.
- `link_check.py`: LINKS, 1,725 -> 1,725 authored bytes against census index
  `c95fcfcfcd` (2026-11-05 05:17 UTC). No headline gain claimed.
- `link_batch_audit.py` on the staged tree: INCONCLUSIVE (exit 2). Its index
  predates the outgoing base and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
  receipt. Complete affected-consumer closure remains unverified; carry this
  provider and its consumers into the next scheduled census.

No real link, nightly measurement or smoke run was started.
