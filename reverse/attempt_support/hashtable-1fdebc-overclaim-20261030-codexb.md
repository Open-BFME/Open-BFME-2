# Duplicate hashtable assignment at 0x001FDEBC

Base: `150043baed`. Retire
`Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva001FDEBC.cpp`, its only
ledger row and its two unused clear/copy pins. This is duplicate-ownership
cleanup under LINK-060, following LINK-066's earlier instantiation cleanup.

## Target facts and identity boundary

Two matched rows claimed the same complete 31-byte range:

- `??4Rva000427195@@QAEAAU0@ABU0@@Z`, retained in
  `Code/GameEngine/Source/GameClient/Rva000427195Dtor.cpp`;
- the removed STLport hashtable assignment over `Rva001FDEBCRecord`.

The retained assignment tests self-assignment, calls the existing clear owner
at 0x003A2A41 (`Common/RTS/Team.cpp`), calls the existing 192-byte copy owner
at 0x001FDC0F (`Common/RTS/PlayerTemplate.cpp`), then returns its receiver.
Its complete bytes and relocations verify. The sweep emitted a different
opaque one-byte record's clear/copy bodies, both rejected by the ordinary
preview, and unresolved record copy/destructor names.

The sweep's comment explicitly calls its element spelling/layout donor
inference. Matching this assignment's shape does not prove that record's
identity or extent. No native element name or layout is recovered here.
The existing owner and its declarations are unchanged; later type recovery
and movement into the approved PlayerTemplate TU remain separate work.

## Verification and provider audit

- Before removal, `./build.sh` passes all 25 rows across the two assignment
  owners. Both frozen-file checks pass.
- Strict `link_check.py --prepare-current` passes all 194 rows and the owned
  data row across the retained owner, PlayerTemplate and Team. The sweep's
  separate strict preparation passes its one row.
- `eh_verify.py` reports 32 EXACT graphs across the three retained sources,
  with zero exceptions or missing objects.
- Ordinary paired previews before removal report all three retained sources
  LINKS: 795, 2,162 and 7,580 authored bytes. PlayerTemplate's existing
  since-census difference is unrelated to this change.
- All 17 current sweep COMDAT byte/relocation digests equal the census
  object's definitions. Raw object hashes differ; normalized COMDAT facts,
  rather than raw equality, establish the comparison.
- The census graph shows that removing the sweep removes 15 selected
  definitions, all specific to `Rva001FDEBCRecord`, with zero other object
  touching any of those names. The two shared placement-new/delete copies
  retain their selected provider `Common/RvaSmallVtableCtors.cpp`.
- A source search finds the record only in the removed source and its two
  pins. No remaining code names the removed assignment, clear or copy.
  The pins did not define native providers.

The scoped comparison uses index `12b9e7a7c0`, dated 2026-10-30 10:11
(embedded census `2c21184e84`). It establishes the stated provider scope,
not a new census or complete current consumer closure.
Local detailed selection receipt: `build/retire-1fdebc-codexb/provider-audit.json`.

## Path and debt audit

Audit range: `150043baed` to this staged change. The only source-path change
is the sweep deletion; no row moves or TU-map regeneration are performed.
The retained owner supplies exactly the removed range, so unique covered
bytes are unchanged. No other new ledger source is introduced.

Search the retired full path, basename and record token across active tools,
hooks, workflow/configuration files, source/includes and registries. No active
consumer needs updating. The only pre-existing full-path references outside
the removed function row are the scheduled census's historical
`reverse/link_status.csv` row and the linking checklist; the latter is
updated. Previous obstacle history is retained. The committed TU map already
selects the retained owner at this address and does not name the sweep.

The removed source has no gate, data, code-identity, header, Microsoft-header,
hatch, flag-override, data-owner or fold-proof register key to transfer or
retire. Its removed code row is explicitly tombstoned in `deleted_rows.csv`.
Pin counter retirement uses `hatch_counters.py --update`.

Final checks: `check_csv.py` passes with 99,013 function rows, 9,394 pins
and 2,239 data rows; `pin_consistency.py --check` passes with no new or
stale findings. `hatch_counters.py --staged` credits the pin total falling
from 9,396 to 9,394. Source files decrease by one; no measured linking or
image-ownership gain is claimed.

The outgoing `link_batch_audit.py` result is **INCONCLUSIVE**: its index
at `12b9e7a7c0` predates outgoing base `150043baed`, and the affected
consumer `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`
lacks a current receipt. This is not complete current consumer closure.
Carry that consumer and the removed-provider comparison into the next
scheduled census; the three tested provider units retain LINKS in preview.
