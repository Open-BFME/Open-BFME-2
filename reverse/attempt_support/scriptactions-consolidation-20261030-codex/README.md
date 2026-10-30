# ScriptActions consolidation prerequisites (2026-10-30)

Base: `c647a75e55b27d0c76c8b56a8475fd4ba680ec52`.
Scope: `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp`.

The default picker claimed the seed and 311 candidate donor files. The current
naming planner reports original-path and grouping evidence; the supported
`tu_skeleton.py` plan rebuilds the stale TU map in memory. No regenerated map
is committed. This work does not establish a new donor name or layout.

## Canonical declaration adoption

The seed's private `ScriptActions` declaration is replaced with the registered
`GameLogic/ScriptActionsBFME2.h`. Its nonvirtual member definitions keep their
existing names, access, parameter types and bodies. The header supplies the
already registered SubsystemInterface base and class layout. The unused local
`EmotionType` declaration leaves with the private view; the CommandButton and
UpgradeTemplate forward declarations remain necessary.

The header names an STLport vector in a declaration, so this source now opts
into the existing STLport include mode. Its documented
`_STLP_DONT_FORCE_MSVC_LIB_NAME` configuration keeps the previous linker
library directives: this TU needs the type declarations, not a new automatic
library directive. No shared header or shim changes.

Before and after `./build.sh` pass all 52 function rows, 19 renumbered funclet
pins, three string literals plus the empty-string references, eight floating
literals and zero named imports. `find_declared_unmatched.py` passes both.
A COFF comparison excludes only `.debug*` sections and normalizes internal
relocation targets to section/offset pairs: all 112 retained sections, 8,200
bytes, 440 relocations and 202 external symbol records are identical. This
includes linker directives, constants and EH data; no provider, COMDAT or
external binding changes. No new match, linking-byte gain or debt retirement
is claimed. The separate Thing adoption queue entry remains unchanged.
`header_adopt_lane.py accept --class ScriptActions` passes (no queue row existed
for this class/source). Ordinary `link_check.py` retains LINKS, 5,461 -> 5,461 B,
against the published 2026-10-30 10:11 index at `12b9e7a7c0`. This is a preview,
not a census measurement.

## Native inline integer getters

After the canonical-declaration change, the read-only class-view
planner found a declaration mismatch among the 32 Parameter-bearing donors.
ScriptActionsCounters.cpp, ScriptActions_livingWorldRegion.cpp and
ScriptActions_doStandGround.cpp mark their defined, forced-inline `getInt`
as `dllimport`, suppressing extra copies. Removing that annotation keeps
all 29 rows exact, including the 20,985-byte action dispatcher and switch
table. Frozen-file, literal and import checks pass. The counter donor's
existing ScriptEngine header queue entry remains unchanged; no debt is retired.

The object comparison identifies sections by their external definitions and
occurrence within each section kind, normalizes local relocation targets to
section/offset pairs and normalizes `.sxdata` symbol-table indices to the
symbols they name. All retained non-debug bytes, relocation targets, external
symbol records and SEH handler references are identical under those
normalizations. The sole addition in each donor is the four-byte
`?getInt@Parameter@@QBEHXZ` COMDAT (`8b4108c3`, digest `dbc10ce76e7d`).
It is an exact twin of all three copies in the published
`12b9e7a7c0` index: ScriptEngineRva00205D5D.cpp, Rva003b6d92Finish.cpp and
ScriptConditionsRva003E8E23.cpp. This proves copy identity, not a separately
recovered out-of-line retail function. Retained object facts are:

| Donor | Sections | Bytes | Relocations | External records |
| --- | ---: | ---: | ---: | ---: |
| Counters | 7 | 352 | 12 | 11 |
| Living-world region | 110 | 25,798 | 2,219 | 610 |
| Stand ground | 35 | 1,437 | 41 | 43 |

The four-source ordinary preview retains LINKS for all 29,055 authored bytes
(seed 5,461, counters 214, living-world region 22,970, stand ground 410).
The final supported class-view dry-run now reports `Parameter: plan` across
all 32 files, with no field renames. Its proposed 0x20-byte superset uses the
largest existing view; this is a mechanical reconciliation proposal, not proof
of a newly recovered retail layout. No view rewrite has been applied. Applying
it still requires the tool's per-file layout, byte and external-symbol checks.

## Verification limits and remaining work

Strict current preparation passes all 81 rows across the seed and three donors,
creating reusable receipts. The combined batch audit against base
`c647a75e55` and review tree `babf2608942329c3dd9a1491d37e6ee0e147ebdb`
is INCONCLUSIVE: the index predates the base, and affected consumer
Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. Full affected
consumer selection and loss checks remain unverified. Carry the four sources,
the existing inline providers, the added identical integer-getter copies and
their consumers into the next scheduled census. No census gain is claimed.

The first broad merge dry-run started from the seed before header adoption.
It was interrupted when that input mismatch was recognized; it produced no
final accepted/rejected set and is not a current merge verdict. No donor is
deleted or repointed. A supported merge still needs a fresh trial on the
current seed. The current class-view survey refuses the Player and Object
plans at nested-declaration forms (UnitRevivalTracker return declaration and
ModelConditionFlags member declaration respectively); these diagnostics do
not establish incompatible retail layouts. The separate Thing adoption and
mixed-source prerequisites remain open.

At selection time, official BFME 1 upstream was fetched at
`85ff94681faf00d093304e48f8e3069b88252399`. Another worker held the reference;
this pass retained the verified `e5127cf32f0ea4bb6e31934782783817f719b651`
gitlink from `7859458f65` and did not advance the freshness stamp.

## Publication rebase and shadow findings

Runner publication rebased these changes onto `8c0120e29c`. Upstream did not
change the four edited source files. Both obstacle-register entries are kept
when resolving the documentation conflict. The runner synchronized BFME 1 to
the upstream gitlink `1d5131d3f193cdf01a99da66ccd6828639585650`.
On the rebased result, `check_csv.py`, all 81 function rows, literal/import
checks, all four frozen-file checks and both object comparisons pass again.
The source commits were handed to the fleet publisher as `e63de4f443` and
`62d8d8d190`; transport may rebase these hashes again.

The integer-getter commit hook also reports two new shadow findings in
ScriptActions_livingWorldRegion.cpp. Both name `?clear@AsciiString@@QAEXXZ`
with retail target `0x00036410`, class `wrong`, from these rows:

- `?doLivingWorldSetRegionRefToAdjacentRegion@ScriptActions@@IAEXABVAsciiString@@0_N1@Z`
- `?rva003C3943@ScriptActions@@IAEXABVAsciiString@@0@Z`

These retained external bindings are unchanged in the before/after object
comparison; the annotation cleanup neither introduces nor fixes them. The
identity register remains in shadow mode. Their interpretation and any repair
remain open; no baseline entry is added and no false-reject verdict is claimed.
