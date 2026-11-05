# Drawable ID selection and snapshot consumer repair

Inspected revision: `032781edc486`, 2026-11-05. This continues LINK-534 for
`InGameUISelectDrawable.cpp` and `ObjectDoXfer.cpp`, after their former peer claims
expired. Both source files were claimed before editing. The picker's mouseover
target was already repaired by `032781edc486`; its scoped build passes 16/16 rows.

## Change and target evidence

The missing `?getID@Drawable@@QBE?AW4DrawableID@@XZ` definition is pinned to
retail RVA `0x0055A88B`, where the ledger already owns the seven-byte dword
getter as `?get@Rva0055A88BDwordField@@QBEHXZ` in `DispDwordFieldGetters.cpp`.
That provider reads `this + 0x100`, matching the established Drawable ID offset.
Its scoped byte verification passes ([provider-build.log](provider-build.log)).
This establishes the callable body, not a recovered identity for the opaque
holder class.

The selection result and object snapshot now call that existing provider and
cast its result to their existing DrawableID enum. The null-drawable snapshot
branch still supplies INVALID_DRAWABLE_ID. No source paths, ledger rows, pins,
aliases or debt registers change.

## Verification

- Before editing, both declared-unmatched checks pass and the scoped build passes
  18/18 rows. Both checks also pass after editing.
- [build-after.log](build-after.log) passes all 18 rows, the ten funclet bindings,
  five string references, float references and import references.
- [object-audit.json](object-audit.json), produced by
  [object-audit.py](object-audit.py), preserves all 60 external definitions and
  60 external COMDATs. Each object removes exactly the missing getter reference
  and adds exactly the existing provider reference. All COMDAT bytes, sizes and
  relocation tuples match after normalizing only that substitution, with local
  relocation labels normalized as in the census. One COMDAT fingerprint changes
  per unit: evaluateSoloNexus and Object::xfer. The provider object defines the
  replacement symbol. Pre-edit objects remain scratch under
  `build/drawable-id-final-consumers/`.
- [link-before.log](link-before.log) and [link-after.log](link-after.log) both
  report LINKS for both units, 4,023 bytes, against census `c95fcfcfcd` at
  2026-11-05 05:17. The preview already accepted the old pin, so this preserves
  the preview result and claims no measured link gain.

Commands: `find_declared_unmatched.py` separately on each source, `./build.sh`
on both sources, `link_check.py` on both sources before and after, and
`./build.sh '?get@Rva0055A88BDwordField@@QBEHXZ'` for the provider.

GameClient.cpp remains peer-held and still calls Drawable::getID. It is the
remaining unrepaired consumer from LINK-534's original twelve. Confirm these
two consumers disappear from the next real-link missing-name errors; no new
real-link, census or runtime result is claimed.
