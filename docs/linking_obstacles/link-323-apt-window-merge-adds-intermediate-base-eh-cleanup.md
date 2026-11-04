### LINK-323: Apt window merge adds an intermediate-base EH cleanup
Status: Blocked on primary-base identity/codegen. Updated: 2026-11-04; inspected revision: `0ee5a16ed3`.
Evidence / affected units: `BfmeAptGameWindowConstructor.cpp` and `_bfme_AptGameWindow.cpp`; [constructor cleanup and trial evidence](../../reverse/attempt_support/apt-game-window-constructor-20261104-codex.md), ordinary-preview index `f12552d0a7`.
Completed: constructor uses real base/member construction; 9/9 rows exact across both units, previews preserve LINKS for 104 and 243 bytes. Destructor trial restored.
Remaining / next check: reconcile context-constructor primary-base identity with GameWindow and callers, or preserve the direct GameWindow destructor target in cleanup 0x00794E2A. An inline intermediate destructor still emits an unrowed callee there.
Clearance: constructor cleanup only; no merge or debt retirement.
Census confirmation: no new result claimed.
