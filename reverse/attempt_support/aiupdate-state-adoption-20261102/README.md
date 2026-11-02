# Native AIUpdate cluster: canonical StateMachine adoption, 2026-11-02

The existing three-row `AIUpdate/Rva002645FF.cpp` cluster now includes the
canonical AIUpdate and StateMachine interfaces instead of defining fake
Slot110, Slot8 and StateMachine classes. All three existing function identities
and native bodies remain. The private object has exactly three external code
definitions, with no additional named AIUpdate provider. The owning
`header_adopt_lane.py accept --class StateMachine` passes and retires its one
header-queue entry, including the previously linking unit's preservation guard.
Normal commit verification remains mandatory.

Target facts: the 87-byte body at2645FF calls the referenced AI object's virtual
slot110 and then the current State's virtual slot8. Canonical APIs currently
spell those slots `AIUpdateInterface::isIdle` and `State::isAttack`. Calling
those existing APIs does not independently prove the enclosing placeholder's
original name or semantics. The other33/35-byte neighboring bodies also remain
verified. No source path, layout, pin, global binding or unique bytes are added.

The separately trialed named `AIUpdateInterface::isIdle` twin was exact, but is
not admitted: `reverse/class_contracts/AIUpdateInterface.json` records the
slot110 spelling as a majority decision while its target-layout identity is
still the address-named2645FF owner. No independent target-name evidence was
found in the bounded review. This is a naming prerequisite, not a byte-match
failure or lost-row regression. The old donor-based definition in AIUpdate.cpp
is untouched. A future named-provider repair needs independent target identity
evidence and coordinated retirement of that old strong definition; native
byte equality alone does not establish the name. Whole primary-table closure,
global provider selection and runtime remain unverified.

The deferred named-provider trial and resolved87B private proof are now banked as handoff evidence only. The code text is not a live provider, approved name or progress. The private donor-removal proof preserves its nine matched bodies, but that removal is not applied. Do not land either half until independent target-name evidence and a coordinated current provider audit support it. The actual three-row canonical StateMachine adoption remains separate and already passed its owning acceptance tool.
