# AsciiString command-name header adoption boundary

Target: `GameMessage::getCommandTypeAsAsciiString`, RVA `0x0030FA44`,
`Code/GameEngine/Source/Common/System/MessageStreamCommandName.cpp`.

The unchanged source byte-verifies all four rows (including its exception
handler and two funclets), with 363 literal references verified. A current-object
link preview reports LINKS for 5,433 authored bytes. These are preview results,
not a new census measurement.

Trial: replace the local StringBase-derived AsciiString with the existing
canonical `ascii_string.h` using `BFME_ASCII_IMPLICIT_DTOR`, retaining the
function body and compiler flags. This mode avoids introducing a new shared
header switch. It still changes the main body's bytes, and the scoped `$L1776`
funclet loses its exact same-source parent-EH verification. The canonical
constructors invoke StringBase construction through casts, whereas the local
constructors use base initializers; the source already documents sensitivity
to the compiler's inlining budget. The mode alone does not reconcile that
boundary. Do not accept the header queue entry on this evidence.

The trial was restored. `./build.sh` again verifies 4/4 rows and all 363
literal references. No game source or header queue change is retained.

Other leads examined in the same class queue remain prerequisites, not repairs:
the geometry-vector helper uses shallow string copies; StringRecord allocation
helpers have the same ownership issue; Apt's local string identity needs
EAStringC evidence. The three-string body at `0x00689380` has a Video assignment
pin and a BFME 1 assignment counterpart, despite its current constructor-shaped
placeholder declaration. Reconcile that identity and signature through supported
ledger tools before attempting canonical string initialization there.
