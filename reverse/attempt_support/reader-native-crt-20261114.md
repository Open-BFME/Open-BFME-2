# Model reader: native CRT declarations

Scope: `Code/Libraries/Source/WWVegas/WW3D2/GenRva001808B0.cpp`,
the complete 171-byte row at RVA 0x001808B0. Its address-derived owner and
method identity are retained.

Replace the copied `_mbscpy` and global `operator new` declarations with
`mbstring.h` and `new`. Use the native unsigned-character pointer API at
the two multibyte-copy calls. This leaves the buffer, source pointers,
extension string, allocation size and file/chunk operations unchanged.

The prior recorded header attempt rejected a blanket CRT switch because
the row imports `strchr` and calls `_mbscpy` through its direct thunk.
Use `/D_CRTIMP=` for the multibyte declarations; temporarily save and
undefine it around `string.h` so that header supplies its normal /MD
import declaration, then restore it. `new` supplies the global allocation
declaration including its exception specification. No copied replacement
prototype or body is introduced.

A private object comparison retains all 171 bytes, every relocation and
the complete sets of external definitions and references. In particular,
`__imp__strchr`, `__mbscpy` and the existing global allocation reference
retain their routes. The native gate passes the one row, its extension
literal and its import. The EH verifier finds zero EH records and no
missing object; the declared-unmatched check finds no open body.

The scoped owning `ms_header_audit.py scan --write-queue` finds no local
Microsoft declaration and removes only this source's queue row (458 to
457 files). Native census/current-object link previews both retain
171 -> 171 bytes against 2026-11-13 17:59 / 5e4cbaea7d. That index predates
47 source-path changes, so this is a bounded preview, not a new full link.
No startup, runtime, memory improvement or crash fix is claimed.
