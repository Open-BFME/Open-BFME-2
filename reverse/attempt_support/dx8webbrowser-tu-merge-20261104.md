# DX8WebBrowser TU consolidation, 2026-11-04

`tu_skeleton.py --merge Code/Libraries/Source/WWVegas/WW3D2/dx8webbrowser.cpp`
absorbs `DX8WebBrowserInitialize.cpp`, reducing source files by one and keeping
all 18 code rows. The tool rebuilds its stale TU map in memory; the committed
map changes only the seven moved source columns. Mixed donors `BfmeConv804.cpp`
and `WebBrowserComWrappers.cpp` remain separate. Planner original-path and donor
leads are supporting evidence, not claims that those external paths are BFME 2
source.

Prerequisite commit `c07469ec70` adopts `WW3DClass.h`; the header lane accepts
both WW3D and the already included DX8Wrapper header, retiring two queue rows.
The merge transfers the GUID data row and its protected data-ledger key to the
destination. There are no baseline entries for either browser path in the
code/data identity or gate registers, and no pin, alias or hatch removals.
The merge engine refreshes the destination MS-header queue record; remaining
adaptation findings are retained. No header-queue rows remain for these paths.

Verification:

- `./build.sh` destination: 18/18 function rows, one GUID row, two literals and
  seven imports pass; nine renumbered funclet labels verified via parent EH.
- `find_declared_unmatched.py`: all defined functions already matched.
- `eh_verify.py`: four EXACT, no nonexact or missing-object cases.
- Staged TU ownership, class gate, case collisions, CSV and whitespace checks
  pass. Code identity reports zero new findings; data shadow check reports zero
  findings and the sequential converged check reports zero second names and
  zero unjudged rows.
- `link_check.py --prepare-current` writes a strict reusable destination
  receipt. Ordinary `link_check.py` reports LINKS, 559 -> 1,330 bytes, against
  census f12552d0a7 (2026-11-04 20:47). The retired donor contributed 771 bytes:
  this preserves local closure, not a census gain or a real-game link claim.
  The merge tool's linked-donor guard accepts both inputs.

Tooling compatibility audit covers the outgoing GroupOrder constructor moves
already recorded in `grouporder-tu-link-audit-20261104.md` plus this browser
move, through parent `60ae8fd89a` and the staged merge. Combined searches of
tools, hooks, workflows, source/includes, build/configuration files and source
registries find no active hard-coded donor references needing updates. Active
function/data/TU/register owners are repointed by the merge tool. Remaining
donor mentions are provenance comments, historical census/name-blocker records
and attempt evidence, intentionally retained. Existing local variable names
are clear or conventional; no speculative naming changes are included.

There is no matching browser obstacle entry. The prior GroupOrder batch audit
remains inconclusive because its census predates the outgoing base and a wider
shared-COMDAT consumer lacks a current receipt; see its linked evidence above.
The normal outgoing audit must still check changed provider/consumer bindings.
Carry both merges into the next scheduled census rather than treating local
previews as global link proof. No nightly, link-cycle or smoke runner was run.

Post-commit audit at `76a8594dfc`: the first invocation omitted the required
`--sources-from` argument and did not audit anything. The corrected invocation
uses a NUL-delimited destination-only verified-source list and exits 2:

```
link batch audit: INCONCLUSIVE baseline: index at f12552d0a7, outgoing base HEAD^; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```

Thus provider selection and complete affected-consumer closure remain unknown.
The browser scope is handed to LINK-344 for the next scheduled census.

The runner's pre-handover debt check refused the initial bundle because the
header-accepted source had subsequently vanished in the merge. Both owning
`header_adopt_lane.py accept` checks pass again on the destination (WW3D and
DX8Wrapper); no additional queue rows are removed. The follow-up commit carries
per-key `Debt-Retired` explanations for this vanished-source case. All seven
donor function rows and the GUID still exist in the destination, so deletion
tombstones would be false. No check is bypassed or edited.
