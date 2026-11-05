# RvaSmartPtr12 field/reference consumers adopt the canonical header

Base: `a66a74a3b9`; preview index: `f44cbcf5b0` (2026-11-05 15:19).

Three consumers can adopt the existing header without changing its lifetime
contract. `Rva000B8F5A.cpp` accesses its existing handle member through `field00`
and the canonical pointer operator. `GPUParticleStorageConstructor.cpp` consumes
a const handle reference. `ScriptEngine.cpp` uses explicit constructor/unlink
calls through casts; its separate handle wrapper retains its own lifetime code.
Only their private RvaSmartPtr12 declarations are removed.

Verification:

- `find_declared_unmatched.py` passes before and after all three changes.
- Scoped `./build.sh` passes 164/164 function rows and three data rows, including
  funclet, string, float and import checks.
- One `header_adopt_lane.py accept --class RvaSmartPtr12` invocation over all
  three sources passes and retires exactly three header-queue rows.
- Current `link_check.py` previews preserve 2,435, 354 and 7,303 bytes,
  respectively (10,092 total). ScriptEngine's unreferenced float-record
  constructor diagnostic is nonblocking. This is no new real-link measurement.
- External COFF definitions before/after: Rva000B8F5A 29/30, GPU storage 82/82,
  ScriptEngine 334/334. The removed-definition set is empty for each object,
  so no other object's import or alternatename can lose a provider. The sole
  addition is the canonical pointer operator in Rva000B8F5A. No alternatename,
  pin, ledger identity, shared header or source path changes.

The remaining consumers that inline destruction or require a default
constructor still need the lifetime-contract reconciliation already recorded
under LINK-155 and `header-adopt:RvaSmartPtr12@inline-dtor` in the attempt log.
