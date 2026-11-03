### BuildAssistant canonical Module lookup storage (2026-10-30)

Cleared for `Common/System/BuildAssistant.cpp`: the CastleMemberBehavior lookup
returns an unadjusted Module pointer; isLocationClearOfObjects reads its
ObjectID at +0x18. A partial view keeps that field beyond the canonical base.
All 69 rows, nine EH graphs, 222 external code definitions/relocations, one
data row, two strings and 42 float literals remain verified. The owning
acceptance tool retires one Module key; ordinary preview preserves
LINKS/11,630 bytes against `ccafe54d1d`. No census gain is claimed.
[Native helper, caller and strict-object evidence](../../reverse/attempt_support/module-buildassistant-lookup-20261030/README.md).

The accepted batch at `16b007b4e7` retains an INCONCLUSIVE wider audit on the
older index and missing current 0CreateAHeroManager affected-consumer receipt.
The hook's eight code-identity shadow findings remain outside this Module
adoption: before/trial retained definitions and relocation targets are
identical, and the normal nine EH graphs remain exact. No identity register
or baseline is expanded or retired. Carry the wider provider/consumer scope
and those independent findings into their owning lanes and the next census.
