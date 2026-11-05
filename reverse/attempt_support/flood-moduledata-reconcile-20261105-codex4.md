# FloodUpdate module-data reconciliation

Inspected base: `7dc4b67c8e`; worker `yasinschroeder-codex4`, 2026-11-05.

The approved FloodUpdate TU could not absorb its module-data fragments:
the constructor redefined STLport templates, while the destructor used a
Snapshot-derived `list<int>` view incompatible with the consumer's padded
`list<FloodMember *>` view. Reconcile all three to Snapshot inheritance and
the existing four-byte `list<int>` ABI. The consumer interprets stored values
as FloodMember pointers; this does not identify retail's original template
argument. Scalar offsets remain +4, +8, +0xC and +0x10. The constructor now
uses the ordinary STLport list and Snapshot cleanup instead of a private
allocator/list-base recreation and an explicit vtable store.

Verification before consolidation:

- `./build.sh` on the three edited files and unchanged Rva0048E16CCtor:
  22/22 rows exact, including renumbered EH funclets; string and float checks pass.
- `find_declared_unmatched.py`: clean for all edited files.
- `eh_verify.py`: five exact EH records, no nonexact or missing records.
- `link_check.py` on the three edited files: all LINKS against the fetched
  2026-11-05 05:17 index at `c95fcfcfcd`; these were already census-linked
  units. No new census coverage is claimed.
- `tu_skeleton.py --merge .../FloodUpdate.cpp --dry-run`: both module-data
  fragments accepted, 21 rows retained with the existing TU.

Remaining donor: Rva0048E16CCtor.cpp. Its separate view uses BfmeE16 while
the consumer requires vector<Coord3D>. A trial using `__declspec(nothrow)`
instead of `throw()` retained the consumer bytes, but the rewritten ctor
still called vector<Coord3D>'s constructor instead of retail's rowed
_Vector_base at 0x00211E58. Declaring the base constructor out of line did
not change that call. Both trial files were restored; no nonmatching body
remains in Code/. The next attempt needs evidence for the vector wrapper's
inlining, while retaining the caller exception contract.
