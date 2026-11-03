### Scoped Microsoft-header queue refresh (2026-10-30)

The audit CLI now refreshes only explicit scan paths when --write-queue is
requested; unrelated queue and occurrence records stay intact. A scan without
paths still replaces the full inventory. Live refresh reclassifies
Rva00131BE5Ctor.cpp from drop-in to conflicting: its operator new throw()
differs from the shipped header's throw(...). All unrelated queue records
remain byte-identical. No game source or linking measurement changes.
[Evidence](../../reverse/attempt_support/ms-header-scoped-queue-refresh-20261030.md).
