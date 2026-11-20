### LINK-563: Radar composition needs event and base view reconciliation

Status: Blocked. Updated: 2026-11-05; inspected revision: f0f6176eead83c4c8bb26f6e69e006fcca7a97a1.
Evidence / next check: [supported merge and view diagnostics](../../reverse/attempt_support/radar-composition-20261105-codexb2.md); zero donors accepted. Reconcile RadarEvent +0x4C pointer/slot use and SubsystemInterface ownership, enable canonical Radar's typed event-array contract, and fix TheRadar forward-declaration ordering before retrying.
Clearance: none; no source/provider change or census gain claimed.

2026-11-20 root20: Radar's slot 6 body at 0x002D7E68 now has the
native virtual spelling. Its direct and indirect callers retain
retail dispatch. A scratch trial keeps all 16 lifetime rows while
emitting both exact 13-slot primary tables. Slot 2 at 0x0004FA11 still
requires an approved Radar getter identity, followed by a common
lifetime declaration. [Evidence](../../reverse/attempt_support/radar-snapshot-table-20261120-root20.md).
