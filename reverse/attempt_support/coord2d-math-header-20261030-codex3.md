# Coord2D math header adoption, 2026-10-30

Base: `a5f5309dbd`. The default picker selected the Coord2D adoption queue.
The registered plain layout lacks the constructors, destructor, base conversions
and arithmetic declarations implemented by the existing 44-row coord2d.cpp.
Its earlier attempt correctly identified that missing contract (LINK-098).

The canonical header now has an explicit COORD2D_VIEW_MATH declaration view.
It carries the same existing Coord2DBase inheritance and complete member
surface from coord2d.cpp, plus the two already declared separate rotation
members. The math implementation selects this view after its existing base
record declarations and removes its private Coord2D class body. Other users
keep the existing plain header view or the existing constructor companion.
This transfers an existing target reconstruction's declaration; it establishes
no new donor identity, source path, class layout or method name. No body,
ledger identity, pin, compiler flag or data definition changes.

Checks:

- find_declared_unmatched passes for both changed files; the existing
  inline anchor remains honestly marked absent from retail.
- Normal byte verification passes 44/44 rows. Strict preparation passes 46/46
  across the math unit and its rotation companion, including three literals
  and eleven compiler float references. Neither unit has an EH-data row.
- All 60 external COMDAT fingerprints, 37 strong definitions, undefined
  external sets and weak/COMMON facts are identical before and after.
  The adjacent object-facts JSON records the shared facts; null retail
  verdicts are digest-only comparison results, not retail identity proof.
- The owning header acceptance tool passes and retires only coord2d.cpp's
  queue row. No debt baseline or hatch register changes.
- Ordinary preview retains 2/2 LINKS and 1,293 authored bytes (1,112 + 181)
  against index 12b9e7a7c0, 2026-10-30 10:11. This predicts no census gain.
- The header-dependent walk bounds the changed header to 280 ledger sources;
  the normal commit hook verifies that dependent scope before publication.

The staged-tree link_batch_audit is INCONCLUSIVE: the index predates the
source base and affected consumer Common/0CreateAHeroManager21FE49.cpp lacks
a current strict receipt. Full affected-consumer selection/loss verification
and scheduled-census confirmation remain pending. Carry the header's
consumers and the existing coordinate providers into the next scheduled
census. No runtime, ownership or source-file gain is claimed.

Remaining Coord2D queue entries have separate prerequisites: AnimateWindow's
getVel/setVel and AIStatesSmallUpdates' path-offset callee encode struct
Coord2D where this header uses class. The old terrain-init queue row refers
to a corrected historical private-class identity, not a current Coord2D use;
the acceptance tool's discovery-error exception does not cover that case.
Those sources, their identities and their queue rows remain unchanged.
