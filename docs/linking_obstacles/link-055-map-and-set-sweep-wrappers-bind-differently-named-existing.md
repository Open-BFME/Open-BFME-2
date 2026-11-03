### LINK-055: map and set sweep wrappers bind differently named existing tree workers

Status: Blocked on row and receiver identity reconciliation. Updated: 2026-10-26; inspected revision: `896af216804e`.
Evidence / affected units: `StlSweepW4Rva00464431.cpp` and `StlSweepW6Rva0016DEC0.cpp`. Raw retail calls and current-provider previews: `build/link-worker-w5/retail-probe-final.log`, `before-extra-providers.log` and `after-cohort.log`.
Completed: diagnosis only. The 29-byte map wrapper calls 0x00463E4D, already rowed as the 294-byte `Rva00463782::rva00463E4D` in `Rva00463E4DHintInsert.cpp`. The 21-byte set wrapper calls 0x0016D6A0, already rowed as the 108-byte `_Rb_tree<Gen_p12pod,pair<const Gen_p12pod,int>>::_M_find<Gen_p12pod>` in `RvaTreeFindGenP12pod00927790.cpp`. Both actual providers LINKS; the sweep units each retain U1/L1/S1. The latter provider compares three integer fields, which does not establish the sweep's string-containing record identity.
Remaining / next check: reconcile the existing row names, operation and receiver layouts through the naming lane before suppressing template bodies. Declaring the current pinned names alone cannot supply a provider; casting containers to other instantiations is not a repair. No source trial was applied and no missing match is claimed.
Clearance: pending.
Census confirmation: not claimed.

**Served-unit recheck (2026-10-27, `9ac97a4584`, index `bf3dd31211`):**
`StlSweepW6Rva0016DEC0.cpp` still previews U1/L1/S1 with the current
`RvaTreeFindGenP12pod00927790.cpp` provider, which retains LINKS (108 B).
The wrapper remains byte-exact (21 B). The native callee's final reverse
comparison rejects a non-equal lower-bound candidate, so the operation is
`find`, not the sweep's `lower_bound`. Its native tree compares three signed
integer key words, unlike the sweep's string-containing element. The retail
caller index has no wrapper caller; the outer container and constness remain
unproven. BFME 1's 0x00927BF0 tree-find instantiation is a structural lead,
not canonical owner evidence. No source change or repeated suppression trial
was retained; a blocked verdict defers this candidate pending receiver and
operation identity reconciliation. Census confirmation remains unclaimed.
