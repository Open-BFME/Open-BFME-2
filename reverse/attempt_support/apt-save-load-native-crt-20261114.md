# AptSaveLoad::Externs: preserve mixed CRT call routes

Scope: `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptSaveLoad_Externs.cpp`,
the complete 385-byte matched body at RVA 0x00433DFE.

Replace the three copied declarations of `_strcmpi`, `_mbscpy` and
`_mbscat` with the toolchain's `string.h` and `mbstring.h`. The
multibyte declarations take unsigned-character pointers; explicit casts
at the seven existing calls express that API without changing the
buffer, constants, call destinations or return handling.

The earlier recorded header attempt correctly rejected a blanket /MD or
`/D_CRTIMP=` switch: this body imports `_strcmpi` through its IAT and
calls `_mbscpy`/`_mbscat` through the existing direct thunks. The now
verified AptPlayer change at d19ddaeff16 establishes a scoped header
context technique for that split. This source sets `/D_CRTIMP=` for its
nonimport declarations, temporarily saves/undefines the macro for
`string.h`'s native /MD import declarations, then restores it before
`mbstring.h`. There is no hand-written replacement prototype.

A private before/after object comparison preserves all 385 bytes, every
relocation and the complete sets of external definitions and references.
In particular, the reference to `__imp___strcmpi` and direct
`__mbscpy`/`__mbscat` references are unchanged. The native gate verifies
1/1 function, twelve string references and the imported call. The EH
verifier finds zero EH rows and no missing objects; the declared-unmatched
check finds no open body.

The owning scoped `ms_header_audit.py scan --write-queue` finds zero local
Microsoft declarations and retires only this source's queue row (459 to
458 files). Native census and current-object link previews both retain
385 -> 385 bytes against 2026-11-13 17:59 at 5e4cbaea7d. That index predates
47 source-path changes, so these previews are bounded predictions, not
a fresh complete link or runtime proof. No linked-byte increase,
memory improvement or crash fix is claimed.
