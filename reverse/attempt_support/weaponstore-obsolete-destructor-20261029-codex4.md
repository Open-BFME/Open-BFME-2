# WeaponStore obsolete destructor removal

Inspected base `2f86c49f4552`, 2026-10-29, seat codex4.

The default picker claimed the 47-byte WeaponStore constructor for link repair.
LINK-009 already records its split identity with Rva002CCD56 and the unsupported
placeholder-to-real merge. Current native ownership is unchanged: the complete
225-byte destructor, deleting destructor at 0x002CD5E0, EH handler and unwind
funclet are rowed in Rva002CCD56Dtor.cpp. The constructor installs the table
at VA 0x00C02114; that relationship alone does not establish an original name.
No rename, alias, pin, row move or new matching claim is made.

The retained Zero Hour destructor in Weapon.cpp is different: its emitted body
is 145 bytes, and its table is only 24 bytes. Remove that unrowed implementation
and its `present-unmatched` marker. The donor does not provide BFME 2's complete
two-vector teardown. `hatch_counters.py --update` retires exactly its one key:
present_unmatched falls from 3,666 to 3,665. This is hatch cleanup, not completion
of the constructor's link task.

Verification and provider audit:

- Normal builds preserve all 13 function rows in Weapon.cpp, WeaponStore.cpp
  and Rva002CCD56Dtor.cpp, plus Weapon.cpp's data row. The source checker
  accepts both states; the declared-unmatched count falls from 30 to 29.
- Strict `link_check.py --prepare-current` passes 24/24 rows and ten data rows
  across those three units plus WeaponStoreReset.cpp and WeaponStoreNewOverride.cpp.
  The existing WeaponTemplateParseClearNuggets.cpp provider separately passes
  its one row.
- `eh_verify.py` passes the destructor's one EXACT graph with no baseline or
  missing object. No covered code or EH ownership is removed.
- Object comparison removes 26 external COMDAT definitions, including the
  obsolete complete/deleting destructors and table. It adds no definitions.
  Of the 986 retained copies, 985 keep their relocation-aware fingerprints.
  The only changed retained copy is the unrowed privateFireWeapon donor:
  its body remains 1,014 bytes with identical relocation names/offsets; one
  source-line argument changes from 1,835 to 1,826 after deleting nine lines.
- Against index 85f6b7f40c (2026-10-29 15:08), every removed definition touched
  by another object has another provider. The relevant current reset and
  new-override consumers retain LINKS with the existing destructor owner.
  The first new-override preview lacks parseClearNuggets because it refreshes
  that unit's current field table without refreshing its existing provider;
  including WeaponTemplateParseClearNuggets.cpp restores LINKS. This is an
  input-freshness issue, not a removed provider.
- The six-unit preview preserves all 1,045 authored bytes in the four linking
  units (destructor 263, reset 87, new-override 605, parser 90). Weapon.cpp
  retains its existing 18 unresolved names and DamageInfo COMDAT/selection
  blockers. WeaponStore.cpp loses its conflicting table-copy blocker but
  still has unresolved protected `~WeaponStore` and fake base `unused`.

Remaining work: reconcile the complete native subsystem view and admit the
placeholder-to-real identity merge before retrying the constructor. Weapon.cpp
also retains its existing unrelated donor/header blockers. Full affected-consumer
verification and the next scheduled census remain pending. No linked-byte or
image-ownership gain is claimed.
