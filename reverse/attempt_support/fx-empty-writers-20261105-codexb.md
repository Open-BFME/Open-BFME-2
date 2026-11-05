# Exported FX header/footer writers

Baseline: `969171e019dd9917346d677f3b4218fdc3ef6b84`.
Source: `Code/GameEngine/Source/GameClient/Rva005613F9Write.cpp`.
Claim: `0x005613F9` and the source scope.

## Target facts and repair

Retail exports 1939, 1942, 1954 and 1959 all name the complete 35-byte
body at `0x005613F9`: respectively `FXParticleSystem::DefaultModuleTemplate<6>`,
`ButterflyDrawModuleTemplate`, `QuadDrawModuleTemplate` and
`StreakDrawModuleTemplate`, each with `void writeINI(File &, unsigned int) const`.
The existing placeholder row already matched the header/footer sequence.
These exported identities add no new covered address range. No donor is used.

Replace the placeholder with the first exported identity and emit the other
three writers in the existing source. `rename.py function --dry-run` refuses
the namespace/template/signature change as beyond an identifier rewrite, so
the canonical hand-rename path records a tombstone and a re_log verdict.
The three folded rows use `add_match.py --icf-owner` with this source as
fold proof. The limited class views only declare these out-of-line methods;
they make no object-layout claim. No source path, pin or alias pragma changes.

## Verification

- Original `./build.sh`: 1/1; final: 4/4 exact, including literal/import checks.
- All four emitted bodies equal the original object's complete bytes:
  `8d44240850ff74240851e8000000008d44241450ff742414e80000000083c414c20800`.
  Both REL32 relocations are identical: offset 11 to
  `?Rva0055C9A0WriteHeader@@YAXPBXPAVFile@@PAI@Z`, offset 25 to
  `?Rva003AFC6BWrite@@YAXPAVFile@@PAI@Z`.
- External-definition comparison: four added exported names; the only removed
  definition is `?rva005613F9@Rva005613F9@@QAEXPAVFile@@I@Z`.
  Before the edit, only the original object contained that name; afterward an
  all-object binary symbol-name scan finds it in none of 24,966 objects under
  `build/match/`. The index's touches also list only the original source.
- All four exported names have no prior strong or COMDAT provider in local
  index `112a456a2c` (2026-11-05 15:52; underlying census `c2a9f8e0d7`).
  Fetch-index kept this newer local index and imported the published objects.
- `link_check.py` on the source: LINKS, 35 -> 35 authored bytes. This is a
  scoped preview, not a real link or a new census.
- `find_declared_unmatched.py`: all defined functions matched;
  `check_csv.py` and `git diff --check` pass.

The next automated real link must confirm these four exports leave its errors.
Other folded exports in LINK-583 remain open; no game-running result is claimed.
