# Rva003AEEB3 header-adoption boundary (2026-11-04)

Scope: the three queued units selected by `next_work.py --tier header --claim`.
No source or header-queue change remains applied.

`header_adopt_lane.py adopt --apply` rejected all three:

- `Rva005E2C70Destructor_Rva003abc21.cpp`: the private base has a 28-byte
  `m_storage` at +4, incompatible with the canonical base's recovered fields.
- `ModuleCtorChainsA_Rva003ABAF3_Rva003ABB93.cpp`: the private base has a
  24-byte opaque field at +4, likewise not a canonical field. Do not erase
  that layout warning without reconciling the view and its virtual slots.
- `Rva003A5817Dtor.cpp`: the canonical include fails the existing 39-byte row.

One additional source trial replaced the private novtable declaration and
manual secondary-vptr writes with the canonical include and an empty native
destructor. `./build.sh` failed its sole row: retail starts `8b c1 f7 d8`
and performs two null-guarded secondary stores; the trial starts `c7 01` and
emits automatic stores at +0, +0x14 and +0x18. This is a code-generation
boundary, not evidence that the recovered canonical layout is wrong.

The original destructor was restored immediately; frozen-source inventory
again reports all defined functions matched. No debt was retired and no link
gain is claimed. Next work needs a byte-preserving native destruction strategy
compatible with the canonical header, rather than repeating a mechanical swap.
The other units need their own layout/slot reconciliation first. Existing
LINK-157 concerns explicit table consumers and remains unchanged by these trials.
