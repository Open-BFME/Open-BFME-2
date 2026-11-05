# Radar composition boundary (2026-11-05)

Inspected revision: `f0f6176eead83c4c8bb26f6e69e006fcca7a97a1`. BFME_CLAIM_OWNER: yasinschroeder-codexb2.

The current-map queue approves 66 rows in Radar.cpp's scope. The supported
`tu_skeleton.py --merge Code/GameEngine/Source/Common/System/Radar.cpp --dry-run`
accepts no donor and writes no source/ledger changes. Its link guard identifies
the seed and all four candidate donors as census-linked. No loss or gain is claimed.

Target facts and prerequisite checks:

- `find_declared_unmatched.py Radar.cpp`: all definitions matched; existing
  RadarObject constructor hatch remains.
- Radar_deleteListResources.cpp and RadarFrameTick.cpp compositions fail C2143 /
  C2501 at TheRadar before Radar is declared in the composed ordering.
- RadarDtor.cpp and RadarRva002D7BD3.cpp compositions fail C2011 for
  SubsystemInterface and C2065 for m_ref. The seed's RadarEvent has a
  RadarEventRefSlot at +0x4C; these donors have a RadarEventRef pointer there.
- `tu_views.py Radar.cpp --dry-run --no-merge-check` confirms Radar is
  canonical-header work; RadarObject's base clauses conflict (Snapshot versus
  no base), RadarEvent's +0x4C member views conflict, and ClientFrameSubsystem
  lacks a usable layout. Object alone has a mechanical sharing proposal;
  applying it does not address the demonstrated merge blockers.
- `class_views.py --unused --files` over all five whole-file candidates finds
  no unused-class candidates.

Next work: reconcile the actual RadarEvent pointer/slot use in the ctor/dtor
views, resolve SubsystemInterface include ownership, and provide a typed event
array contract compatible with canonical Radar before retrying composition.
Also repair TheRadar's forward-declaration ordering for canonical-header donors.
No private view, shared header, escape hatch, protected register, provider or
consumer was changed. The local dry-run logs are build/radar-merge-dry-run.log
and build/radar-views.log; this handoff preserves their relevant verdicts.
