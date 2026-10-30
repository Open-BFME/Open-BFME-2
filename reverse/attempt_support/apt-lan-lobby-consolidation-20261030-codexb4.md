# AptLanLobby declaration prerequisite (2026-10-30, codexb4)

Base: `84887c9bc0`. Scope claimed through the default consolidation picker:
AptLanLobby.cpp, the four adjacent whole-file donors and Common/Rva004442FD.cpp.
The supported naming planner was generated under
`build/consolidation/aptlan-codexb4`; original-path hints do not prove a BFME 2
source path. The supported merge rebuilds current TU approvals in memory.

## Declaration repair

The initial merge dry run rejected all five donors at compilation.
Common/Rva004442FD.cpp needs fields absent from the seed's method-only class
view. Copying its complete class declarations into that seed adds no function
body or binding. Neither class is in the canonical-class register.

`./build.sh` verifies all 47 rows across seed and donor; the seed's eight EH
graphs remain exact. The seed object's 116 normalized COMDAT fingerprints,
225 external bindings and one weak binding equal the saved original object.
`find_declared_unmatched.py` is clean. No debt is retired and no census gain
is claimed.

## Remaining donors

- GetValidSelectedGameInfo uses `m_listboxGames` where the seed uses
  `m_customGamesList` at the same offset; reconcile the views before merging.
- MPOwnerValidatGameInfo disagrees with the seed's first virtual slot.
- GameCreate lacks seed declarations including Cancel and has further class
  conflicts (GameEngine, GameTextInterface, LANAPI and callback return type).
- GamesListTooltip needs GameInfo/GameSlot method and layout reconciliation,
  plus a LANAPI ValidateGameInfo declaration.
- Nine mixed files remain separate; this pass does not move their rows.

These are existing composition prerequisites, not lost matched rows. The
initial trial and tu_views plans are in `build/aptlan-dryrun-codexb4.txt` and
`build/aptlan-views-codexb4.txt` respectively. Carry moved-provider selection
and affected consumers into the next scheduled census.
