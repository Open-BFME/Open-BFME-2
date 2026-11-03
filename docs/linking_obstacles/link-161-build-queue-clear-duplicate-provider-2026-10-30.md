### LINK-161: build-queue clear duplicate provider (2026-10-30)

The inferred clear rename `6066b2f51f` collides with the observer's existing
inline `Rva005E8044::clear`. Census `e1f7c1dd18` records this as the sole blocker
in `StrategicInGameUIBuildQueueUnitQueued.cpp` and `GapBodiesSeat5A.cpp`.
The observer now retains its visible body using the established import/forceinline
recipe, suppressing only the extra external definition. The strong owner row
`005E8183/11` remains unchanged and exact; no import, pin, row or alias is added.
Private checks preserve all 15 caller rows, all 31 retained external code bodies
and symbolic relocations, and all four emitted parent EH graphs. Strict ordinary
two-source preparation passes 36/36 rows and EXACT 3 owned EH graphs; ordinary
preview 2/2 LINKS clears 1,449 authored bytes against `e1f7c1dd18`. Broader
consumer/census confirmation remains pending. [Evidence](../../reverse/attempt_support/queue-clear-duplicate-provider-20261030/readme.md).

The combined outgoing audit has 39 strict rows across its three explicit
witnesses, including WallHub, but remains INCONCLUSIVE on the older index and
missing current `Common/0CreateAHeroManager21FE49.cpp` affected consumer.
Carry the full scope into the next scheduled census; no aggregate clearance
is inferred from the bounded preview.
