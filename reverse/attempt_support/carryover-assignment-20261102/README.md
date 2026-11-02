# CarryoverUnit assignment provider

Native fill 1EBEAB constructs a live CarryoverUnit temporary through its
real copy constructor 1EB79E, passes that same temporary through fill1EB84E
to assignment1EB20E, then destroys it through CarryoverUnit's real destructor
37DEE4. Derived ArmySummaryEntry construction and LivingWorldBuilding base
assignment independently corroborate the same base-object interpretation.
The tail's original application type remains unknown; the body uses the
existing native Rva001EAFC1 assignment view at its proven +94 offset.

The new typed assignment compiles to exactly the existing 84-byte body,
including symbolic relocations. add_match --icf-owner admits its whole-body
twin of BfmeAssignRecord172::operator= without removing that provider or any
consumer. This recovers a usable typed interface; it adds no unique coverage.
All ten current source rows and two EH graphs pass normal/strict checks.
All thirteen prior complete code definitions remain unchanged; the assignment
and an incidental AsciiString assignment copy are the two added definitions.
The scoped prediction remains LINKS (385 -> 468 own bytes); that increase
includes an existing shared body and is not a global census gain.

Carryover's manual shared header remains a separate uncommitted trial:
five of thirteen units pass; others need layout/interface reconciliation.
The old synthetic vector fill and overflow remain unchanged until typed
helpers and their callers can migrate together. No row/pin is retired here.
