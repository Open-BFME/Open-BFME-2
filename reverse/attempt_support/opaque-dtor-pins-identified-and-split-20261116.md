# The ten names OpaqueScalarDeletingDtors.cpp cannot resolve: all identified, and they need two different repairs

`next_work.py --claim` serves `??_GRva00119D00@@UAEPAXI@Z` @ 0x00043057 as a
link-cycle repair worth 1,924 bytes: "the real link stops here: 8 name(s) it
references exist nowhere". Two earlier verdicts stand on this address, both
recording that the referenced destructors "exist as pins only" and that the
identities are unproven. **Both halves of that are now settled.** There are ten
such names, every one is identified, and they do not share a repair.

## Why a pin is never enough

`??1Rva0090840@@UAE@XZ` and its nine siblings are in `reverse/symbols.csv` and
in no `reverse/functions.csv` row. A pin records that an address carries a name;
it puts no definition in any object, so a real link cannot resolve one. Measure
it this way and the ten fall straight out:

    ./build.sh Code/GameEngine/Source/Common/OpaqueScalarDeletingDtors.cpp
    # 87 undefined externals in the object; subtract every name that has a
    # functions.csv row (a real definition) and keep the ones whose only
    # provider is a symbols.csv pin

Beware that `reverse/symbols.csv` writes these addresses with seven hex digits
(`0x0090840`) where `reverse/functions.csv` uses eight (`0x00090840`). Compare
them as integers; a string compare silently finds nothing and makes every pin
look unbacked.

## Every one of the ten has a real, matched body at its own pinned address

| the name the unit references | pinned rva | the rowed body actually there | size |
| --- | --- | --- | ---: |
| `??1Rva00119D00@@UAE@XZ` | 0x00119D00 | `??1Render2DClass@@QAE@XZ` | 101 |
| `??1Rva005333F@@UAE@XZ` | 0x0005333F | `?rva0005333F@Rva0005333FHolder@@QAEXXZ` | 19 |
| `??1Rva0084CEF@@UAE@XZ` | 0x00084CEF | `??1Rva00084CEF@@QAE@XZ` | 18 |
| `??1Rva0089851@@UAE@XZ` | 0x00089851 | `??1RunwayInfo@FlightDeckBehavior@@QAE@XZ` | 67 |
| `??1Rva00B6CF1@@UAE@XZ` | 0x000B6CF1 | `??1BfmeStringRecord000B94D2@@QAE@XZ` | 53 |
| `??1Rva0090771@@UAE@XZ` | 0x00090771 | `??1Rva000906DE@@UAE@XZ` | 7 |
| `??1Rva0090840@@UAE@XZ` | 0x00090840 | `??1Rva007E3C20Vp6Stream@@UAE@XZ` | 182 |
| `??1Rva009D6FA@@UAE@XZ` | 0x0009D6FA | `??1Rva0009D55BProduct@@UAE@XZ` | 360 |
| `??1Rva0049B47C@@UAE@XZ` | 0x0049B47C | 89 rows fold here (7B fold point) | 7 |
| `??1ObjectModule@@UAE@XZ` | 0x0049B47C | the same fold point | 7 |

Nothing here is a guess: each is the set of `functions.csv` rows at exactly the
pinned address.

## The split: five of them can never be defined at all

The pins are all spelled `UAE` -- public **virtual**. Group the table by whether
any virtual destructor is rowed at that address and it breaks 3/5:

**Consistent (3).** `Rva0090771`, `Rva0090840` and `Rva009D6FA` each sit on a
rowed `@@UAE` destructor. The placeholder and the real name describe the same
function with the same ABI, so carrying the identified class resolves these --
a rename of a matched row, which belongs to the naming lane under
`docs/naming.md`, not to a repair seat.

**Contradictory (5).** `Rva00119D00`, `Rva005333F`, `Rva0084CEF`, `Rva0089851`
and `Rva00B6CF1` sit on a `@@QAE` body -- public **non-virtual** -- and on
nothing else. No definition of a *virtual* destructor will ever appear at a
non-virtual destructor's address, so no rename and no alias admission can
resolve these five. The unit's own model is what has to change.

`Rva00119D00` is the one with independent proof, and it is worth quoting because
it settles the direction. `Code/Libraries/Source/WWVegas/WW3D2/Render2DClass.h`
opens with target facts: "Render2DClass has no bases, virtual functions or vptr
... Destructor 0x00119D00 releases +0x40 ... neither body stores a table. These
are member cleanups, not base destructors." The canonical header and the
destructor TU both declare `~Render2DClass()` non-virtual, and the ledger rows
it `??1Render2DClass@@QAE@XZ`. Against that, `OpaqueScalarDeletingDtors.cpp`
declares `class Rva00119D00 { virtual ~Rva00119D00(); }`, purely so the TU emits
a scalar deleting destructor. The `virtual` is the reconstruction's own, not
retail's, and the undefined name is its direct consequence.

That leaves a real open question for whoever takes the five: retail **does**
have a 28-byte `??_G` at 0x00043057, and MSVC emits `??_G` only for a class with
a virtual destructor. So either that `??_G` belongs to some other class whose
complete destructor ICF-folded onto Render2DClass's 101-byte body, or the 28-byte
body itself is a fold point shared with other `??_G`s. It is rowed in this unit
as the sole provider, so nothing in the tree currently answers which. Settling
that is the repair; asserting either way without it is not.

## The unit cannot simply drop them

The first instinct -- delete the redundant placeholder classes -- does not
survive checking. Of the unit's 73 rows, **65 addresses are provided only by this
unit**, and for the three that are not, this unit is the *canonical* side of the
fold rather than the spare copy:

- 0x00091153, 0x0009D9A1 and 0x000728C6 each have a sibling row elsewhere whose
  own notes read "rowed as `??_GRva0090840@@UAEPAXI@Z`" (and likewise for the
  other two) -- the siblings are ICF aliases pointing *at* this unit's name.
- 0x004A10FD carries about 38 rows, two of which name this unit directly in
  `fold-proof=Code/GameEngine/Source/Common/OpaqueScalarDeletingDtors.cpp`.

Removing this unit's rows would orphan those references. `tools/class_views.py
--unused --files <this unit>` likewise reports nothing prunable.

## What is not in the ten

Four more of the object's undefined externals are in neither ledger and are a
separate matter: `??_GRva0049B47C@@UAEPAXI@Z`, `?f1@MiBase1@@UAEXXZ`,
`?f1@Rva00494A97_S1@@UAEXXZ` and `?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A`
(the last is data, not code).

## Why this is a handoff

The three consistent names are a rename, which is the naming lane's. The five
contradictory ones need the `??_G`-at-0x00043057 question answered before any
edit, and that answer changes the unit's class model rather than a ledger row.
Neither is a repair seat's call, which is what both earlier verdicts said; what
is new here is that the identities are no longer unproven and the ten are no
longer one problem.

## Reproducing

    python3 tools/next_work.py --claim        # draws the item

    # the ten: undefined externals of the unit's object (secnum 0, class 2,
    # value 0) that have no functions.csv row but do have a symbols.csv pin
    # the split: for each pinned address, whether any functions.csv row there
    # is spelled @@UAE or @@MAE
