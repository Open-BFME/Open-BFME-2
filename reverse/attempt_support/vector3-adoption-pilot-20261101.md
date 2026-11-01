# Vector3 frozen-header adoption pilot, 2026-11-01

Base: `5fce89b57a`. Target: replace private `class Vector3` bodies with the
existing `Code/Libraries/Source/WWVegas/WWMath/Vector3Data.h`. The header and
`reverse/functions.csv` are unchanged. This is shared-definition adoption, not
source-path consolidation or a census measurement.

Selected 20 claimed, non-frozen, same-class-key consumers. The established header
uses 12-byte storage with float X/Y/Z at offsets 0/4/8. The lane's compiler layout
probes establish each consumer's field correspondence; field spelling alone is
not layout evidence. No donor path or inferred historical TU is claimed here.

## Result

- Existing adoption lane: 19/20 byte-pass.
- Additional conservative full-object runtime/provider equality: retain 14/20.
- Owning `header_adopt_lane.py accept`: all 14 pass the normal byte/data checks
  and combined ordinary link prediction; 14 corresponding queue rows retired.
- Retained scope: 62 function rows, 2 data rows; predicted linked bytes remain
  11,724 -> 11,724 against census index `46c2713cfd` (2026-11-01 03:29).
  These bounded predictions do not establish current whole-program linking.
- Full-object equality for the retained files covers non-debug section bytes,
  relocations, external definitions, weak bindings and COMDAT selection policy.

The normal acceptance build also passed string, float, import and funclet checks.
Fourteen private Vector3 bodies are replaced by includes; no shared-header edit.

## Remaining consumers

`GameLogic/Object/Rva000E04CEUpdate.cpp`: field token `x` also belongs to Coord3D.
The tool refuses an ambiguous token-wide rename; source left unchanged.

Five byte-passing trials were restored because the extra equality check also
rejects additional emitted inline providers. A second bounded trial diagnosed:

| Source suffix | Additional providers |
| --- | --- |
| Common/VslotRva0009AE98Projection.cpp | Vector3 default constructor |
| Common/VtableSlotBodiesR3.cpp | Vector3 default constructor |
| LivingWorld/LivingWorldArmyIcon.cpp | Vector3 default constructor |
| LivingWorld/Rva0009C814ArmyLines.cpp | Vector3 default constructor |
| LivingWorld/Rva002BEDCAMovementDuration.cpp | Vector3 three-float constructor and `??ZVector3@@QAEAAV0@ABV0@@Z` |

No prior external provider was removed, no existing external function body bytes
changed, and weak bindings were unchanged. These are conservative pilot refusals,
not demonstrated runtime regressions. All five originals were restored and a
normal build passed 52/52 rows. Reconsider only with provider/consumer admission
for the extra COMDATs; this pilot does not broaden that policy.

## Measured workflow

| Phase | Seconds |
| --- | ---: |
| Original 20-source normal build | 16.36 |
| Existing batch adoption | 29.34 |
| Restore five extra-provider trials | 8.29 |
| Accept retained 14, including combined link preview | 21.23 |
| Total measured native workflow | 75.22 |

Adoption includes 39 layout probes (12.46s) and one 19-source byte build (15.71s).
Acceptance includes a 10.80s byte build and 9.83s combined link prediction.
Selection, claims, investigation, tests and commit hooks are outside these timings.
Scratch phase logs and exact selected sources are under
`build/vector3-adoption-pilot/` locally.

## Queue observation

In one live claims snapshot, Vector3 had 216 unique queued sources, 50 held by
peers, and nine bounded cohorts. Claiming every queued consumer for each cohort
made all nine unavailable. Restricting explicit consumer claims to the selected
cohort, while keeping class/member-provider and frozen-header protection, made
two cohorts available in the same snapshot. This improves scheduling availability;
it is not a measured reduction in compilation time or a general speedup factor.
