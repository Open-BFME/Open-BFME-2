# LINK-602: particle factory export signature at 0x003AD6DF

Inspected source revision: `76e283b80e65eeb2dc443dca8788358f26a4c034`. Census index: `f44cbcf5b0`,
`2026-11-05 15:19` UTC. This is an export-identity repair, not a new match.

Retail fact: `reverse/exports.csv` ordinal 1530 names the factory at RVA
`0x003AD6DF` with a global `TrackingPtr<FXParticleSystem::ParticleSystem>`.
The existing C++ and ledger put that template inside `FXParticleSystem`,
emitting a different mangled symbol. The indexed object provides only that
incorrect name; neither the index's strong nor COMDAT providers has the export.

Old symbol:
```
?createModule@?$ConcreteModuleTemplate@V?$DefaultModuleTag@$05@FXParticleSystem@@@FXParticleSystem@@UAEPAV?$DefaultModule@$05@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@2@@Z
```
Correct export:
```
?createModule@?$ConcreteModuleTemplate@V?$DefaultModuleTag@$05@FXParticleSystem@@@FXParticleSystem@@UAEPAV?$DefaultModule@$05@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
```

Changed `Code/GameEngine/Source/GameClient/System/FXParticleSystem/Rva003AD6DFCreate.cpp` to forward-declare the global template, corrected its existing
row in place, and tombstoned the old spelling. `rename.py function --dry-run`
refused this signature-only correction with `the new name is the old name`;
the function identifier itself is unchanged. No pin or alias was added.

Before editing, scanned **26,379** `.obj` files under `build/match/`.
The only exact-symbol hit was this factory's definition. COFF external refs,
weak defaults, `/alternatename` and `/INCLUDE` checks found no user of the old
symbol. The index's touches agree: only this factory object touches it.
No link-wide compatibility definition needs preserving.

Validation:

- Original picker unit `ModuleTemplateFactorySlots.cpp`: 27/27 byte matches.
- Factory before and after: 1/1 byte match, 60 bytes; literals/import checks pass.
- Current factory object defines the exact export above and no longer defines
  the old symbol. Object SHA-256: `8e1d3997d5516826cdd49bcfc00570da7c155a15969eb233d6c1b2c3c1f50e92`.
- `find_declared_unmatched.py`: all defined functions matched.
- `check_csv.py`: passes, unchanged 99,481 function rows.
- Combined `link_check.py` preview: both the factory and picker unit link
  cleanly, retaining 60 and 1,363 own bytes respectively. This is a census
  prediction, separate from the missing real-link export proof above.

The factory body already existed at the correct address; this repairs its
export signature and adds no byte-match or census credit. Remaining particle
factory exports owned by `ModuleTemplateFactorySlots.cpp` retain their existing
placeholder identities. A new real link must confirm removal of this export
from its error list; no image, smoke result or full-link improvement is claimed.
