# BIG archive reader: stale Microsoft-header queue entry

Source: `Code/GameEngine/Source/GameClient/Win32BIGFileSystemRva006046B0.cpp`.
Inspected tree: `d9bcefa38e`; preview index: `12b9e7a7c0` (2026-10-30 10:11).

The CRT-header repair already landed in `a120ba71e799a0264e206a29fa3850ab0f8b29b4`.
The source includes `<string.h>`, `<mbstring.h>` and `<new>`; no source change
is needed. See the [original repair evidence](bigarchive-ms-headers-20261028-codexb.md)
for the imported/direct call distinction and unchanged object bindings.

The current owning auditor scan finds only two `_CRTIMP` configuration macro
definitions, which it explicitly excludes from local-declaration debt. Its
include-closure findings are empty and `classify` returns no queue category.
Calling `ms_header_audit.refresh_queue` with this source's scan removes exactly
one stale queue entry containing four findings and adds none. Unrelated queue
rows are preserved. Scratch scan evidence is in
`build/win32big-scoped-refresh.json`.

Checks after the publisher's rebase settled:

- `find_declared_unmatched.py`: all definitions matched.
- `link_check.py --prepare-current`: nine function rows and one data row verify;
  all three generated funclets verify through their parent. Strict preparation
  accepts a reusable receipt.
- Ordinary `link_check.py`: LINKS, 606 authored bytes retained against the
  published index above.
- `eh_verify.py`: EXACT 1, baseline 0, missing-object 0.

This retires stale queue debt; it is not a new source repair or census gain.
No source, ledger, pins, shared headers or paths change. The original repair's
broader consumer/census prerequisites remain pending, including the previously
unverified `Common/0CreateAHeroManager21FE49.cpp` consumer. No runtime test or
full consumer closure is claimed.
