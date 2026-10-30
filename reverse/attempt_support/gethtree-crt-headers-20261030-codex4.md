# GetHTree CRT header cleanup

Base: `c647a75e55b27d0c76c8b56a8475fd4ba680ec52`. Source:
`Code/Libraries/Source/WWVegas/WW3D2/GetHTree.cpp`.

The Microsoft-header picker served local `_mbscpy` and `_strlwr`
declarations. The source now takes both prototypes from the toolchain
headers and passes unsigned-character pointers to `_mbscpy`. Including
`string.h` first preserves the imported `_strlwr`; saving and restoring
`_CRTIMP` around `mbstring.h` preserves the direct native copy thunk.
No shared header, game-class definition, compiler flag, source path, ledger
row or pin changes.

Verification:

- Normal builds before and after pass all four matched rows, the one string
  literal and the named import. Both frozen-source checks pass. The parent's
  EH graph is EXACT; existing parent evidence resolves both renumbered
  compiler funclet labels without a ledger edit.
- All four COMDAT name/digest/size records, thirteen external symbol records
  and the empty weak-external set remain identical. The digests include
  relocations. This preserves the direct `__mbscpy` and imported
  `__imp___strlwr` dependencies; it is not new retail coverage for unrowed
  definitions. [Object comparison](gethtree-crt-headers-20261030-codex4.json).
- Strict explicit-provider preparation passes 4/4 rows for GetHTree and
  3/3 rows across HTreePrototypeOwner.cpp and HTreePrototypeOwnerAssign.cpp.
- The fetched index is published at `12b9e7a7c0` (2026-10-30 10:11), with
  embedded census `2c21184e84`. The isolated preview reports the missing
  HTreePrototypeOwner constructor and 189 -> 0 authored bytes. The bounded
  three-source preview refuses the consolidated HTreePrototypeOwner.cpp as
  absent from that census. These are incomplete previews, not an observed
  loss caused by this cleanup: the caller's before/after object facts are
  identical. The constructor provider remains rowed at native `0x0017FBED`;
  no replacement pin or duplicate body was added.
- The staged three-source batch audit exits 2, INCONCLUSIVE: the index
  predates this base and the affected consumer
  Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. Full consumer
  selection and loss checks remain unverified. Carry GetHTree, its existing
  ownership providers and wider consumers into the next scheduled census.

The measurable cleanup is removal of the source's two local Microsoft-name
declarations through the owning auditor's scoped queue refresh. No census,
image-ownership, source-file or byte-coverage gain is claimed.

Reference freshness remains incomplete. Official BFME 1 master was fetched
once without recursion at `85ff94681faf00d093304e48f8e3069b88252399`;
the clean, committed reference remains the previously verified
`e5127cf32f0ea4bb6e31934782783817f719b651`. Another worker holds
`file:reference/open-bfme-1`. The initial old-input full verification was
stopped at baseline/lib preparation (exit 143) after that conflict became
known; no full-gate result, new-input trial or successful freshness stamp
is claimed. No donor implementation was imported or read for this cleanup.
