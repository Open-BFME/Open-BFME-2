### AptScriptColour clean-donor declaration and merge (2026-10-31)

The missing qualified `AptObject::DestroyGCPointers` declaration from the
2026-10-27 trial is cleared. Both partial call declarations are reconciled
in a separate verified commit; the supported merge then absorbs the one
clean donor into its approved TU and removes one source file. Both 45/30-byte
bodies and all external code definitions/relocations are unchanged. Normal
gates, strict preparation and the census-based LinkGuard pass. The bounded
preview conserves the cohort's 75 linked bytes; no new coverage is claimed.
The three mixed-donor prerequisites and broader consumer/census verification
remain open. [Proof and path audit](../../reverse/attempt_support/apt-colour-consolidation-20261031.md).

The prepublication outgoing audit is INCONCLUSIVE: index `3c7a254a38`
predates base `2f86780fee`, and the affected CreateAHeroManager21FE49
consumer lacks a current receipt. Retain this limitation for the scheduled
census; the exact two-body preservation and LinkGuard do not clear that
broader consumer scope.
