# CreateAHeroManager accessor header adoption

Date: 2026-11-05. Inspected base: `932ccdf03d559f61a88caf6040efd982adfa2880`.
Owner: yasinschroeder-codexb2.

Three units replace their private CreateAHeroManager declarations with the
registered `Code/GameEngine/Include/GameLogic/CreateAHeroManager.h`. The shared
header and its storage/layout contract are unchanged. Existing accessor views
are cast over that header's opaque member storage, rather than introducing
another class definition. No function identity, source path, pin, alias or
ledger owner changes.

| Source under Common/ | Retail RVA | Bytes | Header storage used |
| --- | --- | --- | --- |
| CreateAHeroManagerHeroList.cpp | 0x0021F797 | 16 | field174 at +0x174 |
| CreateAHeroManager_GetBlingBinder.cpp | 0x0021A106 | 46 | field168 at +0x168 |
| CreateAHeroManager_GetDefaultHero.cpp | 0x0021A6C8 | 96 | field174 at +0x174 |

Target facts: the existing verified bodies address the binder-vector storage
at +0x168 and hero-list storage at +0x174. These are the offsets the canonical
header already declares. The casts preserve the existing operand types and
do not infer a complete original container type from those accesses.

The automatic adoption refused HeroList because its old four-byte placeholder
member did not match the canonical sixteen-byte storage extent. The manual
change accesses the existing storage without reducing that extent. The other
two similarly keep the canonical storage and retain their existing operand views.

Verification:

- Normal scoped `./build.sh` verification passes each complete body (3/3,
  158 bytes); frozen-file checks report all definitions matched.
- A temporary pointer local in GetBlingBinder changed MSVC register allocation.
  Keeping the view casts at the existing force-inline helper calls restores the
  complete retail body; no failed body remains.
- Owning `header_adopt_lane.py accept --class CreateAHeroManager` passes all
  three units and retires exactly their three rows in reverse/header_queue.tsv.
- Combined ordinary preview, published index c95fcfcfcd (2026-11-05 05:17):
  all three LINKS, preserving 16 + 46 + 96 = 158 authored bytes. This is
  bounded preview preservation, not a new census measurement or headline gain.
- Search of the data/code-identity baselines finds no keys for these sources.
  No protected register debt is discarded; only the owning tool retires header debt.
- `git diff --check` passes.

The other CreateAHeroManager consumers retain their existing queue entries;
nested class/container types and lifetime views remain separate work. No broad
class clearance or whole-game build/runtime result is claimed.
