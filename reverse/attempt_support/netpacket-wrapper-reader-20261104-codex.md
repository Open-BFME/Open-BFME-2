# NetPacket wrapper reader canonical-header prerequisite

2026-11-04; inspected base `c24465d7c6`. Scope: existing 299-byte
`NetPacket::readWrapperMessage` at `0x0058E0E2`, in
`Code/GameEngine/Source/GameNetwork/NetPacketO1.cpp`.

The existing donor algorithm is retained with its license and exact revision.
Only its compiler context and allocation contract change: replace the donor
header graph, unused private views and pool macro with the registered
`NetCommandMsg.h` and `NetWrapperCommandMsg.h`; use ordinary global new for
retail's 0x38-byte wrapper. Target constructor/setter/layout evidence belongs
to that canonical header. The donor algorithm is not evidence of a BFME 2
source path or of BFME 2's allocation ABI.

The 299-byte parent still matches. Before this repair its existing EH baseline
key reported `bytes_differ`, six bytes at `.text$x` 0x0079CF40. The ordinary
new expression now emits retail's global-delete cleanup: EH verification is
EXACT. `eh_verify.py SOURCE --write-baseline` removed that one fixed key
(27 -> 26); no baseline key was manually deleted. No ledger extent, pin,
alternate-name route or source path changes in this prerequisite.

## Verification and providers

- Normal `./build.sh SOURCE`: 1/1 matched, 299 bytes; string/float/import
  checks pass. Frozen-file checks pass before and after.
- Both `header_adopt_lane.py accept --class NetWrapperCommandMsg SOURCE` and
  `--class NetCommandMsg` pass; neither source had a queue row to retire.
- `eh_verify.py SOURCE`: EXACT 1. `check_csv.py` passes.
- Ordinary link preview against the 2026-11-04 13:15 census at `f6d845ecd4`:
  reader LINKS 299 -> 299, seed LINKS 33,226 -> 33,226. Combined 33,525 bytes.
  `link_check.py --new-variants` on the pair passes. These are predictions,
  not census updates or a real-link result.
- Before/after strict COFF comparison: no added/changed external code
  definitions; no added/removed external data definitions. Three unneeded
  code definitions disappear. A strict scan of all 26,617 available cached
  objects finds no undefined references to any of them. The wrapper's
  `operator new(size_t, NetWrapperCommandMsgMagicEnum)` and corresponding
  delete have no other providers or referrers. The `??_H` compiler array
  helper has 2,045 alternate providers and no undefined referrers. No aliases
  were removed. Full outgoing batch audit and next scheduled census remain
  authoritative for integration beyond this bounded audit.

This clears the old NetPacketO1 BaseType/header composition prerequisite.
The two serializer views and Unicode helper have separate existing blockers;
no claim of their repair is made.
