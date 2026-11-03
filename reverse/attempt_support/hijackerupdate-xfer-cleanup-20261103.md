# HijackerUpdate unverified donor xfer cleanup

Inspected revision: `b2aa7352f44a40f53c272a379632a281e568161f`.

## Target facts

- The six matched rows in `Code/GameEngine/Source/GameLogic/Object/Update/HijackerUpdate.cpp` pass `./build.sh` before this change.
- The retail body at 0x004A3FAA is already rowed as `?xfer@Rva004A3F8B@@MAEXPAVXfer@@@Z` in `Code/GameEngine/Source/Common/Rva004A3F8BXfer.cpp` (102 bytes). This cleanup changes neither row nor source.
- The published provider index (2026-11-03 20:03, provider revision `8661f15284`, census revision `23b85ddde5`) marks `?xfer@HijackerUpdate@@MAEXPAVXfer@@@Z` unreferenced. The only provider is HijackerUpdate's object; no per-object reference graph root or edge names this symbol. This is index-scoped evidence, not a new census.

## Donor facts and retained attempt

The removed definition came from the Zero Hour port retained in the seed. Its version-first transfer order differs from the rowed retail implementation's base-transfer/light-CRC/version order. No BFME 2 name or source-path recovery is claimed. The old definition was covered only by a counted `present-unmatched` marker. Preserve it here as an unverified donor attempt:

```cpp
// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@HijackerUpdate@@ present-unmatched
void HijackerUpdate::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpdateModule::xfer( xfer );

	// target ID
	xfer->xferObjectID( &m_targetID );

	// eject pos
	xfer->xferCoord3D( &m_ejectPos );

	// udpate
	xfer->xferBool( &m_update );

	// is in vehicle
	xfer->xferBool( &m_isInVehicle );

	// was target airborne
	xfer->xferBool( &m_wasTargetAirborne );

}

  // end xfer
```

## Consolidation prerequisites

`tu_views.py` found no mergeable donor and applied no edits. `HijackerUpdate` base clauses differ (`UpdateModule` in the ctor versus `RvaUpdateModule` in update). The current merge trial rejects Xfer for a canonical/shared-header redefinition, PoolKey for SubsystemInterface redefinition, and ctor/update for `INVALID_ID` redefinition before further hierarchy reconciliation. Reconcile the seed's donor header environment against the canonical declarations in separately byte-verified changes before retrying these same merges.

## Verification

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Update/HijackerUpdate.cpp`: 6/6 rows exact; literal, float and import reference checks pass.
- `find_declared_unmatched.py`: all defined functions already matched; unclaimed definitions fall from 3 to 2 (existing absent-from-retail anchors).
- `hatch_counters.py --update`: `present_unmatched` 2396 -> 2395; only the seed xfer key disappears.
- Current-object `link_check.py` after removal: seed 104/104 and retail Xfer owner 102/102 bytes link; before removal, all five scoped units link (672/672 bytes). These predictions do not update census headlines.
- No source paths, pins, aliases, matched rows or provider identities changed. The removed unrowed symbol has no reference in the published index. No `/alternatename` was removed.
- `link_check.py --prepare-current` on the changed TU passed: all six rows byte-verified with a strict reusable compiler receipt; no census/index/status updates.
- `link_batch_audit.py --base HEAD^ --tip HEAD --sources-from build/hijackerupdate-verified-sources.bin` after strict preparation returned 2 (inconclusive): index `8661f15284` predates the outgoing base, and affected consumer `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. The first audit had also refused the changed TU's non-strict receipt; the supported preparation command resolved that narrower issue.
- The provider-removal audit is therefore not a full clearance. Carry the changed TU and affected consumers into the next census; do not count a linking headline gain.
