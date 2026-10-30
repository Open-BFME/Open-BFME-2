# Buddy callback CRT header cleanup

Base: `150f22a728`, 2026-10-30. Source:
`Code/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThreadCallbacks.cpp`.

The Microsoft-header picker served two local declarations: `free` and
`_mbscpy`. The retained change replaces `_mbscpy` with the toolchain's
`<mbstring.h>` prototype and passes the required unsigned-character pointers.
Saving/restoring `_CRTIMP` around that header preserves the direct native
`__mbscpy` thunk, while existing headers keep their import configuration.

The `free` migration was tried and restored. Retail calls the existing
C++-linkage `?free@@YAXPAX@Z` pin at `0x00030830`. Including `<stdlib.h>`
instead emits imported C free, and changes both requestCallback
(`0x005511E5`) and messageCallback (`0x00551139`): the required final EH
state store disappears and the cleanup call changes from `e8` to `ff 15`.
The unchanged declaration is documented in source and its blocked attempt is
recorded through re_log. Reconcile the string/allocator cleanup contract before
retrying this part; the queue must retain that remaining finding.

Verification of the retained change:

- Normal builds before and after pass all eight function rows and both named
  imports. Both parent EH graphs are EXACT. The existing funclet row's
  `parent=` evidence resolves its renumbered compiler label to the same RVA.
- Frozen-source checks pass before and after.
- The header auditor's supported `refresh_queue` API reduces this source from
  two local declarations to one, `free:mangle`, preserving unrelated queue
  records. `_CRTIMP` is a configuration input, not a removable definition;
  this rescan has no include-closure diagnostics.
- All eight COMDAT name/digest/size records, six strong definitions, twelve
  undefined names and zero weak bindings are unchanged, including the direct
  `__mbscpy` and C++ free dependencies. No source path, pin, ledger row or
  private game-class definition changes.
  [Preserved object facts](buddy-callbacks-msheaders-20261030-codex3.json).
- Strict current-input preparation passes 8/8 rows. The ordinary preview is
  LINKS and retains 628 authored bytes against index `6fe1089c24`
  (2026-10-30 04:25). This predicts no linked-byte gain.
- The staged batch audit is INCONCLUSIVE: its index predates the outgoing
  base, and `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`
  lacks a current receipt. Full affected-consumer selection and loss checks
  remain unverified; the obstacle register carries the next-census handoff.

The initially selected R5VectorDtorEHFramedPolymorphic identity task was
released after checking the existing handoff against current sources: its
Gen00141A00 row still duplicates the native Rva002D0EDCElement assignment at
`0x002D0F65` and binds the incompatible helper cohort. No unchanged trial was
repeated and no row/debt entry was altered for that scope.
