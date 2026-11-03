### Buddy callback CRT header boundary (2026-10-30)

At base `150f22a728`, BuddyThreadCallbacks.cpp now uses the toolchain's
`mbstring.h` declaration for `_mbscpy`, preserving its direct native thunk.
All eight rows, two named imports and both parent EH graphs verify; the
object's COMDAT digests and external definitions/dependencies are unchanged.
Strict preparation passes 8/8 rows and the source previews LINKS, retaining
628 authored bytes against `6fe1089c24` (2026-10-30 04:25).

The local `free` declaration remains necessary: replacing it with `stdlib.h`
changes the existing C++-linkage allocator target at `0x00030830` to imported
C free and removes required unwind-state stores in both callbacks. That trial
was restored and recorded. Reconcile the string/allocator cleanup contract
before retrying this remaining header finding.

The staged batch audit is INCONCLUSIVE on its older baseline and a missing
current `Common/0CreateAHeroManager21FE49.cpp` receipt. Full affected-consumer
selection and loss checks remain unverified; carry the callbacks and wider
consumers into the next scheduled census. No linked-byte gain is claimed.
[Evidence and preserved object facts](../../reverse/attempt_support/buddy-callbacks-msheaders-20261030-codex3.md).
