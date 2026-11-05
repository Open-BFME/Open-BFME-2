# Science parser: canonical ScienceStore adoption

Inspected base: `34dbe32ba718c88b6659fd344f6e8dd842425387`.
Scope: `Code/GameEngine/Source/Common/RTS/ScienceStoreParseScienceDefinition.cpp`,
selected as a donor in the approved Science.cpp consolidation group.

The parser's private ScienceStore view stored a vector at +0x0C. Replace that
view with Common/ScienceStore.h and cast the canonical field0c storage to the
caller's existing vector<const ModuleData *> spelling. The three canonical
pointers retain the vector layout and existing template providers. Use the
existing Rva001FFE93 name directly: the old local ScienceInfo typedef conflicts
with the header's forward declaration. No ledger name, pin or class identity is
changed.

Keep each vector expression based on the current TheScienceStore. An initial
local vector reference incorrectly retained the receiver across allocation and
callback calls and did not match retail; the repeated expressions preserve the
retail reloads and restore the full byte match.

Verification:

- `./build.sh` passes both code rows (62 + 330 bytes) and the 112-byte field table.
- `find_declared_unmatched.py` passes.
- `header_adopt_lane.py accept --class ScienceStore` passes and retires exactly
  the parser's ScienceStore header-queue row through the owning tool.
- Ordinary current-object preview reports LINKS, 392 -> 392 own bytes, against
  the 2026-11-05 05:17 census at `c95fcfcfcd`. The new-variants check also passes.
- Data identity reports zero findings; converged data checks report no second
  names or unjudged rows. EH verification finds no EH-bearing rows in this unit.
- CSV integrity and diff whitespace checks pass.

The refreshed supported merge dry run now gets past the ScienceStore field
conflict. It next rejects the parser because the composed Overridable declaration
lacks setReloadState. Reconcile its canonical accessors/opaque +0x0C write and
the queued INI view next; both class scopes were held by peers during this pass.
The destructor donor still fails the selected Rva001FF909 vtable guard, and
StlSweepR3Rva001FFD6B still fails bytes. The unchanged seed/tree pair remains
accepted. Rva001FFA5A and Rva001FFEE9 are already shared according to tu_views.

No merge is applied: the supported apply command refused shared-address claims
at 0x0007FAB3 and 0x0014F3C4 held by another worker. No source path moves,
TU-map regeneration, hatch edits, source-count reduction, new census measurement
or linked-byte gain are claimed. Local logs are under
`build/science-parser-session/`; the initial merge refusal is in
`build/science-session-merge.log`.
