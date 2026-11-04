# GameSpy miscellaneous-preferences consumers adopt canonical headers

Base: `63a90856f8`. Ordinary link preview uses the census from
2026-11-04 20:47 at `f12552d0a7`.

`AptOnlineLoginLocale.cpp`, `AptOnlineShellScreens.cpp` and
`Thread/PeerThreadPushStatsBfme.cpp` now include the existing
`GameSpyMiscPreferencesClass.h` instead of private declarations. The two Apt
consumers also remove their private `UserPreferences` bases; the canonical
parent is included explicitly as well. The two files enable the existing STLport
include environment required by `UserPreferences.h`'s map. The shell's existing
vector view is unchanged.

Target/compiler facts: the canonical headers already document the native
0x14-byte complete preferences object, its map/string base and virtual table.
The discarded private padding fields have no accesses in these consumers.
Their constructor, destructor and preference-method calls retain their existing
bindings. This adopts established class contracts; it adds no recovered name,
layout claim or donor-source attribution.

Verification before and after:

- Ordinary `./build.sh` over the three sources: 27/27 function rows and both
  data rows match; string, float and import checks pass. Existing EH-label
  renumbering is verified through the parent exception graphs.
- `find_declared_unmatched.py` passes each source.
- External-symbol sets and relocation-aware COMDAT digests are identical,
  compared using `tu_views.coff_externals` and `link_census.comdat_bodies` on
  ordinary build objects: locale 17 symbols / 3 bodies, shell 53 / 24,
  statistics publisher 33 / 3.
- `header_adopt_lane.py accept --class GameSpyMiscPreferences` passes each
  consumer and retires its three queue rows through the owning tool.
- `header_adopt_lane.py accept --class UserPreferences` passes the two Apt
  consumers and retires their two queue rows through the owning tool. All five
  debt rows are removed only by successful acceptance.
- Ordinary `link_check.py` predicts LINKS for all three: locale 202 -> 202,
  shell 988 -> 988, statistics publisher 666 -> 666 authored bytes. The
  combined 1,856 -> 1,856 result is a scoped prediction, not a new census or
  real-link measurement.

No source paths, function ledger rows, pins, aliases, hatches or data/code-
identity keys move. Obstacle-register searches found the previously completed
statistics-core and GameSpyInfoInterface adoptions in this consumer; neither
contract nor its recorded next step changes here.
