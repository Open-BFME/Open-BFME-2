### GetHTree CRT headers and missing ownership-provider census object (2026-10-30)

At base `c647a75e55`, GetHTree.cpp replaces its local `_mbscpy` and
`_strlwr` declarations with the toolchain headers, preserving the direct copy
thunk and imported lowercase call. All four rows, the literal, named import
and parent EH graph verify; all four COMDAT fingerprints and thirteen external
symbol records remain identical. Strict preparation passes 7/7 rows across
the caller, HTreePrototypeOwner.cpp and HTreePrototypeOwnerAssign.cpp.

The index published at `12b9e7a7c0` (embedded census `2c21184e84`) lacks the
consolidated constructor provider. Isolated preview reports that unresolved
name; the bounded three-source preview refuses the absent census unit. The
staged audit is INCONCLUSIVE on the older baseline and missing current
Common/0CreateAHeroManager21FE49.cpp consumer receipt. Full affected-consumer
selection and loss checks remain pending; carry the caller, ownership providers
and wider consumers into the next scheduled census. No census gain or new
linking clearance is claimed.
[Verification and reference-refresh boundary](../../reverse/attempt_support/gethtree-crt-headers-20261030-codex4.md).
