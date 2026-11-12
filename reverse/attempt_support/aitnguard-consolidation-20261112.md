# AITNGuard: shared machine views before consolidation

Base `5586b0ec3f6`, 2026-11-12. Claimed cohort: AITNGuard.cpp,
AITNGuardMachineCtor.cpp, AITNGuardReturnStateOnEnter.cpp, AITNGuardStates.cpp
and AITNGuardXfer.cpp under GameLogic/AI.

## Supported planning and initial boundary

`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/AI/`
catalogues the original-path evidence, alternatives and declaration/compiler
blockers. Its hints and stale-map entries supply no approval. The supported
`tu_skeleton.py --merge ... --dry-run` rebuilds the map in memory and finds
47 approved rows, four mixed files retained and no accepted donor. No map,
source move or merge is committed by that trial. `tu_views.py --dry-run`
separates canonical-header work from conflicting private views.

Initial composition fails on the missing machine xfer declaration, machine
field spellings and ObjectID types, plus incomplete AIUpdateInterface and
AIEnterState declarations. All five inputs are census-linked; preserving
those units is a requirement, not an optional byte-only check.

## Three machine views reconciled

Use the existing AITNGuardMachine.h in the seed, ReturnStateOnEnter and Xfer.
The registered 0x50-byte layout keeps position +0x3C, nemesis +0x48 and
guard mode +0x4C. No shared header or layout contract is edited.

- The seed adopts the existing declarations without changing its matched code.
- ReturnStateOnEnter explicitly converts the header's unsigned ID to the
  existing ObjectID enum at findObjectByID. All three rows remain exact;
  24 retained COMDAT fingerprints are unchanged. Its emitted inline ID getter
  follows the canonical unsigned return type instead of the private enum view.
- Xfer uses the existing asBase view for the same 12-byte coordinate triple,
  the canonical guard-mode name and an explicit ObjectID pointer view at the
  existing serialization helper. It retains the actual helper calls and raw
  version-2 transfer. All three rows and four retained COMDAT fingerprints
  remain exact; the existing inline asBase helper is also emitted.

Normal `./build.sh` verifies 35/35 rows across these three sources and the
restored constructor, including the seed's data row, two string references,
float and import checks. All three frozen-file checks pass. The owning
`header_adopt_lane.py accept --class AITNGuardMachine` passes the three edited
units and retires exactly their three queue entries.

Strict preparation also verifies all four explicit sources. Own previews
retain LINKS for 857, 505, 176 and 417 bytes (1,955 total) against index
`aa7acf764d` of 2026-11-12 19:19. The index warns of four unrelated path
changes; this is a scoped preservation result, not a new census or image.

## Constructor provider identity remains blocked

The canonical constructor trial verifies all nine source rows but loses its
previously linking 417 bytes: GetSnapshotName is unresolved and the indexed
table copies disagree. Its native six-byte provider at `0x00545B8F` is already
rowed as `?name@AITNGuardMachine@@QBEPBDXZ` in ModuleNameGetters3.cpp.
The canonical header needs `?GetSnapshotName@AITNGuardMachine@@MBEPBDXZ`.
This is an existing body with the wrong role/identity, not a missing body.

Current rename routes cannot safely perform that correction. `name` is not
weak or recorded as inferred; the basis guard refuses its replacement.
Virtual mode keeps the identifier, to-class refuses the existing/readable
owner, and prepared respell still uses the basis guard. The WB entry is a
PLACEHOLDER, not original-name proof. This is the existing LINK-514 lk77
canonical-base-override tooling gap. A bounded independent read-only review
confirmed the guard and existing upgrade precedents. No alias, pin or invented
provenance is added. The complete trial is saved under ignored build/ and the
constructor source is restored; its 417-byte preview links again. A blocked
constructor record describes the identity prerequisite.

## Remaining composition work

Retry the supported merge after committing the accepted reconciliation and
refreshing the planner. The States donor's State prefix is 0x1C; the shared
base is 0x20 and several derived pads compensate for that difference. Adopting
the base without removing the compensating pads shifts fields by four bytes.
Its private member template also needs reconciliation. The ReturnState views
name AIEnterState and Rva00341930 as different nominal bases; preserve the
existing xfer callee until their relationship is proved. TeamTemplateInfo and
TunnelTracker private views still disagree. No new private copy of a registered
class may be introduced by a merge.

Four mixed sources remain outside this cohort's mechanical merge: the const
and module-name getter collections, Rva004D759CDerived and RvaSmallVtableCtors.
No split or forced TU assignment is attempted.

The preceding FESL header push's broader audit was INCONCLUSIVE because
Common/AIBaseBuilder.cpp lacks a current receipt. Carry that scope and these
guard declarations into the next normal census; no game-running result is
claimed by header adoption or a preview.
