# AptBoolean header adoption: what blocks five of the six queued units (2026-11-14)

Batch: `header_adopt_lane.py adopt --class AptBoolean --header Code/Libraries/Source/Apt/AptBoolean.h`
over the six queued units. The lane's trial failed all six. One unit was then
adopted by hand (`AptValue/AptValueConstructBuiltInObjects.cpp`, commit
"adopt the shared AptValue and AptBoolean headers"); the other five stay queued.

## Shared blocker: `AptObject/AptScriptFunction.h` carries its own `AptValue`

`AptMiscObjects.cpp`, `AptObject/AptKeyLookup.cpp`, `AptObject/AptArrayConstructor.cpp`
and `AptActionInterpreter.cpp` include `AptObject/AptScriptFunction.h`, which
defines `class AptValue` itself. `AptBoolean.h` includes `AptValue.h`, so
adoption stops at `AptValue.h(20) : error C2011`. No unit in the tree includes
both headers.

Measured experiment (reverted, nothing committed): replace that class in
`AptScriptFunction.h` with `#include "../AptValue.h"` and rename the two
`mnValueData` users (`AptValue.cpp:496`, `AptArrayConstructor.cpp:326,348`) to
`field04`.

- `./build.sh` over the 20 `.cpp` includers: 570/570 before, 569/570 after.
- The one failure is `?_createObject@AptActionInterpreter@@...` (0x00706A40,
  2496 B) in `AptActionInterpreter.cpp`: 10 differing bytes, first at +0x3D4,
  all in the `Date` branch (`new Rva006FBF90(...)`, 0x40-byte allocation).
  Retail keeps 0 in esi and -1 in edi (`33 f6 83 cf ff 3b c6`); the rebuilt
  body swaps them (`33 ff 83 ce ff 3b c7`). Its funclet `$L2054` then fails
  only because the parent no longer matches.
- Relocation targets of that function are unchanged. `getVariable` and
  `_FunctionAptActionGetUrl2` switch from the const to the non-const `c_cih`
  overload and still match.

The flip does not follow any one declaration. Against the original header,
with single additions to the private `AptValue`:

| Addition | Result |
|---|---|
| four forward declarations before the class | 101/101 |
| virtuals moved ahead of the non-virtuals | 101/101 |
| `mnValueData` renamed `field04` | 101/101 |
| `void setRefCount(unsigned int);` | `_createObject` fails |
| `void zzz();` in the same place | `_FunctionAptActionInitObject` fails instead |
| `friend class AptGC;` | `_FunctionAptActionInitObject` fails |

With the full swap in place, dropping the non-const `c_cih` overload or the
`friend class AptGC` from `AptValue.h`, and deleting the now-redundant forward
declarations in `AptActionInterpreter.cpp` (lines 112, 777..820), each left the
same single failure.

Inference (mine, not proven): two functions in this unit hold a register tie
that the compiler breaks by something that depends on the member names declared
in `AptValue`. That would also explain why every other class's queue line for
this unit reports `FAIL ?_createObject`. The swap of `AptScriptFunction.h` is
otherwise ready; it needs `_createObject` (and probably
`_FunctionAptActionInitObject`) written so the tie does not arise. I did not
attempt that.

## `AptValue/AptBoolean.cpp` (the provider)

Not attempted beyond reading. The unit's private `AptBoolean` derives from a
three-slot private `AptValue` and inlines its constructor into `Create`
(0x006D88C0). With `AptBoolean.h` the inlined constructor stores the 15-slot
`??_7AptBoolean@@6B@`, whose slots name `AptBoolean::ForceDelete`,
`DeleteThis`, `IsGarbageCollected`, `RegisterReferences` and the deleting
destructor. The ledger rows those addresses under other names
(0x006D8860 `??0Rva006D8860BoolValue`, 0x006D8880 `??_GRva006D88B0`,
0x006D88B0 `??1Rva006D88B0`, 0x006D8A20 `?rva006D8A20@Rva006D8670`), and
`tu_map.csv` gives none of the four an approved unit. Expectation (unmeasured):
adoption here adds unresolved names until those rows carry `AptBoolean` names.

## Not checked

- No `link_check.py` or real-link run for the reverted header swap.
- The `AptActionInterpreter.cpp` "Data rows: FAIL 1 of 1" line was not
  investigated separately.
