# INI multibyte CRT header adoption

Base `890f92d901`, 2026-10-26. Claimed scope: INI.cpp and both string readers.
This is one homogeneous header/signature adaptation; both callers must use
the standard parameter types when the shared local prototypes are removed.

## Retail evidence

The exact current bodies independently establish the call shape:

| Body | Boundary / size | `_mbscpy` call VA | `_mbscat` call VAs |
|---|---|---|---|
| `INI::getNextQuotedAsciiString` | `0x0002E93F..0x0002EA4F`, 272 bytes | `0x0042E99A` | `0x0042E9DA`, `0x0042E9E7` |
| `INI::getNextAsciiString` | `0x0002EA4F..0x0002EB38`, 233 bytes | `0x0042EA9F` | `0x0042EAD1`, `0x0042EADA` |

All six are five-byte E8 calls. The copy target at RVA `0x00629176` is
`FF25 D0A6BB00`, whose IAT slot `0x00BBA6D0` names `msvcr71.dll!_mbscpy`.
The append target at RVA `0x0062988C` is `FF25 E8A5BB00`, whose IAT slot
`0x00BBA5E8` names `msvcr71.dll!_mbscat`. These are observed retail bytes and
PE import identities, not names inferred only from the existing pins.

The native VS 2003 `mbstring.h` declares both as `unsigned char * __cdecl`
functions taking `unsigned char *` and `const unsigned char *`, qualified by
`_CRTIMP`. The old private prototypes used `char *` instead.

## Change and verification

Include `mbstring.h` with empty `_CRTIMP` for the observed thunk calls, then
restore the existing imported `_CRTIMP` configuration before the other CRT
headers. The six call sites explicitly reinterpret the same buffer/token
addresses as the standard unsigned-character pointer types. Their return
values remain unused. No bytes are copied differently, no wrapper or pin is
introduced, and no shared header, compiler flag, boundary or ledger row changes.

- Normal whole-file verification: 53/53 rows, 3,945 bytes, 54 string literals
  plus one empty reference, one float and nine named imports.
- Seven TU EH graphs are EXACT; the normal verifier resolves five renumbered
  funclet labels without a pin or row-label edit. Frozen-file check passes.
- Code identity: 168 references, 141 owner, 18 alias, seven EH and two fold
  bindings, zero wrong bindings. Data checking finds zero findings.
- Owning scoped Microsoft-header refresh removes only INI.cpp's queue row:
  two local prototypes become zero; zero failed classifications. Two deliberate
  `_CRTIMP` configuration occurrences remain. This closes this file's local
  Microsoft-declaration queue item, not its other linking prerequisites.
- Independent read-only review confirms all six thunk calls, pointer addresses
  and constness, the unused returns and restoration of the imported configuration
  for the other headers. No source, queue or ABI blocker was found.

Logs under `build/codex-cleanup-20261025/`:
`iteration21-mb-retail.log` and
`iteration21-mb-header-{build,eh,frozen,identity,data,ms}.log`.
Matching coverage and the census figures are unchanged; the separate batch-link
audit still needs Eva.cpp's strict include inventory and a current index.
