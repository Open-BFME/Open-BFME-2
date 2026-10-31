# ThingTemplate stale exemptions and current link boundary

Base: `e78b61f1b2d2`. The default picker claimed the whole unit and served
`pair<AsciiString, AudioEventRTS>::~pair` at `0x002A12E1`, 53 bytes. This is
an existing matched body, not a new or lost native range. All 23 unit rows
verify before editing. Current preview at `4a490aa2e4` (2026-10-31 22:25)
still reports ten unresolved names, four losing COMDATs and two wrongly
selected providers. The unit's current authored-byte preview is 882 bytes;
the picker's 945-byte historical credit is not a measured gain.

## Retired exemptions

`ModuleInfo::getNuggetWithTag` already owns a verified 43-byte row at
`0x0033C21C` in this file under its exact compiled name. Its unmatched marker
is stale. `ThingTemplate::initForLTA`'s marker is inside the existing
`#if defined(LOAD_TEST_ASSETS) && 0` donor-reference block; the block cannot
emit a definition under any flag set, so it needs no compile exemption.
Remove only these two comment lines. No inactive donor body or instruction
body is altered, and no claim of a new retail implementation is made.

The owning `tools/hatch_counters.py --update` removes exactly these two keys
from `reverse/hatch_baseline.tsv`, reducing `present_unmatched` 3587 -> 3585.
No other register entry changes. There is no row, pin, alias, class, header,
compiler option, global or source-path change.

## Verification

Normal and strict checks pass 23/23 rows; frozen-file checks pass. The complete
external object facts are identical before and after: all 1,091 COMDAT
byte/relocation digests, 29 strong definitions, 88 undefined symbols and zero
weak aliases. All 48 scoped code/data bindings are identical. All five EH
graphs are EXACT. `comparison.json` records the common facts/bindings digest;
the build, strict, EH and counter receipts accompany it. Marker retirement
adds no C++ bytes and does not clear the unit's link prerequisites.

## Remaining link work

The ten unresolved names are AudioEventRTS default/copy construction,
destruction and setEventName; Player production-cost lookup; INI byte-index
and dynamic-audio parsing, scanIndexList and scanInt; and the BitFlags<11>
name list. Losing copies are the served pair destructor, BitFlags<11>'s
constructor, the FX map's insert_unique and the weapon findBestInfoSlow.
The last two are also wrongly selected. The existing identity-register keys
remain; none is retired by this comment-only change.

The imported-source audit and AudioEvent destruction/assignment handoff in
`docs/linking_obstacles.md` already distinguish the misleading historical
AudioEvent name from the native list cleanup at `0x004EC395`. The native
53-byte pair range is also covered by an existing neutral typed-pair fold.
These existing facts are prerequisites, not grounds to add another pin,
reinterpret a different container or rename the real 0x88-byte audio class
from a same-name/byte-match hit. No body/codegen trial or shared-class rewrite
is attempted in this pass. LINK-146's earlier vtable repair remains separate.

The outgoing audit is INCONCLUSIVE: its index predates the exact outgoing
base and affected `Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry the scope into the next scheduled census; broader consumer
selection/loss clearance and full-unit linking remain unverified. No direct
census, nightly or smoke runner was started. No paths move, so no active
path consumer needs repointing.
