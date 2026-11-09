# Army entry constructors need the real base hierarchy

Status: cleared for ArmySummaryEntry and CarryoverUnit in
Common/ArmySummaryEntry.cpp (2026-11-09); ArmySummary adoption remains open.

Both entry constructors use their real shared bases, replacing the private
CarryoverUnit/MemberAC/ArmySummaryEntry views and manual derived-table stores.
All eight existing rows verify. Both emitted tables match all five native
slots; seven helper bodies independently match native, including the secondary
adjustor and deleting destructor. The 556 retained COMDATs are unchanged and
all eleven added copies agree with existing indexed providers. No source path,
ledger, pin, extent or flag changes. Own LINKS verdict preserves 363 bytes.

Two owning header acceptances retire their register rows. Five units remain
for each adopted class. This source retains only its ArmySummary queue entry
(14 class entries overall). The supported read-only preflight still finds its
manual ArmySummary vtable declaration; the complete constructor also needs
the measured +4 no-throw base initializer and opaque-vector lifetime interfaces
reconciled with the canonical header. Equal 16-byte views do not prove a class
identity. The existing exact ArmySummary body is preserved.

Evidence: reverse/attempt_support/army-entry-canonical-construction-20261109.md.
The previous push's broader AICowerState_onEnter.cpp missing-receipt audit
remains open (index 5b5011469d, base 8541635d74); this scoped LINKS check and
header recovery do not close it or establish an image/runtime result.
