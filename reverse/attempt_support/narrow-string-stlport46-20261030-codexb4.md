# Narrow-string STLport 4.6 migration

Inspected base: `40e30bd124` (2026-10-30). The default picker claimed
`Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_string.cpp` for whole-file
migration. BFME 1 freshness was already verified on 2026-10-29 at donor
`b53c85e7f9d65a7f636271a06e9d0ce2ed2deabb`; no reference update here.

## Target facts and change

The file owns eight existing rows, 397 ledger bytes. Its unchanged 4.5.3
control passes 8/8. The earlier blocked attempt at 0x0001C680 stopped at
C2244 on the proxy allocate specialization. The recent ostringstream
constructor migration provides a supported lead: 4.6 inherits allocation
from allocator rather than defining the old proxy member.

The TU now selects the supported 4.6 header/patch layer. Removing the old
allocate declaration reveals the analogous inherited deallocate compile
boundary for this TU's custom allocator; removing both declarations makes
all eight rows exact. The recovered static byte allocator and direct game
free calls remain as before. No shared headers, source paths, row names,
addresses, extents, pins or debt registers change. The source comment names
the actual release; retail-version evidence remains the vendor provenance.

All eight rows gain `migrated=stlport-4.6` through add_match --replace-existing.
For the two existing folded-address rows, the tool's --icf-owner check names
the already rowed empty StringBase method and const-range append twin;
no new duplicate body, ownership claim or fold metadata is introduced.

## Verification

- Whole-file normal build: 8/8 rows, three named imports; frozen-file check
  reports all definitions matched. The owning migration queue no longer
  serves this file. check_csv and diff whitespace checks pass.
- Before/after external COMDAT comparison: 31 -> 30, no additions and no
  retained name/digest/size changes. The sole removal is `string::npos`.
  Defined externals lose only that constant; undefined names, weak external
  bindings, alternates and forced includes are identical. The saved index
  has 389 equal-digest npos copies, a baseline observation rather than a
  current full-image provider proof.
- Final strict current preparation: 51/51 rows across narrow_string,
  narrow_string_append, float_format, narrow_ostringstream_dtor,
  narrow_stringbuf_overflow_setbuf and narrow_ios_imbue. Five float references
  and 22 named imports verify; EH is EXACT 2. Existing renumbered funclet
  labels resolve through their parents' exact EH graphs.
- Ordinary joint preview against index `12b9e7a7c0`, 2026-10-30 10:11:
  6/6 LINKS, 4,529 -> 4,529 authored bytes. Respective source counts are
  396, 254, 2,619, 418, 567 and 275. Existing unreferenced helper diagnostics
  remain. The migrated TU had no emitted legacy proxy helper to retire;
  LINK-140's wider provider/consumer prerequisites remain separate.

## Publication boundary

The outgoing staged-tree audit includes pending commits as well as this
migration. Against origin base `6e3f45976c7c2f76725ca2910c37a76032b993cc`
and staged tree `91fc4b26523b0ff658b589d302d32fbc9fbf40a6`, it exits 2:
the index predates the base and 48 affected sources lack current receipts,
first `Code/GameEngine/Source/Common/BfmeConv1456.cpp`.
Full affected-consumer selection and loss verification remains unverified;
carry this provider, the removed npos copy and affected consumers into the
next scheduled census/current-receipt audit. No census, image-ownership or
debt improvement is claimed. The existing local CRT declaration finding
remains in the Microsoft-header queue.

Scratch objects, comparison JSON and verification logs are under
`build/narrow-string46-codexb4/`.
