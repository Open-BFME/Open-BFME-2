# Logger and texture helper Microsoft-header cleanup

Source base: `1f26b04a7b`, 2026-10-30.

FprintfAppendLine.cpp now compares the format pointer with the C++ null
pointer constant directly, eliminating its local NULL macro. Its remaining
`_vsnprintf` declaration stays queued: including stdio.h would also introduce
the CRT fprintf declaration, incompatible with this game's object-and-format
helper. The logger identity work described in
`../compute-path-logger-header-20261030-codexb4.md` remains necessary.

TextureHandleAssignment.cpp includes the pinned Microsoft `<new>` header
for operator delete[] and removes its local declaration. The existing
absent-from-retail emission helper and inline anchor are retained.

Normal builds pass before and after: all three logger rows (including the
parent-resolved cleanup) and both texture rows match. The logger's named
CRT import also verifies. Each object retains exactly the same three
COMDAT bodies and relocations and the same external-symbol set (10 logger,
9 texture); `object-comparison.json` records their hashes and identities.
The new-variants link check passes for both sources. Frozen-file checks pass.

The scoped Microsoft-header queue refresh removes the texture finding and
reduces the logger from two findings to one. No match, census, ownership or
source-file count change is claimed. BFME1 input freshness remains limited
as recorded in `../ai-upgrade-merge-recheck-20261030-codexb5.md`; this cleanup
uses the existing pinned compiler headers and no donor implementation.
