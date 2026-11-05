# AIInternalMoveToState serializer header adoption

Inspected revision: `aa2dcfa7c1` (2026-11-05).

Four serializers now include the existing canonical
`GameLogic/AIInternalMoveToState.h` instead of private movement-state views:

| Source under Code/GameEngine/Source/Common | Retail RVA | Verified bytes |
| --- | --- | ---: |
| Rva0033FF2BXfer.cpp | 0x0033FF76 | 180 |
| Rva00340D70Xfer.cpp | 0x00340D70 | 201 |
| Rva00340E97Xfer.cpp | 0x00340E97 | 142 |
| Rva00342B87Xfer.cpp | 0x00340C2D | 50 |

The base serializer and Rva00342B87 serializer use the existing `asBase`
adapter for the canonical coordinate members. Rva00340D70 now starts its own
fields directly at +0x4C after the complete canonical base. Rva00340E97 uses
the inherited +0x4A flag and retains padding +0x4C..+0x4F before its +0x50
field. These changes preserve the offsets already established by the rowed
serializers; they do not establish new class identities for the derived types.

Verification:

- Normal `./build.sh` passed each original and changed source, all four rows
  (573 bytes), including string, float and import checks.
- `find_declared_unmatched.py` passed before and after the changes.
- `header_adopt_lane.py accept --class AIInternalMoveToState` over all four
  changed sources passed every member and retired four queue rows. This
  includes the lane's byte verification and combined current-object link check.
- `header_adopt_lane.py accept --class State` also passed Rva00342B87Xfer.cpp
  after its direct canonical base include was added, retiring its State queue
  row. Total header debt retired: five rows. The final four-source movement-state
  acceptance passed again after that include change.
- Parsed original and changed COFF external definitions through
  `exit_link.coff_view` / `external_definitions`: no removed definitions in
  any of the four units. The two coordinate-adapter users additionally emit
  the existing `asBase(Coord3D&)` inline; the other two definition sets are
  unchanged. The existing link-wide xfer alternatename remains in place.
- The base serializer's explicit link preview also passes, preserving
  180/180 linked bytes against census f44cbcf5b0 (2026-11-05 15:19).

LINK-513's missing virtual providers and its two blocked vtable-emitting
consumers remain outside this repair. No real-image or runtime result is claimed.
