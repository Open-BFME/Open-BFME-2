# DeployStyleAIUpdate virtual command provider, 2026-11-05

Inspected revision: `5480792e2e21669a6107feefa61e069ddca6e057`.
Scope: the four approved DeployStyleAIUpdate source files, claimed by
`yasinschroeder-codex5`; the command row also holds its RVA claim.

## Target evidence and repair

`tools/rename.py function --rva 0x0048EA0F --virtual` proves the command's
virtual identity from retail table `0x00C4CA00`, slot 154 (`+0x268`), installed
at object offset zero by destructor `0x0048E852`. The existing canonical
DeployStyleAIUpdate header declares the corresponding virtual. This establishes
virtual dispatch identity; it makes no new donor or field-layout claim.

The seed's declaration and ledger incorrectly emitted the nonvirtual
`?doCommand@DeployStyleAIUpdate@@QAEXPBUAICommandParms@@_N@Z` provider.
The supported rename tool respelled it as
`?doCommand@DeployStyleAIUpdate@@UAEXPBUAICommandParms@@_N@Z`, preserving
its RVA, extent and source, and tombstoned the old identity.

The first automatic rewrite changed the comment and ledger but missed the
C++ declaration; verification reported the new symbol absent and the tool
restored the files. Its supported `--prepared` option supplied the explicit
`virtual` declaration. The same tool then verified all **28/28 seed rows**,
including the constructor and renumbered EH funclets. The final source diff
is only that keyword and the mangled-name comment. No new pin or alias is used.

## Composition trial and remaining prerequisites

The required consolidation planner ran under
`Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/`. The supported
`tu_skeleton.py --merge .../DeployStyleAIUpdate.cpp --dry-run` accepted no donors:
helper and Xfer private-seed field expressions did not compile together, and
the destructor did not byte-match in that composition. No merge was applied.
The prior seed-layout and factory prerequisites in LINK-277 remain.

A separate supported `header_adopt_lane.py adopt` trial for the destructor
byte-matched **4/4 rows** but exposed seven unresolved vtable names before
this repair. Repeating it with the repaired seed removed the `doCommand`
unresolved name. Six remain:

- `?GetSnapshotName@DeployStyleAIUpdate@@MBEPBDXZ`
- `?aiDoCommand@DeployStyleAIUpdate@@UAEXPBUAICommandParms@@@Z`
- `?isIdle@DeployStyleAIUpdate@@UBE_NXZ`
- `?loadPostProcess@DeployStyleAIUpdate@@MAEXXZ`
- `?vslot094@AIUpdateInterface@@UBEPAXXZ`
- `?vslot095@AIUpdateInterface@@UBEPAXXZ`

The two inherited providers are also documented by LINK-235. Restore the
existing provider identities before landing destructor adoption; then resolve
the seed/member composition and retry the supported merge. The trial destructor
was restored; no header debt was retired.

## Verification scope

- Final seed: `./build.sh` through the rename tool, **28/28 exact**; string,
  float and import checks pass. `find_declared_unmatched.py` passes.
- Final restored destructor: **4/4 exact**; its declared-unmatched check passes.
- `link_check.py --fetch-index` retained census **2026-11-05 05:17**, revision
  `c95fcfcfcd`, importing the current object store. Current-object previews
  preserve seed **2,890 -> 2,890** and destructor **128 -> 128** linked bytes,
  together **3,018 -> 3,018**. The rejected canonical destructor trial gave
  128 -> 0 and was restored. These are previews, not census gains.
- `check_csv.py` passes (99,463 function rows); no source paths, shared headers,
  debt registers or escape hatches changed. No real-link or smoke run was made.
