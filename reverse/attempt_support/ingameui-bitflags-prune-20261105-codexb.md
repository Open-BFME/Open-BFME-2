# InGameUI selector-emitter cleanup (2026-11-05)

Starting revision: `3070912f47ac8b7058e62d32602c6032ece78b72`.
`next_work.py --claim` selected the InGameUI consolidation scope. The previous
[guarded merge handoff](ingameui-donor-prune-20261104-codex5.md) identified the
host's differing `BitFlags<116>` constructor and selected `Drawable::isSelected`
copy as prerequisites. This change addresses those emitters; no donor or row
moves into another source file.

Removed the four unverified Zero Hour `selectAllUnitsByType` definitions
(plain, AcrossRegion, AcrossScreen and AcrossMap), their private
`KindOfSelectionData`/`kindOfUnitSelection` support and four corresponding
`present-unmatched` hatch entries. Neither the function ledger nor the pin
ledger names these four decorated methods. A baseline scan of all 24,959 other
cached objects found no occurrence of their decorated names. This establishes
unused donor definitions under these spellings; it does not establish the
identity or absence of corresponding retail selection behavior.

## Provider and code checks

The [object audit](ingameui-bitflags-prune-20261105-codexb.json) compares the
saved, byte-verified baseline object with the rebuilt host using
`link_census.object_symbols`, `object_references` and `comdat_bodies`. It scans
all 24,959 other cached `.obj` files for every removed external name, then
parses definitions and runtime references in the 614 candidate objects. Debug
references are excluded. All census objects touching removed names are present.

- Thirty external definitions disappear; none are added. No retained host code
  references a removed definition, and no removed sole provider has an outside
  runtime consumer.
- Every retained external COMDAT has the same normalized byte-and-relocation
  digest.
- The `BitFlags<116>` constructor remains provided by DumbProjectileBehavior,
  ThingTemplate, Player and ScoreKeeper; its outside runtime caller is
  ThingTemplate. The removed `Drawable::isSelected` copy has no runtime users;
  StealthUpdate keeps another provider.
- No aliases, pins, declarations, matched bodies or ledger rows change. Only
  the four removed markers' hatch entries are retired. No other register key
  is retired.

`./build.sh Code/GameEngine/Source/GameClient/InGameUI.cpp` passes before and
after: both code rows (55 bytes) and both data rows remain exact.
`find_declared_unmatched.py` passes after the edit with 37 unclaimed definitions,
down from 41, covered by the remaining existing markers.

## Link scope and next step

The fetched index is dated 2026-11-04 22:40 at `3a95b274a2`, carrying census
2026-11-04 20:47 at `f12552d0a7`. It predates the starting revision. The baseline
host preview has one blocking COMDAT: `BitFlags<116>::BitFlags()`.

`link_check.py Code/GameEngine/Source/GameClient/InGameUI.cpp` now reports
`LINKS`, predicted LINKED 0 -> 55 bytes, with no blocking names. Four remaining
differences are unreferenced diagnostics. The host's `Drawable::isSelected`
copy is absent, but donor-merge selection has not been retested.

These checks describe cached objects and a prediction against that index. No
new census, real-link result, ownership receipt or completed consolidation is
claimed. Carry the removed-provider scope into the next scheduled census and
confirm the host and previously linking consumers there. Before trying donor
merges, refresh the supported consolidation planner and use `tu_skeleton.py`'s
byte and link guards; the earlier flag/private-view rejections still need their
own evidence.
