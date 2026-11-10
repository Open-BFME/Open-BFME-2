### LINK-018: canonical `Coord3D` member growth blocks header-adoption until dependents are recomputed

**Weapon hidden-result profile check (2026-11-01; base `8c6bd6ae65d`):** All six remaining units pass 113/113 control rows. Replacing the weapon-specific Coord3D constructor with the existing non-POD companion and a named output grows native 30 bytes to 63 (temporary allocation and result copy). The trial is fully reverted; restored external object facts are identical. No queue/header/source change or census gain is retained. The five other units keep their documented class-key/interface prerequisites; shared-member growth is not retried. [Rejected patch, controls and next prerequisite](../../reverse/attempt_support/coord3d-weapon-return-profile-20261101-bce2/README.md).

**Wrapper adoption and deferred retirements (2026-10-29; base `a2e9c2b5b2`):**
The existing constructor companion replaces the private Coord3D/Base view
and tagged return constructor in Rva004EBF4BCopy.cpp; its 72-byte row stays
exact. The owning acceptance tool retires that queue entry plus four existing
companion users (Rva003A35A0Element, Rva00506CF5HomePoint,
stlport_vector_geometryshape_base and AIStructureCreepTactic). Strict
preparation passes 77/77 rows; all five ordinary previews retain LINKS for
6,214 authored bytes against index `85f6b7f40c` (2026-10-29 15:08).
The outgoing audit remains INCONCLUSIVE: the index predates the base and
Common/0CreateAHeroManager21FE49.cpp lacks a current consumer receipt.
Carry that consumer and the wrapper provider into the next scheduled census.
Six queue entries and the class-key/interface prerequisites remain. This
clears five header-debt entries only; no new census gain is claimed.
[Scope and checks](../../reverse/attempt_support/coord3d-wrapper-adoption-20261029-codexb.md).

**Preserved-batch recovery follow-up (2026-10-28):** replay of the older
Coord3D batch removed the geometry helper's deferred queue row again. The
publisher at `3dbbc13cb7` still has no usable per-unit verdict, while the local
preview preserves 121 -> 121 bytes. Recovery restores that exact upstream row
in a new commit and retains the verified source. The retirement remains pending;
[recovery evidence](../../reverse/attempt_support/preparation-recovery-20261028-codex.md)
records the refusal and preserved attempt. No header-debt gain is claimed.

**Companion retirement deferred for publication (2026-10-28):** the
constructor-companion adoptions in Rva003A35A0Element,
Rva00506CF5HomePoint and stlport_vector_geometryshape_base stay in source and
pass the local dry-run push hook (11 sources byte-verified) and local
`link_check` (1,032, 763 and 121 linked bytes preserved). The fleet publisher's
checkout builds no objects, gets `link_check produced no usable per-unit
verdict`, and refuses their header-queue retirement. Their three queue entries
are restored exactly from upstream; no header debt is claimed retired. Rerun
`header_adopt_lane.py accept --class Coord3D` on them once the publisher's
preview yields a per-unit verdict. No census gain is claimed.

**Shared companion debt retirement (2026-10-28; base `9d2ee4a0f4`):**
The existing companion-recognition fix `e46cd47132` resolves the recorded
acceptance false rejection for BridgeObjectCtor,
BridgeBehaviorHandleObjectsOnBridgeOnDie, AIStructureCreepTactic and
OneRingPenaltyUpdate. The owning acceptance tool now passes all four and
retires their queue entries; their sources and shared headers are unchanged.
The combined build passes 68/68 rows. Ordinary preview against `41c28839bf`
preserves 2,613 linked bytes across the three linked units; AIStructureCreepTactic
remains 0 -> 0 with the three existing vector<Object *> selected-copy blockers
(LINK-132/LINK-133). Remaining class-key/member/codegen prerequisites stay open.
This clears four header-debt entries only; no census gain is claimed.
[Scoped evidence](../../reverse/attempt_support/coord3d-companion-retirement-20261028-codexb.md).

**Companion adoption (2026-10-28; inspected `20c2620db2`):** The owning
acceptance tool retires six Coord3D queue entries: four existing companion
users and new adoptions in stlport_vector_geometryshape_base.cpp and
W3DViewGetAxisAlignedViewRegion.cpp. The edited units retain all five rows,
the viewport EH graph and all external COMDAT/definition/reference facts.
Across the six accepted units, twelve EH graphs remain EXACT and ordinary
preview retains 3,123 authored linked bytes (index `41c28839bf`).
AIStructureCreepTactic's existing vector-provider conflicts remain blocked
at zero linked bytes. No new census-linked coverage is claimed.
[Scope, checks and remaining prerequisites](../../reverse/attempt_support/coord3d-companion-adoption-20261028-codex.md).

The home-point companion trial also matches all six rows, but acceptance
refuses the same missing-provider preview as the restored original.
Both missing names now belong to consolidated Common/AIBaseBuilder.cpp,
which is absent from the cached census. Source and queue row are restored;
await a census containing that provider or a separate provider-aware
retirement diagnostic. Library class-key/member-growth prerequisites below
remain open. Carry changed declarations into the normal consumer audit.

2026-11-03: the current index supplies both home-point providers; ordinary previews now retain 2,545 B across the two units, clearing this missing-provider prerequisite only. [Evidence](../../reverse/attempt_support/aibasebuilder-consolidation-20261103/README.md).

Post-handover verification against `bef6d6aaef3`: all eight outgoing/scoped
sources have strict receipts and 75/75 rows exact. The batch audit remains
INCONCLUSIVE because index `41c28839bf` predates that base and affected
consumer Common/0CreateAHeroManager21FE49.cpp lacks a current receipt.
Carry the declarations and consumer into the next normal census. The hook's
shadow Coord3D copy-constructor divergence has the identical pre/post-edit
25-byte fingerprint; that inherited selection prerequisite remains open.

**Real-link Matrix4D exports blocked by the canonical class key (2026-11-06, halilkkaya-lk36; base `bd49217dc8`, real link `306f01e6f6`):**
- The real link reports two unresolved retail exports, `??0Matrix4D@@QAE@ABVCoord3D@@M@Z` and
  `?Set@Matrix4D@@QAEAAV1@ABVCoord3D@@M@Z`, both at 0x00004079 (an ICF fold: the axis-angle
  constructor and `Set` have one body). No object defines or references either spelling.
- Cause: the row is `??0Matrix4D@@QAE@ABUCoord3D@@M@Z` in Snapshot.cpp (its approved TU), which
  includes the canonical `struct Coord3D`. ed350ebef22 ("Adopt canonical Coord3D in 425 units")
  respelled the row from the export's `ABV` to `ABU`.
- Target fact: all 15 retail exports that spell Coord3D spell it `V`, a `class`. The contract's
  "class-key struct (bytes)" comes from `class_contract.ledger_key`, a majority of matched ledger
  names (1,471 `UCoord3D` against 28 `VCoord3D`). Agents chose those names, and the count gives
  the exports no precedence.
- Measured: the class key comes from the definition. A `class Coord3D;` forward declaration
  ahead of the canonical `struct` still mangles `U` (VC7.1 scratch compile). A TU-local
  `class Coord3D` would be a private copy (class_gate). Moving the row to matrix4d.cpp, whose
  private view is a `class`, would leave its approved TU.
- Route: decide Coord3D's key from the exports (`class`) in a class-reconciliation commit: the
  contract, the header and the dependents' row respellings together. Then Snapshot.cpp's row takes
  the export spelling, and an `--icf-owner` twin row with fold-proof gives `Set` its name. The
  matrix4d.cpp exports need the same key when that file merges into Snapshot.cpp. Not attempted.

**Matrix4D class-key prerequisite (2026-10-28):** The canonical struct changes
eight existing class-key decorated Matrix4D symbols; a class forward declaration
does not preserve them. The trial was reverted and the original unit passes
24/24. Establish target identity and reconcile owners and consumers before
adoption. [Scoped evidence](../../reverse/attempt_support/matrix4d-coord3d-adoption-20261028-codexb5.md).
No queue retirement or linking gain is claimed.

**Status: Open. Updated: 2026-10-26; inspected revision: 5dcf22e436c (2026-10-25 trials).**

- **Evidence / scope:** retiring coord3d_crossproduct.cpp's private
  class Coord3D : Coord3DBase view for the canonical Lib/Coord3D.h +
  Lib/Coord3DBase.h pair byte-matches the 97B body (1/1) once CrossProduct
  is declared in the canonical header, but the declaration alone regresses the
  unrelated dependent Player::initFromDict 0x002AFCDF (2,762 B): without it
  the unit is 31/31, with it uild.py's funclet identity check reports
  $L10490 does not hold this funclet while $L10524 and $L10523 match
  equally. An unrelated probe member (int ProbeMember0001(int) const) fails
  identically and deterministically with BFME_OBJSTORE=off, so ANY member
  growth of the canonical class perturbs that dependent's compiled EH funclet
  layout. The trial reverted
  (
everse/re_attempts.log, 2026-10-26 retraction and blocked entries); the
  ledger row keeps the V class-key spelling of its private-view unit and
  
everse/header_queue.tsv keeps the row.
- **Remaining / next check:** member additions to Coord3D.h ship only
  together with a dependent recompute (the precedent header extensions
  24ef6a5e83 and 505f43a1c73 landed with their own dependent work). For
  the Coord3D queue (13 private-body units and 42 view users in
  
everse/header_queue.tsv), inventory a dependent set that reproduces
  PlayerInitFromDict.cpp 31/31 with the grown header before publishing any
  new member; the coord3d_crossproduct.cpp adoption resumes then. Related
  view-shape blocks: TeamPrototypeMoveTeamTo.cpp (inlined user copy-ctor
  by-value staging) and AISpecialPowerPickers.cpp (array-of-Coord3D EH
  unwind registration) are recorded in 
everse/re_attempts.log.
- **Clearance:** none; no header or dependent change is claimed verified.
- **Census confirmation:** n/a (adoption lane; surfaced via the scoped header
  gate, not the link census).

**Player CRT declaration follow-up (2026-10-29, base `656dc5717d`):**
Removing only the redundant memcmp prototype preserves 31/31 rows, all four
EH graphs, 52 COMDAT fingerprints and 157 external symbol entries. The
header queue drops one finding. Removing free or memset separately still
changes initFromDict and makes $L10490 ambiguous; both declarations remain.
This confirms the existing declaration-sensitive prerequisite and does not
clear Coord3D member growth. Strict preparation passes and the ordinary
preview retains LINKS for 4,707 authored bytes at index `85f6b7f40c`. The
older-index batch audit lacks a current CreateAHeroManager consumer receipt;
carry both sources into the next scheduled census.
[Trials and remaining work](../../reverse/attempt_support/player-init-msheaders-20261029-codexb4.md).

#### Assigned Coord3D package, 2026-10-27

- **Inspected `d01dd5afd355`; ordinary preview index `5ce093a71a`, retail-truth-4:** `FiringTrackerXfer.cpp` adopts the registered Coord3D header and the existing Coord3DBase companion. Its transfers and equality calls use `asBase`; the existing public `zero()` member keeps its inline definition in the unit. The owning acceptance tool retires its Coord3D queue row. All matched rows, exception graphs, declaration and data checks pass, and its clean ordinary link preview is preserved. No census gain is claimed.
- **Remaining:** 24 assigned units retain their queue rows and exact original source bytes. `Coord3DCopy.cpp` and `Rva0055A246Ctor.cpp` require a coordinated class-key migration. Other stops require constructor, copy or destructor lifetime contracts absent from the canonical POD header; `BridgeObjectCtor.cpp` additionally requires the base relationship and inline base `set`, while `SidesListDataChunks.cpp` requires inline `add` and `sub`. These prerequisites belong with the class owner and dependent recompute above.
- **Evidence / next check:** per-unit before, rejected-candidate and final build/link outputs, blocked verdicts and final gates are recorded in local `build/header-report.md` and `build/header-h1/`. Final CSV and pin-consistency checks pass. Canonical headers, reference shims and the function and symbol ledgers are unchanged. Resolve each stopped unit's recorded interface or class-key prerequisite before retrying it; broader closure and census confirmation remain open.

#### Coord3D companion acceptance follow-up, 2026-10-28

- **Inspected `523e91ba00`; preview index `41c28839bf`:** after checker fix
  `e46cd47132`, the owning header tool accepts the existing shared companions
  in BridgeObjectCtor, BridgeBehaviorHandleObjectsOnBridgeOnDie,
  OneRingPenaltyUpdate and AIStructureCreepTactic, retiring four queue rows.
  All 68 function rows and eleven EH graphs remain exact. Game sources and
  headers are unchanged. [Scoped evidence and remaining prerequisites](../../reverse/attempt_support/coord3d-companion-retirement-20261028-codex3.md).
- **Clearance:** header debt only. Three ordinary previews preserve LINKS
  for 2,613 authored bytes; the tactic remains at 0 -> 0 with its existing
  selected Object-vector destructor/push_back/growth blockers (LINK-132).
  Eleven Coord3D queue entries and the broader class/provider work remain.
  No new census-linked bytes or selected-provider clearance is claimed.

#### Region3D adoption: separate Coord3D class-key/provider prerequisite

- **2026-10-26, inspected `c973319b7d3`:** the Region3D queue serves
  `WWMath/region.cpp` with a canonical/private Coord3D redefinition. The
  supported, non-applying Coord3D header trial (`--sample 1 --seed 17`) selects
  this file and fails its 47-byte Region3D debug streamer at `0x0000517C`.
  Canonical `struct Coord3D` emits two undefined U-form streamer calls; retail
  calls `0x000050BA`, owned by the V-form provider in `WWMath/coord3d.cpp`.
  A scoped consumer ledger rename cannot migrate that separate provider.
- **Remaining:** reconcile canonical Coord3D adoption across the provider and
  callers, preserving constructor behavior and verifying dependent rows. This
  class-key binding prerequisite is distinct from the member-growth/EH failure
  above. No alias, pin or shared-header growth was applied.
- **Preservation:** the tool restored source/ledger; normal build passes 45/45
  rows and seven string references. Current link preview retains 1,287 bytes
  against census `d1f046749a`; no clearance, queue retirement or census gain.
  Evidence: `reverse/attempt_support/region3d-header-prerequisite-20261026-bce2/`.

#### Bridge Region3D debt subset, 2026-10-26

- **Recovery reconciliation, 2026-10-27:** upstream `2a5ee5a0db` already names the AddBridge records `Coord3D` and matrix rows `Vector4`; retain those types. The earlier opaque AddBridge replacement below is superseded, while the canonical includes and accepted header-debt retirements remain.

- **Inspected `fff0ff229a`:** [the bridge adoption evidence](../../reverse/attempt_support/bridge-region3d-adoption-20261026-codex4/readme.md)
  replaces two incorrect 12-byte Region3D views in
  `BridgeBehaviorHandleObjectsOnBridgeOnDie.cpp` and
  `W3DBridgeBufferAddBridge.cpp` with the already-owned opaque
  `Rva0027C36ATwelve` callback type. `W3DBridgeCtor.cpp` now binds its
  16-byte matrix rows to the existing Vector4 constructor owner. All three
  include the canonical Region3D header; no shared header or callback pin
  changed. The owning adoption tool retires three header queue rows.
- **Verification / clearance:** 9/9 matched rows, three EXACT EH graphs and
  three unmatched-body checks pass. Ordinary before/after link previews
  against index `5ce093a71a` preserve 3/3 LINKS and 1,014 authored bytes.
  Header debt is cleared only for these three sources. This is not a new
  linked-byte gain, strict-closure receipt or census confirmation.
- **Remaining:** the four Region3D queue entries retain their separate
  copy-visibility, opaque 16-byte element, Coord3D lifetime and streamer
  provider prerequisites, detailed in the evidence. The broader LINK-018
  Coord3D member-growth and provider work remains open.

#### Command-pool Region3D debt follow-up, 2026-10-26

- **Inspected after `6bdbf0ba29`:** the existing native builders in
  `Rva000748F6Builders.cpp` identify the +4 member of the command-pool record
  as Matrix3D through its Set and axis-scaling operations. BFME 1's WWMath
  declaration supplies three Vector4 rows. This resolves the preceding
  opaque 16-byte element prerequisite for `Rva000747E5Method.cpp`.
- **Completed / clearance:** this source now declares Vector4 rows against
  the existing constructor owner and includes canonical Region3D. Normal
  builds preserve 3/3 matched; unmatched-body and header-adoption checks
  pass. The adoption tool retires one further header debt row. Ordinary
  before/after previews preserve LINKS and 71 authored bytes against
  `5ce093a71a`; no census gain is claimed. Evidence and raw logs are in
  [the same adoption evidence](../../reverse/attempt_support/bridge-region3d-adoption-20261026-codex4/readme.md).
- **Remaining:** three Region3D entries retain the copy-visibility, Coord3D
  lifetime and streamer-provider prerequisites. LINK-018 remains open.

#### Coord3D consumer adoption package, 2026-10-27

- **Inspected `0c1d1f01636`:** `AIUpdateInterface_requestMeleeApproachPath.cpp`, `DockUpdateXfer.cpp`, `W3DViewCameraModFinalLookTowardBfme.cpp` and `W3DViewCameraModLookTowardBfme.cpp` now include canonical Coord3D. Field initialization preserves the local-copy code, and the transfer unit uses the canonical `asBase` accessor. The owning acceptance tool removes their queue entries. Normal byte checks and paired ordinary link previews against `5ce093a71a` preserve the assigned rows and clean link states. Per-unit raw outputs and final checks are recorded in `build/header-report.md` and `build/header-hc2-coord3d/`.
- **Remaining:** the other assigned units retain constructor, destructor, member, code-generation or class-key prerequisites. In particular, the array and by-value units require nontrivial coordinate lifetimes, while `coord3d.cpp`, `coord3d_crossproduct.cpp`, `matrix4d.cpp` and `region.cpp` retain V-form coordinate rows that canonical struct adoption would rename. Sources are restored or untouched, their queue entries remain, and blocked verdicts identify the evidence. Resolve the class-owner interface and provider prerequisites before retrying. This package establishes header-debt retirement only; LINK-018 remains open and no census or strict-closure gain is claimed.

- **2026-11-04, WaterTracks:** canonical Region3D's new declaration-only copy option preserves the retail bounds-getter call while removing the BFME 1 Coord3D include conflict; Thing acceptance retires this consumer's queue row after byte/data and link-preservation checks. [Evidence and remaining selected-view prerequisites](../../reverse/attempt_support/watertracks-thing-adoption-20261104.md); broader LINK-018 remains open, with no census gain claimed.


2026-11-05 follow-up: The Coord3DBase-only follow-up still reaches the canonical Coord3D declaration. Coord3DCopy requires the existing member and DeflectSpecialPower requires a coordinated onCollide class-key migration. All trials were restored. [Native trial and prerequisite](../../reverse/attempt_support/header-composition-prerequisites-up-to-hundred-each-20261105-1425.md).


**2026-11-07 ownership (swarm Link lane).** The class-key flip itself stays with Dave Razidlo's
class-key rename (scope above: 338 directly including units at minimum, through the lane's class-key
rename path). Once that lands, the swarm Link lane takes the two `Matrix4D` exports' follow-up only:
respell `Snapshot.cpp`'s row to the export spelling `??0Matrix4D@@QAE@ABVCoord3D@@M@Z`, then give `Set`
its name with an `--icf-owner` twin row (fold-proof) at 0x00004079. Real link `f98a8da771` still lists
both as unresolved.

**2026-11-09 status (swarm Link lane).** `Coord3D` is still `struct` and the real link at `26501393cb` still lists both `Matrix4D` exports. The follow-up
stays waiting on the class-key flip: a row respell alone would not compile to the export spelling. Dave Razidlo's last Coord3D commit is 2026-11-06, and no
`Coord3D` claim or branch was found, so whether that work is active needs asking.

**2026-11-10, axis-angle constructor and Set.** A shared force-inlined implementation in the approved Snapshot.cpp TU emits both retail export names when compiled with the retail Coord3D class key. Both bodies match all 357 bytes after resolving the same relocation. The current canonical struct still emits U for both names. The [tested patch and controls](../../reverse/attempt_support/matrix4d-axis-angle-exports-20261110/README.md) are ready for the coordinated class-key change. No production row or export has moved yet.
