### LINK-199: OptionsMenu firewall donors still block composition
Status: Blocked. Updated: 2026-11-04; inspected revision: 762d2a6f1d.
Completed: the supported merger absorbs Common/OptionPreferences.cpp into OptionsMenu.cpp, preserving all 77 destination rows and the bounded linking preview. The two firewall donors remain unchanged.
Remaining / next check: reconcile GlobalData through its existing header-adoption queue before composing getFirewallPortAllocationDelta; investigate getFirewallNeedToRefresh's composed byte mismatch. The older-index batch audit also needs current affected-consumer receipts before full closure can be established.
Evidence: [composition, provider equivalence and complete-batch audit limits](../../reverse/attempt_support/optionsmenu-composition-20261104-codexb4.md).
Clearance: composition prerequisites remain open; no census gain or full consumer clearance claimed.
