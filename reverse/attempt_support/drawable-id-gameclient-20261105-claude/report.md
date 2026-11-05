# GameClient.cpp drawable ID getter link repair

Inspected revision: `3a8ef21839` (2026-11-05). Scope: `Code/GameEngine/Source/GameClient/GameClient.cpp`,
the last of LINK-534's twelve consumers of the undefined `?getID@Drawable@@QBE?AW4DrawableID@@XZ`
(`reverse/exit_link_blockers.tsv`: one missing name).

## Change

The unit's two unrowed `present-unmatched` bodies, `GameClient::addDrawableToLookupTable` and
`GameClient::loadPostProcess`, read the drawable ID through `Drawable::getID`. They now call the
existing byte-matched provider `?get@Rva0055A88BDwordField@@QBEHXZ` (RVA `0x0055A88B`, dword at
`+0x100`, `Code/GameEngine/Source/Common/DispDwordFieldGetters.cpp`), cast to `DrawableID`, the same
binding the eleven earlier consumer repairs used. Ledger rows, pins, hatches, headers and paths are unchanged.

## Verification

- `find_declared_unmatched.py`: all defined functions already matched, before and after.
- [build-after.log](build-after.log): 2/2 rows and 3 data rows verify; [provider-build.log](provider-build.log): provider 1/1.
- [object-audit.json](object-audit.json) ([object-audit.py](object-audit.py)) compares the pre-edit object with the
  final one: all 622 external definitions and 616 external COMDATs are kept; exactly one undefined external
  changes (missing getter -> provider, which the provider object defines); only the two edited COMDATs change
  digest, and their bytes, sizes and relocations are equal after normalizing that one name.
- [link-after.log](link-after.log): LINKS, LINKED 5 -> 5 bytes against census `3a95b274a2`; preservation
  evidence only, no link gain claimed.

## Remaining

Confirm in the next real-link run that GameClient.cpp no longer lists the missing getter.
