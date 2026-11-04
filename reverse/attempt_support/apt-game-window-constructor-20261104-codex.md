# Apt window constructor cleanup and remaining consolidation prerequisite

Inspected revision: `0ee5a16ed3`, 2026-11-04, codex.

## Retained constructor change

`Code/GameEngine/Source/GameClient/GUI/BfmeAptGameWindowConstructor.cpp`
now derives its primary context-constructor view from canonical `GameWindow`
and derives `_bfme_AptGameWindow` from that view and `Rva005248D0`.
The +0x270 member uses the `AsciiString` type already established by the
native destructor's source view. The +0x274 and +0x278 fields keep their
unknown, offset-based identities. Ordinary C++ base and member construction
replaces embedded base storage, an explicit secondary-constructor call, two
manual vtable writes, and their two `__identifier` declarations.

Target facts: the 94-byte constructor at RVA 0x0051268C calls the existing
context constructor at 0x00313847, constructs the secondary base at +0x218,
installs the two existing tables, initializes the string at +0x270, then
stores -1 and zero at +0x274/+0x278. The existing 90-byte destructor at
0x005126F5 destroys the string, secondary base and GameWindow prefix.
No new original class name, retail source path or donor identity is inferred.
`BfmeAptScreenBase` remains the existing structural spelling of the context
constructor; its inline destructor reaches canonical GameWindow teardown.

## Verification

Final command:

```
./build.sh Code/GameEngine/Source/GameClient/GUI/BfmeAptGameWindowConstructor.cpp Code/GameEngine/Source/GameClient/GUI/_bfme_AptGameWindow.cpp
```

Result: **9/9 rows exact**, including both constructor rows and all seven
unchanged destructor/message rows. String, float and import checks pass.
Both sources pass `find_declared_unmatched.py`.

Ordinary `link_check.py` over both current objects, index `f12552d0a7`,
census 2026-11-04 20:47, reports:

```
BfmeAptGameWindowConstructor.cpp: LINKS LINKED 104 -> 104 bytes
_bfme_AptGameWindow.cpp:          LINKS LINKED 243 -> 243 bytes
```

These are scoped previews, not a new census or a real-link result.
No source path, ledger, queue, debt register, pin or alias is changed.

## Consolidation trial (restored)

The supported planner ran under `Code/GameEngine/Source/GameClient/GUI/`
(`build/consolidation/codex-gui`). It gives these source names no independent
original-path placement; the current in-memory TU map and `tu_skeleton --plan`
approve the two files' ten retail rows for `_bfme_AptGameWindow.cpp`, including
one still-generated funclet. No map was regenerated on disk.

Before cleanup, `tu_skeleton --merge ... --dry-run` accepted zero donors:
C2373, the constructor's explicit vtable declaration conflicts with the
composed class's compiler-emitted table.

A further trial gave the seed the constructor's primary base view and appended
its two trailing fields. Constructor and parent destructor/message bytes
still matched, but the seed's eight-byte cleanup at RVA **0x00794E2A** changed
its tail-jump identity from `??1GameWindow@@MAE@XZ` to the unrowed intermediate
`??1BfmeAptScreenBase@@UAE@XZ`. The verified parent EH graph maps the old
`$L1203` label to the newly emitted `$L1973`; this is a callee identity problem,
not a label-renumbering problem:

```
target:   8b 4d f0 e9 da fb b7 ff
compiled: 8b 4d f0 e9 00 00 00 00
unresolved: ??1BfmeAptScreenBase@@UAE@XZ
Functions: FAIL 1/9
```

Marking the empty intermediate destructor `__forceinline` did not change
that failure. Both seed variants were restored; the final seed equals its
original tracked bytes. No new pin or alternatename was added.

Next check: reconcile the context-constructor's primary-base identity with
GameWindow and all its existing callers, or establish a compiler shape that
keeps the native GameWindow cleanup directly in the composed EH graph. Merely
pinning the extra wrapper to the existing destructor would add a second real
name and is not a permitted repair. A merge must preserve all rows, table
providers and consumers through the normal merger and batch audit.
