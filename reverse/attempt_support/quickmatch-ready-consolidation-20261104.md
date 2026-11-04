# Quick-match readiness consolidation, 2026-11-04

Inspected revision: `9b9e537438`; owner: `yasinschroeder-codex`.
Scope: approved `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineQuickMatch.cpp`.

The consolidation planner was regenerated with `name_lane.py consolidate --under
Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/`. The merge engine rebuilt
the stale TU map in memory: 107 approved rows, seven whole-file donors and four
mixed files. No TU assignment was changed; the committed map diff only repoints
the readiness row's source column.

The initial merge failed because the seed declared `Rva005BA3AD` without its
schema member. `tu_views.py --class Rva005BA3AD --no-merge-check` reconciled the
seed, readiness and OnMatched views after giving the two incomplete views the
existing complete `PortNegotiationSchema` declaration. All 75 rows across those
three files passed `./build.sh`. These are target-derived private views, not
recovered retail class identities.

The readiness fragment then compiled but failed byte verification under the
seed's `/vmg /vmm` flags. Keeping its existing `Rva005A6709` declaration explicitly
`__single_inheritance` preserves the member-pointer representation without
changing the body. The isolated fragment passed 1/1; the composed trial passed
39/39. `tu_skeleton.py --merge ... --dry-run` accepted the seed and readiness
fragment, and its link guard accepted their composition against census-linked
inputs. Applying the saved plan removed one source file and repointed its one
19-byte row at `0x005BA3AD` into the approved TU.

Verification after the move:

- `./build.sh` destination: 39/39 matched; six string references, two float
  literals and four imports verified; 18 funclet rows verified.
- `find_declared_unmatched.py`: all definitions already matched.
- `check_csv.py`: valid, 99,440 function rows.
- `link_check.py` destination: LINKS, 2,864 own bytes, using census
  `2026-11-04 07:28` at `a62ac1c10b`. Its three allocator/vector diagnostics
  have equal bytes and differing relocations, are unreferenced and are not
  blockers. This is a preview, not a census gain; the extra 19 destination
  bytes already belonged to the removed fragment.

Path/debt audit covers the pending range `origin/master..9b9e537438` plus this
move. There are no other pending source-path moves. A repository-wide search
for `AptOnlineQuickMatchReady` found only the source provenance comment,
historical `reverse/re_attempts.log` and published `reverse/link_status.csv`.
No active tool, include, build rule or fold proof depends on the removed path.
The moved source has no code-identity, data, gate, hatch or header-queue keys.
The destination's MS-header queue was refreshed by the merge tool with identical
content; its order-only change was discarded. The tool's global hatch refresh
also removed ten stale entries in unrelated AIUpdate/W3DVideoBuffer files;
those unrelated changes were discarded. No debt retirement or alias removal is
claimed. Provider/consumer preservation passed the merge link guard; the normal
outgoing batch audit remains the publication check.

Remaining rejected whole-file donors, unchanged by this merge:

- `LadderPrefCopy.cpp`: `LadderPref` declaration visibility/order (C2061).
- `Rva005BA6EEPopulate.cpp`: `QuickMatchPreferences` visibility at `m_prefs`
  (C2146).
- `AptOnlineQuickMatchConstructor.cpp`: duplicate `FunctorMethod` (C2086).
- `AptOnlineQuickMatchOptions_OnMatched.cpp`: differing `GameSpyStagingRoom`
  views, first missing member `inProgress` (C2039).
- `QuickMatchPopulateSideComboBoxRva005BB3A1.cpp`: early declaration ordering
  (C2143).

Reconcile each donor's private declarations in a separate verified change before
the next merge. Header-adoption prerequisites printed by the merge tool remain;
the four mixed sources require their approved splits before whole-file merging.
