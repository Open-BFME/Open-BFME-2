# Debug console cleanup: identity fix needs the provider cohort

Inspected 29c5ceda1fb5b10685912e113655ccbcc9640b2f, 2026-10-29.
Constructor and destructor scopes were claimed; all trial source edits and the
identity-register retirement were restored before releasing them.

## Target and control

DebugIOCon's constructor is 466 bytes at 0x00040C40. Its eight-byte unwind
action at 0x0075CEA0 calls 0x0003F320, owned by the protected virtual
DebugIOInterface destructor (seven bytes in debug_io_flat.cpp). The source
instead binds the public DebugIOConBase destructor. The original ZH
internal_io.h confirms DebugIOCon derives from DebugIOInterface; debug_io.h
declares the protected destructor. These donor facts support the base role,
not a complete BFME 2 interface/vtable recovery.

The original constructor, destructor and the rowed interface destructor pass
9/9 rows together, including the 85-byte destructor, its scalar deleting
destructor, both unwind actions and both EH handlers. The original console
unit previews LINKS for 476 authored bytes against census 840db2d676.

## Tested hypotheses

1. A declaration-only real DebugIOInterface base keeps 4/4 caller/provider
   rows, all 19 constructor imports and the exact EH graph. All 484 constructor,
   cleanup and handler code bytes are unchanged. The local identity scan goes
   from one wrong binding to none; data checks remain at zero findings.
   After populating eight missing cache units (129 rows, two data rows), the
   retirement tool can retire the key. However, the ordinary link preview
   drops 476 -> 0: the emitted DebugIOInterface vtable differs from the first
   copy, and its scalar deleting destructor is not retail's body. The register
   change is therefore not kept.
2. A forced-inline, typed native-destructor bridge retaining the old base
   view in both units fails the original 85-byte DebugIOCon destructor. It
   adds an external call to its normal teardown; the normal build fails 1/9.
3. Keeping that bridge only in the constructor preserves all 9/9 rows, but
   still drops 476 -> 0 in the ordinary preview: DebugIOConBase's destructor
   is not retail's body and its scalar deleting copy differs from the first.

The [direct-base trial](debug-console-identity-20261029-round3/direct-interface.patch),
[shared bridge](debug-console-identity-20261029-round3/two-file-bridge.patch) and
[constructor-only bridge](debug-console-identity-20261029-round3/constructor-bridge.patch)
are zero-context diagnostics; replay needs git apply --unidiff-zero. None is
a repair to apply without repeating both byte/EH and provider-selection checks.

## Remaining prerequisite

Reconcile the DebugIOInterface/DebugIOCon vtable and deleting-destructor
providers as a cohort, including their compiler frame context. The existing
debug-family handoffs also record BFME 2's extra native interface slot, absent
from the six-slot ZH declaration. A local base-name substitution or forwarding
body is not enough. Do not retire the identity key on byte equality alone,
force an alias, change link order, or weaken the selection guard.

The final restored constructor passes its three rows and 19 imports again.
No source, header, compiler flag, pin, alias or register change survives.
No linking, ownership or debt reduction is claimed by this attempt.
