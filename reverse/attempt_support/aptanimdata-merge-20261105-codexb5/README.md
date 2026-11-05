# AptAnimData consolidation, 2026-11-05

At `039bf7c2b1`, the supported `tu_skeleton.py --merge` accepts
`AptAnimData.cpp` and `AptAnimDataRenderData.cpp` in
`Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/`. The donor is removed;
all nine matched rows remain in the approved destination. The merger rebuilds
the stale map in memory and changes only the donor's source column in the
committed map, alongside its functions.csv source. Seven approved rows and two
homeless compiler companions compose successfully. This lowers source files
by one and recovers no new matched bytes.

The naming planner was run over that GUI directory before editing. The map's
approved destination remains provisional: its WorldBuilder W3DAptAux.cpp hint
is alternative evidence, not proof of BFME 2's original filename. No stronger
original-path claim is made here. Prior map/findSlot deferrals are in
`consolidation-queue-20261104-seat.md` and the earlier attempt log.

## Prerequisites and bindings

`9c24c129f1` reconciles both AptAnimData views: the enumerator observes
baseDirectory at +0; createRenderData addresses map at +8. Padding and private
lookup-map declarations express only those target observations. Method bodies
were unchanged and both inputs passed their byte and link checks.

An initial merge trial preserved bytes but changed the parser's cleanup call
from StringBase<char>::releaseBuffer to AsciiString's destructor. The seed's
BFME_ASCII_DTOR_DECL flag caused that difference. Its stale symbols.csv pin at
0x00036410 hid the different ledger identity (the destructor row is 0x0048BA39).
That trial was discarded before committing. `039bf7c2b1` removes the seed flag:
the enumerator's two cleanup sites now also bind directly to releaseBuffer.
Its eight rows, two EH graphs and 266-byte preview stayed exact; its existing
shadow code-identity finding disappeared. No pin or shared shim was changed.

Against the two inputs after those prerequisite fixes, the final merged object
retains all 78 external COMDAT byte-and-relocation digests. No external
definition is lost or added. The sole removed undefined external entry is
createRenderData, now resolved inside the TU. See [symbol-audit.json](symbol-audit.json).
No alternatename, hatch or provider was removed.

## Verification and limits

- `./build.sh AptAnimData.cpp`: 9/9 exact, eight string literals plus one empty
  string and two import references verified; all compiler funclet pins resolved.
- Frozen-source check clean; `eh_verify.py`: 2/2 EXACT; staged code-identity
  check: nine rows, zero new findings (shadow).
- Ledger, case, class and staged TU ownership checks pass. Neither input owns
  data, identity, header, Microsoft-header, flag-override or hatch debt keys;
  there is no debt retirement or stranded key. The merge's report refreshes
  introduce no further changes.
- The merger's current link guard protects both census-linked inputs.
  `link_check.py --prepare-current` produces a strict reusable receipt;
  the ordinary preview reports LINKS for 1,151 authored bytes against index
  `c95fcfcfcd` (2026-11-05 05:17 UTC), equal to the former inputs' combined
  preview scope (266 + 885). This is no census gain or game-link proof.
- The full outgoing batch audit remains **INCONCLUSIVE**: its index predates
  outgoing base `f0f6176eea`, and three inherited source objects lack current
  receipts, first ClickReactionBehavior.cpp. See [link-batch-audit.txt](link-batch-audit.txt).
  Carry ClickReactionBehavior, staging-room transfer views and this TU into
  the next scheduled census; external-consumer selection remains unverified
  by that broader audit. No prohibited census or smoke runner was started.

## Complete outgoing path audit

The audited range is `origin/master` (`f0f6176eea`) through these staged changes,
including the inherited unpublished ClickReactionBehavior and staging-room
commits. Its source removals are ClickReactionBehaviorCtorThunk.cpp into
ClickReactionBehavior.cpp and AptAnimDataRenderData.cpp into AptAnimData.cpp.
Combined old-path, basename and directory searches cover tools, hooks,
workflows, build/configuration inputs, source includes and path-keyed ledgers.
The only active source mentions left are the merger's provenance comments.
There is no tooling or include consumer to update. Old link_status.csv rows,
the name_agreed.csv historical explanation, runtime survey and prior attempt
evidence retain their historical paths. The inherited ClickReactionBehavior
audit documents its three hatch transfers and retained aliases. No source path
is changed by the staging-room view prerequisite or its blocked-merge handoff.

The strict receipt was regenerated for the final TU; stale donor cache entries
are not used as proof for it. The source-path audit must be repeated if a later
session adds relevant moves or consumers before publication.
