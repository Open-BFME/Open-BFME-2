# Morph-init family vtables (0x00874F68..0x00874FD8)

Five bridged tables in `Code/GameEngine/Source/Common/RvaMorphInitFamily.cpp`
(`Rva005CDMorphBase` 0x00874F68, `Rva005CDSub84/A0/BC/D8` 0x00874F84,
0x00874FA0, 0x00874FBC, 0x00874FD8). Each retail table has 7 slots; the unit
compiles 1 (the `??_E` of a dtor-only view).

## Retail slots (target facts, from the real link at 1e864b34e0)

| slot | base 0x874F68 | subs |
|---|---|---|
| 0 | 0x0057569A (`??_GRva005CD3A5`, shared scalar deleting dtor of the Rva005CCDDD family, OpaqueScalarDeletingDtorsB13.cpp) | same |
| 1 | 0x005CD242 (`Rva005CD242::rva005CD242`, Rva005CD242.cpp; uses +0x1C) | same |
| 2 | 0x000B3FD0 (1-byte `ret`) | 84: 0x005CD284 (Rva002BF6A7Forward.cpp), A0: 0x005CD2D0 (Rva005CD2D0ResetGroundPlacement.cpp), BC: 0x005CD31C, D8: 0x005CD378 |
| 3..6 | 0x000B3FD0 | same |

## Why it is blocked

- The four subtables are installed by `?setupNN@Rva005CDMorph@@QAEPAV1@HHHHH@Z`
  (0x005CD257/2A3/2EF/34B), which are really `Rva005CDSubNN` constructors
  (base ctor 0x005CD1D3 in place, store +0x20, install the sub table). No
  `rename.py` route respells a method row as a constructor of another class,
  and without a constructor row the subs have no installer for
  `rename.py function --to-class` to prove slot 2.
- Slot 1 (0x005CD242) sits in all five tables; `--to-class Rva005CDMorphBase`
  refuses while the subs are views unrelated to the base, which the
  constructor respell would fix.
- Slots 2..6 (base) and 3..6 need 0xB3FD0 ICF twins (`add_match --icf-owner`)
  and slot 0 needs a `??_G` twin of 0x0057569A emitted by the unit.

Order if a constructor-respell route appears: re-derive the subs from
`Rva005CDMorphBase`, respell the four setup rows as their constructors, declare
slots 1..6 in the base (empty slots 2..6) and the slot-2 overrides, then move
the five placeholders with `--to-class` (placeholder identifiers, no vote) and
admit the folds.
