# EmotionTrackerUpdate constructor base-header repair

Inspected base `f143cd5169ff4f7ae719e816da08661b2b7887ab`, 2026-10-29.
Claim: 0x004B21B9 and its EmotionTrackerUpdateCtor.cpp file scope.

## Cause and change

The current ordinary preview rejects only the constructor's primary
`??_7EmotionTrackerUpdate@@6BObjectModule@@@` COMDAT. Its private
ObjectModule has only the destructor slot and emits four bytes; the earlier
EmotionTrackerUpdateDtor.cpp already uses the canonical ObjectModule header
and emits forty bytes under the same name. Adopt that existing header in the
constructor. The canonical base stores Object*, so the distribution calculation
explicitly casts to the existing local +0x74 ID view. This resolves the incomplete
Object error recorded by the earlier automatic adoption attempt without changing
that target field access or introducing a new private class.

This is base-declaration reconciliation. It does not recover the complete
EmotionTrackerUpdate derived virtual interface or establish that every slot of
the shared table equals retail. The separate Thing queue item remains: the
canonical Thing requires Matrix3D/Coord3D definitions and has neither this local
Object-ID field nor its public asObject spelling. Object/Thing reconciliation
needs its own verified views/accessors. No shared header, source path, function
ledger, pin, hatch register or data identity changes.

## Verification

- Before: the constructor builds 5/5 rows, but ordinary preview rejects its
  primary vtable COMDAT (0 authored bytes linked).
- After: normal/strict-current builds pass all 11 rows across constructor and
  destructor. The constructor's EH graph is EXACT; its three old compiler
  labels are resolved through the verified parent EH graph. Frozen-file checks
  pass before and after; literal, float and import checks pass.
- The constructor preserves all 37 other external COMDAT fingerprints and
  removes none. Its new 40-byte table and five added base inline methods have
  exactly the destructor object's byte-and-relocation fingerprints. See the
  [comparison](emotion-tracker-base-header-20261029-codex.json).
- `header_adopt_lane.py accept --class ObjectModule` passes and retires exactly
  this file's queue row. The Thing row stays queued.
- Ordinary paired preview against index `85f6b7f40c` (2026-10-29 15:08):
  constructor LINKS 0 -> 430 authored bytes; destructor LINKS 159 -> 159.
  This is a bounded prediction, not a census-linked gain.
- Staged-tree link batch audit: INCONCLUSIVE. The index predates the base;
  affected consumer `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`
  lacks a current receipt. Carry that consumer and the changed constructor
  provider scope into the next scheduled census. Full consumer closure is
  unverified; no ownership or census gain is claimed.

Local raw before-source/object and audit output are in
`build/emotion-tracker-link/`; the checked facts above are recorded here.
