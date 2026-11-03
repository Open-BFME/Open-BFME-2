### LINK-013: INI consolidation made a non-retail `set<AsciiString, BfmeStringNoCaseLess>::insert_unique` the kept copy

**Status: Cleared in the eight-unit ordinary preview; census pending. Updated: 2026-10-25; inspected revision: aa31e9bac4.**

- **Evidence / scope:** the census at f995f30157 lost the six units that call
  `_Rb_tree<AsciiString, …, BfmeStringNoCaseLess>::insert_unique` (row 0x0002C908, 153 B,
  owner `stlport_nocase_asciistring_set_insert.cpp`) to `wrong_selected`. Its index holds
  five copies:
  - non-retail (digest c5d4a74a154c): `INI.cpp` (object 576, first in link order since
    the INI merge) and `SidesListDataChunks.cpp` (object 2445)
  - retail (digest 46fbdb7211c9): `stlport_nocase_asciistring_set_insert.cpp`,
    `stlport_nocase_asciistring_set_touch.cpp` and `stlport_rb_tree_insert_unique_nocase.cpp`

  Before the merge a retail copy came first, so SidesList's copy was latent.
- **Completed:** both units declare the `insert_unique` specialization decl-only, so they
  emit no copy and bind the kept retail one. `./build.sh`: INI.cpp 39/39,
  SidesListDataChunks.cpp 91/91. `tools/link_check.py` against the f995f30157 index:
  - now LINK (0 -> 8,773 B predicted): SidesListDataChunks.cpp 6,726 B,
    Rva006047F3Family.cpp 1,659 B, the three WWLib owner units 388 B
  - INI.cpp itself still fails in that preview, on duplicate INI members (`~INI`,
    `INI::scanInt`, …) from `INI_ctor.obj` and `INI_scanInt.obj`. Those units were merged
    into INI.cpp after f995f30157, so these duplicates are stale-index artifacts, not this
    repair.
- **Historical guarded-input check (2026-10-26, `9e1ca7f93f`):**
  [the guarded INI check](../../reverse/attempt_support/ini-current-ledger-prerequisites-20261026.md)
  preserves all 39 rows (3,039 bytes) and five EXACT EH graphs. The published
  index remains `f995f30157`; ordinary preview retains 11 duplicate and eight
  selected findings. The supported current-ledger preview refuses before its
  link verdict because 11,481 providers lack current compiler evidence. This
  count is a strict currency prerequisite, not byte mismatches or a new source
  regression. No source edit, new linked-byte gain or false reject is claimed.
- **Current-provider verification:** the LINK-014 follow-up checks all eight
  insert_unique / _M_find units together and previews all 11,872 B clean,
  including INI.cpp. The historical duplicate-index and __lower_bound
  prerequisites below are cleared in that bounded check.
- **Approved-TU follow-up (2026-10-26, base `80732a72b7`):**
  [the INI consolidation](../../reverse/attempt_support/ini-approved-consolidation-20261026.md)
  absorbs six whole donors and preserves 52 rows / 3,837 bytes in the TU.
  Two prerequisite commits remove one unused alias and one stale marker.
  The two-source comparison cohort retains eight EXACT EH graphs, zero wrong
  code bindings and zero data findings. Before composition, current ordinary
  preview against the newer `763dc8759f` index accepts all eight original files
  (3,894 authored bytes); this confirms inherited repairs, not a new gain.
  After composition, that preview retains six duplicate and four selected
  findings naming absorbed definitions. Post-merge closure is not claimed;
  twelve remaining whole donors need declaration/codegen reconciliation.
  The next [lookup-parser repair](../../reverse/attempt_support/ini-lookup-clean-throw-20261026.md)
  replaces its artificial default exception/throw-info anchor with normal C++
  throws, preserving all 108 bytes and its clean 108-byte preview. A fresh
  approved composition at `468141e4c7` absorbs that donor unchanged: INI.cpp
  now verifies 53 rows / 3,945 bytes, with eight EXACT EH graphs and zero wrong
  bindings or data findings in the two-source cohort. Eleven donors remain
  blocked by declaration/view reconciliation. Ordinary preview now retains
  seven duplicate and five selected findings; the additional lookup owner is
  still the retired donor in the index. Post-merge closure remains unconfirmed.
  The transferred data catalogue retains its old unused throw-anchor spelling;
  this is a source-path transfer, not a new emitted anchor or ownership gain.
- **Publication proof (2026-10-26, `7d17532afb`):** the full normal gate passes
  all 98,252 function and 2,216 data rows. The bounded publication audit still
  stops on Eva.cpp's include-inventory prerequisite described in LINK-008;
  neither the seven-donor consolidation nor its stale-index diagnostics are
  upgraded to a full linking verdict.
- **Native integer-throw cleanup (2026-10-26, base `091dbc15da`):**
  [The byte parser](../../reverse/attempt_support/ini-byte-parser-clean-throw-20261026.md)
  replaces its manual runtime call and zero-filled anchor with `throw ERROR_BUG`.
  All 62 body bytes, all 53 TU rows, the cohort's eight EH graphs and 178 code
  bindings remain verified. Retail and compiled exception metadata agree on
  a four-byte `int`. Ordinary preview retains the same seven duplicate/five
  selected old-index findings, with no new unresolved reference or linking
  gain claimed.
  A separate follow-up removes five duplicate macro/prototype occurrences;
  the owning Microsoft-header queue reduces INI's local count from 13 to eight,
  retaining its CRT conflict classification and all 53 matched rows.
  The next separate cleanup replaces TRUE/FALSE with C++ boolean literals and
  uses the existing standard NULL definition: eight local occurrences become
  five function declarations, with all 53 rows and seven TU EH graphs exact.
  The new full build against the maintainer's pinned BFME 1 `ff391a5e90`
  also passes all 98,252 function and 2,216 data rows; it does not resolve the
  strict batch-link inventory prerequisite or confirm a new census gain.
  A further verified declaration cleanup uses the already included `string.h`
  for `strlen`/`_strcmpi` and adds `stdio.h` for `sscanf`: five local prototypes
  become two (`_mbscpy`/`_mbscat`), retaining all 53 rows and seven EH graphs.
  [Standard multibyte declarations](../../reverse/attempt_support/ini-multibyte-header-adoption-20261026.md)
  then replace the last two prototypes. Both readers' six native calls are
  verified against the named CRT import thunks; standard unsigned-character
  pointers and header-specific import configuration preserve all 53 rows,
  seven EH graphs and 168 code bindings. The owning scoped refresh removes
  INI.cpp's Microsoft-declaration queue item; the linking prerequisites remain.
- **Latest publication and rebase check (2026-10-26):**
  [The publication audit](../../reverse/attempt_support/ini-publication-current-provider-audit-20261026.md)
  records full byte/data verification at `f8aefae21a` and the completed,
  explicitly provisional 54-object shadow audit. No INI.cpp-specific cause
  was found in its reported possible losses; this does not establish full
  linking closure. After rebasing onto `b85e569cee`, INI.cpp is unchanged from
  the published source and the nine-source reconciliation cohort passes
  1,014 functions, 24 data rows and twelve EXACT EH graphs.
- **Historical remaining / next check:** the next census confirms the six units. INI.cpp's own link
  also depends on the separate `__lower_bound` provider repair.
- **Clearance:** preview scope only (five of six units against the f995f30157 index).
- **Census confirmation:** confirmed by the census at `73061d9452` (2026-10-27 14:34,
  `reverse/link_status.csv`): INI.cpp, SidesListDataChunks.cpp and the three nocase-set
  owner units (`stlport_nocase_asciistring_set_insert.cpp`, `..._set_touch.cpp`,
  `stlport_rb_tree_insert_unique_nocase.cpp`) are linked. Checked 2026-10-28 by seat
  halilkkaya-lk3; `Rva006047F3Family.cpp` no longer exists under that path.
