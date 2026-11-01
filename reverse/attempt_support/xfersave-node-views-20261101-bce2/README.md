# XferSave string-node and iterator view reconciliation

Base `0efa0eac7c8` (the separately verified CRT-declaration prerequisite).
Claimed TU: Code/GameEngine/Source/Common/System/XferSave.cpp and its eight
clean donor candidates. The current evidence planner, all nine frozen-file
checks and the supported merge/private-view plans were reviewed first.

The seed's node/iterator field spellings now also serve Rva0060D269.cpp and
rva0060D2E9Rva0060D2E9Farm.cpp. The node retains the existing donor's unsigned
payload at +0x10 after the pointer and STL string; the seed previously needed
only the pointer/string prefix and never allocates an instance of that node.
The iterator remains two pointers at +0/+4. All three units now spell the
same constructor and fields. The compiler-layout planner confirms the common
blocks. Original application names and a complete container identity remain
unknown; this is agreement between the existing recovery views.

The mechanical planner could not rename the old `key` token safely because
it is also a function parameter. The targeted edit changes the class blocks
and the one iterator member access only, retaining those function parameters.
The existing wrapper's `inline`/`__declspec(noinline)` attribute order is
normalized to the seed's exact spelling so composition deduplicates it.

Verification:

- Normal builds pass all 25 edited-unit rows. All 191 external COMDAT
  byte/relocation fingerprints, strong/undefined/weak symbol sets are identical
  before and after the complete view/attribute change, including after strict
  preparation. No provider body or code binding is added or removed.
- The complete nine-source strict cohort passes 44/44 rows and eight EXACT
  EH graphs. Ordinary preview against 0d24c60eef (2026-11-01 09:19) retains
  eight LINKS units and 2,219 authored bytes. The untouched constructor still
  has the same two unresolved opaque-element destructors and remains unlinked.
- Frozen-file checks pass. No ledger, pin, hatch, shared header, source path,
  compiler option or register key changes.

The supported merge still accepts no donor. The finder now gets past both
include-context and duplicate-definition errors, but its composition emits
121 rather than native 128 bytes. Read-only inspection of the merge tool's
existing scratch objects identifies the only failed row as 0x0060D269;
disassembly shows an outlined string-destructor call in place of retail's
inlined null-check/free cleanup. This is not the earlier speculative
iterator/EH visibility explanation. The next test is the seed's existing
declaration-only string-destructor specialization, in a separate change.
Other view, template, Xfer-header, byte and deque-provider stops remain.

No file reduction, newly linked census bytes or recovered C++ bytes is claimed.
Adjacent receipts preserve the current failure as well as the verified
prerequisite. The diagnostics read already-built isolated scratch objects;
they do not invoke the compiler or modify the shared build cache.
