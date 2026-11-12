### LINK-172: particle-info Snapshot post-load entries were false pure (2026-11-01, halilkkaya-codex)

Status: Partial repair / census pending. Rva0056224F now overrides the
canonical Snapshot loadPostProcess slot with retail's empty RET at 000B3FD0.
Both table RVAs 0081D358 and 0081D348 slot 1 reference its real matched
protected override instead of __purecall. Eight source rows and 13 strict
cohort rows pass; both units remain LINKS, current prediction 836 -> 837 B
(the extra byte is an admitted shared fold, zero unique-byte gain).
Slots 2/3 in both tables remain false pure: getter profile and existing
placeholder-owner reconciliation are still needed; getter 003AE26A's file is
held by StarkillerHDX. [All eight slots, native targets, remaining prerequisites
and verification](../../reverse/attempt_support/purecall-slot-audit-20261101/particle-info.md).

2026-11-12: A shared declaration placed the real transfer at slot 3 of
0x0081D358 and matched 10/10 rows including the caller. Slot 2 still
emitted __purecall. The joint rename refused the getter's current free
cdecl spelling, so the transaction restored the sources. See the
[slot evidence and required getter admission](../../reverse/attempt_support/render-object-info-slot-005622a6.md).
