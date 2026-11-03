### Palantir obsolete guard provider cleanup (2026-10-29)

At base `71d01c340b`, the parent already emits both exact guard-rollback
funclets for `0x009FF04C`; the external `g_Va00DFF04C` definition and its
remaining extern are unused. Removing them and refreshing the generated guard
index row lets the owning retirement tool remove ten stale callback data keys,
and lowers address-global hatch occurrences by three. All 38 function rows,
two data rows and 11 EH graphs pass. Callback and surviving clearer previews
retain LINKS for 1,652 authored bytes against index `85f6b7f40c`. Full consumer
and census confirmation remain pending; no census gain is claimed.
[Scoped evidence](../../reverse/attempt_support/palantir-guard-data-retirement-20261029-codex4.md).
