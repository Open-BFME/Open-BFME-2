### GeneralAllocator snapshot Microsoft-header cleanup (2026-10-29, codexb4)

At base `addc18930a`, Rva00034D10Snapshot.cpp replaces three copied Windows
and placement-new definitions with the real headers. /EHsc retains the
original C API exception contract; the existing field-initializing Snapshot
constructor supports a TU-local nothrow declaration. Both rows, both imports,
the EH graph, all four COMDAT fingerprints and all 12 external symbol records
are preserved. The header auditor reports clean and removes its queue row.
Strict preparation passes; preview retains LINKS, 874 -> 874 authored bytes
against index `85f6b7f40c`. The staged-tree audit is INCONCLUSIVE on that older
index and a missing current Common/0CreateAHeroManager21FE49.cpp receipt.
Carry both sources into the next scheduled census; broader closure remains
unverified. No census gain is claimed.
[Evidence](../../reverse/attempt_support/snapshot-msheaders-20261029-codexb4.md).
