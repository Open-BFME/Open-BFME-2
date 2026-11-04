# Shroud erase merge prerequisites

Base: `0a655903c5`; follows the canonical-header adoption in
[shroud-erase-header-20261104.md](shroud-erase-header-20261104.md).

The seed and erase donor previously defined the same signed `less<int>` inline
specialization separately. Both now include one TU-scoped comparison header,
which keeps the same body and prevents C2995 on composition. A first trial
then exposed a non-retail single-iterator erase COMDAT under the seed's flags.
The donor now declares that specialization out of line: its existing retail
provider is rowed at 0x005530A8 in `stlport_map_int_ptr_o1.cpp`. No pin or alias
is added, and the provider is not edited.

Verification:
- `./build.sh` seed and donor: 27/27 rows match; float/import/literal checks pass.
- Both `find_declared_unmatched.py` checks pass; donor retains only its two pre-existing admitted STL helper definitions.
- `link_check.py` seed and donor: both LINKS, preview retains 2,030/2,030 census-covered bytes against the 2026-11-04 11:27 index at `3a8028f34e`. This is a prediction, not a census gain.
- `tu_skeleton.py --merge .../W3DShroud.cpp --dry-run`: accepts seed plus erase donor, current census-linked-unit guard passes. No source path is moved in this prerequisite commit.

The interpolation donor remains outside the composition: duplicate typed iterator
comparison C2995 is now the first diagnostic. Its canonical W3DShroud view also
cannot supply the seed's lifetime-bearing private members; see LINK-225. That
independent prerequisite is not solved by sharing the comparator.

Publication preflight for the previous adoption commit stopped on an older
BuildingBehavior identity retirement because ToggleMountedSpecialAbilityUpdate's
provider object was stale. Its normal scoped build passes all 17 rows; no source
or ledger edit was needed for that cache repair.
