# Current Microsoft-header audit retires an already completed locale key

Source `Code/Libraries/Source/WWVegas/WWLib/stlport_LocaleFacets.cpp` is unchanged, including its existing real Microsoft headers
and retail lstrcmpi import spelling. The default picker served a stale key
claiming27 local definitions. Current native `ms_header_audit.py show` reports
clean; the owning scoped `scan --write-queue` removes that one stale record,
preserving all unrelated queue entries. This is queue maintenance, not a new
source migration or27 newly removed definitions.

The normal byte gate preserves20 existing rows. All70
external code bodies and all non-debug sections match the before-object.
Strict provider preparation passes. No source, shared header, flags, native
identity or baseline change. Bounded link preview only:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/Libraries/Source/WWVegas/WWLib/stlport_LocaleFacets.cpp: LINKS  LINKED 6,113 -> 6,113 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 6,113)
link_check: 1 of 1 link cleanly; LINKED 6,113 -> 6,113 bytes (3.6s)

```
