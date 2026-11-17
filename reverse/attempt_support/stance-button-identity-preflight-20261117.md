# StanceButton table identity preflight

The served Rva00567CCDCtor.cpp primary table 0086CF0C has a missing slot 1.
Its native target 005679A4 is already rowed as
InGameToggleStanceCommandButton::Impl::StanceButton::DoUpdate (131 bytes).
LINK-514 explicitly records this exact two-table identity dependency: both
emitters still use Rva00567960, and a placeholder-to-member move cannot move
the already named provider. No duplicate method family is needed.

The constructor's +8 movie interface, +10 implementation, +14 stance and
+18 countdown fields agree with the named update view. The normal unchanged
constructor build passes; no source, header, row or alias edit is retained.
Reconcile the placeholder class with the established StanceButton identity
using the normal naming path, including both table emitters and callers.
That path needs reverse/deleted_rows.csv, currently claimed by another
contributor. Release the table, file and class scopes; both bridge pass tests
remain open until the identity repair and fresh real link.
