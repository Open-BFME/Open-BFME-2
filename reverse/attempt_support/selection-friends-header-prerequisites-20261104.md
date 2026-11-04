# SelectionXlat friends header prerequisites, 2026-11-04

Inspected base: `4ee23edebd`. Scope: the claimed SelectionXlat TU and its three
remaining donors; only `SelectionXlatSelectFriends.cpp` changes.

The supported header lane replaces the donor's private `GameMessage`,
`GameTextInterface` and `ImageSubscriptMap` declarations with their registered
headers. Each `header_adopt_lane.py adopt --class CLASS --header HEADER --apply
SOURCE` passed the ordinary byte verifier. `header_adopt_lane.py accept --class
CLASS SOURCE` then passed and retired exactly four queue rows: those three
classes and `Drawable`, whose registered header was already included. No other
debt register, hatch or function row changes.

Final verification:

- `./build.sh Code/GameEngine/Source/GameClient/MessageStream/SelectionXlatSelectFriends.cpp`:
  4/4 matched rows; both unwind-label renumberings verified through parent EH
  data; string, float and import reference checks pass.
- `find_declared_unmatched.py` on that source: all defined functions matched.
- `eh_verify.py` on that source: one EH row, EXACT 1, no missing or nonexact rows.
- `check_csv.py`: passes all 99,451 function rows.
- `link_check.py` on that source: LINKS, LINKED 329 -> 329 bytes, against the
  2026-11-04 12:23 census at `40fe1783d7`. This preserves an existing preview
  result; it is not a new census or linking gain.
- Scoped naming reviewed all seven bindings of `SelectionTranslator::selectFriends`:
  `msg` becomes `maxSelectionWarning`; six clear or explicitly dead bindings
  stay. A native child proposed the batch and the parent reviewed/applied it
  through `name_lane.py scoped`; the combined byte verification passed.

The `InGameUI` header adoption failed byte verification of the 321-byte
`selectFriends` body at RVA `0x0042FE7F`; the tool restored the source. Its queue
row remains. Next: compare the rejected canonical call sites with retail before
changing the view; the abbreviated failure does not establish the cause.

The supported post-adoption `tu_skeleton.py --merge .../SelectionXlat.cpp
--dry-run` still accepts no donors. `adopt_first` for the friends donor is now
only `InGameUI`. Composition still reports an AsciiString redefinition there;
the constructor retains its explicit-vtable declaration conflict, and Translate
retains IRegion2D/vector declaration conflicts. No donor is deleted, row moved,
TU map regenerated, or failed reconstruction retained in Code/. These are
remaining prerequisites, not a source-file reduction.
