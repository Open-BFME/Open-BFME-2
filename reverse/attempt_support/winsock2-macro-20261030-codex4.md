# Retire the duplicate winsock2 MAKEWORD definition

Base: BFME 2 `59bc925312`, verified BFME 1 reference `7a8a034a`.
Scope: `reference/shims/sweep/winsock2.h`, claimed through the Microsoft-header
picker after the default link target was handed off as blocked.

`winsock2.h` includes `winsock.h`, which includes `windows.h`. The sweep
Windows header already defines the identical `MAKEWORD` macro; an SDK Windows
header also supplies it. Remove the redundant guarded fallback from
`winsock2.h`. This changes no socket declaration or header selection.

The owning `ms_header_audit.scan_text` and `refresh_queue` path reports zero
local occurrences, no scan error and the same 96 include-closure findings.
Only this file's queue row is retired. The broader sweep Windows/socket
header debt remains; this is not an SDK-header migration.

Verification:

- Frozen-file checks pass before and after the edit.
- Staged `header_dependents.py` bounds the change to 23 ledger sources.
- Normal `./build.sh` verification of that scope passes 452/452 function rows,
  five data rows, 296 string literals, 51 empty-string references and 77 named
  imports. All 246 funclet pins verify.
- Before objects were snapshotted after the reference update's successful full
  gate. After rebuilding, all 12,482 non-debug sections (payload, relocations,
  size and flags), 12,010 external COMDAT fingerprints, 12,841 external symbols
  and reference roots/edges are identical across the 23 objects. Uninitialized
  sections with a zero raw-data pointer retain their size/flags and have no
  file payload; timestamps and debug sections are not compared.

Scratch evidence is `build/winsock2-macro-20261030-codex4/`: `before.json`,
`before-audit.txt`, `after-audit.json`, `dependents.txt`, `build.log`,
`compare.py` and `object-comparison.json`. These are current-object checks,
not census measurements; no linked-byte or ownership gain is claimed.
