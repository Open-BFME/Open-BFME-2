### LINK-291: NetworkInterface adoption in W3D display needs StringBase reconciliation
Status: Blocked for `W3DDisplay.cpp`; two statistics consumers cleared by byte and link-preservation previews. Updated: 2026-11-04; inspected revision: `5199deee0b`.
Evidence / completed / next check: [scoped adoption and verification evidence](../../reverse/attempt_support/networkinterface-w3d-stats-20261104.md). `W3DDisplayGatherDebugStats.cpp` and `W3DDisplayGatherNetworkStats.cpp` adopt the existing header and retire two header-queue rows; reconcile `W3DDisplay.cpp`'s private `StringBase<T>` and the 0x000481AA / 0x0075D142 return-value EH contract before retrying its header adoption.
Census confirmation: awaiting the next scheduled measurement; no real-link or headline gain claimed.
