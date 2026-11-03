### Pinger ownership placement refresh (2026-11-01, Cortys)

The supported current planner and in-memory split still approve no pinger TU:
eight pingerMain.c rows and eleven peerPing.c rows remain unresolved. General
C-static names are still not scoped by ledger_io (its local_static covers only
_$E compiler initializers). Both files remain19/19 exact. No body, data key or
row is moved or removed; the four piNextID keys and piSettingData scheduling
prerequisite stay open. See reverse/attempt_support/pinger-placement-prerequisite-20261101/.
