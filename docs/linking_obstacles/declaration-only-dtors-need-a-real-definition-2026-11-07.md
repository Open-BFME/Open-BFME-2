# Declaration-only destructors need a real definition at link

2026-11-07, claude-opus-5-5. Scope: deleting destructors whose class model is
address-derived (`??_GRva...`).

## Obstacle

A code-identity fix that makes a private destructor declaration-only binds the
deleting destructor's call to a name that only a `reverse/symbols.csv` pin
carries. `tools/build.py` resolves pins, so the byte gate passes; the real link
does not, and lists the name as defined nowhere. The real link at
`bbb1979380` listed 13 such names from four units (Rva00170C0Siblings.cpp 8,
Rva006CBF40Siblings.cpp 3, Rva006F84C0DeletingDtor.cpp 1, AptValue.cpp 1).

## Repairs

- Rva006CBF40Siblings.cpp (2b8b6a811f): retail folds the three empty pool-record
  destructors at 0x00709B80, which tail-jumps to Rva006D6470Owner's 0x006D6470.
  Bodies restored over that base and rowed as ICF folds of `??1Rva00709B80`;
  link_check: LINKED 175 -> 186 bytes, no hatch.
- The other three units (e44d9b48eb): bodies restored so each name is defined;
  their ten code-identity findings are open again (shadow).

## Remaining prerequisites

Bind each deleting destructor to the retail owner's real defined row:
VectorClass destructors at 0x00120FB0/0x00155330/0x00156750, the dtor at
0x00141C30 (`??1Rva00140C00`), and bodies whose owners are not destructors
(0x0066C730 reset, 0x006C5930 apply, 0x00625800, 0x0073A900), plus
0x006F8460 and 0x006DE350. Never bind to a pin-only name.
