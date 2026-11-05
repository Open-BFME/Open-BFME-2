### LINK-222: NetWrapperCommandMsg serializer views have other message layouts

Status: Cleared for the two serializer views. Updated: 2026-11-05; inspected revision: `c1a5a2b848`.
Scope: `FillBufferWithFrameCommand.cpp` (`0x0058C80F`) and `Rva0058CD6AWrite.cpp` (`0x0058CD6A`); their private wrapper views describe frame and buffer-bearing layouts that differ from the canonical wrapper contract.
Next: the serializer merge is applied; the remaining Unicode-helper boundary is tracked by [LINK-044](link-044-netpacket-private-views-and-remaining-list-copy-identity.md), and the separate constructor prerequisite remains [LINK-188](link-188-netcommandmsg-dtor-and-ctor-units-cannot-adopt-the-canonical.md).
Evidence: [trial refusals, layout comparisons and three passing queue retirements](../../reverse/attempt_support/netwrapper-header-debt-20261104.md). No source changes or census clearance claimed.

2026-11-05: [Receiver reconciliation](../../reverse/attempt_support/netpacket-serializer-views-20261105-codex4.md) preserves both complete bodies and external bindings (398 bytes), passes both link previews, retires two header-queue rows through acceptance, and admits both ordinary merge donors. Census confirmation is pending.
2026-11-05: [Applied consolidation audit](../../reverse/attempt_support/netpacket-serializer-merge-20261105-codex4.md) records the two-file absorption, 212/212 byte and 67/67 EH checks, and unchanged provider bindings; census confirmation is pending.
