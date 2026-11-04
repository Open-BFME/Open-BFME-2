# LivingWorldBuildPlot header adoption: native slot providers are prerequisite

Inspected `d5414a57f0` on 2026-11-04. No source, header, ledger or queue
change is retained. This is cleanup of an existing header-adoption blocker,
not lost coverage or a new regression.

The seven-unit `header_adopt_lane.py adopt --class LivingWorldBuildPlot
--header Code/GameEngine/Include/GameLogic/LivingWorldBuildPlot.h --apply`
cohort retained no candidate. Current diagnostics:

- `OpaqueScalarDeletingDtorsB11.cpp`: absent-from-retail `EmitVtableTag *`
  constructor is not declared by the shared header (C2511).
- `Rva004FC4D1Dtor.cpp`: automated layout discovery stopped on
  `vendor/stlport/config/stl_dec_vms.h:50` (trigraph/continued comment).
- `rva003F2150Rva003F2150Farm.cpp`: building pointer versus canonical
  four-byte owner field at +0x20.
- `LivingWorldBuildPlot.cpp`, `LivingWorldBuildPlotDoXfer.cpp`, and
  `LivingWorldBuildPlot_Unresolved.cpp`: private `Rva00575674` owner versus
  canonical `Rva000AD6F4` at +0x20.
- `LivingWorldRegion.cpp`: class-key adoption also requires the callers in
  `LivingWorldLogic.cpp`; do not change only the provider's mangling.

## Bounded destructor trial

[Reproducible source diff](livingworldbuildplot-header-20261104-codex.patch)
replaces the private class with the shared header, substitutes its evidenced
16-byte `Rva00330757Member` base for the 12-byte vector view, keeps the existing
Snapshot include surface, and gives the base its existing free-first-pointer
inline destructor. The header's field names replace the two private owner names.
The base destructor is already rowed at 0x0007FAB3 in
`LivingWorldRegionConstructor.cpp`; no new pin or identity is invented.

`./build.sh Code/GameEngine/Source/Common/Rva004FC4D1Dtor.cpp` passes all
11/11 rows, string/float/import reference checks, and all five native funclet
bindings through the verified parent EH graph. The frozen-file check passes.
However, `header_adopt_lane.py accept --class LivingWorldBuildPlot` refuses
retirement: ordinary `link_check.py` predicts LINKED 194 -> 0 bytes against
census `f12552d0a7` (2026-11-04 20:47), with three unresolved symbols:

- `?crc@LivingWorldBuildPlot@@UAEXPAVXfer@@@Z`
- `?loadPostProcess@LivingWorldBuildPlot@@UAEXXZ`
- `?xfer@LivingWorldBuildPlot@@UAEXPAVXfer@@@Z`

Target/header facts: native primary table C63530 is described by the header
as deleting destructor, postprocess, name getter, and DoXfer. The earlier
Snapshot include selects its lower-case compatibility API; the private class
inherited its three pure slots, but the shared class redeclares them as concrete
methods without providers. Byte matching the destructor does not validate
those newly emitted table references. Do not make the native slots pure or
add alias pins merely to obtain header acceptance. Reconcile the actual slot
providers and the existing getter owner before adopting this destructor.
The existing DoXfer provider is rowed at 0x004FC57F in the separate transfer
source; postprocess/name provider ownership must be investigated separately.

The complete original source was restored and rebuilt: 11/11 rows pass,
all five EH bindings pass, and ordinary preview is LINKS 194 -> 194 bytes.
All seven header-queue entries remain. No linked-byte, ownership, debt or
census gain is claimed.
