# FireLogicSystem guarded merge, 2026-11-05

Parent: `12a01444a14919040cce3dfeb4cecac016466e89`.
Path audit: `origin/master` at `1cccc2dd2bae3c9c4d0be20dc8e1a2d904ebfe92`
through that parent plus this staged merge. Earlier handed-over commits are
immutable; their existing evidence remains applicable.

## Result and placement

After the separately verified allocator-contract prerequisite, the refreshed
`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Map/` packet
and normal `tu_skeleton.py --merge ... --dry-run` accept the opaque-record tree
helper. The supported merge absorbs
`Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva0028681A.cpp` into
`Code/GameEngine/Source/GameLogic/Map/FireLogicSystem.cpp`. Two approved rows,
0x0028681A (56 bytes) and 0x0028691C (5 bytes), move without name or extent
changes. Only their source cells change in functions.csv and tu_map.csv; the
map is not regenerated. The destination now owns 34 matched rows. Source files
decrease by one, with no claimed increase in matched or census-linked coverage.

The ObjectID helper remains rejected for bytes and is unchanged. Its attempted
prerequisite, shared base-destructor COMDAT conflict and next step are described
in [the prerequisite report](readme.md). Mixed files remain untouched.

## Verification and bindings

- `./build.sh` passes 34/34, five string literals, six floating literals and one
  named import. Frozen-file, class, staged TU-ownership and whitespace checks
  pass. `check_csv.py` retains 99,463 functions, 9,313 symbols and 2,268 data rows.
- EH verification is EXACT for all three EH-bearing rows, with no missing object.
- The supported merge guard preserves all three census-linked input units while
  removing the donor. The current previews are LINKS 3,112 bytes for the merged
  destination and LINKS 66 bytes for the untouched ObjectID helper, against the
  2026-11-05 05:17 `c95fcfcfcd` index. The displayed destination increase from
  3,051 to 3,112 is the donor's existing 61 bytes changing owner.
- `merge-object-proof.json` compares a scratch, verified compilation of the
  parent's 32-row destination plus the original helper object against the final
  object. All 234 external definitions survive, with none added; no COMDAT is
  lost. 230 COMDAT digests agree. The only two changed digests retain identical
  raw code and change the free-call relocation to the existing matched wrapper,
  as in the separately published prerequisite. Thus existing update/map-index
  and tree-clear bindings are retained by composition.
- Converged data identity passes all 11 addresses, with no second names or
  unjudged rows. Shadow checks report the existing tree-clear and update/map-index
  binding findings, and the pending-vector wrong-name finding at 0x009FEC84.
  Their symbols and unchanged COMDATs are retained; no baseline key is retired.
  These findings remain cleanup work and are not presented as resolved.

## Registers, consumers and wider scope

Neither the absorbed donor nor its rows own identity, data, gate, hatch or header
debt keys. The four existing destination header-queue items (CommandList,
DamageInfo, FireLogicSystem, TerrainLogic) remain. The merge engine transfers
header ownership and refreshes the Microsoft-header queue through their owning
tools; neither queue needs a diff. No alias pragma or hatch is removed.

The complete pending path batch also contains the previously handed-over
`Common/Rva00531132.cpp` absorption into BooleanBitmapSet. Combined old-path and
basename searches across tools, hooks, workflows, source/includes, build/config
files, registers and documentation found no active filename consumers of either
deleted source. Remaining filename references are generated source provenance,
historical attempt evidence and the historical link_status.csv snapshot. Class
names containing Rva00531132 remain valid and are not path consumers. Existing
ledger and fold-proof references resolve to current tracked owners.

The earlier BooleanBitmapSet audit records an inconclusive wider batch check
because `Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. Preserve
that follow-up under LINK-001 for the next scheduled census. The pre-push batch
audit remains authoritative for any additional outgoing consumer findings. No
real-link, census, nightly or smoke run was started, and no global linking gain
is claimed.
