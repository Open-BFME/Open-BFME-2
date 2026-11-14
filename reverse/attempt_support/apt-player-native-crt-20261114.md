# AptPlayer: native CRT declarations with mixed call routes

Scope: `Code/GameEngine/Source/GameClient/GUI/AptPlayer.cpp`.
Remove the `strchr`/`sprintf` header-hiding macros and copied import
declarations. Use the toolchain's `string.h` and `stdio.h` declarations.
No function body, data definition, pin, alias, shared header or ledger row
changes.

Retail's 93-byte `AptPlayer::UnloadLevel` at 0x00222481 uses a DIR32
reference to `__imp__sprintf` at body offset 54. The 306-byte
`AptPlayer::FindRenderImage` at 0x00223AC4 similarly references
`__imp__strchr` at offset 198. The native import-reference verifier checks
both routes. In contrast, `AptPlayer::GetExtern` at 0x00223E4B calls the
existing `_mbscpy` thunk through a REL32 reference (object name
`__mbscpy`). These are different call forms, not interchangeable spelling.

Two private probes explain why a TU-wide CRT switch is insufficient.
Keeping `/D_CRTIMP=` for all headers changes the first two calls to
REL32 `_sprintf`/`_strchr`, shortening both bodies by one byte.
Removing that flag retains the two imports but changes `GetExtern` to
import `_mbscpy` and changes the emitted external `free` reference.
Neither probe was applied to the source.

The retained change saves the existing `_CRTIMP` macro, undefines it while
including the two native headers, then restores its prior value before
the existing STLport and `mbstring.h` includes. The headers themselves
select their normal /MD import declarations. No replacement CRT prototype
or copied macro value is supplied by this source.

An isolated object comparison covers all 69 retained rows, including
compiler cleanup rows. All row bytes and relocations are unchanged after
resolving compiler-local labels by section and owner-relative offset.
The complete sets of external definitions and references are unchanged.
The native gate verifies 69/69 rows, 11 nonempty and four empty strings,
one compiler float and both imported calls; all 16 EH records are EXACT.
The declared-unmatched check finds no open bodies.

The owning scoped `ms_header_audit.py scan --write-queue` finds zero local
Microsoft declarations and removes only this source's queue row (460 to
459 files). Both native link previews retain 4,015 -> 4,015 bytes against
the 2026-11-13 17:59 census at 5e4cbaea7d. That index predates 47 source-path
changes; this is a scoped prediction against that index, not a new full
link or runtime result. No linked-byte increase, bridge retirement,
memory improvement or crash fix is claimed.
