# Apt view constructor consolidation, 2026-11-04

## Scope and evidence

At `defdb8c250`, the native merge absorbed
`Code/GameEngine/Source/Common/Rva00789900Init.cpp` into
`Code/GameEngine/Source/Common/W3DAptComponentView3D.cpp`. This removes one
source file and transfers the existing 51-byte constructor at `0x0074055A`.
The destination now owns 18 matched rows / 1,291 bytes, formerly 17 / 1,240
plus the donor's one / 51. This is source consolidation, with no matched or
census-linked coverage increase claimed.

The supported `name_lane.py consolidate --under Code/GameEngine/Source/Common/`
planner was refreshed before the merge. Its device-side Gui original-path hint
is investigation evidence only. The current TU map approves the Common TU on
provisional evidence; the merge changes only the constructor's source cell,
not its destination, confidence or evidence. No external donor path is claimed
as recovered BFME 2 source.

The preceding commit scopes the explicit vtable declaration inside
`W3DAptComponentTable` while preserving its existing C-linkage COFF name. This
resolves C2373 against the compiler-generated vtable without adding a symbol,
alias or pin. Standalone byte verification passed 1/1, its link preview retained
51 bytes, and an isolated seed/constructor composition passed 18/18 before
applying the native merge.

## Verification

- `tu_skeleton.py --merge Code/GameEngine/Source/Common/W3DAptComponentView3D.cpp`
  accepted the seed and constructor. Its LinkGuard retained the census-linked
  providers/consumers; six other donors were rejected and left intact.
- `./build.sh Code/GameEngine/Source/Common/W3DAptComponentView3D.cpp`:
  18/18 matched; source claims, strings, floats and imports passed. Seven funclet
  pins passed the parent-graph check despite compiler label renumbering.
- `find_declared_unmatched.py` passed before and after the merge. The seed's
  existing unclaimed-body note and counted marker remain unchanged.
- `eh_verify.py`: two EH-bearing rows EXACT, zero missing or non-exact objects.
- [Object comparison](object-comparison.json): all 22 external code definitions
  and nine external data definitions have identical full bytes and relocations
  to the two pre-merge objects. No definitions were added or removed. The two
  TU-local BSS definitions retain identical zero-initialized storage sizes,
  offsets, attributes and absence of relocations (BSS has no raw object bytes).
- `link_check.py` with the fetched index: LINKS, destination 1,240 -> 1,291
  bytes against census `2026-11-03 20:03`, revision `8661f15284`. Its current
  dependency cache was used. The transferred donor already linked separately.
- `check_csv.py`: 99,431 functions, 9,343 symbols, 2,269 data rows, OK.
  `tu_ownership.py --staged` and `check_case_collisions.py` passed.
- `data_check.py --converged`: 11 addresses, zero second names or unjudged rows.
  Shadow data checking reports the two existing local statics at `0x00A1F4E0`
  and `0x00A1F2B8` as wrong-name. Their names, references and storage are
  unchanged. Shadow code identity reports duplicate `??1Rva00740555@@UAE@XZ`;
  that definition already exists in the seed and is byte/relocation-identical.
  Neither finding was retired or added to a baseline.

## Registers and path consumers

The native tool repointed the one function row and TU-map source cell. The
absorbed donor has no gate, data-identity, code-identity, header or Microsoft
header register keys. The seed's header-adoption debts remain. Native header
transfer and Microsoft-header refresh produced no queue changes. The hatch
counter refresh produced no baseline change; the seed's existing address-global
and present-unmatched counts remain. No alternatename pragma was removed.

Immediately before publication, the outgoing tree comparison was inspected
against fetched `origin/master` (`9624d680c2`). Upstream-only renames and receipts
in that comparison were distinguished from our eight pending commits using
merge base `1fe9f84105`; those commits contain no source-path moves. The staged
constructor absorption is the sole outgoing source-path change.

A combined old-path/basename search covered tools, hooks, workflows, source and
header includes, build/configuration files, docs and reverse registers. No
active path consumer needs changing. Remaining old donor mentions are its
historical `reverse/link_status.csv` census row, two older attempt handoffs and
the merged TU's provenance comment. These intentionally retain their original
paths. Active function and TU ownership now resolve to the surviving source.

## Remaining merge prerequisites

The native trial rejected these donors without editing them:

- `Common/Rva007401E5Ctor.cpp`: C2600, constructor absent from the chosen view.
- `Common/Rva007401F6Dtor.cpp`: C2504 / incomplete `AsciiString`, base/type order.
- `Common/FamilyDeletingDtors_muse-e282.cpp`: C2664, missing constructor overload.
- Device `GUI/W3DAptComponentView3DSetup.cpp`: undefined `SimpleSceneClass` base
  and subsequent type-order errors.
- Device `GUI/W3DAptComponentView3D.cpp`: `RenderInfoClass` / `CameraClass`
  declaration-order errors.
- Device `GUI/W3DAptComponentView3DAnimInfo.cpp`: `StringBase` template
  redefinition against the bfme2_ascii shim.

Read-only `tu_views.py --dry-run` also identifies canonical CameraClass and
LightClass adoption prerequisites; Rva00740555 novtable disagreement;
Rva007401F6Base virtual-slot disagreement (xfer versus loadPostProcess);
Rva007401F6 declaration attributes; and a W3DAptComponentView3D slot disagreement
(SetLight versus setup). Reconcile those views/header prerequisites in verified
commits before retrying a further merge. No view patch was applied here.
