# AudioLoopUpgrade header acceptance follow-up, 2026-11-04

The false rejection in [the consolidation handoff](audioloop-consolidation-prerequisites-20261104.md)
is fixed separately in `Resolve ambiguous adoption includes in compiler search order`.
The helper constructs the normal compiler command without compiling and checks
the ordered include roots. It declines proof when implicit CL options or an
unmapped drive make that order uncertain. Adjacent and earlier shim headers
continue to shadow the canonical header; comments and disabled includes do not
qualify.

Verification:

* `python3 -m pytest -q tools/tests/test_header_adopt_lane.py tools/tests/test_gate_exploits.py`:
  204 passed, 1 skipped. Includes duplicate-suffix acceptance, shadow-header
  refusal, quote/angle behavior, environment search order and unavailable proof.
* AudioLoopUpgrade's `GameLogic/Module/UpdateModule.h` directive resolves to
  `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` with the real compiler
  command.
* `python3 tools/header_adopt_lane.py accept --class UpdateModule Code/GameEngine/Source/GameLogic/Object/Upgrade/AudioLoopUpgrade.cpp`:
  PASS, retired two queue rows in the working tree. The normal verdict includes
  structural, byte and link checks; its output is `build/audioloop-update-accept-fixed.log`.

The queue-only edit was restored before committing. The outgoing debt gate
loads `header_adopt_lane.py` from its trusted upstream base (`_head_header_verdicts`
in `repair_queue.py`), which does not yet contain this include-checker fix.
Publishing the retirement together with the verifier change would therefore
fail the old acceptance check. Both queue rows remain; no debt retirement is
claimed here.

Next step: after the include-checker commit lands upstream, rerun the acceptance
command above and commit its two queue removals normally. The source repair
remains byte-exact (17 code rows and one data row), with a 680 -> 680 link
preview. The constructor-order and class-layout consolidation prerequisites in
the earlier handoff still apply; no source paths moved.
