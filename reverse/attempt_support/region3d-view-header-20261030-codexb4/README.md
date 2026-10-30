# W3DView Region3D header adoption

Base: `28a66c803b`. Scope:
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewGetAxisAlignedViewRegion.cpp`.

## Target evidence and representation

The existing parent at `0x00085B41` (380 bytes), cleanup at `0x0075FACD`
(19 bytes), and handler at `0x0075FAE0` (10 bytes) all remain exact.
The corner array retains the out-of-line Coord3D constructor/destructor
references, owned by coord3d.cpp at `0x0047A6A9` and `0x000B3FD0`.
The complete parent EH graph remains EXACT.

Previous trials in re_attempts.log established two requirements: the corner
array must keep those lifetime calls, while the map-extent output storage
must introduce no additional constructor, destructor, or unwind state.
Including canonical Region3D with the existing Coord3DCtorView companion
meets the first requirement. Using six floats of output storage, viewed
through Region3D at the virtual getExtent interface, meets the second.
Assignments to the output region now use Coord3D directly, so both private
Region3D and the separate Coord3DData view disappear.

The raw storage declaration is a reconstruction choice, not a claim about
retail's original local declaration. The existing BFME 1 provenance in the
source remains unchanged; no new donor source or original symbol is claimed.
No shared header, ledger identity, pin, source path, or hatch changes.

## Verification

- Normal before/after builds: 3/3 function rows, both floating-point literals,
  and the parent-resolved cleanup label pass.
- `find_declared_unmatched.py`: all defined functions are matched.
- `eh_verify.py`: one graph, EXACT, no baseline or missing object.
- `link_check.py --prepare-current`: one explicit provider byte-verified
  with a strict reusable receipt; no census/index/status change.
- `header_adopt_lane.py accept --class Region3D`: PASS; the owning tool
  retires this source's single Region3D queue row.
- [Before/after external object facts](object-comparison.json), collected
  with link_census.object_facts and a neutral verdict callback, are identical:
  three COMDAT fingerprints, one strong definition, nine undefined names,
  zero weak externals. The function fingerprint is `e7fc412560c9` in both.
  This comparison normalizes compiler-local label numbering and is separate
  from the exact parent, cleanup, handler, and EH checks above.

Ordinary preview against index `85f6b7f40c` (2026-10-29 15:08) retains
LINKS, 389 -> 389 authored bytes. This is a per-unit preview, not a census.
Outgoing audit results are recorded below after completion.

## Refreshed checks and outgoing audit boundary

Rechecked at `0b3c172274` after pulling origin/master. The normal source build
still passes all three rows and both floating-point literals;
`find_declared_unmatched.py`, strict current preparation, the EXACT parent EH
graph and the owning Region3D acceptance check all pass. The ordinary preview
again retains LINKS, 389 -> 389 bytes against `85f6b7f40c`.

The staged outgoing-batch audit (base `4bc55a5889`, including the two earlier
campaign prerequisite commits) exits 2, INCONCLUSIVE: the index predates the
base, and two source objects lack current receipts, first
`Code/GameEngine/Source/GameLogic/System/LinearCampaignManager.cpp`.
Supported preparation of the three campaign providers compiles the two stale
objects, then refuses a strict reusable receipt for LinearCampaignManager:
its include inventory has a macro or parent-traversing include with unknown
search roots. This is the preparation mode's explicit uncacheable-input
boundary; no check, compiler input or receipt was overridden.

The subsequent normal campaign build passes 35/35 function rows, its data
row and all three string references. This verifies those existing commits'
rows; it does not establish affected-consumer closure. Repeating the audit
after that build reduces the missing current receipts to one,
LinearCampaignManager.cpp; the result remains INCONCLUSIVE (exit 2).

Full affected-consumer selection/loss verification remains unproven. Carry
the W3DView provider, campaign providers and their affected consumers into the
next scheduled census. No new census or smoke run was started.

## Remaining scope

This retires one header debt row; it claims no census linking gain. The other
Region3D queue entry, region.cpp, still has the separate Coord3D class-key
and streamer-provider prerequisite. W3DView consolidation still needs its
supported merge and remaining private-view reconciliation. External consumer
selection and census confirmation remain for the scheduled census.
