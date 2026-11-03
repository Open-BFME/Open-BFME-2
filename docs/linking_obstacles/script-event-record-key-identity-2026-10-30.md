### Script-event record key identity (2026-10-30)

At base `cc891735cc`, the constructors at `0x00332F5B` and `0x00332FC1`
misidentified their leading name key as a private `UnicodeString`. Retail's
setter at `0x003316BA` stores `nameToKey`'s result there. Both records now
reuse the existing four-byte `Rva00336BE4Key` and its rowed constructor at
`0x00326BE6`. All four source rows retain identical raw bytes; only the two
zero-constructor relocations change spelling at the same native target.

The two UnicodeString header-queue rows remain. The owning acceptance tool
requires the canonical string include because the historically queued sources
did declare that private class; its discovery-error exception cannot accept
this identity correction. Both false rejects are recorded. The earlier
buffer-identity-accessor prerequisite for these records is superseded; a
supported identity-correction acceptance path is still needed. No new census
coverage or debt retirement is claimed.
Strict preparation passes 13/13 rows across both records, the existing key
provider and the two parser consumers; their final preview retains 5/5 LINKS
and 1,295 authored bytes against `6fe1089c24` (2026-10-30 04:25).
The staged audit is INCONCLUSIVE on the older source baseline and missing
current `Common/AIGameTeam.cpp` receipt. Full affected-consumer selection and
loss checks remain unverified; carry the repaired records, key provider,
parsers and wider consumers into the next scheduled census.
[Native evidence and verification](../../reverse/attempt_support/script-event-key-identity-20261030-codex3.md).
