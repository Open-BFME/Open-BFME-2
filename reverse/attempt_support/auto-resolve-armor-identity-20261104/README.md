# Auto-resolve armor lookup identity, 2026-11-04

Inspected revision: `c02844f60cd652e9c51955c233f913491aab0ddb`.
Source: `Code/GameEngine/Source/GameClient/GUI/Rva00427157Ctor.cpp`.

The registered identity scan originally reported three findings: two calls to
the typed `_M_find<NameKeyType>` at RVA `0x002888D4`, and one hash-map subscript
at `0x0041F4E5`. These are existing owners and existing fold-proof pins, not
unrowed bodies. No ledger rows, pins or link-wide aliases were changed.

The committed repair exposes the integer hash and const pointer-bucket accessors
for inlining while suppressing competing out-of-line accessor copies. The emitted
lookup is exactly retail's 47 bytes with zero relocations; see
[lookup-proof.txt](lookup-proof.txt). The owning retirement command,
`repair_queue.py retire identity Code/GameEngine/Source/GameClient/GUI/Rva00427157Ctor.cpp`,
passed and removed two registered keys. The remaining subscript key stays in the
register; [final-identity.log](final-identity.log) reports it.

Verification: [final-build.log](final-build.log) preserves all 13 matched bodies
and the FieldParse data row; [final-eh.log](final-eh.log) reports three exact EH
parents. [final-variants.log](final-variants.log) records a successful new-variant
check. [final-link.log](final-link.log) preserves the 691-byte LINKS preview
against the fetched census index at `5a13f2cd61`; this is not a new census result
or a real-link coverage claim. Retirement initially lacked current provider
objects; rebuilding those through `build.sh` passed 2,146 rows across 198 sources
([refresh-build.log](refresh-build.log)).

The remaining subscript fold fails recursively at hash-table resize
`0x0053F1EC`: retail is 184 bytes. No-exceptions, native allocator and visible
vector destruction/swap trials reduced the emitted resize from 303 to 191 bytes.
The latter still uses seven extra bytes around mutable bucket indexing and
different ESI/EDI homes. `/G7`, `_CRTIMP`, `/Ob2` and a natural mutable subscript
did not close that difference. These observations do not establish a native
compiler setting or layout. All insertion trials were reverted; the failed
[resize191.patch](resize191.patch) is evidence only. Next: reconcile that resize
code shape against the existing native owner before attempting subscript debt
retirement. The blocked attempt is recorded through `re_log.py`.
