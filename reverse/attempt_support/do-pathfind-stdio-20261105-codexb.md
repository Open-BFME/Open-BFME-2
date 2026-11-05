# doPathfind logging header cleanup

Base: `17d40f9e00`. Scope:
`Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_doPathfind.cpp`.

Replace the local `fprintf(void *, const char *, ...)` declaration with
`stdio.h` and use its `FILE *` stream type. Configure `_CRTIMP` only while
including that header so the emitted call remains direct `_fprintf`, not
`__imp__fprintf`; restore dllimport before the remaining headers. The existing
ledger owns `_fprintf` at RVA 0x002CEC42 as the game's format-and-append helper,
not the CRT import. This cleanup preserves that existing binding and makes no
claim about recovering the logger's original C++ type.

Verification:

- Before and after `./build.sh`: the whole 1,883-byte function matches, including
  fifteen string references and two float constants.
- Before and after `find_declared_unmatched.py`: all definitions matched.
- All 24 external COMDAT byte-and-relocation fingerprints and all 44 external
  symbol records (name, storage, definition status and value) are identical;
  both objects have no weak bindings. The unchanged undefined `_fprintf`
  record confirms the direct call binding.
- `link_check.py --prepare-current`: one explicit provider passes normal byte
  gates with a strict reusable receipt.
- Ordinary preview before and after: LINKS, 1,880 -> 1,880 authored bytes against
  index `c95fcfcfcd`, dated 2026-11-05 05:17. This is a scoped preview, not a
  new census or a full consumer audit.
- `ms_header_audit.py scan --write-queue` on this source removes exactly its
  one `fprintf:abi` row; scoped `check` is clean. No unrelated queue changes.
- `git diff --check` passes.

The real-link picker initially served Rva00219B9EAccessor.cpp's historical
memset blocker. Current source already contains `92d6835101`; byte verification
passes 91/91 and preview LINKS at 3,086 bytes. The other untried memset target,
Rva0051C0E7Ctor.cpp, already contains `ce7565b2ca`. Neither received a source
edit, and both inspection claims were released. Existing LINK-181 records
this repaired memset cause; no unchanged obstacle entry was rewritten.
