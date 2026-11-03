### GiveUpgradeUpdate helper composition prerequisites (2026-10-28)

Status: declarations verified; composition blocked on current census placement.
At base `2eb6108a74`, index `d92e7e6635`, the existing destination view now
declares its already-rowed base intent and exit methods. All ten rows across
the destination and two helpers remain exact; both EH graphs and all external
object facts are preserved. All three units preview LINKS, and strict receipts
cover them. No new linking gain is claimed.

The supported merge now compiles both helper fragments but refuses their
composition because a census-absent file would move the merged object earlier
than the guard can judge. No paths moved. Refresh their placement in the next
normal census before retrying; the other class/layout/include prerequisites
and four mixed files remain. [Evidence and verification boundary](../../reverse/attempt_support/giveupgrade-declarations-20261028-codex3.md).

The declaration batch audit is INCONCLUSIVE: older index d92e7e6635 and
missing current receipt for affected consumer
Common/0CreateAHeroManager21FE49.cpp. Carry it and this provider scope into
the next normal census.
