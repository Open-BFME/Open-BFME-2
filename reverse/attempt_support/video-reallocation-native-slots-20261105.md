# W3DVideoBuffer reallocation view, 2026-11-05

Inspected revision: `6d190544dd`. Scope: the existing 0x00072480 / 32-byte
`W3DVideoBuffer::Rva00072480` row. No source path or ledger row moved.

Target facts: the slot map in
[LINK-101's retail-table evidence](link-101-w3dvideobuffer-vtables-20261103/README.md)
places the pure base method at slot 0, the destructor at slot 1, three-argument
allocation at slot 2, and this reallocation method at slot 12. The constructor
view already follows that order. The reallocation view instead declared the
destructor first and an obsolete two-argument allocation second; a separately
named three-argument method happened to occupy the required slot 2.

The reallocation view now shares the constructor's VideoBuffer declaration,
uses its derived virtual-method order and calls the already-rowed
three-argument `allocate`. Its state layout and field offsets are unchanged.
No table or destructor provider is added, and both link-wide aliases in the
seed remain untouched. This is declaration reconciliation, not new coverage.

Verification before and after the change:

- `./build.sh Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DVideoBufferRva00072480.cpp`:
  1/1 functions byte-exact, string/float/import checks pass.
- `find_declared_unmatched.py` on that source: all definitions matched.
- `link_check.py` on that source: LINKS, LINKED 32 -> 32 bytes, using census
  2026-11-05 05:17 at `c95fcfcfcd`. This is a local prediction, not a census.
- `tu_views.py W3DVideoBuffer.cpp --dry-run`: VideoBuffer changes from a
  slot-0 conflict to already shared (two files). W3DVideoBuffer still conflicts
  with Allocate's flattened view; Rva00739C70 and W3DRadarResetSurface have
  the previously recorded completeness/member-rename prerequisites.
- A fresh `tu_skeleton.py --merge W3DVideoBuffer.cpp --dry-run` accepts no
  donors: four sources lose rows under the seed's empty carried codegen
  override and six report no baseline match. It writes no source or ledger.

Remaining work: reconcile the flattened Allocate view and existing lifetime
providers, then the seed's compiler environment and remaining private views.
The merge pass test is still blocked. No debt retirement, source-file decrease,
headline linking gain or runtime verification is claimed.
