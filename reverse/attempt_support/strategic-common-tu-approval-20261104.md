# StrategicInGameUI Common TU approval investigation

Inspected revision: `168988f976`; scope:
`Code/GameEngine/Source/Common/StrategicInGameUI.cpp`.

The default picker serves three noncontiguous proposed rows: `0x005D015C`
(354 B, GetStartingBattleMessage), `0x005D232D` (40 B, GetSelectionPortrait)
and `0x005D2355` (102 B, GetSelectionPortrait). This is approval cleanup,
not missing byte coverage. No source or mapping edit was attempted.

Current checks:

- `check_csv.py` passes (99,451 function rows).
- `find_declared_unmatched.py` on the selected source passes.
- `name_lane.py consolidate --under Code/GameEngine/Source/Common/` reports
  separate WorldBuilder path hints for the source's portrait and button-image
  bodies; neither is target TU proof. The file contains both bodies at
  `0x005D2355` and `0x005F031D`, so it is mixed/incomplete routing.
- `tu_skeleton.py --plan` rebuilds the stale map in memory and lists only seven
  approved EH rows in one mixed donor, Rva005CF9FFFlagNotifyDtors.cpp. It does
  not approve the three served parent/body rows. No safe merge is available.

A concrete interleaving anchor is the 10-byte RefCountClass::Release_Ref at
`0x005D1A7D`, already rowed in WW3D2/hlod.cpp. The map assigns it to
WWLib/refcount.cpp using S (class site). The GeneralsMD donor's refcount.h
lines 146–153 define Release_Ref inline inside the class; refcount.cpp has no
Release_Ref definition. The target source includes refcount.h under size
optimization to emit its exact 10-byte form. These are donor/header and
existing-source facts, not evidence that any StrategicInGameUI body belongs
in a particular BFME 2 TU.

`tu_map.header_comdat` currently treats header-defined constructors and virtual
methods as COMDATs, but excludes ordinary nonvirtual methods such as this one.
Before retrying approval, investigate whether that exclusion incorrectly gives
this inline member a hard S anchor, with regression/holdout validation for any
mapper-rule change. Removing it alone would not prove the WorldBuilder paths
or authorize splitting/moving the mixed source. No map was regenerated or
committed, no inline owner was moved, and no coverage or source-file reduction
is claimed.
