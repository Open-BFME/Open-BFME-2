# BannerUI declaration prerequisites

Inspected base: `666892446c3aff518e8b273d7cf14c9114731f06`.
Destination: `Code/GameEngine/Source/GameClient/GUI/InGame/Tactical/BannerUI.cpp`.

## Evidence and change

The default picker selected the current-input approved BannerUI group: 83
approved rows, 20 whole-file candidates with 79 matched rows, and 11 mixed
sources that must remain separate. `name_lane.py consolidate` was run for
`Code/GameEngine/Source/GameClient/GUI/InGame/Tactical/`. Its WorldBuilder
Tactical path and BFME 1 Palantir/Apt alternatives are routing leads, not proof
of BFME 2's original filename. No naming or TU-map change is made here.

The first supported merge dry run accepted nothing. Even the composed seed
failed: its local `#define V` and `#undef V` were collected before MessageStream,
leaving the class's `V(0)` through `V(17)` unexpanded. Several donor combinations
also lost the seed's forward declaration of Rva00222A8BTarget when composition
selected a later donor's complete declaration.

The prerequisite expands the same 18 pure virtual declarations in MessageStream
and replaces the Apt target's forward declaration with its existing interface
from `GameClient/Rva00216517Fire.cpp`. The `invoke` signature is existing target
evidence, not a recovered donor name or new layout claim. No body, virtual slot,
pin, row, source path or registered debt changes.

## Verification

- Before editing, `find_declared_unmatched.py` passed for all 20 candidates.
  Strict `link_check.py --prepare-current` verified all 79 function rows and two
  data rows with current reusable receipts. An earlier concurrent preparation
  correctly refused changing temporary inputs; the stable retry passed.
- After editing, `./build.sh` passes 29/29 seed rows, including the verified
  renumbered funclets, 13 literals, one empty-string reference, one float literal
  and one named import. The frozen-file check still passes.
- The seed's 71 COMDAT name/digest/size entries, 13 exclusive definitions,
  56 undefined externals and one weak binding are identical before and after.
- `eh_verify.py` reports 7/7 EH graphs EXACT. Enforced converged-data checking
  reports 11 addresses, zero second names and zero unjudged rows.
- Fresh strict seed preparation passes. The ordinary preview against census
  index `d92e7e6635` (2026-10-28 15:58) remains LINKS, 1,885 -> 1,885 authored
  bytes. This preserves a bounded preview; no census gain is claimed.
- The second supported dry run accepts the seed and five donors, 36 matched
  rows total: Rva002160C4Dtor.cpp, Rva00216108Dtor.cpp,
  FamilyDeletingDtors_Rva00216108.cpp, Rva00216245Fill.cpp and Rva00216D5C.cpp.
  Its merge guard accepts that subset. The prerequisite commit itself does not
  perform the merge.
- The staged-tree batch audit is INCONCLUSIVE: its index is older than the
  outgoing base, and BannerUIUpdate.cpp lacks a receipt current for the changed
  declaration inputs. The unchanged seed COMDATs and bindings establish the
  bounded repair only. Carry the affected consumers into the next normal census;
  broader consumer clearance is not claimed.

## Remaining work

The first dry run also found incompatible private views of BannerUI,
BfmePod28, Gen_003A8BE0, Rva00216094 and Rva00216BF0; allocator/template
redefinitions; and a selected Gen_003A8BE0 destructor duplicate in a trial
without a census object. Do not treat declaration repair as clearance of those
obstacles. Use the supported merge verifier and reconcile rejected views in
separate byte-verified commits. The group includes six existing hatches and
one Microsoft-header queue entry; this prerequisite leaves their owners intact.
The second dry run still rejects the direct Rva00216517Fire donor for declaration
ordering, along with 13 donors with other compile failures. The early Apt
interface only clears ordering for the accepted subset, not every composition.
