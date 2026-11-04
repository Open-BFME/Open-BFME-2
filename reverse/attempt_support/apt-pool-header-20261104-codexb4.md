# Apt pool header adoption, 2026-11-04

Inspected source revision: `293fbba275`.
Canonical header: `Code/GameEngine/Include/Common/Rva006DB270.h`, registered by
`1508ea469e`. Its existing target evidence establishes a nonvirtual 28-byte
receiver with a free-list array at +0, pool pointer at +4, unsigned size limit
at +0xC, configuration byte at +0x13 and usage counter at +0x14. No donor
identity, original field name or new layout is claimed here.

The header queue still listed two private receiver declarations:
`Code/Libraries/Source/Apt/AptActionInterpreter.cpp` and
`Code/Libraries/Source/Apt/DogmaAllocator.cpp`.

- The standard `header_adopt_lane.py adopt --apply` accepted the interpreter.
  The earlier queue diagnostic about `_createObject` no longer reproduces with
  current inputs; the complete unit passes without a compiler-shape change.
- The codemod conservatively refused the allocator's anonymous union before
  applying a rewrite. Manual adoption replaces only the private class and
  maps the four member uses in `Rva006DB270::freeBlock` by their identical
  offsets/types: `m_minByte` -> `byte13` (+0x13), `m_maxSize` -> `field0C`
  (+0xC), `m_firstPool` -> `field04` (+4), `m_used` -> `field14` (+0x14).
  The separate `Rva006DB090` receiver and its union remain unchanged.
- Both sources include the canonical header at the former private declaration.
  The canonical header itself, public symbols, row identities and provider
  bindings are unchanged. No alias, pin, hatch or baseline is added.

Verification:

- `find_declared_unmatched.py` passes for both sources before and after edits.
- `./build.sh` over both units: 107/107 code rows and 2 data rows match;
  151 string literals, 3 empty-string references and 2 float literals verify.
  Existing compiler funclet labels are verified through their parent EH data.
- `header_adopt_lane.py accept --class Rva006DB270` over both units: PASS,
  PASS; the owning tool retires exactly two header-queue rows after byte and
  link checks. Neither source retains a private `Rva006DB270` body.
- Explicit `link_check.py` against index `f12552d0a7` dated 2026-11-04
  20:47: interpreter LINKS 12,344 -> 12,344 bytes; allocator LINKS
  468 -> 468 bytes. These are scoped previews, not new headline credit.
- `check_csv.py` and `git diff --check` pass.

The earlier BridgeBehavior picker item was independently rechecked unchanged:
51/51 rows match and the current index predicts LINKS 4,673 -> 4,673 bytes.
Its existing pool-head repair already appears in the obstacle register and is
not new progress from this session. Its claims were released.

This pass retires header debt only. It does not merge files, alter the census,
run a real link or claim a smoke result. The unrelated AptValue/root receiver
reconciliation tracked in LINK-197 remains outside this scope.
