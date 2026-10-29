# Benchmark allocator CRT header cleanup

Inspected base: `51e60093bf`, 2026-10-29. Source:
`Code/Libraries/Source/Benchmark/AllocateMemory.cpp`.

The Microsoft-header picker selected the local imported malloc declaration.
Replace it with the toolchain's `<stdlib.h>` and select `/MD`, so `_CRTIMP`
continues to declare malloc as dllimport. No function bodies, source paths,
ledger identities, shared headers or pins change.

The Microsoft-header auditor classifies the resulting source as clean. Its
scoped `refresh_queue` API removes the one-definition queue entry, preserving
unrelated records. No baseline or whitelist changes.

Before and after `./build.sh` verify both rows (AllocateMemory, 204 bytes;
ReportError, one byte) and the named malloc import. The frozen-file check
passes before and after. Strict current-provider preparation also passes.
The ordinary link preview preserves LINKS, 205 -> 205 authored bytes, against
index `840db2d676` (2026-10-28 20:44). This is not a census gain.

The staged-tree batch audit remains INCONCLUSIVE: the index predates the base,
and affected consumer `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`
lacks a current receipt. Carry that consumer and the allocator provider into
the next scheduled census; consumer-wide link closure remains unverified.
