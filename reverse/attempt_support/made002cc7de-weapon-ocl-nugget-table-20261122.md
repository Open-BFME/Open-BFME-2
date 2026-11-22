# Made002CC7DE (WeaponOCLNugget) table 0x00864588: bridged, needs class registration

Inspected on 2026-11-22 after `next_work.py --claim` served the vtable bridge
`??_7Made002CC7DE@@6B@` (0x00864588) in `Code/GameEngine/Source/Common/Made002CC7DE.cpp`.
Landed so far: that unit now includes the canonical `Rva00507823.h` base instead of a
private two-virtual copy, so it emits a 14-slot table (still mismatching slots 1, 2, 5-9).

## Target facts

- Retail table 0x00864588 (14 slots): 0x005096AB (??_G), 0x00508925, 0x00507943,
  0x0050B238, 0x0050B238, 0x0050962B, 0x0050965A, 0x0047A699, 0x005095FB, 0x0050959C,
  0x000D43D0, 0x000D43D0, 0x0047A699, 0x0047A699. Slots 3, 4 and 10-13 equal the base
  table 0x00864010 and need no override.
- Shared bodies (ICF folds, as `75496d76651` did for Made002CCBCA): 0x00508925 is in
  four tables (0x00864370, 0x00864404, 0x00864588, 0x00864C94) and is `push; push; call
  0x005075D6; test al,al; setne al; ret 8`; 0x00507943 is in twelve; 0x0047A699 is `false`.
  Inline overrides `rva005075D6`, `vslot02` and `vslot07` reproduce them.
- Unique bodies (only 0x00864588 references them): 0x0050962B and 0x0050965A
  (`Rva0050962B::rva0050962B/rva0050965A` in `Common/VslotSmallBodiesY.cpp`), 0x0050959C
  (`Rva0050959C::rva0050959C` in `Common/VslotSmallBodiesL.cpp`) and 0x005095FB
  (`?rva005095FB@Made002CC7DE@@UAEXXZ` in `GameLogic/Object/Made002CC7DEResolve.cpp`,
  declared as a new virtual, i.e. slot 14, instead of overriding slot 8 `rva00507877`).

## Why blocked

`rename.py function --rva 0x0050962B --to-class Made002CC7DE --new vslot05 --also
0x0050965A=vslot06 --also 0x0050959C=vslot09 --also 0x005095FB=rva00507877` with
prepared sources refuses: "Made002CC7DE has no canonical header in
reverse/canonical_classes.csv: the name of retail table 0x00C64588 slot 5 is voted on the
registered class". Registration needs `class_contract.py --class Made002CC7DE` to decide,
and it queues:

- `inherited@0x104`/`@0x108`: `GameLogic/Object/WeaponNuggetParse.cpp` views all ten
  nugget classes over a private `WeaponNuggetHead` (`WeaponTemplate *m_owner` at +0x104;
  the parse entries store the weapon there), while the canonical `Rva00507823.h` has
  `int m_field104`. Adopting the canonical base there makes every `new <Nugget>` view
  abstract (pure slots 5-7), so each nugget view needs its retail override set first;
  the canonical field should probably become the `WeaponTemplate *` owner (contract edit).
- `slot14`: the Resolve unit's new virtual `rva005095FB` (fixed by the respell above).

## Suggested order

1. Retype `Rva00507823::m_field104` as the weapon-owner pointer in its contract and header
   (the parse entries are the evidence) and adopt the header in `WeaponNuggetParse.cpp`,
   giving each nugget view its retail slot 5-7 declarations from its own table.
2. `class_contract.py --class Made002CC7DE --write`, choose an official header path (no
   BFME 1/ZH donor defines it) and register it through `header_adopt_lane.py run`.
3. Re-run the `--to-class` move above; prepared sources that compiled are reproducible
   from this note (Y/L bodies take `const void *` and cast; slot 9 passes `(void *)a`).
4. Add the slot 1/2/7 inline overrides in `Made002CC7DE.cpp` and admit them with
   `add_match --icf-owner` (fold-proofs: `VslotSmallBodiesAD_Rva00349D02.cpp`,
   `Made002CC5E1Rva00507991.cpp`, `System/Xfer.cpp`).

## Sibling: `??_7Made002CC774@@6B@` (0x00864520, DamageFieldNugget)

Same blocker, same contract QUEUE lines (`bases`, `inherited@0x104/0x108`) from
`WeaponNuggetParse.cpp`. `Made002CC774.cpp` already adopts the canonical base (b695d80).
These are target facts from the retail table 0x864520:
- slot 1: 0x005092D4. Rowed as placeholder `?rva005092D4@Rva005092D4@@QAE_NPBXPAVObject@@@Z`
  in `VslotSmallBodiesAD.cpp`.
- slot 2: 0x00507943. ICF; rowed as `DamageNugget` and `Made002CCBCA` overrides.
- slots 3-4: 0x0050B238. Same as the base.
- slot 5: 0x00509307. Rowed as `BfmeAimAAE::bfmeFireAAE`, `BfmeConv2116.cpp`.
- slot 6: 0x005093C6. This is the unit's own `Made002CC774::rva005093C6`, which is
  non-virtual in source.
- slots 7, 12, 13: 0x0047A699, the Xfer ICF.
- slot 8: 0x005092B2. Rowed as `Rva005092B2Resolve.cpp`.
- slot 9: 0x00509367. Rowed in `VslotSmallBodiesL.cpp`.
- slots 10-11: 0x000D43D0.

After step 1 above, register `Made002CC774`. Then move slots 1, 5, 8 and 9 with
`--to-class`, make slot 6 virtual, and add the ICF slot 2/7 inline overrides.
