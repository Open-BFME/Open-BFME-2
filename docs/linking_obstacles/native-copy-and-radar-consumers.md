### Native string-copy and radar predicate consumers

Status: string-copy consumers repaired locally; fresh full link pending.

The authoritative real link at 1ffed447 reports the withdrawn helper names
`BfmeUniVKE::bfmeCopyUVKE` and `BfmeSubBSF::bfmeSetBSF`. Their native calls
target the existing StringBase<char> copy constructor at 000365F0. The two
consumers now construct that canonical type directly in their original storage,
using the header's existing public-copy declaration. No alias or new pin.

Official build: 2/2 rows, 95 bytes; EH has no graphs or missing objects.
Provider-inclusive scoped link preview: 3/3 clean, provider's 197 bytes
unchanged, consumers 64 and 31 bytes. New-variant check passes. The census
is still 0534e78db3 (16:28); these are scoped predictions, not real-link gains.

The radar consumer's withdrawn bool spelling is the next related repair.
The native 66-byte predicate already exists in Player.cpp at 002AA04C.

Evidence: [handoff](../../reverse/attempt_support/native-copy-and-radar-consumers.md).
