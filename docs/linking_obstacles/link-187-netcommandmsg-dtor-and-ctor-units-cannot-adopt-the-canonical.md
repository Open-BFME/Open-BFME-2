### LINK-187: NetCommandMsg dtor and ctor units cannot adopt the canonical header without a non-retail MemoryPoolObject vtable (2026-11-03)

Status: Open (header-queue blocker; no census loss landed).

Units: `Code/GameEngine/Source/GameNetwork/` Rva004D6134Dtor, Rva004D60CADtor, Rva004D6208Dtor,
Rva004D62A9Ctor, Rva004D64F5Dtor, Rva004D67D0Dtor, NetGameCommandMsgDtor, NetHeroCommandMsg and
NetCommandMsgCtor. Twenty sibling units adopted `GameNetwork/NetCommandMsg.h` on 2026-11-03 (commits
"Adopt the canonical NetCommandMsg header ...", LINKED unchanged); these nine were tried and reverted.

Cause: the canonical `NetCommandMsg` derives from `MemoryPoolObject`, whose `virtual ~MemoryPoolObject() {}`
is inline. The units that define or call `NetCommandMsg::~NetCommandMsg` (declared out of line, so they
need an `inline` definition to keep retail's inlined body) then emit `??_7MemoryPoolObject@@6B@`. Retail
has no such table (no retail address), and the emitted copy differs from the first copy in link order
(the existing two-slot copies, see LINK-009), so `link_check.py` predicts each unit drops out of LINKED.
NetCommandMsgCtor also fails bytes: `??_GNetCommandMsg` (0x004CEEA6) calls the dtor instead of the
inlined vptr store.

Next step: settle the MemoryPoolObject base contract once at the class level (canonical header or
class contract, a full-gate shared-header change): either the canonical base emits no table of its own
in these units (retail inlines every base dtor vptr store) or all `??_7MemoryPoolObject@@6B@` copies
agree. Then adopt the nine units with an inline dtor. Other leftovers of the same class queue:
BFMEConnectionManager_relayCommand (`prepareForRelay` not a canonical member), Connection.cpp (C1083),
NetCommandMsg_detach.cpp (`deleteInstance` not found), DisconnectManagerO1.cpp (Zero Hour view).
