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

## Xfer consolidated after machine adoption

At base `1b96b70da24`, the refreshed guarded trial accepts the seed and
AITNGuardXfer.cpp. The supported merge reuses that verified composition and
moves all three Xfer rows (0x00545B95, 0x00545C1D and 0x00545EB2) into the
approved AITNGuard.cpp. No compiler-generated row moves without its parent.
The ordinary build verifies 23/23 function rows, the data row and its string
reference; the unmatched-body check passes. The generated map's local source
repointing is restored rather than committed. The hatch updater produces no
net register change. This removes one source file and recovers no new bytes.
Strict preparation verifies the entire four-source cohort (48/48 rows).
Scoped previews retain all four units: 1,033, 1,383, 417 and 505 bytes, 3,338
in total, equal to the preceding five-unit total. The preview's apparent
176-byte increase in the destination is the absorbed donor, not a link gain.

The single consumer audit covers this complete outgoing path change from
`1b96b70da24`: no old-path dependency exists in tools, hooks, workflows,
includes, executable configuration or source registries. The merge removes
the three stale `not merged yet` comments. Its `from` comment preserves
provenance; previous census rows, generated TU-map source columns and dated
attempt inventories intentionally retain their historical paths. No active
consumer requires a separate edit. The census index remains older than
unrelated path changes, so its warnings and the earlier INCONCLUSIVE broader
audit remain limitations, not a clean image or census result.

## States: three canonical bases accepted

After the Xfer move landed as `ec7da76cdc4`, AITNGuardStates.cpp now includes
the existing State, StateMachine and AITNGuardMachine headers directly.
The former 0x1C State prefix omitted the canonical trailing flag; removing
four compensating four-byte pads and shortening AIAttackState's padding keeps
all derived fields at their proven offsets. No shared header changes.

Use StateMachine's existing getCurrentStateID rather than the private member
template and present-unmatched duplicate. Explicit ObjectID conversions at
the lookup boundary preserve the enum ABI while using the machine header's
unsigned ID storage. AIAttackState declares its existing update and snapshot
overrides so allocating the state remains valid with the abstract shared base.

Private verification matches all 13 rows, retains 28 emitted COMDATs unchanged,
and replaces four private accessor spellings with their canonical counterparts.
The final ordinary build and all three header_adopt_lane accept verdicts pass;
the owning tool retires three header-queue rows. The scoped link preview stays
at 1,383 bytes. The obsolete marker is removed through hatch_counters.
Remaining InnerState, DamageInfo and TeamPrototype adoption work is separate.

The Xfer push's shadow asBase finding was checked against the former donor:
both emitted copies have the same 5-byte COMDAT hash `341dc3ec187f`.
It is a moved existing copy, not new helper behavior. The broader push audit
remains INCONCLUSIVE, now naming Common/Rva004D759CDerived.cpp's missing
current receipt; retain that provider in a future normal census scope.

## InnerState uses its bounded header

The next trial removes the private AITNGuardInnerState declaration and uses
AITNGuard.h. Its existing opaque attack pointer is cast at the use sites;
typed deletion still calls the same virtual destructor before global delete.
The header's eight-byte exit-conditions record keeps its existing vptr and
frame layout. Passing that record to the attack constructor uses an explicit
interface-pointer cast; no vptr, provider, constructor or shared header changes.

All 13 rows match in private and ordinary verification, and all 31 retained
COMDATs remain identical. Only the superseded private getGuardMachine accessor
disappears. Strict preparation and the owning InnerState adoption verdict pass,
retiring one queue row. DamageInfo and TeamPrototype are the two remaining
header entries for this source. The previous base-adoption push's broader
audit was INCONCLUSIVE because its strict States receipt was absent after the
final include edit; the present strict preparation supplies that receipt.

## DamageInfo uses the complete canonical record

Replace the private twelve-byte prefix and its invented nested input record
with Damage.h. Both attack-aggressor reads now select the canonical m_sourceID
at complete-object +8 directly. No body-module signature or callee changes.
All 13 rows and 31 retained COMDATs remain identical; ordinary verification,
strict preparation and the owning DamageInfo acceptance pass and retire one
queue row. TeamPrototype is the only remaining header entry in this file.
The InnerState push's wider audit remains INCONCLUSIVE for AIBaseBuilder.cpp's
missing current receipt; no runtime or fresh whole-tree link result is claimed.

## TeamPrototype completes this file's header queue

Replace the private TeamTemplateInfo/prototype projection with Common/Team.h.
The outer state's target test now reads the canonical m_attackCommonTarget at
prototype +0x216 directly, removing the TU-specific template-info helper and
the guessed +0x200 subobject boundary. This does not move or rename a row.
All 13 bodies and 30 retained COMDATs match; only the superseded helper
disappears. Ordinary verification, strict preparation and the owning
TeamPrototype acceptance pass and retire the last header entry for States.
All six original header entries for this file are now cleared through their
owning acceptance tool. A fresh guarded TU composition is still required;
header acceptance alone does not establish that the remaining donors merge.

## Seed views reconciled after the next guarded trial

On `c40bbd895ae`, the refreshed supported merge still accepts no additional
donor. States and Return fail on undefined AIUpdateInterface and AIEnterState
bases in the combined text; the constructor retains its mode/abstract-state
and snapshot-identity prerequisites. No merge is applied. The attempt record
uses the existing 395-byte lookForInnerTarget row as its file-scope anchor.

The seed now includes the existing AIUpdateInterface, AIStateMachine,
DamageInfo and TeamPrototype headers. The guard scan reaches getGoalObject
through the actual +0x30 state-machine pointer. Damage fields use complete
offsets +8/+0x78, and the prototype flag uses +0x216 directly. No shared header,
row, callee or data binding changes. Both obsolete private accessor emissions
disappear; all 23 rows and all 76 retained COMDATs remain identical.
The ordinary build, strict preparation and all three owning adoption verdicts
pass, retiring three more seed header entries. The initial strict command ran
under the sandbox user and stopped at Git's repository-ownership check; the
normal repository-owner command supplies the successful strict receipt.
AIEnterState ancestry and the remaining donor reconciliation still need proof;
these header adoptions do not establish a new accepted merge or a working image.

## Native AIEnterState prefix shared by the three guard consumers

After the seed preparation, the supported composition no longer reports the
AIUpdateInterface base error. It still refuses States on AIEnterState ancestry,
Return on ancestry/Object redefinition, and the constructor on its known
mode/abstract-state prerequisites. No donor is moved by that trial.

The native facts are preserved in `aitnguard-enter-native-20261113.json`:
constructor 0x00342EAC calls 0x0033F279, clears +0x4C/+0x50 and installs
VA 0x00C12E90. Getter 0x00342ED1 returns the literal AIEnterState at
VA 0x00C12ED8. Its table slots 3..6 hold 0x00341930, 0x0034FB77,
0x003510A5 and 0x0035455A. The existing matched onEnter/onExit owners establish
the entry ObjectID and timeout names; the shared AIInternalMoveToState header
establishes the 0x4C base extent. These are target facts, not donor layout.

AITNGuardEnterStateView.h shares that 0x54-byte consumed prefix across the
three guard units. It does not claim an original EA header path or transfer
the constructor, destructor or snapshot identities. Return's timer stays at
+0x54 by removing the former compensating padding. Its transfer body still
calls the existing 0x00341930 provider through an explicit receiver boundary;
the old protected method's spelling and actual call remain unchanged. No new
pin, alias, helper body or ledger row is introduced.

Ordinary and strict builds pass all 39 rows, the data row and three string
references. The final object comparison retains all 131 COMDATs identically,
with none added, removed or changed. Three own link previews retain 2,921
bytes; the old index's 176-byte difference is the already-landed Xfer move.
Direct registered-header dependencies replace the seed's remaining private
Rva00041A06 declaration (an initial include-only trial exposed the duplicate).
Four owning accept verdicts retire the three remaining seed entries and
Return's State entry. Seed, States and Return now have no header-queue rows;
the constructor's separate State entry remains. A fresh guarded merge is
still required. The prior push's broad audit remains INCONCLUSIVE for the
missing current AIBaseBuilder.cpp receipt.
