# ariesudp mechanical consolidation trial (2026-11-05)

Inspected destination `Code/Libraries/Source/Fesl/ariesudp.cpp`; 5 approved rows,
2 pull donors and 2 mixed donors. `python3 tools/tu_skeleton.py --plan` routes
`Rva00661650AriesUdp.cpp` and `Disp8NullAdjustGetters.cpp` as shown by the plan.
The current dry-run accepted no donors and rejected
`Code/GameEngine/Source/GameNetwork/Rva00661650AriesUdp.cpp` with the exact
reason `bytes`. LinkGuard names both the destination and rejected donor as
census-linked. No claims or source changes were made. Next useful step is for a
code-recovery contributor to reconcile the donor's bytes with its approved
`ariesudp.cpp` body, then retry the tool's guarded dry-run.
