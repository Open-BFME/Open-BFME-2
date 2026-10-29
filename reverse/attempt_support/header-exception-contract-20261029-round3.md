# Microsoft-header audit preserves exception contracts

Control: `54f489336`; three compiler trials use the unchanged current sources.
The completed task corrects task classification, not game code or a link census.

## Problem and change

The parser discarded every trailing throw specification. Its signature
comparison therefore called an unspecified declaration, throw(), throw(...)
and a typed throw list identical. Under VC7.1 /EHsc, replacing an explicit
throw(...) extern-C declaration with an unspecified CRT declaration can remove
required native unwind cleanup. A green drop-in label was unsafe guidance.

The parser now preserves that specification separately from return/parameter
types. Unequal C++ exception contracts are classified ABI/conflicting; identical
contracts retain the prior result. Equal inline body tokens cannot override a
signature conflict. Index version 14 invalidates old cached declarations.
This is conservative static classification; byte/EH gates remain authoritative.
No exemption, baseline, compiler flag, pin, alias or game source is changed.

A scoped scan against the real VC7.1 headers reclassifies exactly two queued
sources from drop-in candidate to conflicting, without retiring their debt:

- GateOpenAndCloseBehaviorPushOut.cpp: memset throw() versus unspecified.
- Rva00587F69Dtor.cpp: free throw(...) versus unspecified.

Unrelated queue records remain byte-for-byte. Other queue rows need their own
normal rescan; this is not a whole-queue refresh or a verified header adoption.

## Compiler evidence, all trials restored

- Rva00587F69Dtor.cpp owns three 59-byte horde destructors plus six EH rows.
  Replacing its local free declaration with stdlib.h removes all three native
  EH frames and shortens each main body to 25 bytes; all nine rows fail.
  The restored original passes 9/9 again and its control preview LINKS 207 B.
- GateOpenAndCloseBehaviorPushOut.cpp's string.h substitution fails the main
  body and a scoped EH funclet. The original passes 9/9 again; its control
  preview LINKS 554 B. The different exception contract alone is sufficient
  to refuse a drop-in promise; no exact replacement shape is claimed.
- The separate PlayerInitFromDict.cpp trial (stdlib.h/string.h together,
  reordered includes, then stdlib.h alone) grows initFromDict from 2762 to
  2764 bytes and makes two EH funclet bindings ambiguous. Its cause is not
  established by the exception-contract fix: its original declarations have
  no explicit throw clause. It is restored and passes 31/31 again; its control
  preview LINKS 4707 B. This remaining candidate needs its own compiler proof.

The [horde](header-exception-contract-20261029-round3/horde.patch),
[gate](header-exception-contract-20261029-round3/gate.patch) and
[stdlib-only player](header-exception-contract-20261029-round3/player.patch)
patches are zero-context failed diagnostics (replay with --unidiff-zero), not
changes to apply without fresh byte/EH and selection checks.

## Validation

Three new regression tests fail against the original auditor. After the fix,
the Microsoft-header and required gate-exploit suites report 110 passed and
one aggregate red-team test skipped because no external fixture files are present. No skip or refusal assertion
is weakened. Six existing rename-refusal cases previously crashed because the
mock context lacked root after picker-cache integration. Giving that fixture
its isolated temporary root makes all six execute their original assertions;
__FILE__ and included donors are still refused. No rename production code changes.
The real index validation passes, and its scoped classification reproduces the
exception conflicts above. Header-adoption code changes are all reverted.

The [current FX-list check](fxlist-identity-current-20261029-round3.md) separately
confirms a stale particle edge cannot be retired while a known list/StringBase
identity conflict remains. No repair or debt reduction is claimed for that scope.
