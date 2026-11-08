# DamageNugget canonical class adoption, 2026-11-08

DamageNugget.cpp adopts canonical Thing, Matrix3D and Vector3 together.
The Object view uses Thing's existing cached-position member; template flag
reads cast the real template pointer to the unchanged bounded data view.
The fallback facing vector reads the matrix's X column directly. Normalize
computes its squared length from the canonical vector fields so the native
inlined arithmetic remains visible. No new name, shared header, global,
alias, pin, flag, source path or ownership row is introduced.

All 14 existing source rows, three EH graphs and eleven float references
pass normal verification, including seven funclets whose compiler labels
renumber. The file is unfrozen. Owning-tool header acceptance independently
passes for each class and retires exactly three header_queue rows. Strict
preparation passes 19/19 rows across the source and the two explicit native
provider units. Staged-peer new-variant checking passes; ordinary preview
conserves LINKS/1,393 authored census bytes at d171e84869.

Twenty-seven retained code COMDAT facts, including bytes, relocations,
flags and selection policies, remain identical; all seven externally named
data allocations agree. The two omitted Get_X_Vector/Length2 copies retain
strictly current earlier native providers. SlowDeathRandomForceRva0045D636
and BaseHeightMapCastRay still provide their complete native bodies before
this object in default real-link path order; the census likewise retains
outside native copies. The added 34-byte compiler iterator exactly matches
native 0x00001423 with no relocations. Its bytes, flags and ANY policy also
agree with the existing ATL provider.

The emitted Normalize copy improves from 57 bytes (calling Length2) to the
complete native 100-byte body at 0x0006924F. A private check passes all 14
source rows plus that existing native row. The final actual object passes
compile_function's full comparison and an explicit float-referent check;
the current earlier BaseHeightMapCastRay copy passes the same checks.
final-proof.json records these boundaries, hashes and provider policies.
The existing ownership remains in tri_compute_normal.cpp; no row is added
or repointed, and this is not 100 new bytes of coverage.

This clears only these three header-adoption debts and the stated copy
quality issue. Cached d171e84869 selection and current explicit providers
are bounded evidence, not a complete current image, runtime clearance or
new census. Canonical Object adoption, the remaining DamageNugget views and
retail TU consolidation are still separate work.

Published as e834581c00; first attempt landed in 43.2 seconds. Required
row/EH/scoped-DIR32 checks pass. Broader audit remains INCONCLUSIVE: index
d171e84869 versus outgoing base ca053513b317febbcba85988de518b2b40da03a7;
DamageNugget itself lacked a current strict receipt after rebase. A local
post-publication refresh passes 19/19 rows across it and the two explicit
providers, and the full scoped object/provider proof passes again. This
refresh does not rewrite the recorded push audit or establish image closure.
