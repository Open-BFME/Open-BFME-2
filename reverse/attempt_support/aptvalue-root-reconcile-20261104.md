# AptValue root reconciliation (LINK-197): blocked by AptActionInterpreter.cpp regalloc

Date: 2026-11-04. Base: 50c527824d. Model: claude-opus-5-5. Patch: [aptvalue-root-reconcile-20261104.patch](aptvalue-root-reconcile-20261104.patch).

## Change tried

- `AptObject/AptScriptFunction.h`: replace its private `class AptValue {...}` with `#include "../AptValue.h"`.
- `AptValue.h`: rename the pure slots 12/13 `vslot12`/`vslot13` to `IsGarbageCollected`/`RegisterReferences`
  and the +4 word `field04` to `mnValueData`. These are donor names from the APT 0.19.03 PDB declaration
  that AptScriptFunction.h already carried. Target fact: the ledger already names the slot-13 overriders
  `RegisterReferences` (AptValueWithHash 0x006DCC00, AptObject 0x0070DFD0).
- Rename the slot overrides and calls to match in AptCIHClass.h, AptBoolean.h, AptActionInterpreterParseStream.cpp,
  AptActionInterpreterConstantHandlers.cpp, Rva006E3230Validate.cpp, AptGC.cpp, AptDisplayList.cpp,
  Common/Rva00709C10Cluster.cpp and AptValue/AptValueToBoolBFME2.cpp.

## Result

- 27 of the 28 claimed sources byte-match (`./build.sh`), among them AptValue.cpp 30/30,
  ConstantHandlers 182/182, AptScriptFunction.cpp 44/44, AptMiscObjects 39/39 and AptFactoryConstructors 37/37.
- AptActionInterpreter.cpp fails two rows on an esi/edi swap:
  - `_FunctionAptActionInitObject`
  - `_createObject`, where the swap sits in the TextFormat/Color default-value loads.

## Bisect

The bisect rewrote the canonical header's member set and changed no code.

- Dropping the non-const `c_cih(bool)` overload fixes InitObject.
- With that overload dropped:

| Member set | Result |
|---|---|
| Old private member set | passes |
| Old + `setIsDefined..isRegister` (12 members) | `_createObject` fails |
| Old + either half of those 12 | passes |
| Old + `isFloat..rva006DDF60` (16 members) | passes |

So the cause is a declaration-set tie-break in MSVC 7's register allocator, not the member count.

Replacing the 19 `(BfmeAptValue006DCD20 *)` casts on `toInteger()` in `_createObject` with canonical calls
does not flip the tie-break back.

## Next

Pick one of these:

1. Remove AptActionInterpreter.cpp's private BfmeAptValue006DCD20 view and its alternatename aliases (lines 56-59 and 89-92)
   in favour of canonical calls. This is a larger declaration-set change that may restore the tie-break.
2. First split the interpreter's consumers of AptScriptFunction.h so that they no longer need the private AptValue.

The patch applies cleanly at 50c527824d.
