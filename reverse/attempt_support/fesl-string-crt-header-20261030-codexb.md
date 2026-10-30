# FESL string-copy CRT header cleanup

Inspected base: `e969e5b869`, 2026-10-30. Source:
`Code/GameEngine/Source/GameNetwork/Y2FeslSafeStrCopy.cpp`.

The Microsoft-header picker selected the local `strncpy` declaration. The
source already includes `<string.h>`. Removing the redundant declaration by
itself changes the 98-byte parent to 99 bytes and replaces the direct
`_strncpy` call with an indirect `__imp__strncpy` call. The byte gate rejects
that trial. The existing `/D_CRTIMP=` compiler setting lets the header supply
the declaration while retaining retail's direct CRT thunk call.

The final change removes the local declaration and documents that binding.
No body, path, ledger identity, pin or shared header changes.

Verification:

- `./build.sh` passes all 13 rows, four string literals and two empty-string
  references. The declared-unmatched check passes before and after the edit.
- All 17 COMDAT fingerprints (bytes and relocation targets) and all 19
  external symbol records equal the pre-edit object.
- `data_check.py --converged` passes: 11 addresses, zero second names and
  zero unjudged rows.
- The Microsoft-header auditor reports clean. Its scoped `refresh_queue`
  removes exactly this source's one-definition queue entry.
- Strict `link_check.py --prepare-current` verifies the source and all 13
  rows with a reusable current receipt.
- Ordinary link preview retains LINKS, 468 -> 468 authored bytes, against
  index `85f6b7f40c` (2026-10-29 15:08). This is a preview, not a census gain.

The staged-tree batch audit is INCONCLUSIVE: the index predates the base and
affected consumer `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`
lacks a current receipt. Carry that consumer and this provider into the next
scheduled census. Full consumer closure remains unverified. The unchanged
object fingerprints and symbols above establish the bounded object comparison;
they do not replace a current consumer audit or census.
