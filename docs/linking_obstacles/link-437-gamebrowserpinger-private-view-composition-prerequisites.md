### LINK-437: GameBrowserPinger composition has incompatible private service views
Status: Blocked. Updated: 2026-11-05; inspected revision: 463674729a.
Evidence / affected units: `Code/Libraries/Source/Fesl/gamebrowser/gamebrowserpinger.cpp` and its three GameNetwork pull donors; [allocated consolidation dry run](../../reverse/attempt_support/gamebrowser-pinger-consolidation-20261105-codex.md).
Completed: allocation, scoped planner and TU plan passed; dry run accepted no donors because class declarations and private service views conflict. LinkGuard lists the destination and all three donors as census-linked.
Remaining / next check: reconcile the `Rva00803080`, `Rva007EAServiceHub`, `Rva007EAServiceList` and `Rva00803080Request` views and `Gen008030A0` vftable ownership; then rerun the supported merge and consumer checks.
Clearance: pending; no merged object or consumer-binding verification was possible.
Census confirmation: not claimed.
