# PartitionManager allocator macro retirement

Inspected base: `46af8b351c90`. Claimed source:
`Code/Libraries/Source/partitionmanager/partitionmanager_impl.cpp`.

The Microsoft-header picker served this file's remaining local `free` macro.
Remove the header-wide redirection and specialize the three remaining vector
allocator deallocators, alongside the existing FlightDeckInfo specialization.
A TU-local inline helper binds the GameMemory function before STLport imports
the CRT's `::free` into `_STL`; this avoids an ambiguous overload without a
macro, extra linker symbol or new pin.

Target fact: the native FlightDeckInfo growth call at RVA `0x00627CA0` reaches
the existing GameMemory wrapper at `0x00030830`, named by
`?free@_STL@@YAXPAX@Z`. The preceding
[math-header cleanup](partition-math-headers-20261030-codexb4.md) established
that binding. This change preserves it for every emitted deallocator; it does
not infer additional donor names or layouts.

Verification:

- Original and final builds pass all 13 rows, six float references and three
  named imports. The existing funclet label renumbers; its parent EH data
  still verifies the same RVA `0x007A78B0`.
- Before/after COFF comparison preserves exactly 93 external COMDAT names,
  sizes, raw bodies and relocation fingerprints. The external symbol inventory
  is identical, and both weak-alias sets are empty. Scratch snapshots and the
  comparison are under `build/partition-free-20261030-codexb5/`.
- Supported strict preparation passes. Frozen-file checks pass before and
  after the edit.
- The owning header auditor's scoped `refresh_queue` removes this file's one
  remaining queued finding and leaves unrelated records unchanged. The three
  preexisting unresolved STLport include inventory notes remain; this is not
  proof that those included definitions are header-clean.
- Ordinary paired preview against census index `12b9e7a7c0`
  (2026-10-30 10:11) retains LINKS for PartitionManager's 2,620 authored bytes
  and FlightDeckInfoVectorInsertOverflow.cpp's 441 bytes. No new census-linked
  bytes or image-ownership result is claimed. Wider consumer selection remains
  subject to the outgoing batch audit and the next scheduled census.

Selection review: the default link picker first served
`Rva008312E0StringReplace.cpp`. Its current source and the clean-C++ handoff
still leave the documented replaceBase selection/grouping prerequisite open;
neither row has an approved TU. No source edit or repeated compile trial was
made for that target, and its body and file claims were released.
