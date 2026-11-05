# LivingWorldBuildPlot method consumers adopt the canonical header

Base: `240fe9bd60`, 2026-11-05. Class and both modified source scopes claimed.

The canonical header already proves the 0x38-byte object and four-byte owners
at +0x20/+0x24. This change replaces private LivingWorldBuildPlot declarations
in LivingWorldBuildPlot.cpp and LivingWorldBuildPlotDoXfer.cpp with that header.
The existing setter call keeps its Rva00575674 receiver through a local cast;
storage and cleanup use the canonical Rva000AD6F4 fields. The icon-template
read keeps the existing local pointee view. No shared header, pin, ledger
identity, vtable provider or alias is added or changed.

Checks:

- `./build.sh` for the two sources: 22/22 rows match, eight renumbered
  funclet bindings verified through parent EH data; string/float/import checks
  pass. `find_declared_unmatched.py`: all definitions matched.
- One combined `header_adopt_lane.py accept --class LivingWorldBuildPlot`
  passes both sources and retires exactly their two header-queue rows.
- Ordinary combined `link_check.py`: 676 -> 676 and 657 -> 657 census-linked
  bytes, both LINKS against census 2026-11-05 15:19 at `f44cbcf5b0`.
  This is a preview, not a real-link or game-running result.
- Rebuilt original sources through `./build.sh`, saved their objects under
  build/codex2-livingworld/, restored the edited sources and rebuilt 22/22.
  `link_census.object_symbols`: seed 12 -> 12 external definitions; transfer
  8 -> 6. Both objects keep identical external-reference sets, weak externals,
  /alternatename maps and /INCLUDE directives. All 18 retained external
  COMDATs have identical byte/relocation digests (`comdat_bodies`).
- The two removed definitions are getRegionID/getBuildingID const accessors
  on LivingWorldBuildPlot; equivalent local inline helpers serve this TU.
  `rg -a -l --hidden --no-ignore --glob '*.obj'` across all 39,439 cached
  objects under build/ finds their spellings only in the saved original
  transfer object. Neither appears in reverse/exports.csv, functions.csv,
  symbols.csv or Code/. Thus no other cached object imports either name,
  including through an /alternatename directive. There is no removed alias.

Five other class-queue rows remain. The earlier full-cohort attempt is recorded
in livingworldbuildplot-header-20261104-codex.md: destructor/constructor
virtual-slot providers, the deleting-destructor emission constructor and
coordinated class-key callers remain separate prerequisites. They were not
retried without new evidence. This clears only the two method-consumer
private-view prerequisites; it does not clear the class's lifetime providers
or change a census headline.
