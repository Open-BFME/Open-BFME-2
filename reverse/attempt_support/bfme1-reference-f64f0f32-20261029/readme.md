# BFME 1 reference refresh, 2026-10-29

Advance the verified reference from `e42b9782fd4cce1f79832a6ed591b0b8fdbbc2fc`
to official upstream master snapshot `f64f0f32d56adf72bee366d42cbb2a72cf192ae3`.
The clean reference checkout was fetched once from
`https://github.com/Open-BFME/Open-BFME-1.git`. Both full gates used BFME 2
`d2cd76f186722d448490064e0501819dddceead6`, the existing compiler environment
and `BUILD_POOL=8`. No target source, ledger, pin or verifier change was needed.

## Verification

`old-full.txt` and `new-full.txt` preserve the complete gate output. Both
`./build.sh` runs exited 0: 98,943/98,943 functions and 2,235 data rows pass,
along with literals, imports, DIR32 consistency, pins, module registration,
source coverage and the no-op patch. The original processes were polled to
completion, without duplicate runs. This is reference maintenance; it claims
no census-linked, image-ownership, recovered-source or matched-byte increase.

`input-audit.json` records 479 changed upstream paths and the old/new input tree
IDs. Compiler, vendor and Zero Hour reference trees are identical. Five shim
headers changed: StateMachine views in sweep, turretai and turretai_constructor,
and AIUpdate views in sweep and aiupdatelayout. The upstream edits change BFME 1
accessor offsets/declarations and constructor emission. They are donor facts,
not evidence for changing BFME 2 layouts. Existing layout paths still resolve;
no migration or nested-reference initialization was necessary.

The initial 24,490 dependency receipts contained 24 intersections with changed
inputs: 23 existing source owners and one obsolete ai_Rva002FD791 owner. The new
full gate rebuilt 23 of 20,805 translation units. `dependency-validation.json`
checks the refreshed receipts against the actual changed-header hashes.
The final scan finds 23 current consumers: Drawable.cpp no longer includes the
changed headers, while AIGetAdjustedVisionRange.cpp now appears. The latter
was covered by both full gates and was additionally rebuilt under each reference
for the binding comparison (`extra-old.txt`, `extra-new.txt`, both exit 0).
`final-current-dependencies.json` records the complete final consumer set.

`binding-comparison.json` compares the union of 24 existing sources' compiled objects
between gates using the included read-only `object_audit.py` and the `link_census.comdat_bodies`, `_coff_symbols`
and `_weak_externals` readers. All COMDAT names, body digests/sizes, external
definitions, undefined symbols and weak bindings agree. Object hashes may differ
because the compilation metadata changes. This scoped comparison is not a link
census or runtime test. No nightly, link cycle or game smoke run was started.

## Donor cache refresh

The old ordinary sweep cache was archived out of its active lookup path;
`discarded-cache.json` records its hashes. Historical scratch trials are not
current validation. The full build refreshed the affected current-source trials.

`affected_donors.py` reproduces a scoped native-byte sweep from the changed
non-decoder donor paths, using upstream ledger metadata and the two retail
images. It reads no donor source text. `donor-summary.json` records the revision,
image hashes, output hash and counts: 387 changed source paths, 2,635 selected
rows and 1,528 eligible native bodies; 113 unique placements, 122 ambiguous,
1,283 without an exact placement and 10 without a discriminating needle.
The complete results remain in ignored `build/bfme1-refresh-f64f0f32/` and can
be regenerated with the included script. These are native-byte leads, not donor
identity proof, source-transfer approval or a full sweep control-floor result.

The ignored successful freshness stamp was written only after the new full gate
completed. The submodule pointer and this audit are published together.
