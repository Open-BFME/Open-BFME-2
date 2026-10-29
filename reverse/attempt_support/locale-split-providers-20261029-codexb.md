# STLport locale provider repair (2026-10-29)

Base: `d375abbc4ff2a666545684be56ed931bd50de4bf`. Claim owner: `yasinschroeder-codexb`.
Selected boundary: `__Locale_time_destroy`, RVA 0x000205A0, 122 bytes.
Provider scope: `Code/Libraries/Source/WWVegas/WWLib/stlport_LocaleFacets.cpp`
and `vendor/stlport-4.6-bfme/_c_locale_win32.c.patch`. Related obstacle: LINK-139.

## Evidence and change

The published index at 85f6b7f40c (2026-10-29 15:08 index timestamp) and
current facets object reproduce all 16 duplicate worker definitions. The
pre-migration source at e39aeab6dd^ defines the existing external
`__category_name[6]`; `reverse/data_ledger.csv` still assigns its 24 bytes at
RVA 0x009A7190 to the facets source. LocaleComposeName.c references it.
The migrated vendor implementation instead supplies private `__loc_categories`.
These are current source/provider facts, not a new upstream-name claim.

The facets adapter opts into `_BFME_LOCALE_SPLIT_PROVIDERS`. Exact-context
patches suppress only the 16 competing public workers; their existing split
owners remain. Other external workers stay emitted, including providers without
ledger rows. The adapter declares the existing `_Locale_common_default` worker
because the upstream header does not declare that internal shared helper.
The overlay restores the single external category table under its existing
identity and directs its extractor to the same table. The pristine STLport 4.6
release, function ledger, source paths, pins and hatches are unchanged.

Comparing object definitions against the index removes exactly the 16 duplicate
functions plus six no-longer-used category-prefix string COMDATs, and adds only
`___category_name`. The corresponding literals remain owned by LocaleComposeName.
No unique function provider is removed.

## Verification

- `find_declared_unmatched.py` passes before and after the facets edit.
- `./build.sh` over the ten locale units: **53/53 rows**, 45 literals,
  five empty-string references and 178 named imports exact.
- Facets alone: **20/20 rows**, 13 literals and 118 imports exact.
- `link_check.py` with all ten current objects: **10/10 LINKS**, 0 to
  **11,083 authored bytes**, against index 85f6b7f40c. This is a preview,
  not a new census or a change to headline LINKED.
- The overlay pytest suite reports **17 passed, 2 failed**. Both failures
  are existing `test_marker_changes_only_opted_in_commands` path assertions:
  they expect a POSIX vendor path inside Wine's Windows-form INCLUDE value.
  Running the same suite with the original committed patches in an isolated
  scratch directory reproduces the same two failures. No test/check is changed.
- The staged header dependency scan reaches 1,321 ledger sources because the
  overlay hash participates in every opted-in compiler command. The commit hook
  must verify this whole dependency scope.

## Checked locale units

- `Code/Libraries/Source/STLport/LocaleUnshiftStrwcmp.c`
- `Code/Libraries/Source/WWVegas/WWLib/LocaleComposeName.c`
- `Code/Libraries/Source/WWVegas/WWLib/Rva0084D890CodePointConversions.c`
- `Code/Libraries/Source/WWVegas/WWLib/stlport_LocaleCodePageQueries.c`
- `Code/Libraries/Source/WWVegas/WWLib/stlport_LocaleCtypeCase.c`
- `Code/Libraries/Source/WWVegas/WWLib/stlport_LocaleFacets.cpp`
- `Code/Libraries/Source/WWVegas/WWLib/stlport_LocaleMbtowc.c`
- `Code/Libraries/Source/WWVegas/WWLib/stlport_LocaleStrcmp.c`
- `Code/Libraries/Source/WWVegas/WWLib/stlport_LocaleWctomb.c`
- `Code/stlport/LocaleTimeDestroy.c`

## Remaining verification

The next scheduled census must confirm the locale repair and current consumer
bindings. No direct census, game link cycle or smoke runner was started.
Strict preparation of all ten explicit providers passes (53/53 rows) and
produces reusable receipts. The outgoing batch audit remains INCONCLUSIVE:
index 85f6b7f40c predates the base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry the changed facets provider and its consumer scope into the
next scheduled census. This limitation is separate from the ten-unit preview.
Publication runs the mandatory 1,321-source dependency gate.
