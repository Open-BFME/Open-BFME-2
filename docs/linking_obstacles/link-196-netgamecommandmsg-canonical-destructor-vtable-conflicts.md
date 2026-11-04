### LINK-196: NetGameCommandMsg canonical destructor vtable conflicts
Status: Blocked on coherent first-provider vtable declarations/emission. Updated: 2026-11-04; inspected revision: 32e66a3660ef.
Evidence / affected units: [adoption and restored-trial evidence](../../reverse/attempt_support/netgamecommandmsg-headers-20261104-codex3.md).
Completed: canonical NetGameCommandMsg adoption in constructGameMessage, Connection and sendLocalGameMessage; canonical NetCommandMsg in the latter two; five header queue rows accepted, 25 retained rows exact and ordinary preview preserves 2,220 bytes.
Remaining / next check: NetGameCommandMsgDtor trial matches both rows but drops 91 -> 0 preview bytes on MemoryPoolObject and NetGameCommandMsg vtable COMDAT conflicts; restored. Inspect first providers and reconcile vtables before retrying; constructor and NetPacket queued prerequisites remain.
Clearance: only the three accepted source units; destructor adoption remains blocked.
Census confirmation: awaiting; no measured linking gain claimed.

2026-11-04: NetPacket now passes canonical NetGameCommandMsg, NetWrapperCommandMsg and NetFrameCommandMsg acceptance; its three queue rows are retired with 209/209 exact and 33,226 preview-linked bytes preserved. Constructor/destructor vtable work remains the next step ([evidence](../../reverse/attempt_support/netpacket-command-headers-20261104-codex.md)).

NetPacket publication carry (`f728572445`): batch audit INCONCLUSIVE at index `5a13f2cd61` because the source object lacks a current strict receipt; carry the unit and affected consumers into the next scheduled census ([audit evidence](../../reverse/attempt_support/netpacket-command-headers-batch-audit-20261104-codex.md)).
