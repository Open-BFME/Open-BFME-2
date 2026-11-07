# Separate the native float setter from a RenderObjClass alias

2026-11-07, before source SHA in report.json, investigated after `009791f6a9`.

## Target facts and recovery

Retail 0x005AD93A is a complete 14-byte thiscall body: load the float argument,
store at receiver+0x4C, ret4. RenderObjClass::Set_ObjectScale at 0x0006CEBF
instead stores at +0x48. The old gen-alias/object-symbol row incorrectly gave
both addresses the RenderObjClass name. No named direct caller or image word
identifies the former body's original owner; the retained tool outputs and
raw bytes in target-facts.json state those evidence limits.

The replacement is a small ordinary C++ field setter under an address-derived
owner/method placeholder. The padding establishes only the observed field
offset, not the original class's complete layout or name. The supported
add_match.py --replace-rva path replaces the anonymous scaffold row. No pin,
assembly, alias, new source file or source-path move is added. Its existing
collect.cpp placement stays pending TU evidence.

The anchor's explicit RenderObjClass::Set_ObjectScale call is removed. It
existed to force the incorrectly attributed header copy into the object and
is no longer needed to preserve the row. Other anchor uses remain for their
existing verified rows. The EFB4C owner-identification prerequisite is unchanged.

## Verification

* Private candidate and normal add_match verification: all five collect.cpp
  rows exact, including the complete new 14-byte body.
* Before/after object comparison: the only removed external definition is
  the incorrect Set_ObjectScale copy; the only added one is the new setter.
  Every other external body's bytes/relocations and storage/COMDAT properties
  are equal. This does not claim the unrowed internal anchor is unchanged.
* CSV and unmatched-definition checks pass. Retail coverage is retained.
* `progress.py origin/master` measures authored C++ +14 bytes; the broader
  C++-exact total remains +0 because the alias already covered the address.

The fresh link index is dated 2026-11-07 13:23 at `9c81acd297`.
The refreshed ordinary preview reports both collect.cpp and MeshClassLifetime.cpp
LINKS: 148 -> 162 and 1,049 -> 1,049 authored bytes respectively, 1,197 -> 1,211
combined. This is current-object prediction, not a new census or real image.
The initial current-ledger attempt could not judge the whole local checkout's
compiler evidence; the successful ordinary preview refreshed stale providers
against the published index. Outgoing-consumer results accompany publication.
Only a future actual real link can confirm table retirement. LINK-619's six
alignment-only RenderObjClass providers remain independent prerequisites;
this change alone does not recover the full MeshClass table.

The retained private_probe.py reads the before-source from git history and
writes candidates only under build/, using tu_skeleton.Verifier. Its proposed
symbol map is private; all live ledger writes used add_match.py normally.
