# Bridged table 0x008ED808 (`??_7Rva006FB9B0@@6B@` / `??_7Rva006FB960@@6B@`), 2026-11-14

Base `3e6d5a5449`. Read-only analysis; no source, ledger or queue change.

## Target facts

- One retail table, two tree names: `Rva006FB960` (constructor 0x006FB960 in Rva006FB960Cluster.cpp, AptValue type 4,
  int at +8) and `Rva006FB9B0` (destructor 0x006FB9B0 in Rva006DE350Derived.cpp, deleting destructor 0x006FB980 in
  Rva006FB9B0DeletingDtor.cpp; 12 bytes, freed through the pool at 0x00E176E8).
- Slots 0..14 (the queue's `retail_target_rva` values are decimal): 006DCAC0, 006DCB20, 006CBCD0, 0065CE90, 0073B660,
  0065CE90, 00180FD0, 0003FD80, 006C8770, 006CBCF0, 0069E440, 006CBD00, 0073B660, 0069E440, 006FB980.
- Against AptValue's table 0x00CEAED0 (Apt/AptValue.h) only slots 12, 13 and 14 differ: 12 is the byte-false body
  0x0073B660, 13 the one-byte return 0x0069E440, 14 the deleting destructor. Slots 2 and 9 are AptValue's own
  (unlike AptBoolean, which overrides both).
- `??1AptValue@@MAE@XZ` is rowed at 0x006DE350, the address the 11-byte destructor jumps to.

## What the source needs

One class in one shared header, derived from `AptValue`, declaring `IsGarbageCollected() const`,
`RegisterReferences() const` and the destructor, used by all three units in place of the two opaque views and the
`Rva006DE350` base view. Sibling table 0x008ED844 (`Rva006FB9C0` / `Rva006FBA10`, type 8) has the same split.

## Why this stopped

- The two overrides need bodies in the tree. Retail folded them into 0x0073B660 and 0x0069E440, so they can only be
  rowed as ICF twins with `fold-proof=`. This seat is instructed not to add a second body at an address that has one.
- tu_map.csv gives 0x006FB960, 0x006FB980 and 0x006FB9B0 no approved unit, so the three views cannot be merged; a
  shared header is the only route and both names must be reconciled first (class identity unproven: type 4, int payload).
- halilkkaya-au holds live header_adopt_lane claims on Apt units (Rva006DBB40/Rva006DBB60 members of AptValue).

Not measured: whether the 11-byte destructor and the 35-byte deleting destructor still match when the class derives
from `AptValue` instead of `Rva006DE350`.
