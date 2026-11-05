# ProductionQueueHordeContain snapshot consolidation, 2026-11-05

## Change and evidence

`tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Contain/ProductionQueueHordeContain.cpp`
absorbed `ProductionQueueHordeContainXfer.cpp`: one source file removed,
17 matched rows preserved. The transferred row is `xfer` at 0x0048127E,
54 bytes. Current TU-map approval is the destination without the
`HordeContain/` directory; the planner reports that directory as alternative
original-path evidence, not approval to move there.

The prerequisite intermediate-base repair is a separate commit. The merge
retains its imported, inline HordeGarrisonContain destructor and all existing
linker aliases. No alias, pin or debt key was removed or added.

## Verification and batch audit

- `./build.sh` destination: 17/17 matched; three renumbered EH labels verified;
  one string reference verified. `find_declared_unmatched.py` passes.
- `check_csv.py`: 99,455 function rows, 9,324 symbols, 2,268 data rows; passes.
- `link_check.py` destination: LINKS, 495 own bytes (441 plus the transferred
  54); preview against census 2026-11-05 05:17 at c95fcfcfcd. This is not a
  new census or a claim of increased global linked coverage.
- Merge link guard checks the census-linked seed and affected donor/consumer
  units; composition accepted. No second HordeGarrisonContain destructor
  definition is emitted.
- Staged code-identity check: 17 rows, zero new findings (shadow). Enforced
  converged data check: 11 addresses, zero second names or unjudged rows.
- Exact-path searches found no donor/destination entries in the code-identity,
  data-check, header-adoption or Microsoft-header debt registers. The merge
  calls header-adoption transfer and scoped Microsoft-header refresh; neither
  queue changed. Data ownership stays with the seed. Shadow data checking still
  reports the existing flash-constant duplicate/name findings at 0x00A03780
  and the static-guard name finding at 0x00A0377C (compiler guard label changed
  from S1 to S3); these remain unresolved, with no retirement claimed.
- Path audit covers origin/master 48e8ebf76c through the outgoing batch plus
  this merge. Its only source deletion is ProductionQueueHordeContainXfer.cpp.
  Searches of tools, hooks, workflows, source/header includes, root build/config
  files and docs found no active donor-path consumer to update. Functions and
  TU-map source columns were repointed by the merge tool; the map was not
  regenerated. Remaining donor-path references are the provenance comment in
  the destination and historical reverse/link_status.csv census evidence.
  Doxygen already names the destination. No protected-register keys needed
  transfer; hatch regeneration produced no diff. Diff whitespace checks pass.

## Remaining prerequisites

The same dry run rejected the constructor and slot donors on private-view
composition, Rva0048130EDtor on declaration ordering, the vector-destroy donor
on specialization after instantiation, and ModuleDataDtor on compilation.
They remain unchanged in their existing owners. Mixed helper files were not
split. Reconcile each donor in a separate byte/link-verified change before
retrying its merge. No new persistent link obstacle was found in this pass.
