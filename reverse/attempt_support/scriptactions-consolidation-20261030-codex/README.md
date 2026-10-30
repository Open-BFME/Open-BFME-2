# ScriptActions consolidation prerequisite (2026-10-30)

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

BFME 1: official upstream was fetched at `85ff94681faf00d093304e48f8e3069b88252399`.
The reference is held by another worker. The verified `e5127cf32f0ea4bb6e31934782783817f719b651`
gitlink from `7859458f65` is retained; no freshness stamp is advanced.
