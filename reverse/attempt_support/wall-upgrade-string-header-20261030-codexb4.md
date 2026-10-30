# WallUpgradeUpdate memset header attempt

Inspected base: `3134afceb4`. Claimed source:
`Code/GameEngine/Source/GameLogic/Object/Update/WallUpgradeUpdate.cpp`.
The existing source passes the frozen-file check and verifies all 15 rows,
including nine parent-resolved funclets and two floating-point literals.

The only Microsoft-header finding is the local `memset` declaration with
`throw()`. Replacing it with `<string.h>` makes the scanner report clean,
but changes the 586-byte parent at `0x004AB57E`: it adds EH state 1 around
the zeroing call, exchanges EBX/EDI roles and invalidates the parent-resolved
`$L913` funclet location. Giving `ObjectStatusMaskNone`'s inline constructor
`throw()` does not change that result. Neither trial is retained.

The earlier `GateOpenAndCloseBehavior::rva00498FAA` verdict in
`reverse/re_attempts.log` already identifies this exception-specification
blocker in WallUpgradeUpdate and other mask consumers. A constructor-level
exception specification is not a solution under this TU's current flags.
Find a truthful header-based representation that preserves the call's EH
behavior before retrying. No header, tool, flag or gate exception was added.

The original source is restored and its Microsoft-header queue row remains.
The blocked verdict names the parent boundary and this handoff. No matching,
linking or debt progress is claimed for this attempt.
