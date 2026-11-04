# AIStatCollector final clean donor

Base: `9e671822ba`. Scope: the approved AIStatCollector TU and residual
`Code/GameEngine/Source/Common/Rva00282B26.cpp` (only row 0x004DFE4F).

## View reconciliation

The original merge dry run refused the donor because the seed's Rva004DFCE6
exposes `objects1C`, whereas the donor read separate `begin`/`end` members.
The seed also only forward-declared the Rva004DFE4F method's receiver prefix.
`tu_views.py --dry-run` independently identifies the overlapping vector fields
and proposes the donor's 0x24-byte receiver prefix for the seed.

The donor now reads the seed's existing vector<Object*> at +0x1C and active
byte at +0. The seed declares the donor's existing list at +0x10/+0x14 and
callback at +0x20. These are target layout observations; no original class
identity or donor name is inferred. No alias or pin changes.

Verification before committing reconciliation:

- `find_declared_unmatched.py` on both files: all definitions matched.
- `./build.sh` on both files: 43/43 functions exact, float/import/string
  checks pass; all nine renumbered funclet labels verified through parent EH.
- `link_check.py` on both current objects: 2/2 LINKS, 2,803 -> 2,803 bytes
  against the 2026-11-04 11:27 census at `3a8028f34e`.
- New merge dry run accepts the seed and donor with no rejected clean donor;
  41 rows in its composition. Three mixed files remain outside the merge.

The consolidation planner completed with no missing inputs and its snapshot
check passed before editing. It supplies investigation hints only; the merge
tool rebuilds the stale TU map in memory. No regenerated map is committed.

Merge, publication audit and post-merge verification follow separately. No
census or real-link gain is claimed by this prerequisite change.
