# MultiplayerColorDefinition canonical-header adoption

2026-11-04; inspected base `496c9e949d92a79d0bd4401b25549b55ae1a9cff`.

Replace eleven private MultiplayerColorDefinition bodies in lobby, chat, load
screen, network GUI and Living World units with the existing canonical
GameNetwork/MultiplayerColorDefinition.h. MultiplayerSettings.cpp already
includes it and needs only its stale queue row retired.

Target facts are documented in the unchanged canonical header: packed color
at +0x10, availability byte at +0x3C and three RGB triplets used by
LivingWorldPlayer at +0x04, +0x24 and +0x30. Bind only the corresponding
MultiplayerColorDefinition accesses to those existing canonical fields;
GameSlot color fields and MultiplayerSettings padding keep their own bindings.
LivingWorldPlayer's three receiving triplets use canonical RGBColor, preserving
their sizes, offsets and trivial copy operations. The extra triplets and flag
keep the header's neutral names; this makes no new original-name claim.

The automatic adopter refuses ambiguous token renames, unmatched padding
members and the nonstandard brace/semicolon formatting in AptMpGameSetup's
Rva0043DC40 unit. Explicit include replacements and receiver-specific accesses
resolve this cohort without changing the tool or the canonical header.

Verification:

- [Scoped build](build.log): 397/397 function rows, three data rows, string,
  float and import checks pass across all twelve units.
- find_declared_unmatched.py passes on every unit before and after adoption.
- [Owning acceptance](accept.log): all twelve units pass structural, byte and
  combined link checks; header_adopt_lane.py accept retires exactly twelve
  queue rows. No census-linked-byte loss is predicted.
- No function/data ledger ownership, pin, alias or source path is changed.
  This is header debt retirement, with no claimed census or runtime gain.
