# INI follow-up publication and current-provider audit

Published `f8aefae21a397402f7e3d90a8674a408f4c8ca24`, 2026-10-26 05:38 UTC.
The source push completed normally, without bypassing or restarting a gate.

## Verified publication scope

Bounded supported preparation supplied strict reusable receipts for all 54
changed sources, verifying 932 function rows and nineteen data rows. The subsequent
pre-push full gate passed all **98,252 functions**, **2,216 data rows**,
214 STLport constructor folds, named references, pins, module/source checks
and the no-op image. Its final changed-source check retained **116 EXACT EH
graphs**. Converged-data enforcement judged all 23,032 sources against ten
addresses, with zero second names and zero unjudged rows.

These are normal verification receipts, not proof of a newly linked image.
`progress.py origin/master` retained C++ exact 7,984,346 bytes (+0) and
BYTE-MATCHED 100%, with no new official LINKING/LINKED measurement.

## Shadow audit: completed, provisional

Unlike the earlier broader batches, this 54-object scope did not include
Eva.cpp and completed strict preparation. Eva's separate include-inventory
prerequisite is not cleared by its absence. The audit retired 89 old objects
and overlaid 54 current objects on index `763dc8759f`; that index predates
outgoing base `5994f7c59a`, so the tool explicitly labels its result
**INCONCLUSIVE** and the findings provisional.

It reports 287 `REVIEW provider disappeared` lines and 30 `POSSIBLE LOSS`
lines. Repeated consumers overlap; no lost-byte sum is inferred. The overlay
does not refresh every unchanged replacement provider after a consolidation.
For example, TheCaveSystem is already owned by CaveContain.cpp, and the two
object-definition parsers are owned by INIObject.cpp. Those owners were not
part of this 54-source refresh. Neither example disposes of the other findings.

Independent fixed-revision review found that 53 of the 54 source files were
already identical to upstream `c330885439` inspected before publication;
only INI.cpp differed. No INI.cpp-specific cause was found
in these reported losses, which is narrower than global linking clearance.
Two real declaration/definition discrepancies were identified for follow-up:

- Five consumers spell WW3D::IsCapturing public (`@@2_NA`), while ww3d.cpp's
  shim declares the existing definition private (`@@0_NA`). The public form
  is the current data-ledger name; simply undoing the consumer changes would
  restore shadow data findings.
- Twenty-three consumers spell TheSkirmishGameInfo as GameInfo*, while the
  menu implementation defines SkirmishGameInfo*. Current data identity and
  the provider's complete include contract must be reconciled before editing.

These are investigation targets, not claims that this INI patch caused them
or that all other audit findings are stale. Remaining findings need suitable
current providers and ultimately the maintainer's next census.

## Post-publication reconciliation

The required pull rebased the local work onto `b85e569cee`. The retained six
audio sources and INI.cpp are identical to their published `f8aefae21a` forms;
upstream's current Count EH labels are retained in the ledger. The vector
overflow identity retirement was repeated through its owning tool at the
new FlammableUpdate.cpp path after normal verification (8/8 rows) and refresh
of its AutoFindHealingUpdate provider (3/3). One key was retired, one retained.
All unrelated upstream Microsoft-header queue rows remain present.

A nine-source reconciliation cohort passed 1,014/1,014 function rows,
24 data rows and twelve EXACT EH graphs. The separately verified removal of
an unused competing audio provider is documented in
[its repair handoff](largegroup-unused-erase-provider-20261026.md).

Local detailed receipts: `build/codex-cleanup-20261025/iteration21-push.log`,
`iteration21-prepare-{0,28}.log`, `iteration21-progress.log`,
`iteration22-rebased-cohort-{build,eh}.log` and
`iteration22-flammable-retire-current.log`.

## Next publication preparation

The later required pre-publication pull rebased the branch onto `2e0de76bf0`.
None of that upstream increment touched the branch's current source-edit
scope. INI and the new audio/capture repairs remain identical to their
verified pre-rebase sources. The streak-data retirement was repeated through
`repair_queue.py retire data`: two stale keys removed, zero remaining findings;
the neighboring statistics key retains upstream's new statistics.cpp path.
The owning scoped INI queue refresh preserves all new upstream entries through
each replayed consolidation and cleanup, ending with no INI queue row.

Immediately before publication, the complete `origin/master..bc38a424c2`
path audit again covers all seven absorbed INI sources, including basename
references, active tooling, hooks, includes, configuration and registries.
The search results are unchanged after the rebase: remaining references are
historical attempts/census data or source comments, with no active consumer
requiring a removed path. No tooling rewrite is needed.

Supported preparation of 82 explicit current providers (28 + 28 + 26) passes
650 function rows and supplies all 82 strict reusable receipts. This includes
the unchanged ww3d.cpp data owner. It is preparation, not a completed push or
link-closure verdict. Fresh progress against `2e0de76bf0` still reports C++
exact 7,984,346 (+0), BYTE-MATCHED 100%, and unchanged official census figures.
Receipts: `iteration23-prepare-{0,28,56}.log`, `iteration23-progress.log`,
`iteration23-final-path-consumers.log`, `iteration23-rebase-streak-retire.log`
and `iteration23-ms-rebase-{12,13,8,5,2,0}.log` in the same local evidence folder.
