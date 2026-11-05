# BuildAssistant header retirement recovery

The fleet publisher refused the saved header-adoption batch against master
`6d409fd607c65c809f113d4d95597486c9b56638` on 2026-11-05:

```
repair_queue: Code/GameEngine/Source/GameClient/InGameUIHandleBuildPlacements.cpp: reverse/header_queue.tsv row (BuildAssistant) removed but acceptance fails: link_check predicts a loss of census-linked bytes
PRE-PUSH FAILED: retired debt has no passing outgoing verdict
```

Restore this queue row exactly as preserved before the adoption, per the
preparation-recovery instruction. Keep the source adoption and the other
retirements pending their normal hook checks. Retry this row only through
`header_adopt_lane.py accept` after current byte and link acceptance passes.
The original publisher output is saved locally in
`build/recovery-publish-3.log`. This records an acceptance refusal, not a
measured real-image link regression.
