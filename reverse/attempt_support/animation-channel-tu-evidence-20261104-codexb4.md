# Animation-channel placeholder cleanup and TU evidence

Inspected `7e4a6b6204523bbc8872543930b6d9f63cfc02f8`, 2026-11-04.
Scope: `Code/GameEngine/Source/Common/Rva000B3B2B.cpp`,
`Rva000B3BA8.cpp` and `Rva000B3C61.cpp` in the same directory;
five matched rows at 0x000B3B2B, 0x000B3BA8, 0x000B3BCF,
0x000B3C61 and 0x000B3CCF (526 bytes).

## Verified cleanup

Retail VA 0x00BBB8D8 (RVA 0x007BB8D8) holds `00 00 80 3F`,
IEEE single-precision 1.0. Replace the external address-named float in
Rva000B3B2B's complement calculation with `1.0f`. This removes a private
external declaration without adding a global, pin or alias.

- `./build.sh` on all three original sources: 5/5 matched.
- `./build.sh Code/GameEngine/Source/Common/Rva000B3B2B.cpp` after
  replacement: 1/1 matched (125 bytes), one compiler float literal verified.
- `find_declared_unmatched.py` on the three sources: all defined functions
  already matched, both before and after the change.
- `hatch_counters.py --update`: address_global occurrences 3941 -> 3939;
  only this source's two-occurrence key removed.
- `link_check.py --fetch-index`: retained census 2026-11-04 02:25 at
  `5a13f2cd61`, imported 17,987 reusable compiled objects.
- `link_check.py --census-only` for Rva000B3B2B: LINKS, 125 -> 125 bytes.
- Current-object `link_check.py` for all three sources: 3/3 LINKS,
  526 -> 526 bytes. This is a preview, not a new census or a linking gain.
- No existing obstacle entry matched these source names, RVAs or the float's
  old spelling; no unresolved linking obstacle encountered in this scope.

## Placement remains unresolved

`tu_evidence.py --source Code/GameEngine/Source/Common/Rva000B3B2B.cpp`
returned only its header (no structural signal). The fresh
`name_lane.py consolidate --under Code/GameEngine/Source/Common/` report
has no TU candidate for any of these five rows. No TU assignment, source move,
name change or regenerated map is included.

Target facts: the nearest mapped row below is 0x000B3A80, proposed by N as
W3DScriptedModelDraw.cpp; the row above is 0x000B3D39, approved by S as
W3DModelDraw.cpp. These do not form an approved same-TU bracket.
The WorldBuilder pair records for 0x000B3BCF and 0x000B3C61 cite refcount.h
at score 2; those header paths do not identify the emitting game TU.

Donor facts: BFME 1's Rva00760660ChannelUpdate.cpp describes two 0x1c-byte
channel records at +0xdc/+0xf8 and calls analogous setter/reset helpers.
Its AnimationInfo0076EBE0.cpp also uses 0x1c-byte tracks. These are structural
leads only: those reconstructed paths and placeholder names do not prove
BFME 2 source identity or canonical method names.

Next useful placement check: recover an independent target file/name anchor
for these BFME-specific track helpers, or a firm bracket covering the run.
The current retail layouts and weak editor pairs do not justify a merge.
