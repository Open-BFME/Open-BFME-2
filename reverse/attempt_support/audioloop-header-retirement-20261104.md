# AudioLoopUpgrade UpdateModule queue retirement, 2026-11-04

Continues [the deferred acceptance](audioloop-header-acceptance-20261104.md).
Inspected checkout `a1ad5f0db7`; upstream contains the include-checker repair
`8347432f87` and the canonical sound-storage repair `08ea943f29`.

Claimed `file:Code/GameEngine/Source/GameLogic/Object/Upgrade/AudioLoopUpgrade.cpp`.
`find_declared_unmatched.py` reports all defined functions already matched.
Ran the normal retirement path:

```text
python3 tools/header_adopt_lane.py accept --class UpdateModule Code/GameEngine/Source/GameLogic/Object/Upgrade/AudioLoopUpgrade.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Upgrade/AudioLoopUpgrade.cpp
  retired 2 row(s) from reverse/header_queue.tsv; commit it with the adoption
```

The verdict checks the canonical include and class structure, byte-verifies the
source and requires its link preview to preserve census-linked bytes. Output:
`build/audioloop-update-accept-landed.log`. The register diff removes only the
two UpdateModule rows for this source (RVA lists `0x004B7B20 0x004B7D37` and
`0x004B7E3C`). No source, ledger row, hatch or alias changed.

`check_csv.py` passes: 99,434 functions, 9,338 symbols and 2,269 data rows.
The outgoing hook independently verifies the retirement against the upstream
verifier; the earlier verifier-landing dependency is resolved.

The DieMuxData constructor-order and AudioLoopUpgrade class-layout prerequisites
in [the original handoff](audioloop-consolidation-prerequisites-20261104.md)
remain. They were not retried in this queue-retirement pass. This clears only
the two stale UpdateModule queue entries, not the TU consolidation or the broader
LINK-168 family.
