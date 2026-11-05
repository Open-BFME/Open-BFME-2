### LINK-454: ariesudp donor bytes block mechanical merge
Status: Blocked. Updated: 2026-11-05; inspected revision: `62a33a9bd4`.
Evidence / affected units: `Code/Libraries/Source/Fesl/ariesudp.cpp` and census-linked `Code/GameEngine/Source/GameNetwork/Rva00661650AriesUdp.cpp`; current guarded dry-run evidence: [attempt](../reverse/attempt_support/ariesudp-consolidation-20261105-codex.md).
Completed: plan and dry-run; zero donors accepted, donor rejected with `bytes`.
Remaining / next check: reconcile the donor's bytes against the approved destination body, then rerun `tu_skeleton.py --merge ... --dry-run`.
Clearance: pending.
Census confirmation: no new census claimed.
