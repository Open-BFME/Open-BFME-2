# W3DGameClient: re-identify 0x0008FCAE, then adopt canonical ThingFactory

2026-11-04, base `65e0863673`. Follows
[native boundaries](../w3d-gameclient-native-boundaries-20261103/README.md) and
[factory adoption trial](../w3d-gameclient-factory-adoption-20261104/README.md).

Target facts (retail disassembly, `tools/retail_body.py`): 0x0008FCAE and the
device factory 0x0004C45D have the same shape, EH prolog, `push size`,
`call 0x0042FDA0`, null test, ctor call. 0x0008FCAE pushes 0xD8 and calls
0x00104EBF. 0x0004C45D pushes 0x2B0 and calls 0x00049DEA (`??0W3DDisplay`).
Neither reads `this`. The prior audit places 0x0008FCAE at slot 14 of table
0x00BC7C90 (Rva008FCA3), not in the device table.

Change:
- The row is respelled `?rva0008FCAE@Rva008FCA3@@QAEPAXXZ` (address-derived;
  owner not recovered) with body `return new Rva00104DB0;`. The ctor resolves
  to the existing row `??0Rva00104DB0@@QAE@XZ` at 0x00104EBF.
- The anchor no longer emits ZH's inline `W3DGameClient::createGameDisplay`.
  Its only referrer was `??_7W3DGameClient@@6BSubsystemInterface@@@`, and the
  census index shows only this unit's pre-073e438f61 object emitting that.
- The [candidate patch](../w3d-gameclient-factory-adoption-20261104/candidate.patch)
  applies unchanged. createRayEffectByTemplate now calls canonical
  `ThingFactory::newDrawable` (row 0x002CF21B).
- Two pins go, with their hatch lines: `??0W3DDisplay@@QAE@XZ=0x00104EBF`, a
  second address for the real ctor row at 0x00049DEA, and
  `?newDrawable@BFMEThingFactory@...=0x002CF21B`, which nothing references now.
  Pin total 9341 -> 9339.

Verification: [build](build.log) 6/6 exact, string/float/import OK;
find_declared_unmatched clean; check_csv OK; pin_consistency OK.
[Link preview](link-check.log) against index 8661f15284: no unresolved names
and no wrong-selected rows. Only `?setFrameRate@Rva0004C6C6@@QAEXM@Z`
remains as a duplicate. That is index-relative: the census object of
VtableSlotBodiesR3F.cpp predates the 0x0004C6C6 split (999c019595), and the
current source keeps only a comment there. No census or real-link gain is
claimed until the next census covers this unit and VtableSlotBodiesR3F.cpp.

Inference only, not applied: Rva008FCA3 (0x40 bytes, made by game-client
factory 0x0004C4C7, beside W3DGameWindowManager gadget rows) may be
W3DGameWindowManager, which would make 0x0008FCAE allocateNewWindow and
Rva00104DB0 (0xD8, Render2DSentence member) W3DGameWindow. Naming lane only.
