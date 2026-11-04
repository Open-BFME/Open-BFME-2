### LINK-218: NetWrapperCommandMsg serializer views have other message layouts

Status: Open. Updated: 2026-11-04; inspected revision: `51570733cf`.
Scope: `FillBufferWithFrameCommand.cpp` (`0x0058C80F`) and `Rva0058CD6AWrite.cpp` (`0x0058CD6A`); their private wrapper views describe frame and buffer-bearing layouts that differ from the canonical wrapper contract.
Next: reconcile receiver identities and NetCommandRef declarations against dispatch/reader evidence before adoption; the separate constructor prerequisite remains [LINK-188](link-188-netcommandmsg-dtor-and-ctor-units-cannot-adopt-the-canonical.md).
Evidence: [trial refusals, layout comparisons and three passing queue retirements](../../reverse/attempt_support/netwrapper-header-debt-20261104.md). No source changes or census clearance claimed.
