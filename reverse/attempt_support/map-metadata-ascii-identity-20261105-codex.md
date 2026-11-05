# MapMetaData string cleanup identity

Inspected base: `c19ca81a72`. Scope:
`Code/GameEngine/Source/GameClient/MapMetaDataCopy.cpp`.

## Target facts and change

The identity register held `MapMetaData::~MapMetaData`'s reference to
`??1AsciiString@@QAE@XZ` at retail RVA `0x00036410`, whose owner is
`StringBase<char>::releaseBuffer`. This source selected the shared header's
declaration-only destructor with `/DBFME_ASCII_DTOR_DECL`.

Remove that per-unit override. The default shared-header destructor expands
its call to `StringBase<char>::releaseBuffer`; the emitted 156-byte
`MapMetaData` destructor now references that worker directly at relocation
offset `+0x50`. No class layout, shared header, alias or pin changes.

## Verification

- `./build.sh Code/GameEngine/Source/GameClient/MapMetaDataCopy.cpp`:
  16/16 matched before and after; string, float and import checks pass.
  Renumbered funclet labels resolve through the verified parent EH data.
- `find_declared_unmatched.py` on the source: all definitions matched or
  already marked; no new unclaimed definition.
- `eh_verify.py` on the source: EXACT 1, zero non-exact or missing objects.
- Ordinary `link_check.py` on the source: LINKS, 320 -> 320 authored bytes,
  against the 2026-11-04 22:40 census index at `3a95b274a2`.
- `repair_queue.py retire identity` on the source: PASS, two keys removed,
  zero still found. The other key was the obsolete source association for
  waypoint-tree assignment RVA `0x0030200E`; its current ledger source is
  `MapMetaDataCopyDeferred.cpp`. This does not clear that deferred unit's
  separate tree-identity obstacles.

The first retirement check refused three missing ledger objects and one
stale provider. Normal builds supplied Dinput8ImportThunks (1/1),
GdiplusImportThunks and Netapi32ImportThunks (20/20 combined), and
StringBaseWideReleaseBuffer (7/7); named import checks also passed.
The second retirement check passed without bypassing these prerequisites.

Clearance is limited to this source's two registered identity keys. The
preview preserves its existing linking coverage; no new census or runtime
result is claimed.
