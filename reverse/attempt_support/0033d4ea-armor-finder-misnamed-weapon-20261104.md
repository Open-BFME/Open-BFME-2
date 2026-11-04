# 0x0033D4EA: the "WeaponTemplateSet, BitFlags<17>" finder family is retail's armor finder

Code-identity key (`reverse/code_identity_baseline.tsv`, ThingTemplate.cpp):
`findBestInfo<WeaponTemplateSet,BitFlags<17>>` binds `findBestInfoSlow<WeaponTemplateSet,BitFlags<17>>`
at 0x0033BE70, but the kept copy is not retail's body. Not fixable inside ThingTemplate.cpp.

## Target facts (retail bytes)

- 0x0033DCB8: `push [esp+4]; lea eax,[ecx+0x370]; push eax; add ecx,0x37C; call 0x0033D4EA; ret 4`.
  Callers 0x001D90F9, 0x004BE1CC.
- 0x0033DCD1: same shape with +0x358/+0x364, calls 0x0033D46A (already rowed second as
  `ThingTemplate::findWeaponTemplateSet`).
- 0x0033D4EA (findBestInfo) calls _M_find 0x0033AF5F, slow path 0x0033BE70, operator[] 0x0033D19B;
  the map value is at node+0x14, so the key is 4 bytes.
- 0x0033BE70 (slow path, only caller 0x0033D50C) walks **0xC-byte** elements with the flags at **+0**
  and calls 0x0033ADC0 / 0x0028F55C (one-word SWAR counts).
- 0x0033D46A → slow path 0x0033BDF8 walks elements of stride `edi` with 16-byte flags at **+4**
  (counts 0x0033ADFC / 0x0033AE53, rowed as BitFlags<117>).

## Structural inference (not proof)

ZH's `ArmorTemplateSet` is {flags, ArmorTemplate*, DamageFX*} = 0xC bytes with the flags at +0, and ZH's
`WeaponTemplateSet` starts with a ThingTemplate* and has its flags at +4. So:
- +0x370/+0x37C are the armor sets and finder; 0x0033DCB8 is `ThingTemplate::findArmorTemplateSet`.
- +0x358/+0x364 are the weapon sets and finder. The ThingTemplate.h comments at +0x358/+0x370 have them swapped.
- Every row spelled `SparseMatchFinder<WeaponTemplateSet,BitFlags<17>>` / `map<BitFlags<17>,const WeaponTemplateSet*>`
  is the armor map's instance (13 rows, 9 files: 0x0033D4EA, 0x0033AD5C, 0x0033AF5F, 0x0033B7D0, 0x0033B81C,
  0x0033C0E1, 0x0033C176, 0x0033C471, 0x0033C646, 0x0033CBAD, 0x0033D19B, 0x00604396, 0x00604460).
- The comparator 0x0033AD5C tests 21 bits, so the armor flag count is probably 21. The
  `BitFlags<11>` spelling of 0x0033ADC0/0x0028F55C/0x0033BE70 may need the same correction.

Our compiled `findBestInfoSlow<WeaponTemplateSet,BitFlags<17>>` uses ZH's 0x54-byte WeaponTemplateSet
(stride 0x54, flags at +4), so it can never be 0x0033BE70.

## Next step

Retype the whole family as the armor finder in one batch (the ledger names, the sources and the pins in
reverse/symbols.csv), row 0x0033DCB8 as `ThingTemplate::findArmorTemplateSet`, and then settle the
bit count (11 vs 21) before spelling it. A single-row rename cannot work: the callee relocs of
0x0033D4EA name the rest of the family.
