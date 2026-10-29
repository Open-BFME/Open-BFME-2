# FX-list identity retirement with current providers

Control: `54f489336` (code unchanged from `29c5ceda1f`).
Source: `Code/GameEngine/Source/GameClient/FXList.cpp`.

The registered unowned `Rva001E19E8CallView::call` edge is stale: current
ParticleSystemFXNugget::doFXObj already calls the rowed four-pointer const
reallyDoFX at 001E19E8 directly. This source repair predates this attempt.
The caller and provider pass all 11 rows, their data row, nine float constants,
one import and one string. No replacement alias or source edit is necessary.

The supported whole-source retirement first refused 11 stale provider receipts.
Refreshing exactly those 11 sources through tools/build.py passes 597/597 rows,
three data rows, 71 floats and 112 imports. A second retirement still refuses a
new wrong finding: the FXList copy at 0052BD3A calls a list-copy name at 000365F0,
whose native owner is StringBase<char>'s copy constructor. The current checker
reports two wrong references; this particular key is outside the old register.
No baseline is grown and nothing is retired.

This is the same coherent value/type/provider prerequisite established in
[the 2026-10-25 native investigation](fxlist-obsolete-emissions-20261025/readme.md):
the copy installs the one-string C61A20 table and its list semantics are not
native semantics. Do not repeat declaration-only suppression or a local alias.
Reconcile the native type and all dependent owners/consumers while preserving
coverage before trying whole-source retirement again. No code, pin, alias,
register or linked-byte change is retained; the file claim is released.
