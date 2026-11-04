# BuildingBehavior publication accounting

After the runner rebased the pending batch onto `9e671822ba`, the upstream
IME entry already owned LINK-232. Move only the local BuildingBehavior entry
to the gate-suggested free LINK-236; its obstacle status and evidence stay
unchanged. The earlier shroud handoff retains its historical description of
the previous LINK-231 to LINK-232 adjustment.

The publication preflight also found two referenced provider objects stale
after the rebase. Refresh the four previously recorded dependent providers
with ordinary `./build.sh` verification before resubmitting the outgoing
debt retirement. No source or register is changed to excuse this check.

Verification: the four update providers pass 58/58 rows, and the additional
ObjectCreationUpgrade provider passes 23/23. After their scoped builds,
`repair_queue.py verify-removed --range 9e671822ba HEAD` exits zero.
The batch retirement is now backed by the owning tool's current-object
verdict; no debt key or retirement reason is bypassed.
