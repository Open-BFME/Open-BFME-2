# GettingBuiltBehavior strict compiler receipt

Base: `996746b43c`. Scope:
`Code/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehavior.cpp`.
The file claim was acquired before editing. HashableClass remains untouched.

The projected-decal publication audit needs current evidence for this direct
consumer of shared definitions. Its ordinary object compiled, but the supported
`link_check.py --prepare-current` command refused reusable evidence.

Tracing the existing inventory check first found `<math.h>` refused because
`/I.` makes the checkout an include root whose generated directories are excluded,
while explicit selected STLport overlay roots are under `build/stlport46/`.
Removing `/I.` alone still failed: the explicit
`-Ireference/open-bfme-1/inputs/vendor/stlport` took precedence over the project's
selected STLport and supplied native-header macro includes outside its recognized
roots. Removing both redundant include flags allows the existing STLport marker
and project include selection to work. No body, shared header, pin, alias, hatch,
baseline or tool changed.

Evidence retained under `build/decal-diagnostic/`:

- `gettingbuilt-before-strict.log`: unmodified current-master preparation exits 1.
- `gettingbuilt-after-strict.log`: removing only `/I.` still exits 1.
- `gettingbuilt-canonical-strict.log`: both flags removed; preparation exits 0,
  strict reusable receipt issued, 35/35 functions, one data row, one string,
  two float literals and three imports verified.
- `gettingbuilt-build.log`: official `./build.sh` passes the same rows.
- `eh_verify.py` reports the single EH graph EXACT.
- `gettingbuilt-provider-diff.json`: 74 COMDATs before and after, no added,
  removed or changed byte/relocation fingerprints.
- `gettingbuilt-link.log`: ordinary preview LINKS, 1,925 bytes preserved against
  the index at `aa505f34c8`. This is not a current-master whole-batch verdict.

The earlier consumer audit required 2,873 related providers; 2,795 lacked strict
receipts. Four completed batches prepared 128 before this file stopped the fifth.
Those successful preparations are retained. This source fix clears that refusal;
it does not establish current receipts for the remaining cohort or prove a real
link/runtime result. A subsequent batch audit must name its actual base and tip
and prepare any further missing consumers. Nothing is published by this repair.
