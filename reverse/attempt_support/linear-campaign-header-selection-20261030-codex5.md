# LinearCampaignManager header-selection prerequisite

Base: `31de1b96597a8b25e859009e0806f2b62671fb2a`.
Scope: the existing LinearCampaignManager.cpp seed and Rva001EBCD8Erase.cpp.
No function identity, source path, pin, shared header or protected register moves.

## Existing source and receipt facts

The default picker claimed the seed and its 25 whole-file donors. The naming
planner identified conflicting private layouts and compiler/include settings.
The supported TU plan rebuilt its map in memory: 100 approved rows, 26 whole
files including the seed, 14 mixed files, no refused owners. No regenerated
map is committed, and no unrowed or lost retail body is asserted.

The initial supported merge dry run accepted no donors. Most failures are
incompatible STL helper definitions, missing members or divergent class views.
Four donors compile but fail the merged byte check: StlSweepW4Rva001EBEAB.cpp,
FamilyDeletingDtors_Rva001EBFE5.cpp, RvaTopByteFwds.cpp and
StlportVectorInsertOverflowRva001ED03C.cpp. The view planner also refuses
CarryoverUnit class/struct disagreement, Rva001ED03C overlapping fields,
Rva001ED0DE/Rva001ED0A9 bases and Rva001ED41B field sizes. These are cleanup
prerequisites, not matching regressions; LINK-040's element-family identity
work remains open. No speculative family rename or view rewrite was kept.

Strict preparation of the claimed files stopped at the seed: its explicit
BFME 1 STLport include exposes macro includes outside the receipt tool's
recognised STLport roots. Rva001EBCD8Erase.cpp has the same problem.
The seed already selects the STLport 4.6 compiler environment because two
previously merged donor blocks carry exact `// stlport46` markers, while its
explicit include selects BFME 1's older headers first.

## Bounded repair

Remove the seed's explicit BFME 1 STLport include and make its leading marker
state its existing 4.6 selection. The ordinary build now uses the supported
4.6 base and BFME allocator overlay consistently. For the erase donor, replace
the BFME 1 include with the repository's vendor/stlport path; this preserves
its 4.5.3 const-reference __copy_ptrs declaration. No tool/check is changed.

## Verification

- Normal build and final strict two-source preparation pass all 33 rows
  (32 seed rows and the 62-byte erase row), the FieldParse data row and three
  string references. Both sources now have strict reusable receipts.
- Frozen-file checks pass before and after. EH verification is EXACT for all
  five parents. Existing funclet labels are resolved through parent EH data.
- All 69 seed external provider fingerprints and the donor's one provider
  equal their saved pre-edit objects: body bytes, extent, normalized relocation
  targets/content, section flags and COMDAT selection. Neither external
  definition nor undefined-reference sets change.
- Ordinary preview against the 2026-10-30 10:11 index at `12b9e7a7c0`
  reports both units LINKS, with 1,691 + 62 = 1,753 authored bytes. The seed's
  older census figure is 1,574; its current object is unchanged by this repair,
  so that preview difference is not credited as a gain.
- Neither source owns gate, identity, data-check, header, ms-header or hatch
  baseline keys. No debt retirement, census gain, ownership reduction or
  source-file reduction is claimed.

The original merge refusals above predate this header repair; refresh the
naming packet and supported merge probe before the next composition attempt.
The original native names, layouts and family ownership remain unresolved.
The staged two-source audit is INCONCLUSIVE: its index predates the base,
and affected consumer Common/0CreateAHeroManager21FE49.cpp lacks a current
receipt. Carry both providers and their consumers into the next scheduled
census. Full consumer loss/selection checks remain unverified; strict receipt
availability alone does not close LINK-040. check_csv and staged whitespace
checks pass, and all five changed paths are explicitly staged/tracked.
