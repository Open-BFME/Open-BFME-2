### Typed Carryover uninitialized fill (2026-11-02)

The 40 B native straight uninitialized-fill loop at 1EBA5F now has an exact typed
instance beside its retained generic owner. All 157 original rows, 511 prior
complete code definitions, old data and ten EH graphs remain unchanged.
Normal/strict verification and current typed-provider closure pass. The native
workers have no cleanup-on-throw; no exception promise was added. This is a
same-source folded admission, with no unique/global coverage claim.
Evidence: reverse/attempt_support/carryover-uninitialized-fill-20261102/.
