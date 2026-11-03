### EmotionTracker constructor ObjectModule reconciliation (2026-10-29)

Scoped repair verified at base `025f81f0ca`, index `85f6b7f40c` (15:08 UTC).
EmotionTrackerUpdateCtor.cpp adopts the canonical ObjectModule already used by
its destructor, retaining the existing +0x74 ID read through an explicit view
cast. All 11 paired rows and both EH graphs remain exact. The primary vtable
now equals the destructor's 40-byte table; ordinary preview changes the
constructor from blocked to LINKS for 430 authored bytes and preserves the
destructor's 159. The owning header tool retires one queue entry. Concrete
derived virtual overrides, the Thing header prerequisite and full consumer
confirmation remain open. The older index and missing current
Common/0CreateAHeroManager21FE49.cpp receipt prevent complete batch verification;
carry this provider and its affected consumers into the next scheduled census.
No census gain is claimed.
[Evidence and table comparison](../../reverse/attempt_support/emotion-ctor-objectmodule-20261029-codex3.md).
