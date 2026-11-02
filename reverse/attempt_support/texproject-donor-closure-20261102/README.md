# Texture-projector donor closure

At b5296ff98b, texproject.cpp has one native row (10 B), while unused donor
projector code creates 16 unresolved names. Replace that emission context
with the same native Set_Cull_Volume body defined against the established
MaterialPassClass header. Retail proves the argument store at +0x34; the
header already records its layout and the donor field spelling CullVolume.
No private canonical class, header change or new native claim is introduced.

The complete setter bytes and relocations remain unchanged. It is the only
remaining external code definition; 47 other emitted definitions disappear.
Normal/strict/new-variants checks and the private LinkGuard pass. The current
preview at index 984a4cdc4d (2026-11-02 08:35) now LINKS 0 -> 10 B. Census
confirmation remains pending.

The independent audit finds no outside touches of this unit's projector or
material-pass providers. All 45 shared definitions touched elsewhere have
outside providers. The two selected math helpers are unreferenced and have
identical copies in GapBodiesGE24.cpp. The archived source matches git at b5296ff98b, and the archived object hash
matches the independently observed original. Current replacement receipts
do not authenticate that old object. These limits and the native setter
proof are retained in provider-audit.json.

Owning tools retire the constructor's one present-unmatched occurrence and
the obsolete DX queue row (no DX stand-in remains). No path, pin, native row,
flag override, data key or identity key moves. Earlier ring publication
b5296ff98b's wider audit remains INCONCLUSIVE against 984a4cdc4d versus base
f6ab35ee57, first missing 0CreateAHeroManager21FE49.cpp's current consumer
receipt. Its native checks passed; global clearance remains for census.
