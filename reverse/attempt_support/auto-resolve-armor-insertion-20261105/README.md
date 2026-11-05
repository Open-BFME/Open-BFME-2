# Auto-resolve armor insertion identity, 2026-11-05

Inspected revision: `892820c8d44e2d9f3dc540837269a1e3b0c5b64a`.
Source: `Code/GameEngine/Source/GameClient/GUI/Rva00427157Ctor.cpp`.

The remaining code-identity key for `parseArmorDefinition` at RVA `0x00427392`
bound its typed hash-map subscript to RVA `0x0041F4E5`, but that emitted copy
was not retail's body. This continues the evidence in
`../auto-resolve-armor-identity-20261104/README.md`; it does not retry the
unsuccessful resize reconstruction or introduce a new owner or pin.

Target facts: the existing owner at `0x0041F4E5` is the matched 63-byte
`ObjectLookupMap::findSlot` in `ObjectLookupMapFindSlot.cpp`. Its key is four
bytes, its value is a pointer, and its table and node offsets match the
pointer-valued STLport map used here. The existing `ArmorStoreReload.cpp`
consumer uses the same provider view. The parser now calls that owner through
the map view and stores the newly allocated armor pointer in the returned slot.
This is a storage/ABI view, not evidence of an original armor class spelling.
The byte gate verifies the caller's complete body and its retail call target.

Verification:

- `build.log`: all 13 code rows and one FieldParse data row pass; string,
  float and import references pass too.
- `eh.log`: all three EH parents are EXACT.
- `identity.log`: `repair_queue.py retire identity` passes and removes the
  one remaining registered key, with zero findings left for this source.
  The first retirement refused one stale provider, Weapon.cpp; the normal
  `build.sh` refresh passes all eight rows and its data row in
  `provider-build.log`, after which retirement passes.
- `link.log`: current-object preview preserves LINKS, 691 -> 691 bytes,
  against census index `c95fcfcfcd` (2026-11-05 05:17).
- `variants.log`: no new COMDAT variant is reported.

The frozen-file check is clean. No rows, pins, link-wide aliases, headers or
source paths change. The debt register shrinks only through its owning tool.
No real-link or new census measurement is claimed. The separate EH destructor
prerequisite recorded in LINK-095 is outside this repair's scope.
