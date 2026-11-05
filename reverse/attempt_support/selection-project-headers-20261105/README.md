# SelectionXlat project-header prerequisite, 2026-11-05

Inspected base: `7dc4b67c8e`. Scope: the claimed SelectionXlat TU and its three
remaining donors. Only `SelectionXlat.cpp` changes; no header, ledger, register,
alias pragma or source path changes.

Replace the seed's PreRTS sweep environment and unused engine includes with
explicit STLport and project headers. The local SelectionXlatNative.h still
supplies the same SelectionTranslator declaration; FormationTranslator.h
supplies the existing translator base interface, and the canonical coordinate
headers supply its member types. Preserve PreRTS's `_STLP_USE_NEWALLOC` policy
explicitly. The STLport node-allocator include path remains a library dependency;
the Zero Hour engine and sweep include paths are removed. No claim that the
local SelectionTranslator member types are fully recovered is made.

Verification:

- Normal `./build.sh` passes all 13 rows, including the renamed unwind label.
  String, float and import-reference checks pass. Declared-unmatched reports
  all defined functions already matched, with the same pre-existing unused
  definition note. `check_csv.py` passes 99,463 function rows.
- `eh_verify.py`: EXACT 3/3, no missing objects or nonexact rows.
- All 76 retained external COMDAT providers have identical payload and symbolic
  relocation digests to the saved baseline object. No new provider or undefined
  name appears; weak externals and forced includes are unchanged.
- Dropping the unused donor headers removes 538 STLport constants and one
  34-byte compiler array-construction helper (`??_H@YGXPAXIHP6EPAX0@Z@Z`). Every
  removed provider has at least 260 other same-digest copies in the saved
  index, excluding the seed's object. These are index facts, not a whole-image
  ownership result or proof that all other objects are current.
- The existing purecall alternate remains. The canonical AsciiString header
  brings seven already shared aliases, each with the same target as over 6,400
  indexed copies; no alias is edited or removed. The provider audit records
  these side effects explicitly.
- Current source `link_check.py`: LINKS, 305 -> 305 bytes against the index at
  c95fcfcfcd (2026-11-05 05:17). Data check: zero findings. This preserves a
  preview result, not a census or real-link gain.

The supported merge dry run still accepts zero donors. The friends donor now
passes the former AsciiString conflict and reaches its unsigned subscript on
the seed's `map<const ThingTemplate *, int>` member. Before another merge,
reconcile that member's call view with the donor's ImageSubscriptMap and inspect
why canonical InGameUI adoption fails its byte check. The targeted tu_views
plan independently reports the constructor/friends +0x28 field identity
conflict (signed pointer-map versus ImageSubscriptMap); no view was applied.
The constructor's explicit vftable declaration still conflicts with the seed's
emitted Rva0042FCE6 table. Translate still imports the donor engine environment,
now conflicting on Coord3D/AsciiString; it also retains its special ICoord2D ABI
and vector-helper prerequisites. Port that donor separately, retaining its
byte-proven coordinate construction shape. No failed reconstruction is kept.

The unrestricted tu_views dry run could not parse Object's conditional
class declaration; the targeted SelectionTranslator plan above completed and
is the evidence used here. No tool behavior was changed to work around it.
Source-file reduction, TU approvals, retired debt and headline link gains: none.
