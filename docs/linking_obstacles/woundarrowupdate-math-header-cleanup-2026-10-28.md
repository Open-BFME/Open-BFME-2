### WoundArrowUpdate math header cleanup (2026-10-28)

Status: scoped cleanup verified; full consumer/census confirmation pending.
Base `7dce1ebcf1`, preview index `d92e7e6635`. The real math header and explicit
double-overload selection replace the local sqrt declaration. The 347-byte
row remains exact; all five external COMDAT fingerprints and object bindings
are unchanged. Strict preparation passes and ordinary preview retains LINKS.
One Microsoft-header queue finding retires; no census gain is claimed.
The batch audit is INCONCLUSIVE because the index predates the base and
`Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. Carry this
consumer and the unchanged provider scope into the next scheduled census.
[Evidence and checks](../../reverse/attempt_support/wound-arrow-ms-headers-20261028-codexb.md).
