# Item008: canonical CreateAHeroManager adoption prerequisite

**Ready for Root's ordinary admission.** Source basis:
`bce1ceaf11b75d5f0b81ba1047e91d8d65ee2578`. No production, Git, claims,
shared object, index, register or baseline was modified by this worker.
Private probes used BFME_OBJSTORE=off and at most two compiler workers.

## Final package

Apply **manager-adoption.patch** only. SHA-256:
`de14049907576c971dc6fb1ac79b8c2b59881e1a7062280039dab361d55a3167`.
All final source artifacts use literal LF; their raw-byte hashes and the current
production input hashes are in **manager-final-inputs.json**. Three files change:

- Code/GameEngine/Include/GameLogic/CreateAHeroManager.h
- Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptMyHero.cpp
- Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptMyHero_Unresolved.cpp

The two private manager copies disappear in favor of the existing canonical
header. All existing fields retain their exact names, access, types, offsets,
sizes, base and virtual declarations. The header grants only
`friend class AptMyHero`; this is an explicit access policy for the reconstructed
sources, not a claim about EA's original access specifiers.

The already-public GetClassCount() const helper is retained in the common header
with the same typed span operation, preserving its complete 18-byte COMDAT. The
two existing CreateAHeroClassRecord/CreateAHeroClassList declarations move
verbatim from the two sources to that header, so no replacement container or
new helper name is introduced. Their record remains an opaque stride view,
not a newly identified application type. Canonical field14C stays uint[3].

Only the binder-count source expression changes: its existing BlingBinderList
view reads the existing canonical field168 span. This follows the already-
adopted GetBlingBinder implementation's own Vec20 view of the same field.
The transition-group strings field1E8/field1EC stay private and are read through
the friendship. The class-count call retains its original public spelling.

Root already holds the two source scopes, class:CreateAHeroManager, the header
scope, class:CreateAHeroClassRecord and class:CreateAHeroClassList. No contract
edit, generator invocation, flag change, new alias/pin/pragma or gate repair is
needed by this proposal.

## Verification

**manager-probe-friend-count-view.json**: separate unchanged controls and final
candidates keep 43/43 seed and16/16 destructor-file rows, 5,218 existing bytes,
unmasked and with zero unresolved references. Zero new functions/byte coverage
or runtime improvement is claimed.

**manager-full-audit.json** and **manager-comdat-selections.json**:

| Check | Seed | Destructor file |
|---|---:|---:|
| Strong external code definitions, all raw code/named relocations identical |58 ->58|13 ->13|
| All public/weak COFF records, including DEFAULT identities, identical |143 ->143|70 ->70|
| Physically identical linkable code/data sections |142 ->142|38 ->38|
| Section COMDAT selection/association unchanged |143 section records|39 section records|
| COMDAT count unchanged |138|36|
| Source function-definition inventory |unchanged|unchanged|

Physical section comparison binds private EH labels by actual section/value/
storage, never by an unverified name alias; public and weak names stay exact.
Only diagnostic .debug$S/.debug$T sections are excluded. It is a private evidence
comparison, not an alternative admission gate. GetClassCount retains section23,
selection2 (ANY), association0, raw bytes
`8b815001000081c14c0100002b01c1f805c3`, no relocations. The real six-slot
AptMyHero vtable is unchanged byte-for-byte and in every DIR32 target.

**manager-canonical-cohort.json**: all **88 existing direct canonical-header
consumers**, **2,046 rows**, compile and match before/after in isolated ordinary
native Verifier contexts. No existing Code/ header other than CreateAHeroManager.h
includes it, so the direct source inventory covers its actual literal include
consumers; Root's conservative normal header-dependent/full gates remain required.
Together with the two newly adopting files this is90 unique sources/2,105 existing
rows checked privately. These checks are neither 2,105 completed work items nor a
new real-link result.

## ABI, ownership and field evidence

The private 496-byte manager declarations are observer prefixes ending after
the second transition string; no source constructs, destroys, copies or sizes
those incomplete views. The existing canonical **500-byte** declaration expresses
the actual target object: GameEngine allocates0x1F4 at0x0022FBED, constructor
0x0021FE49 calls the SubsystemInterface constructor at0x0021FE5C, installs the
0x00BE648C table and registers TheCreateAHeroManager atVA0x00DFE344.
The data ledger has one owner for that class-pointer global atRVA0x009FE344.

Native CodeView of the proposed sources gives canonical CreateAHeroManager size
500 with SubsystemInterface at+0; the base is12 bytes. Every other previously
complete class is unchanged, including both helper views. Additional native
type records are forward declarations only. All eleven existing ordinary
manager call declarations have token-identical return/parameter/cv prototypes
in the canonical header; manager-final-inputs.json lists their actual matched
row names, RVAs, complete extents and provider paths.

| Storage | Independent target/provider support | Retained source use |
|---|---|---|
| +0x14C/+0x150/+0x154 |421B ctor21FE49 initializes vector at+14C;63B vector destructor21FDEC and class record providers;88B GetViewInfo219F36 checks span and32-byte stride|Existing opaque32 Record/List and18B GetClassCount; no canonical container type is inferred|
| +0x168/+0x16C/+0x170 |Ctor initializes vector+168;63B dtor21DA57 destroys BfmeStringRecord00219A68;46B canonical GetBlingBinder21A106 uses Vec20 on field168 and signed stride20 arithmetic|Existing UI BlingBinderList count; GetBlingBinder continues supplying each record|
| +0x1E8/+0x1EC |Ctor initializes the two FadeCreateAHeroScreenDown/Up strings;279B dtor21FFEE destroys these members; current187B AptMyHero21DA and760B FrameUpdate read them|Exact existing transition-group accesses, now through friend AptMyHero|

The binder's full20-byte source representation has a word, two AsciiString
members and two words (StringRecordInlineCopyBFME2.cpp, copy0x00219A68). The UI view
reads its first word, first string and final words; its unused middle word does
not acquire a new claimed meaning. Container ownership/lifetime remains with
the canonical manager's existing external providers.

Direct retail PE read at tableRVA0x007E648C gives exactly these14 code VAs:
`6201B9,61A3B7,90B5C6,4B3FD0,9CB9FF,87A699,4D43D0,87A69C,4B3FD0,4B3FD0,4B3FD0,9CB9FF,4B3FD0,87A69C`.
The following bytes start `SubClass`, not another code slot. The header's existing
base/overrides represent this table; no virtual declaration or slot was added.

## Root's admission path

After the measured inputs are released and published normally:

1. Verify manager-final-inputs.json hashes, apply only manager-adoption.patch.
2. Run the normal whole-consumer/header-dependent gate and `./build.sh` on both
   full adopting sources. The private cohort is supporting evidence only.
3. Run `header_adopt_lane.py accept --class CreateAHeroManager` on both sources,
   then native find_declared_unmatched.py. Only native acceptance retires the two
   manager header keys.
4. Commit this prerequisite separately, with its measured evidence. Re-run the
   normal whole-TU consolidation dry-run afterward; do not move rows by hand.

The served AptMyHero consolidation is still open. No donor deletion or completed
served-item credit is asserted. Other outstanding Apt/Matrix/Vector/STL contexts
remain under their own normal gates.

## Rejected controls, preserved for diagnosis

- visibility-only:59/59 but removes the existing18B GetClassCount COMDAT; rejected.
- keep-count with raw span arithmetic: count helper16 instead of18B and the
  186B AptMyHero1A6C instruction order changes; rejected.
- friend-count-view: the single justified friendship variant above retains
  every original code/data/undefined/COMDAT fact and all cohort rows.

Do not apply the earlier two controls or any prior Copy/Vector3 experiment.
