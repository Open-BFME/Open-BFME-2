### LINK-188: NetGameCommandMsg canonical destructor vtable conflicts
Status: Blocked on coherent first-provider vtable declarations/emission. Updated: 2026-11-04; inspected revision: 32e66a3660ef.
Evidence / affected units: [adoption and restored-trial evidence](../../reverse/attempt_support/netgamecommandmsg-headers-20261104-codex3.md).
Completed: canonical NetGameCommandMsg adoption in constructGameMessage, Connection and sendLocalGameMessage; canonical NetCommandMsg in the latter two; five header queue rows accepted, 25 retained rows exact and ordinary preview preserves 2,220 bytes.
Remaining / next check: NetGameCommandMsgDtor trial matches both rows but drops 91 -> 0 preview bytes on MemoryPoolObject and NetGameCommandMsg vtable COMDAT conflicts; restored. Inspect first providers and reconcile vtables before retrying; constructor and NetPacket queued prerequisites remain.
Clearance: only the three accepted source units; destructor adoption remains blocked.
Census confirmation: awaiting; no measured linking gain claimed.
