### LINK-659: needs TU evidence: inline COMDAT 0x00038310 (`Debug::RepeatChar` constructor); retail copy also in DebugPostStaticInit.obj, wrong copy in debug_except.obj
Status: Blocked (needs TU evidence). Updated: 2026-11-12; inspected revision: d104275446 (swarm Link lane).

Evidence / affected units: `??0RepeatChar@Debug@@QAE@DH@Z`, 0x00038310, 18 bytes, rowed in
Code/Libraries/Source/debug/debug_debug.cpp. It is an inline constructor, emitted as a COMDAT by every unit that
constructs a `Debug::RepeatChar`.
- In debug_debug.cpp only two Zero Hour `present-unmatched` bodies construct one (`RepeatChar('=',80)` in
  `AssertBegin` and `CrashBegin`). Both use the static `Debug::Instance`, which BFME 2 does not have (LINK-633).
  Removing them would leave the row without an emitter in its own unit, so both stay until this entry clears.
- Census index (2026-11-12 02:11, at c31795c94c) definers of the name:
  - debug_debug.obj and DebugPostStaticInit.obj, body 4c65958176e8, the retail copy;
  - debug_except.obj, body 1b4b1a0c38cd, a **wrong** copy. It matters for the provider guard and the object-order work
    (LINK-633, P142): an order or merge that puts debug_except.obj first keeps it.
- Retail has no direct `call` to 0x00038310.
- TU evidence: `tools/tu_evidence.py --source` gives no signal for either DebugPostStaticInit.cpp or debug_debug.cpp.
  A freshly computed `tools/tu_map.py` (in memory, not committed) gives 0x00038310 no TU (`by` = `-`). The neighbour
  0x00038330 is only proposed for debug_debug.cpp (S, noncontiguous).

Remaining / next check: TU evidence placing 0x00038310 (approval is computed, never entered). With an approved TU,
rehome the row with the tools. If that TU is DebugPostStaticInit.cpp, which already emits the retail copy, the last
Zero Hour bodies in debug_debug.cpp can then go (the LINK-633 debug-port cleanup). Separately, find why
debug_except.obj's copy differs (its view of `RepeatChar`).
Evidence: `~/bfme2-ops/swarm/sweeps/link-633-order/fix-c/` (`tu_evidence.txt`, `tu_map_0x38310.txt`).
Clearance: pending.
