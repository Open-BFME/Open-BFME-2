### LINK-688: dispatch owner needs a shared accessed-prefix contract
Status: Blocked. Updated: 2026-11-17; inspected revision: 0a5d600aef7.
Evidence / affected unit: Rva000B9A0EDispatch.cpp and GameEngineDevice/GameClient/Rva000B9A0E.h; [current boundary](../../reverse/attempt_support/dispatch-accessed-prefix-20261117-root20.md).
Completed: no production change or repeated compiler trial; all defined owner functions already rowed. Canonical header is currently call-through declarations only; the owner requires active +0x90/+0x94 storage and nested Vec.
Remaining / next check: prove shared accessed prefix and its three existing consumers without claiming an unknown complete class extent/base; then supported nested-record mapping and whole-file adoption verification. Parser normalization alone cannot supply missing storage.
Clearance: none; queue retained, no current link/image/runtime change.
