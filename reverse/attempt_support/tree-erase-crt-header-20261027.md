# Tree-erase CRT declarations

Inspected revision: `90b5ece91e`, 2026-10-27. Claimed each edited source.

The Microsoft-header picker selected Rva002CF2D5Erase.cpp. The same bounded
change applies to Rva002CF302Erase.cpp, Rva002CF32FErase.cpp and
Rva002CFD61Erase.cpp, all under Code/Libraries/Source/WWVegas/WWLib/.
Each replaces its local `free` declaration with `<stdlib.h>`, keeping `/MD`
and adding `/D_CRTIMP=` to preserve the native direct-call ABI.

Target evidence, independently checked for each body:

| Row RVA | Bytes | `_free` REL32 offset | Native target RVA |
| --- | --- | --- | --- |
| 0x002CF2D5 | 45 | 0x1C | 0x00030830 |
| 0x002CF302 | 45 | 0x1C | 0x00030830 |
| 0x002CF32F | 45 | 0x1C | 0x00030830 |
| 0x002CFD61 | 53 | 0x24 | 0x00030830 |

The retail opcode is E8 at each call; signed displacement plus the instruction
end gives the target above. This is the game allocator, not the CRT IAT.
The VS2003 stdlib.h declaration is `_CRTIMP void __cdecl free(void *);`.
The flag removes only its import decoration in these TUs; no private prototype
or linker alias remains necessary.

Validation: normal `./build.sh` passes 4/4 rows (188 bytes), string, float and
import checks. `find_declared_unmatched.py` passes. `ms_header_audit.py show`
reports all four clean, removing four local Microsoft-header declarations.
Before/after COFF inspection confirms identical external defined/undefined
symbol sets and identical complete function bytes and relocation tuples.
The joint ordinary link preview reports 4/4 LINKS, 188 -> 188 authored bytes,
against index `73061d9452` (2026-10-27 14:34). No census gain is claimed.
The committed Microsoft-header queue is an older scan; it was not regenerated.

## Scoped queue retirement (2026-10-29)

Inspected revision: `36091192a6`. The default Microsoft-header picker still
served Rva002CF32FErase.cpp's obsolete local-free finding after the source
repair landed as `ae0a668f96`. The other three helpers retained identical
stale queue entries. All four source claims were acquired for this check.

Current `./build.sh` verification passes 4/4 rows (188 bytes), and the
frozen-file check passes. `ms_header_audit.py show` classifies all four
sources as clean. The auditor's `scan_files` and scoped `refresh_queue` API
remove exactly these four entries from `reverse/ms_header_queue.tsv`,
preserving every unrelated record. No source, ledger, pin or baseline changes.

Ordinary preview against index `85f6b7f40c` (2026-10-29 15:08) retains
4/4 LINKS and 188 -> 188 authored bytes. This retirement records the
earlier source repair in the queue; it adds no new census-linked bytes.

Before selecting this cleanup, two default linking candidates were reviewed
and released without source trials. stlport_LocaleWctomb.c still falls under
LINK-139's documented duplicate-provider prerequisite; no new preview was
run for it. Rva00566695Assign.cpp's current ordinary preview reproduces
LINK-064's two pair COMDAT failures and one wrong selected pair constructor
(0 -> 0 of 179 authored bytes against the same index). Its two-tree element
identity must still be reconciled across the provider/caller family.

## Initial linking lead released

The default picker first selected EvacuateDamageCtorModuleFactoryBody.cpp.
The current ordinary preview still reports U1/L2/S2 against the same index.
Its 0x0002CD7B row remains misidentified: the INIMacroTable lifetime reaches
the nocase tree at 0x0002CC38 and hashtable at 0x0002CCC3, not EvacuateDamage's
members. The TU map marks this row displaced, with no approved destination.
The existing LINK-006 prerequisite still applies: resolve the actual macro
table types and approved ownership before replacing the row and EH identity;
do not suppress the only providers. No source trial was made or retained,
and both the RVA and source claims were released before the header work.
