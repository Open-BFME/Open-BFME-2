# Vector3 aggregate prerequisite: native bodies retained, new provider refused

The old owning queue reports C2552: Vector3 is no longer an aggregate after
adopting its registered constructor-bearing header. There are two zero-value
aggregate sites, at the two black clear values. The first private preflight
expected one site and was corrected before editing source.

Direct three-float construction resolves that compile boundary. Normal native
verification preserves 21 existing rows and all 34 old external code
bodies/relocations. It also emits one additional out-of-line constructor copy:
`??0Vector3@@QAE@MMM@Z`. No separate target ownership, provider suppression or
consumer-selection proof was established for that copy. The canonical header
is not changed and no invented pin, alias or baseline exception is used.

The original source and header key are restored. This is a blocked provider
prerequisite, not completed header debt retirement. The candidate, compiler
output and COFF delta remain in the dated diagnostic package. No full-image
link, new coverage or runtime/allocator improvement is claimed.
