### AIUpgrade consolidation needs a compatible vtable (2026-10-29)

At base `4690ab9c11`, the supported merge dry run rejects all three
whole-file donors to `Common/AIUpgrade.cpp`. The build donor's private view
does not declare the seed constructor. The cost donor reaches the merged
link guard after declaring that constructor and destructor and making the
seed's base fields protected; its one row and the seed's one row still match,
and both separately preview LINKS (86 and 26 bytes) against index
`85f6b7f40c`. The combined object instead changes the selected
`??_7AIUpgrade@@6B@` COMDAT. The transfer donor independently fails on that
vtable and a duplicate `??1AIUpgrade@@UAE@XZ`. The trial declarations were
restored; no path moved. Reconcile the complete native virtual interface and
destructor provider before retrying composition, then check the affected
consumers and the next census. No census gain is claimed.

Rechecked at `1f26b04a7b` on 2026-10-30: the supported merge dry run
still accepts no donors. Build and cost fail on the undeclared seed
constructor; transfer fails on the duplicate destructor and changed vtable
COMDAT. `tu_views.py --dry-run` also reports incompatible AIUpgrade base
clauses. No reconciliation or path move was retained. Details and the
reference-freshness limitation are in
`reverse/attempt_support/ai-upgrade-merge-recheck-20261030-codexb5.md`.
