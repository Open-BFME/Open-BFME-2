# W3DBuffDraw module-data composition

Inspected base: `a861e89a4c`. Claimed scope: W3DBuffDraw.cpp,
W3DBuffDrawConstructor.cpp and W3DBuffDrawModuleDataCtor.cpp under
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/`.

The supported naming planner surveyed that directory. Its original-path
catalogue does not independently route these rows: it labels these files
unresolved and flags the existing data owners and include context. Placement
approval comes from tu_skeleton's freshly rebuilt in-memory TU map: eleven
approved rows, two whole donors and the mixed W3DDrawNameGetters.cpp file.
No regenerated map is committed. No donor path is claimed as target evidence.

The initial supported merge rejects both donors. The draw constructor has a
DrawModule base absent from the seed's partial W3DBuffDraw view. The module-data
constructor declares its vtable as an external raw array, conflicting with the
seed's polymorphic class. tu_views independently reports both conflicts.

## Module-data prerequisite

Reuse the seed's existing eight-byte polymorphic base, AsciiString at +8 and
flag at +12 in the constructor donor. Ordinary member initialization replaces
the explicit vtable store, intrinsic barrier and raw-word clearing. The seed
gains only the constructor and static parser declarations. This retains the
existing partial base contract; it does not establish a complete retail table.

Target facts: the complete constructor at RVA 0x000CEE4C is 17 bytes, the
destructor at 0x000CEE5D is 54 bytes and the parser at 0x000CEE93 is 17 bytes.
The existing field table has ModelName at +8 and PreDraw at +12; the rowed
factory at 0x00064C94 allocates sixteen bytes. The compiler reports the same
sixteen-byte class and field offsets in both reconciled sources. Existing
destruction releases the +8 string through native 0x00036410. No name,
boundary, pin, global identity or compiler profile changes.

Checks:

- Normal and strict reusable preparation pass all eight rows and the 48-byte
  data row across the seed and module-data donor. Both EH graphs remain EXACT.
  The initial three-source build passes 9/9 rows.
- Every existing external COMDAT byte-and-relocation digest is unchanged:
  nine seed copies and four constructor/parser copies. The input union grows
  from thirteen to fifteen only through the implicit AsciiString and partial
  base constructors. The donor now emits six other copies already in the seed;
  all agree. The vtable becomes locally defined and the donor references the
  existing destructor; no existing definition disappears. Scratch objects and
  detailed comparisons are in build/w3dbuffdraw-consolidation-20261030-codexb4/.
- Frozen-file and class gates pass. The owning Microsoft-header analysis finds
  both files clean; neither has a class-header or Microsoft-header queue row.
  Shadow data checks find zero findings; converged checks judge eleven addresses
  with no second names or unjudged rows. No debt register is retired.
- Census-only and ordinary paired previews both retain 2/2 LINKS and 205
  authored bytes against index 12b9e7a7c0 (2026-10-30 10:11).
- The supported merge probe now accepts the module-data donor and preserves
  eight rows. The draw constructor still needs inheritance/interface recovery;
  the mixed name-getter file and generated unwind owner stay separate.

The staged-tree outgoing audit is INCONCLUSIVE: its index is at 12b9e7a7c0,
older than this base, and the affected consumer
Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp lacks a current
receipt. Carry these providers and affected consumers into the next scheduled
census/current-receipt audit. Full selection/loss verification remains open.
No measured linking or image-ownership gain is claimed.
