# Second-unit FX initializer copies 0x007B3E9E..0x007B3EC9 (banked, 2026-11-14)

Status: blocked on placement, not on bytes. The verified reconstruction is banked as commit `976ebb09157` on srv1
branch `swarm/waste/e158-20261114` (worktree `~/bfme2-ops/swarm/wt/waste-fx`). It is unpushed and must never
land as is.

## The defect it was meant to fix

FXParticleSystemModules.cpp binds the same object label twice:
- `_$E158`: object-symbol row at slot 0x007AF48B and bare row at 0x007B3EB4;
- `_$E160`: object-symbol row at 0x007AF496 and bare row at 0x007B3EBF.

`rename.py initializers` refuses the unit until this is resolved (tool lane 2 finding).

## Retail facts (measured on game.dat)

- 0x007B3EB4 (11 bytes) is `mov [0x00E02C48], 0x00E02C40; ret`, and 0x007B3EBF is `mov [0x00E02C4C], 0x00E02C44;
  ret`. They are byte-identical to the slotted 0x007AF48B/0x007AF496, the initializers of the reference members
  `ModuleTag<6, DefaultModuleKey<6>::VALUE, DefaultModuleName<6>::VALUE, DefaultModule<6>,
  DefaultModuleTemplate<6>, DefaultParticleModule<6>>::KEY` and `::NAME` (the data ledger's names for slots
  0x00A02C48/0x00A02C4C).
- Neither is in retail's .CRT$XCU table, and nothing in .text references either.
- Both sit in one contiguous block, 0x007B3E84..0x007B3EF3:
  - 0x007B3E84: pool init, no slot;
  - 0x007B3E9E / 0x007B3EA9: DefaultModuleKey<6> / DefaultModuleName<6> VALUE = GetValue(), no slot. Rowed in
    Rva007AC6DDGlobalInits.cpp as hand-written "second-unit" functions;
  - 0x007B3EB4 / 0x007B3EBF;
  - 0x007B3ECA: the only slotted entry (slot 910);
  - 0x007B3EDA: pool init, no slot.
- The first copies that keep slots are 0x007AF475/0x007AF480 (FXParticleSystemDefaults.cpp) and
  0x007AF48B/0x007AF496 (FXParticleSystemModules.cpp).

Hypothesis, not established: a second retail object instantiated the four template statics too, and its table
entries were discarded in favour of the first copies.

## The banked reconstruction (verified)

Rva007AC6DDGlobalInits.cpp instantiates the four template statics in retail's order:
- `DefaultModuleKey<6>::VALUE = GetValue()` and the same for `DefaultModuleName<6>`;
- `ModuleTag<6,...>::KEY = Key` and `::NAME = Name`.

The object's `_$E1/_$E3/_$E5/_$E7` have retail's 11-byte bodies and become the rows for the four addresses, and the
two bare rows leave FXParticleSystemModules.cpp. Verification: 257/257 matched, `link_check` 2 of 2, no new
code-identity findings.

Two findings shaped it:
- cl 7.1 initializes the KEY/NAME references at run time only after a dynamic initializer in the unit. Instantiated
  alone, they were bound statically and emitted nothing.
- A plain function cannot store into a reference's slot without naming that address twice.

## Why it is blocked (Sol review, FIX FIRST)

The parent-follow rule needs an identified parent object whose source owns the rows. The second retail object is
unknown, and adding the template statics to a placeholder grab-bag only shows what the reconstruction compiles to
(circular placement evidence).

Non-blocking points from the same review:
- the whole-block instantiation is honest as a verified reconstruction mechanism;
- path-order COMDAT selection, which keeps this unit's byte-identical copies when it links first, is not by itself a
  defect, but it stays disclosed.

## Next useful check

Identify the second object's real unit. Candidates are the retail TUs whose other rows bracket 0x007B3E84..0x007B3EF3
in the initializer strip, or whose .text order places a TU that instantiates FX DefaultModule<6> templates. Then
place the four rows there with the banked source. Until then the duplicate label claims remain, and coverage stays
as it is.
