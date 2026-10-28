# MultiplayerSettings native layout prerequisite

Inspected BFME 2 `d5843cec79b763d84b6afa75f8e9effc47574796` (upstream
`51853dba25e3a42b79adfd545c5f53bb8978f49f`), BFME 1 pin
`0424131c818fba6641613ef826222ecf30845025`. Retail game.dat SHA-256:
`f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640`.
This is a prerequisite for the LINK-009 lifetime repair and TU composition,
with the LINK-042 pair-copy provider retained. No lifetime rows move here.

## Target evidence

The constructor at RVA `0x003811D8` constructs a twelve-byte base, a map at
`+0x34`, and colors at `+0x44` and `+0x84`. Allocation at `0x001EF37B` requests
`0xC4` bytes. The map occupies twelve bytes; its count is at `+0x38`, followed
by the lazy color count at `+0x40`. Each complete color occupies `0x40` bytes.
The existing fourteen-slot subsystem view reproduces the target base contract;
no shared header is changed. The implicit virtual lifetime is not emitted by
this prerequisite, and its later verification remains separate.

The constructor zeros `+0x0C` and `+0x14`, stores 10000 at `+0x10`, and sets
the five credits at `+0x20..+0x30` to 500/1000/1500/2000/2500. The native
FieldParse table names **`+0x14`**, not `+0x10`, as StartCountdownTimer.
The meanings of `+0x0C` and `+0x10` remain unresolved; their members use offsets.

Each FieldParse record is four words: token pointer, callback pointer, zero
userdata, member offset. The actual arrays, including their zero terminators:

| Array | Records before terminator | Bytes |
|---|---|---|
| Color, RVA `0x00818F40` | TooltipName +00; RGBColor +04; RGBNightColor +14; LivingWorldColor +24; LivingWorldBannerColor +30; AvailableInWotR +3C | 112 |
| Settings, RVA `0x00818FB0` | InitialCreditsVeryLow/Low/Medium/High/VeryHigh +20/+24/+28/+2C/+30; StartCountdownTimer +14; MaxBeaconsPerPlayer +18; UseShroud/ShowRandomPlayerTemplate/ShowRandomStartPos/ShowRandomColor +1C/+1D/+1E/+1F | 192 |

Callback RVAs are parseAsciiString `0x0002F11E`, parseRGBColor `0x0002F259`,
parseInt `0x0002EF56`, and parseBool `0x0002E850`. Terminators start at
`0x00818FA0` and `0x00819060`. The data inventory's 520-byte settings span
includes following token storage and is not the array's sizeof. No inventory
extent, data-row admission or new owned-byte coverage is claimed.

## Implementation

The seed uses canonical RGBColor and the existing full subsystem view instead
of PreRTS's donor declarations. It keeps the exact compiler directive, four
existing optimize pragmas, singleton, table symbols and out-of-line color-copy
declaration. The two existing function bodies remain unchanged. The local INI
view declares static callbacks only, imposing no instance layout; FieldParse
uses the proven four-word representation. Neither is a registered canonical
class. Zero Hour's trailing Money/vector members are absent from the target.
Donor provenance is a source lead, not evidence for BFME 2 offsets or fields.

## Verification

The normal scoped build verifies getColor (`0x00381373`, 68 bytes), pair copy
(`0x00380DA3`, 29 bytes), and the existing singleton data row. Declaration,
class and data checks pass; there are no applicable EH rows in this seed yet.
An independent reviewer reconstructed COFF relocations and compared both full
arrays with retail: exact 112/192-byte payloads, all 34 DIR32 locations,
callback identities, complete pointed token strings, offsets and terminators.
The pair still calls the out-of-line color copy at `0x00380D30`.

Ordinary previews before and after both report LINKS, 97 bytes, against
published index `d92e7e6635` (2026-10-28 15:58). This is preservation of this
unit's prediction, not a census gain.

Removing PreRTS changes 552 COMDATs to 22: 538 removed, eight native strings
added, fourteen retained. All 538 removed contributions are 1,261 bytes of data,
with zero relocations and no code. Every one was already selected from
FiringTrackerXfer.obj (index position 56; seed position 11309), and its digest
matches that indexed copy. Independent inspection of the current local
FiringTrackerXfer object confirms all 538 digests remain present. No checked
selected binding changes. The undefined set remains the same seven names;
strong definitions remain the singleton and two tables.

Thirteen retained COMDATs are unchanged. The vector-constructor iterator changes
from 50 to 34 bytes and independently matches retail RVA `0x00001423`; removing
PreRTS allows the pre-existing optimization anchor to take effect. Its selected
provider remains atl_vector_constructor_iterator.obj at index position 14,
whose current object has the same native digest. No new outside COMDAT loser,
wrong-selected name or variant was found in the paired seed overlay.

## Remaining

The provider checks use current inspected objects over the published index;
they are not a fresh census or every consumer's compile receipt. The normal
outgoing batch audit remains required. Reconcile the lifetime donor against
this seed and use the supported merger with a fresh approved map. Upstream
`13850b92b` also moved cleanup `0x0077F308` out of its generated owner: preserve
all seven lifetime rows, including `0x0077F308`, `0x0077F310` and `0x0077F31B`,
with their actual parent EH placement. This prerequisite changes none of them.
Align the older candidate's two field names to unknown
`+0x10` / countdown `+0x14`. Keep the existing header debt until its owning
adoption lane accepts it. No new pin, alias, hatch, TU approval or runtime
closure is introduced by this prerequisite.
