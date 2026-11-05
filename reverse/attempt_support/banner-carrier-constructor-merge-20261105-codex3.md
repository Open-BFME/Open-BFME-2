# BannerCarrierUpdate constructor consolidation

Prerequisite: `69760b3a6d` (canonical UpdateModule base adoption), inspected
against census index `c95fcfcfcd`, 2026-11-05 05:17.

`tu_skeleton.py --merge` absorbed
`Code/GameEngine/Source/GameLogic/Object/Update/BannerCarrierUpdateCtor.cpp`
into the approved `BannerCarrierUpdate.cpp` in the same directory. Source
files decrease by one. The engine rebuilt TU approval in memory and changed
only the moved source cell in the committed TU map. Both required file scopes
and the engine's row claims were acquired. Two initial attempts stopped before
editing when origin did not confirm some claims; the subsequent acquisition
and supported merge succeeded without changing the claiming or merge checks.

Verification of the final combined unit:

- `./build.sh`: 47/47 matched code rows, one matched 52-byte data row,
  all 15 funclet pins, 11 string literals and two empty-string references pass.
- `link_check.py --prepare-current`: a fresh strict reusable provider receipt.
  The link preview reports LINKS for all 3,315 authored bytes, equal to the
  previous 3,273 + 42 bytes across the two objects. This is composition
  preservation, not a census coverage gain.
- `eh_verify.py`: EXACT 9/9 graphs. Frozen-source, class and CSV checks pass.
- Compared with the union of the canonical-base destination object and the
  unchanged constructor object: all 147 external COMDAT digests are identical;
  all 148 external definitions, 79 external dependencies (excluding names
  defined within that union), and four weak bindings are unchanged.
- The non-COMDAT `_vtbl_00C4F838` retains all 52 bytes and all 13 relocation
  targets exactly. Its data row and the constructor row now name the TU.
- No removed donor keys exist in the code-identity, data-check, flag, hatch,
  data-ownership or header registers. No debt retirement or alias removal was
  needed. The merge engine refreshed header/MS-header reports; UpdateModule
  acceptance and a scoped MS-header scan pass. Existing Player/W3DBridge debts
  and the destination's four data-ownership keys remain.

Tooling compatibility audit covered this batch's sole path change, the
constructor fragment's absorption, plus the earlier base-adoption commit.
The outgoing commit comparison used the fetched origin/master merge base to
exclude unrelated incoming commits. A repository-wide search for the donor
basename (excluding build artifacts, references and MASM dumps) finds no active
tool, hook, workflow, include, build/config or source-registry consumer.
The remaining mentions are the engine's source-provenance comment, historical
attempts/evidence, LINK-168's prior repair history, and the census-generated
`reverse/link_status.csv` snapshot. Those historical references are preserved;
the next normal census rekeys its snapshot. All active row/path ledgers point
at the combined TU; the protected registers need no transfers.

The remaining mixed-source candidates, Common/Rva0024A797Derived.cpp and
Update/ModuleDataBuildFieldParse.cpp, were not split or moved. Carry the merged
scope into the next normal census for full consumer-selection confirmation;
no real-link or image-ownership improvement is claimed here.
