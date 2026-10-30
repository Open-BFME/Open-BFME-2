# computePath logger declaration: header cleanup deferred

Inspected base: `3134afceb4`. Source:
`Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_computePath.cpp`.
The Microsoft-header picker served its sole `fprintf:abi` finding and claimed
the file. No production source was edited and its queue finding is retained.

## Current evidence

The ledger binds `_fprintf` to RVA `0x002CEC42`, size 108, owned by
`Code/GameEngine/Source/Common/FprintfAppendLine.cpp`. That matched provider
takes a `FprintfTarget *`, formats through `_vsnprintf`, constructs an
`AsciiString`, and appends it to the target's vector at offset +4. It returns
`void`. The consumer currently declares an opaque first argument and an unused
`int` result. This is a game helper, not evidence of the CRT stream operation.
The CRT import has its own row at `0x006298C2` in `imports_001.cpp`.

The earlier [random-value cleanup](random-value-ms-headers-20261028-codexb.md)
already records the same distinction and leaves the logger finding queued.
Including `stdio.h` with `_CRTIMP` disabled and casting the target to `FILE *`
would preserve a C symbol while asserting the wrong object type. That is not
an adequate source-recovery fix. The previous AIStates and attack-path header
notes describe successful byte checks, but those checks do not establish that
this game object is a CRT stream; reconcile their declarations in the same
provider/consumer identity pass.

## Checks and next step

The unchanged source passes the frozen-file check and normal `./build.sh`:
both function rows match, along with 62 strings and 13 empty string literals.
The 3,223-byte `computePath` row at `0x00265E0B` remains matched. The baseline
object is saved under `build/compute-path-stdio-20261030/before.obj` locally.

Recover the logger's identity and a truthful shared declaration across its
provider and consumers before retiring this Microsoft-header finding. Neither
an original donor name nor the object's full layout is established here.
The blocked verdict is recorded through `tools/re_log.py`; the scope claim is
released. No linking, ownership or debt reduction is claimed for this attempt.
