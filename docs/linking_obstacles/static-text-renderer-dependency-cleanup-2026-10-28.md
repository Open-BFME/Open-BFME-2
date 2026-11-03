### Static-text renderer dependency cleanup (2026-10-28)

Status: consumer repair verified in ordinary preview; census confirmation
pending. Inspected base `4154365966`; index `41c28839bf`.
W3DStaticText.cpp replaces unused renderer includes with GameWindow.h and
the existing border-width macro value. All three rows remain exact; all
14 retained external COMDAT fingerprints and strong definitions are unchanged.
Strict preparation and scoped data checks pass. Ordinary preview changes
from blocked to LINKS for 836 authored bytes. LINK-132/LINK-133 remain open
globally; carry this removed-helper scope into the next normal census.
No measured linking gain is claimed.
[Evidence and remaining checks](../../reverse/attempt_support/static-text-link-20261028-codex3.md).
The staged-tree batch audit is INCONCLUSIVE: the index predates the base and
Common/0CreateAHeroManager21FE49.cpp lacks a current affected-consumer receipt.
Carry that consumer and the removed-helper scope into the next normal census.
