### LINK-077: ArmyDetailsPanel icon family views drop the retail `Rva005F4179` slots
Status: Open / prerequisite identified. Updated: 2026-10-26; inspected revision:
`31e2c236a0` (index 2026-10-26 19:02 at `5ce093a71a`).
Evidence / affected units: `Code/GameEngine/Source/GameClient/LivingWorld/InGameUI/Rva005E39F3Ctor.cpp`
(6 matched rows, 345 bytes) and `ArmyHeroIconCtor.cpp` do not link. Their
vftables reference `DoUpdate`, `CreateMovieClip` and `rva005F4254` under three
incompatible views of the virtual base `Rva005F4179`. Retail vftable 0x00C79448
(`Rva005F4179`, read from the image) has eight slots: `??_G` 0x005F41B7,
`__purecall` twice (DoUpdate, CreateMovieClip), 0x001524CA (empty help returning
`TreeHintRef00217D4C`), 0x005F41AF (`mov ecx,[ecx+8]; jmp 0x005F40B0`), 0x000B3FD0
(empty), 0x005F3FF4 and 0x005F3F6B. The most-derived table 0x00C77C50 that
`Rva005E39F3` patches in holds vtordisp thunks rowed as free placeholder classes:
0x005E3A6E (`??_ERva005E3A76`), 0x005E3D84 (`Rva005E3D84`, which jumps to
`Rva005E3AA2Mid::fwd` 0x005E3AA2, the real `Rva005E39F3::DoUpdate`), and 0x005E5237,
0x005E4663 and 0x005E3ECB (`GapForwardersSeat8.cpp`, which jump to 0x005E51D3,
0x005E4389 and 0x005E3E41). `Rva005E3C90Ctor.cpp` links only because it declares
the slots pure.
Remaining / next check: a family rename across `Rva005F4179Dtor.cpp`,
`Rva005F422CDtor.cpp`, `GapForwardersSeat8.cpp`, `RvaVirtualFwdThunks.cpp`,
`Rva005E3E41Twins.cpp`, `Rva005E51D3Wrap.cpp` and `Rva005F40B0Attach.cpp`. Give
`Rva005F4179` its eight-slot declaration in one shared view, then name the thunk
targets as `Rva005E39F3`/`Rva005E3BD5` overrides so the compiler-emitted vtordisp
COMDATs replace the placeholder rows.
Clearance: not cleared.
Census confirmation: not applicable.

2026-11-08: the current Rva005E39F3Ctor.cpp preview now LINKS (289->289
authored bytes, index f4727bbd09); all six rows and two EH graphs are exact.
The served ??_8 no-retail-slots refusal is a separate tooling false reject:
native and compiled vbtable offsets are both (0,36). Neither this preview
nor the valid offset table clears the two actual eight-slot function tables.
See [the scoped evidence](../../reverse/attempt_support/army-icon-vbtable-selector-20261108/README.md).
