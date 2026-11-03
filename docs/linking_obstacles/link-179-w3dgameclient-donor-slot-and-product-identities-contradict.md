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
