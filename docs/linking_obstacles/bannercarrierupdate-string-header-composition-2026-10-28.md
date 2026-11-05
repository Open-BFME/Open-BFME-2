### BannerCarrierUpdate string-header composition (2026-10-28)

Status: destructor prerequisite repaired and merged into the approved TU;
remaining donors and census confirmation pending. Inspected base: `309f097ad1`; preview index: `14dc3d2467`.

The destructor donor adopts the destination's shared AsciiString header,
removing a conflicting private StringBase template. All three donor rows stay
exact, frozen/class/data checks pass, and the donor still previews LINKS for
63 authored bytes. The emitted string-destructor helper is identical to the
destination's existing copy. A strict receipt is current; the batch audit is
INCONCLUSIVE because the index predates the base and lacks per-object consumer
names. No new linked coverage is claimed. Carry this scope into the next census.

[Evidence and remaining donor prerequisites](../../reverse/attempt_support/banner-carrier-consolidation-20261028-codex.md).
The supported merge removes one source file, preserves all nine rows and the
exact union of nine external COMDAT bodies, four exclusive definitions and 22
dependencies. All eleven remaining units preview the same 2,831 authored bytes.
Path/debt/queue checks pass; the final batch audit remains inconclusive.
Next: reconcile the other donors' layout, declaration and compiler-setting
conflicts, and confirm consumer selection in the next normal census.

2026-11-05: canonical UpdateModule adoption clears the constructor's base/declaration conflict; its merge now previews successfully ([evidence](../../reverse/attempt_support/banner-carrier-base-chain-20261105-codex3.md)).
