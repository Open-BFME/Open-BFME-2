### Typed Carryover uninitialized wrapper (2026-11-02)

The 27 B native standard STLport uninitialized-fill wrapper at 1EBAB4 now has an exact typed
instance beside its retained generic owner. All 157 original rows, 511 prior
complete code definitions, old data and ten EH graphs remain unchanged.
Normal/strict verification and current typed-provider closure pass. The native
workers have no cleanup-on-throw; no exception promise was added. This is a
same-source folded admission, with no unique/global coverage claim.
Evidence: reverse/attempt_support/carryover-uninitialized-wrapper-20261102/.
