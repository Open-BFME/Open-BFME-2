# InGameUI list constructor binding prerequisite

2026-11-07. The optimized 114-donor trial still accepted no donor: one
explicit override mismatch, 38 donors losing regional rows, 73 without a
baseline match, one SubsystemInterface declaration conflict, and one composed
byte refusal. Optimization alone did not clear this boundary.

The last refusal is isolated to the 22-byte constructor at 0x002A1B07.
Every instruction and non-call byte agrees. The host's declaration-only
list<Drawable*>::list specialization forces a call to 0x00239CB7; retail
instead calls the rowed _List_base constructor at 0x00239BB0. Restoring the
ordinary inline list constructor after the existing lifetime-provider
specializations permits the inherited constructor layer to inline. Its body
is STLport's existing constructor expression. The allocator and destructor
providers remain declared, and no private class/member type changes.

Private verification preserves the eight host rows; composing the unchanged
donor passes all nine code rows and the existing LinkGuard. The normal host
build passes eight code and two data rows, one compiler float, and its frozen
check remains at 33 existing unclaimed definitions. The before/after objects
retain all 105 external code definitions and equal ordered CRT records. All
seven previously strict borrowed-provider twins remain matching. Five other
borrowed copies remain different or incomparable; this is bounded evidence,
not whole-class or real-image clearance.

A direct _List_base member experiment also produced the native 22 bytes, but
was rejected as a landing strategy: selectMatchingAcrossRegion and its callback
use a live canonical DrawableList at +4, including the destructor at 0x002A0D11.
The applied fix retains that lifetime contract instead of substituting a base
member merely because its storage and bytes fit.

The separate compiler prerequisite passed the full gate: 99,575 code rows,
2,353 data rows, all reference checks and the no-op image check; the following
converged-data audit covered 17,936 sources and 11 addresses without second
names or unjudged rows. A guarded supported TU merge and publication audit
are still required before claiming a file reduction.

## Donor provider cleanup, 2026-11-08

Before consolidation, the constructor donor now declares its existing shared
pool constructor, node creator and destructor providers instead of defining
another allocator implementation. Its private FreelistPool view is removed.
The 22-byte constructor stays exact and the two-source normal build passes
nine code and two data rows. Seven external helper definitions disappear,
with no added definition; all four surviving code definitions retain their
complete bytes, flags and external relocations. The scoped donor preview
continues to predict its existing 22 bytes linking. The member remains a list.

This addresses the first merge's extra pool and destructor emissions. The
speed-preferred out-of-line list-constructor copy must still be checked
against its selected canonical provider in the final composition; a byte
check of the caller alone does not clear that remaining provider question.
