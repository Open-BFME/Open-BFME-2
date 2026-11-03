### Benchmark allocator CRT header cleanup (2026-10-29)

Scoped cleanup at `51e60093bf`: AllocateMemory.cpp replaces its local malloc
import declaration with stdlib.h and `/MD`. Both rows and the named import
remain exact; strict preparation passes, and ordinary preview retains LINKS
for 205 authored bytes against index `840db2d676`. The outgoing audit remains
INCONCLUSIVE because the index predates the base and affected consumer
Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. Carry that
consumer and the provider into the next scheduled census. No census gain or
consumer-wide closure is claimed.
[Evidence](../../reverse/attempt_support/benchmark-allocator-ms-header-20261029-codexb.md).
