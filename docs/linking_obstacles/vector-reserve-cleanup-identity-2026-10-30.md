### Vector reserve cleanup identity (2026-10-30)

At base `9e8a503c96c1`, reserve at `0x00500EFA` now calls the existing
outer-vector cleanup owner at `0x00500EDC`, removing its competing opaque
helper copy. All four caller rows and the provider row verify with strict
receipts. The owning identity tool retires the caller's sole key after ten
missing prerequisite objects are built and verified. Caller/provider preview
retains LINKS for 244 and 30 bytes against index `85f6b7f40c`; no census gain
is claimed. The staged-tree audit is INCONCLUSIVE on that older index and a
missing current CreateAHeroManager consumer receipt. Carry that consumer and
this caller/provider scope into the next scheduled census; full consumer
closure remains pending.
[Evidence](../../reverse/attempt_support/vector-reserve-clear-20261030-codex.md).
