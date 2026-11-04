### LINK-179: W3DGameClient donor slot and product identities contradict native tables

Status: Open; compiler debt retired only. Updated: 2026-11-03, inspected859c899741.

W3DGameClient.cpp keeps five exact rows/337B but its current object has U10 and
the display factory wrong-selected. The native device table7C4738 slot37 points
to already covered4C45D (2B0/ctor49DEA), while its claimed8FCAE factory is slot14
of independent Rva008FCA3 table7C7C90 and constructs Rva00104DB0 (D8/104EBF,
six-slot table7CF800). The existing W3DDisplay ctor pin104EBF is also false; no
row/pin was changed in this pass. The matched Ray148B instead calls existing
real ThingFactory2CF21B; its fake derived receiver persists because the old TU
imports the two-argument donor header. Two canonical-header context trials fail
before code generation, last at duplicate placement array operators and missing
CommandButton context. Nine other unresolved names come from retained unrowed
methods/header factories and their legacy table, not missing matched bodies.

Completed scope: remove the artificial VCI anchor and two optimization pragmas.
Private5/5/EH EXACT and all57 external providers/properties/routes identical;
normal main5/5 passes and owning counter1770->1768. No linking/coverage gain.
Next: coherent actual native GameClient/Subsystem/ThingFactory and allocation
context, then prove paired factory identity readmission and all consumers/TU
ownership; do not suppress the existing methods/table or invent a product name.
[Native witnesses, compile boundaries and complete provider proof](../../reverse/attempt_support/w3d-gameclient-native-boundaries-20261103/README.md).

Clear publication d5d6071842 is carried forward: scoped LINKS0->938, but batch
audit INCONCLUSIVE at index984a4cdc4d/base0d342789bae3f284ec939609c6f004e1a78d09da
because Clear lacked a current object receipt. Next scheduled census must cover
Clear and affected consumers; no whole-current-image/runtime closure is claimed.

**Carved row arrived with an unverified link audit (2026-11-03, landed `43744991a7`):**
`tu_skeleton --split` moved row `0x0004C6C6` (`Rva0004C6C6::setFrameRate`) out of
`Code/GameEngine/Source/Common/VtableSlotBodiesR3F.cpp` into this TU. Bytes are exact
either side of the move: `./build.sh` over both files reports 27/27 matched with float
and string receipts OK, and `find_declared_unmatched.py` is clean on each. The push
hook's `link_batch_audit` was **INCONCLUSIVE**, not clean: index `8661f15284`, outgoing
base `e92c82cbb24`, "1 source object(s) lack current receipts; first:
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DGameClient.cpp", and it printed
"linking UNVERIFIED; audit evidence incomplete". So this TU's link state after the
carve is unmeasured, which the entry's existing INCONCLUSIVE note above already said
for its Clear receipt. Carry this object and its consumers into the next scheduled
census together with that one. The tooling audit over the whole outgoing range found no
added, deleted or renamed path, so no consumer repointing was required beyond the
repoints the split tool applied to `functions.csv`, `tu_map.csv` and the doxygen input
list. No linking, debt or census gain is claimed.

2026-11-04: canonical factory adoption now reaches object generation; five rows stay exact, but refuted display factory8FCAE allocates DC instead of D8 with the canonical base. Reverted; paired display identity/TU correction is the next prerequisite. [Trial and restored checks](../../reverse/attempt_support/w3d-gameclient-factory-adoption-20261104/README.md).

2026-11-04 (later): resolved pending census. 0x0008FCAE is respelled `Rva008FCA3::rva0008FCAE` (`new Rva00104DB0`), the anchor stops emitting ZH's createGameDisplay, the banked canonical ThingFactory patch applies, and pins 104EBF/BFMEThingFactory go. 6/6 exact; the preview has no unresolved or wrong-selected names, only the index-stale setFrameRate duplicate. Next census must cover this unit and VtableSlotBodiesR3F.cpp. [Evidence](../../reverse/attempt_support/w3d-gameclient-display-reidentify-20261104/README.md).
