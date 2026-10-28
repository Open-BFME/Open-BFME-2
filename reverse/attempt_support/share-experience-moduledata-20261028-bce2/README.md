# ShareExperienceBehavior module-data reconciliation

Inspected base 24454a208b3, 2026-10-28. The default picker claims the
approved ShareExperienceBehavior TU and its two whole-file donors. The
in-memory map approves 21 rows; the three whole files hold 18. Three mixed
sources stay outside this pass. The required naming/layout catalogue and
compiler view plan are reviewed; their hints do not approve a move.

## Verified prerequisite

The seed had an eight-byte prefix and an int at +0x14. The already matched
module-data constructor and destructor provide a polymorphic base at zero,
padding at +4, floats at +8/+0xC/+0x10 and a four-byte Rva003623E5Filter at
+0x14. The seed now uses that existing view and the destructor donor uses
the seed's existing field spellings. This is layout reconciliation, not a
new application-name or donor-layout claim. The canonical Snapshot header
and the existing qualified base teardown are retained.

The mechanical view planner refused to rename a field appearing in the
out-of-class initializer. The corresponding declarations and initializer
are reconciled explicitly and verified together. No checker is changed.
The stale present-unmatched constructor comment is removed: its body has an
existing matched owner in the mixed constructor file. The owning counter
tool removes exactly that one register line, present_unmatched 3717 -> 3716.
No hatch, alias, pin, source move or ledger row is added.

All 15 rows in the two changed files remain exact; three EH graphs are
EXACT, two string literals and three float literals verify. Shadow data
checking has zero findings. Across all three scoped files, all 39 normalized
row-reference records and all external object facts are identical to saved
controls (COMDAT digests/verdicts, exclusive definitions, undefined symbols
and weak aliases). The untouched behavior constructor's three rows already
pass, giving 18/18 original scoped rows. Original source/object controls
remain in build/resume-eh-local/turn84 and are not source providers.

## Merge remains blocked

The supported dry-run composes the module-data donor's bytes but refuses
its link guard: the destination is absent from the available index
(2026-10-28 15:58 at d92e7e6635), and the new combined unit would precede
the earliest census-known donor. That link order cannot be judged by this
guard. The refusal is preserved; no merge is applied, no index or rule is
edited, and no linking or source-file reduction is claimed.

The behavior constructor donor still has an undeclared constructor and
incompatible primary/interface base clauses. It is unchanged. Its three
linker aliases stay in place. Three mixed files remain for their own split
or declaration work. Next: obtain destination/consumer coverage through the
next maintainer census, then retry the supported merge and reconcile the
behavior's class/base contract separately. No nightly or smoke run starts.

The outgoing audit on base 2400d7451e7 is INCONCLUSIVE: index d92e7e6635
predates that base and affected consumer
Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp lacks a current
receipt. Prepublish-audit.txt preserves the result. Carry these changed
declarations and consumer coverage into the next normal census; full batch
linking remains unverified despite the exact scoped object controls.

The normal pre-push hook expands the checked scope to five sources through
included-file dependents: 53/53 function rows, two data rows and seven EH
graphs pass. Its audit remains INCONCLUSIVE with three source objects lacking
current receipts, first GameClient/Eva.cpp. Publication-audit.txt preserves
that wider result. Git then rejects the push because master advanced; the
retry keeps normal gates. Carry both audit scopes into the next census.
