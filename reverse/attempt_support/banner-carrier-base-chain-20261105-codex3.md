# BannerCarrierUpdate canonical base prerequisite

Inspected base: `a5b9ba3d4e1a`. Scope: the approved
`Code/GameEngine/Source/GameLogic/Object/Update/BannerCarrierUpdate.cpp`
and its `BannerCarrierUpdateCtor.cpp` donor.

The constructor already derives BannerCarrierUpdate from the canonical
UpdateModule. The destination instead declared BannerBase and BannerOther
stand-ins. Their data/object fields occupy the Module/ObjectModule slots;
adopting UpdateModule and its existing getModuleData/getObject accessors keeps
all destination code bytes exact. This reconciles the declarations without
changing the constructor's explicit retail vtable stores. This is target byte
and existing-header evidence, not a claim of recovered donor source.

Validation:

- `./build.sh` passes all 46 destination rows; the unchanged donor's one row
  and one 52-byte data table also pass. Strict receipts were refreshed for both.
- `eh_verify.py` verifies all nine destination EH graphs. Frozen-source checks
  find no declared unmatched bodies.
- `link_check.py` previews LINKS 3,273 -> 3,273 destination authored bytes and
  42 -> 42 donor bytes against the 2026-11-05 05:17 census index `c95fcfcfcd`.
  This is a preview, not new census linking coverage.
- Object comparison preserves all 144 retained external COMDAT digests. The
  removed BannerBase::getObject helper is replaced by the canonical Module
  and ObjectModule accessors. All 72 undefined symbols and four weak bindings
  are unchanged. A binary search across every current `build/match/*.obj`
  finds no remaining reference to the removed helper.
- UpdateModule header acceptance passes; the scoped MS-header scan finds no
  local definitions and changes no queue rows. Existing Player/W3DBridge queue
  entries remain. No debt is retired.
- The supported merge dry run now accepts BannerCarrierUpdateCtor.cpp with
  no rejected whole-file donor. The two other candidate files are mixed and
  remain outside this merge.

Next: apply the supported constructor merge, verify code/data and provider
preservation, and audit its path consumers before publishing the move.
