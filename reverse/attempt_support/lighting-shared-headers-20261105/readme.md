# Shared RTS3DScene and GlobalData in the lighting family

Inspected base c759a5bbbe968d327460bf9c897f7605d8cac3ba; model GPT-6.
Source: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayLightingScale.cpp.
Both class/header scopes and the source are origin-claimed before editing.
The BFME 1 reference remains committed946f3c05a1b1e60448734e874a8f47f8017cfdb9;
no official-upstream refresh is attempted. Old unrelated November2 commits stay
unchanged in codex/finish-lane-r-next-20261020 and are not part of this batch.

## Removal of the two private definitions

Include the unchanged canonical RTS3DScene.h and GlobalData.h and remove both
private bodies. Call the native scene ambient setter through its canonical
Vector3 argument and use the shared m_infantryAmbient at+0x144. Retail's scene
primary table VA0x00BC63C8 slot6 reaches0x0006E265, unchanged in the exact body.
No scene, base, destructor or virtual-table definition is emitted by this TU.

A direct Vector3::Set trial changes three native callers' component load/store
order. Retain the existing recovered twelve-byte RGB assignment view on the
canonical field: all three inputs are captured before its three stores. The
by-value RGB argument and local row spellings remain unproven ABI views, rather
than being renamed into asserted original types. No new type copy replaces
GlobalData or RTS3DScene under another name.

The real GlobalData fields supply time at+0x134, registered lighting storage
at+0x3C8 (m_terrainObjectsLighting) and+0x650 (field0650). The canonical arrays
have six time rows of three36B records, preserving native0x6C strides. Existing
Rva000443BARow read views keep the three float triplets without changing the
function signatures. field0650's original role stays unknown. Neither the old
private terrain/objects labels nor donor vocabulary establish that role.
Source line endings are normalized from CRLF to LF; flags are unchanged.

## Proof and limits

- All seven original rows (1120 extent bytes;1119 nonpadding bytes) pass normal
  and strict-current verification, including the existing float literal.
- All twelve old external code/data COMDAT fingerprints and relocations remain
  exact; no old definition disappears. The sole additional37B Vector3 value
  constructor equals the already emitted RGB value constructor in bytes and
  relocations. There are no emitted virtual tables before or after.
- Ordinary preview preserves LINKS1119->1119B against indexc95fcfcfcd
  (2026-11-05 05:17). New-variant protection returns0. These are bounded
  predictions, not a new census, real-link result or runtime proof.
- The owning header_adopt_lane accept verdicts each PASS and retire exactly
  one queue row: RTS3DScene and GlobalData. No manual queue or baseline removal.
  No function/symbol ledger, shared header, signature, pin or hatch changes.

Other scene/global users and unknown private RGB/light identities remain
separate work. Full current consumer selection is not proved by this scope;
carry the source and affected consumers into the next scheduled census.

Lighting family: t=12 model=gpt-6 lane=R budget=30m.
