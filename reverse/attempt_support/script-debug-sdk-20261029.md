# ScriptEngine debug callback SDK declarations

Inspected 2026-10-29 at source base `5eb27ead8e`; the preceding local
ShipSlowDeath handoff `86b47366a6` changes no game source. Default selection
claimed setFrame, then the four adjacent files using the same declarations.

## Change and identity boundary

Each file now opts into the supported Platform SDK and includes windows.h
instead of redefining HMODULE as int and GetProcAddress as returning void*.
The existing `?st_DebugDLL@@3HA` global remains int in its defining appGate
unit and all consumers. Its identity is recorded in data_ledger.csv at
RVA 0x009FE158; changing it to HMODULE would change that named binding.
Integer handles are cast to the SDK HMODULE at the API boundary. The app gate
uses the SDK FARPROC return type before the existing callback casts.
No callback identity, global identity, source path or function row changes.

## Verification

All five files live under `Code/GameEngine/Source/GameLogic/ScriptEngine/`.
The table records pre-edit versus final strict-build object comparisons using
link_census.comdat_bodies and object_references. Every COMDAT fingerprint,
size and reference graph is identical.

| Source | Rows | Identical COMDATs | Preview authored bytes before/after |
| --- | ---: | ---: | ---: |
| ScriptEngine_setFrame.cpp | 2 | 4 | 162 / 162 |
| ScriptEngine_appGate.cpp | 2 | 5 | 134 / 134 |
| ScriptEngine_rva002047CF.cpp | 1 | 2 | 55 / 55 |
| ScriptEngine_setSides.cpp | 2 | 3 | 145 / 145 |
| ScriptEngine_updateClientDebugFrame.cpp | 1 | 2 | 55 / 55 |

Normal byte verification and `link_check.py --prepare-current` pass: 8/8
functions, two data rows, eight string literals, seven named import references.
Frozen-file checks pass before and after. allowed_symbols reports eight owner
references and zero wrong bindings. data_check --converged reports five sources,
eleven addresses, zero second names and zero unjudged rows. The Microsoft-header
auditor scans five files clean; its scoped refresh_queue API removes five queue
rows containing ten local declaration findings, preserving all unrelated rows.

Ordinary preview against index `85f6b7f40c` (2026-10-29 15:08) reports all five
units LINKS and retains 551 authored bytes. The index predates the source base.
The outgoing staged-tree batch audit exits 2, INCONCLUSIVE: older index and no
current receipt for `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`.
It is not consumer-wide verification. Carry that consumer and these five
providers into the next scheduled census. No census gain is claimed.
