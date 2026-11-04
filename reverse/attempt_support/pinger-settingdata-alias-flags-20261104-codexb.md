# Shared pinger flag: alias-option boundary

Inspected `47d2405205` on 2026-11-04. Scope:
`Code/GameEngine/Source/GameNetwork/GameSpy/pinger/pingerMain.c` and
`Code/GameEngine/Source/GameNetwork/GameSpy/peer/peerPing.c`.

The picker served pingerMain.c's duplicate `_piSettingData` key at
RVA 0x00A0C104. The data ledger already assigns storage to peerPing.c.
This is existing identity debt, not a missing code row. Earlier trials are in
[pinger-alias-contract-20261027-codexb4.md](pinger-alias-contract-20261027-codexb4.md).

Each trial made peerPing.c's flag externally linked and pingerMain.c's
flag an extern declaration. Every comparison used `./build.sh` over both
files (19 rows); no compiler-cache entry was written by hand.

| Additional trial | Byte-verification result |
| --- | --- |
| Capture only the IP in the first callback argument, then set the flag through a comma expression | Only `_piProcessTrip2` fails; frame remains 24 bytes, body becomes 231 bytes with different register allocation and argument scheduling. |
| Capture callback parameter, port, and IP before the store | Only `_piProcessTrip2` fails; frame becomes 28 bytes, body 233 bytes. |
| Original expressions with `/Oa` | `_piProcessTrip2` matches, but `_piBytesToPing`, `_piProcessTrip1`, `_pingerProcessPing`, and `_piProcessIncoming` fail. |
| Original expressions with `/Ow` | 18/19 match, including `_piProcessTrip2`; only `_piBytesToPing` (RVA 0x006B2170, 141 bytes) fails. |
| `/O2 /Ow /G7` with `FLAG_DEFAULTS=off` | Six rows fail: `_piBytesToPing`, `_piProcessTrip1`, `_piProcessTrip2`, `_piProcessTrip3`, `_piProcessIncoming`, `_piCalculatePing`. |
| `/Ow`, volatile header destination in `_piBytesToPing`, and memmove for its payload | `_piBytesToPing` and `_piProcessIncoming` fail. Volatile compound assignments expand and memmove becomes a call. |

The `/Ow` decoder remains 141 bytes but schedules its first pointer increment
before the first header store. Its inlined 24-byte payload copy also loads
the next word before storing the current word; retail alternates each load
and store. The rest of its decoder matches. This is target-byte evidence
for a narrower source/code-generation boundary, not proof of retail flags
or permission to introduce a scoped optimize pragma or move an unapproved row.

Next useful check: find a clean decoder expression under `/Ow` that preserves
all 141 bytes, or establish approved TU placement before separating the
alias-sensitive decoder. The already-tested `/Oa` and `/G7` alternatives
are not whole-file solutions. The counter keys at 0x00A0C0EC are untouched.

All trial edits were restored. Final ordinary `./build.sh` passes 19/19,
string/float checks, and both named imports. Both declared-unmatched checks
pass. No source, ledger, flag override, hatch, or debt-register change remains;
all five remaining data keys are preserved. No link/census improvement claimed.
