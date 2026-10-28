# Verified BFME 1 reference refresh

I fetched official Open-BFME/Open-BFME-1 `master` into this worktree's own
reference checkout, without recursive initialization. The previous clean
checkout and committed pin were `0424131c818fba6641613ef826222ecf30845025`.
The selected upstream HEAD is `f1648ab18ea1b34b8378f1f20d650fae57bbf24c`
(49 commits). I claimed `file:reference/open-bfme-1` before moving it. No
dirty or unpublished reference work was present.

The delta changes 89 paths: 49 game C/C++ sources, BFME 1 ledgers and attempt
evidence, progress images, `tools/comdat_families.py` with its test, and the
nested `inputs/reference/open-bfme-2` pointer. It adds or changes no header,
toolchain, baseline or compiler-setting path, and no layout path. The
`game/` and `inputs/reference/` resolution verified earlier still applies. The
nested BFME 2 reference is not initialized. The full list is in
[changed-paths.txt](changed-paths.txt).

## Consumers

- None of the changed paths appears among the 1,566 BFME 1 paths recorded in
  this worktree's build dependency sidecars.
- The new-reference run found all 21,089 compiled units dependency-current,
  so no recorded compile input changed.
- `Code/` and `reference/shims/` mention changed donor basenames only in
  provenance comments, never in an `#include`.
- No BFME 2 tool imports the changed `tools/comdat_families.py`.

## Full gates

Both ordinary `BUILD_POOL=8 ./build.sh` runs used the same BFME 2 inputs:
`b740e71229` plus the GameLogic.cpp include fix committed just before this
bump. The Code tree, patch and ledger digests are in
[input-receipt.json](input-receipt.json).

Each run exits zero with `FULL GATE: OK` and verifies:

- 98,945/98,945 functions across 21,090 sources;
- 223 STLport folds;
- 31,537 string literals and 2,247 empty-string references;
- 9,116 floats and 6,424 named imports;
- DIR32, pin and module consistency, and source claims;
- 2,203 data rows and the no-op patch (SHA-256 equal to the retail baseline).

The two logs are byte-identical (SHA-256 `d19f5eb1…`). The update adds no
failing check.

## Pre-existing failure, reported separately

At `b740e71229` itself, the first full gate in this nested worktree
(`build/wt_i`, two directories below a main checkout) failed. GameLogic.cpp
hit C2011 redefinitions from `GameLogicObjectLookupView.h`, which turned the
functions, string, float, import and DIR32 checks red.

The TU spelled two includes as `"../../Code/..."`, and its flags carry `/I.`
with cwd=ROOT. From the nested worktree, cl.exe therefore read the parent
checkout's copy of the header, a different physical file that `#pragma once`
does not suppress. The failure does not depend on the reference. Its own
commit fixes it, and that fix precedes both compared runs.

## Donor scan

I ran `bfme1_sweep.py scan --min-size 16` at both revisions. The results agree:

- 5,538 unique placements, all on claimed ground;
- 5,531 independent boundary controls;
- zero free placements, 3,325 ambiguous, 617 near misses.

The new revision adds four clean donors, and all four lack a usable needle
(38,884 to 38,888 donors; 1,093 to 1,097 without a needle). The `records`,
`near` and `ambiguous` sections of `match.json` are identical. This worktree
caches no donor compile trial, and the update imports no donor implementation.

I did not write the ignored freshness stamp. The lead records it after this
pin lands on master. No BFME 2 ledger, gate, baseline or whitelist changes
in this commit, and it claims no headline coverage or debt gain.
