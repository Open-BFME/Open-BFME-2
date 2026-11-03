### LINK-139: STLport 4.6 locale facets unit re-defines the hand c_locale units (2026-10-29, seat yasinschroeder-claudeb2)

Status: open; no source change. The 2026-10-29 17:26 census (5dc66f1a29 at
85f6b7f40c) drops ten locale units from linked to not linked:
`stlport_LocaleFacets.cpp` (16 duplicates), `stlport_LocaleCodePageQueries.c`
(3), `stlport_LocaleCtypeCase.c`, `stlport_LocaleStrcmp.c`,
`stlport_LocaleMbtowc.c`, `stlport_LocaleWctomb.c`,
`stlport_LocaleTranslateToSystem.c`, `LocaleComposeName.c`,
`Rva0084D890CodePointConversions.c`, `Code/Libraries/Source/STLport/LocaleUnshiftStrwcmp.c`
and `Code/stlport/LocaleTimeDestroy.c`. Cause (structural, from source):
e39aeab6dd moved `stlport_LocaleFacets.cpp` onto 4.6, and it now
`#include`s the whole vendor `src/c_locale_win32/c_locale_win32.c` under
`_STLP_REAL_LOCALE_IMPLEMENTED`, which `stlport_prefix.h` defines for Win32.
That one object therefore defines every external `_Locale_*` worker that the
hand units also define (`_Locale_strcmp`, `_Locale_mbtowc`, `_Locale_wctomb`,
`_Locale_toupper/tolower`, `_Locale_ctype_default`, `_Locale_common_default`,
`_Locale_ctype_name`, `_Locale_compose_name`, `_Locale_extract_*_name`,
`_Locale_btowc/wctob/wchar_toupper/strwxfrm`, `_Locale_strwcmp`,
`_Locale_unshift`, `_Locale_time_destroy`, ...). The duplicates appear on
both sides. Adding `// stlport46` to the hand `.c` units does not change their
objects (scratch: identical bytes under 4.5.3 and 4.6).
Target fact: the rows 0x20500-0x23650 are contiguous in retail .text,
consistent with one c_locale object. `reverse/tu_map.csv` approves no TU for
any of them (`tu` empty, e.g. 0x215B0, 0x21320, 0x22E00), so the rows cannot
be repointed into the facets unit.
Prerequisites (pick one): (a) a TU approval for the vendored c_locale_win32
range (L route), then `tu_skeleton.py --merge` the hand units into it, after
checking that the vendor bodies byte-match those rows; or (b) the 4.6 facets
unit compiles only its own 20 rows' functions again. Pass test: the next
census shows these units linked=yes with zero duplicates.

LINK-139 repair follow-up (2026-10-29, base d375abbc4f): the facets adapter
now opts out of exactly the 16 public definitions owned by the split locale
units. It also restores the existing external category table required by
LocaleComposeName.c. All 53 rows across ten units byte-verify, and all ten
preview LINKS for 11,083 authored bytes against 85f6b7f40c. This clears the
reported duplicate scope in the preview; scheduled census confirmation and
full consumer verification remain pending. Other providers stay emitted; no
TU move or new name is claimed. [Evidence and checks](../../reverse/attempt_support/locale-split-providers-20261029-codexb.md). The outgoing audit is INCONCLUSIVE: the index predates the base and
0CreateAHeroManager21FE49.cpp lacks a current consumer receipt. Carry the
changed provider and affected consumers into the next scheduled census.
Re-checked 2026-10-29 (seat dd-20) at base 36cc3221c3 against index 85f6b7f40c:
unchanged, no source change. `link_check` still reports the pair for
`Code/Libraries/Source/STLport/LocaleUnshiftStrwcmp.c` (`__Locale_unshift` and
`__Locale_strwcmp`) and for `stlport_LocaleWctomb.c` (`__Locale_wctomb`); the
facets object is the other definer of each, with the same COMDAT digest and
retail bytes, so this is ownership, not a byte difference. Option (b) cannot be
done from our side: the facets TU's definitions come from the pristine vendored
`c_locale_win32.c` include, and renaming them away would emit unrowed bodies;
`selectany`/`/Gy` are refused hatches. The rows' `tu_map` entries are still
empty (0x00020D50, 0x00020DB0, 0x00020DF0), so (a) remains the only path and
still needs the TU approval. Pass test unchanged.

LINK-139 selection recheck (2026-10-30, base 0fa815229e): the link picker
still serves `stlport_LocaleWctomb.c` from the pre-repair census. A current
two-source `link_check.py` preview with `stlport_LocaleFacets.cpp` reports
both LINKS (6,205 authored bytes) against index 85f6b7f40c. This confirms
the existing repair for this pair; no new linking gain or census result is
claimed. The full consumer and scheduled-census prerequisites above remain.
