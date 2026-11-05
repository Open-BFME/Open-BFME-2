# ActiveBody max-health consolidation, 2026-11-05

Scope: merge `ActiveBodySetMaxHealth.cpp` into
`Code/GameEngine/Source/GameLogic/Object/Body/ActiveBody.cpp` with
`tools/tu_skeleton.py --merge`. One source file is removed; no matched bytes
are newly claimed. The complete TU verifies 74 functions and two data rows.

## Placement and composition

- Target fact: the existing row at RVA `0x004BDB85` is 126 bytes and names
  `ActiveBody::setMaxHealth`. The current TU inputs approve `ActiveBody.cpp`;
  the merge tool rebuilt the stale map in memory and changed only this row's
  source column in the committed map. Existing placement evidence is retained.
- Planner: `name_lane.py consolidate` under the Body subsystem, report
  `build/consolidation/activebody-20261105-codexb`, inspected before merging.
  The planner was rerun after the declaration prerequisite. Approval comes
  from the TU map and merge checks, not the planner's investigation groups.
- Prerequisite commit `bf7807088c` declares the existing override in the
  seed's complete class and supplies the two missing enum constants already
  present in the fragment. The seed verified 73/73 functions before merging.
- The merge tool accepted only the seed and max-health fragment. It preserved
  all existing bodies, reordered declarations, and repointed the function,
  TU-map source and header-queue source/pass-test. The old fragment's comment
  now explicitly identifies its former secondary-interface view, rather than
  describing the merged complete class as that view. The donor provenance
  remains a donor fact, not a claim about BFME 2's source path.

## Verification and debt ownership

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Body/ActiveBody.cpp`:
  74/74 functions, two data rows, seven string literals plus two empty-string
  references, and 28 compiler float literals pass. No unmatched definitions
  remain (`find_declared_unmatched.py`).
- `eh_verify.py`: eight EH rows, all exact; no absent objects or baseline use.
- `check_csv.py`: 99,471 function rows, 9,312 symbol rows, 2,268 data rows; OK.
- Before composition, the two scoped link previews totaled 8,449 bytes
  (8,323 + 126). After composition the TU's preview is LINKS, 8,449 bytes.
  These are predictions against the local census index dated 2026-11-05
  15:52 at `112a456a2c`, not a new census or real-link measurement.
- The merge's census-linked provider/consumer guard passed. Comparing COFF
  definition sets before and after finds exactly the original union:
  166 external code names, 28 external data names and six TU-local data names;
  no additions or losses. The merge engine's composition checks preserve
  selected COMDAT/provider bindings.
- Data identity retains the seed's existing shadow `wrong-name` finding for
  `?$S2@?1??getModuleNameKey@ActiveBody@@UBE?AW4NameKeyType@@XZ@4IA`
  at `0x00A040B8`; there is no new finding. No data or identity key belonging
  to the removed fragment exists in either debt register.
- Code identity remains in shadow and reports the same divergent
  `Object::getBehaviorModules` definition as the prerequisite commit. The
  staged merge check covers 74 rows and reports that single existing finding.
- The fragment's ActiveBody header-queue row for `0x004BDB85` transfers to
  the destination, retaining its historical failure evidence and debt. The
  seed's other header obligations remain. Neither fragment nor destination
  has an MS-header queue row. No debt is retired and no baseline is changed.
- The first commit attempt passed the byte gate but was refused by
  `repair_queue verify-missing`: header transfer detection compares sets of
  `(class, source)`, and the destination already had its ActiveBody key. The
  transferred row therefore adds no new pair. The commit uses the documented
  vanished-source per-key explanation for the old fragment's ActiveBody key;
  both destination queue rows remain. This accounts for the vanished unit,
  without claiming header adoption or reducing header debt. No check is changed.
- No alias, pin, hatch, data owner or fold-proof provider is removed. Normal
  commit hooks also verify ownership, includes, identity and converged data.

## Tooling compatibility audit

Audited the complete pending range from origin/master `f0f6176eead8`, through
the existing local commits and `bf7807088c`, plus this merge. Its only removed
source path is `ActiveBodySetMaxHealth.cpp`; the other pending source edits
do not move paths. A repository-wide basename search, plus scoped searches
of active ledgers, debt registers and queues, found no active tool, workflow,
configuration, include or source registry requiring an extra path update.
The merge tool already repointed all three active records above.

Intentional surviving mentions are the historical `reverse/link_status.csv`
census row and the merged source's origin comment. Historical attempt logs
are retained. The old source has no remaining active ledger or queue owner.
Current object receipts and byte/link checks use the final destination path.

## Remaining composition prerequisites

The ten other donors were left untouched after dry-run refusals. Next work
requires reconciling `toupper` linkage in the BitFlags fragment; missing
GameLogic/AI/DamageInfo declarations in the particle, Rva004BDFCB and
indestructible/slot fragments; STATUS_53 and Object shapes in load-post-process;
duplicate STLport traits/allocator declarations in the vector fragment; and
constructor/destructor declarations and module-data views in the two ctor
fragments and deleting destructors. Each needs a separate byte-verified
prerequisite before another supported merge. No rejected donor was deleted.
