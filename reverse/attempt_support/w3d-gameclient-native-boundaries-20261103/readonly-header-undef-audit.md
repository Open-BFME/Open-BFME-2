# W3DGameClient: current header and undefined-reference origins

Bounded read-only audit, 2026-11-03. No edits to tracked files, builds, verification runs, index fetch/refresh, claims or publication operations. The parent read the full source and ran the reported normal5/5 and preview. This review reads the cached MAIN-workspace object and its .deps.json, the three resolved headers in full, narrow source-owned ledger rows, and the prior consolidation packet.

## Cache/dependency facts

Source: `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DGameClient.cpp`.
Object: `build/match/^code_^game^engine^device_^source_^w3^d^device_^game^client_^w3^d^game^client.obj`.

The current source MD5 **1fb444313c65bd5a9fdddee9018f60a6** and object MD5 **20bc57f30cd84d5c42bd4dcec7714d38** equal their normal-build dependency receipt. These exact resolved headers also equal their recorded dependency hashes:

- W3DGameClient: `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DGameClient.h`, MD5 **6f0ca07e2eefee102971a64f46967158**.
- GameClient: `reference/shims/sweep/GameClient/GameClient.h`, MD5 **75794077bfe9c2b051688bf36828b41c**.
- ThingFactory: `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingFactory.h`, MD5 **3d1539346a0629acb32f5c6b01b6211c**.

These are the actual compilation inputs, not an assumed Code header or proof of original BFME2 layouts. Full paths, raw COFF references and hashes are retained in readonly-header-undef-audit.json.

## Exact partition of the ten unresolved names

Only **one of the ten** is a direct relocation from one of this source's five matched bodies: BFMEThingFactory::newDrawable from the 148-byte createRayEffectByTemplate. The other nine originate in emitted unrowed bodies, header-inline factory methods, or the emitted vtable.

| Unresolved target | Actual current incoming COFF definition | Relocation offset/type | Origin |
|---|---|---|---|
| BinkVideoPlayer constructor | W3DGameClient::createVideoPlayer, 50 bytes | +34 REL32 | Resolved W3D header inline factory |
| W3DGameWindowManager constructor | W3DGameClient::createWindowManager, 50 bytes | +34 REL32 | Resolved W3D header inline factory |
| W3DInGameUI constructor | W3DGameClient::createInGameUI, 53 bytes | +37 REL32 | Resolved W3D header inline factory |
| W3DTerrainVisual constructor | W3DGameClient::createTerrainVisual, 50 bytes | +34 REL32 | Resolved W3D header inline factory |
| Drawable(const ThingTemplate*,DrawableStatus) constructor | W3DGameClient::friend_createDrawable, 70 bytes | +48 REL32 | Existing source body, not one of the five rowed bodies |
| GameClient::assignSelectedDrawablesToGroup(int) | W3DGameClient primary SubsystemInterface vtable, 180 bytes | +88 DIR32 | Inherited virtual declaration in resolved GameClient shim |
| GameClient::preloadAssets(TimeOfDay) | Same primary vtable | +124 DIR32 | Inherited virtual declaration in resolved GameClient shim |
| BFMEThingFactory::newDrawable(const ThingTemplate*,DrawableStatus,int) | W3DGameClient::createRayEffectByTemplate, 148 bytes | +21 REL32 | **Matched row** at RVA 0x0004C7F0; parent's callee/ABI investigation |
| BaseHeightMapRenderObjClass::setTextureLOD(int) | W3DGameClient::adjustLOD, 122 bytes | +114 REL32 | Existing unrowed source body |
| BaseHeightMapRenderObjClass::unitMoved(Object*) | W3DGameClient::notifyTerrainObjectMoved, 18 bytes | +11 REL32 | Existing unrowed source body |

Exact decorated names, body sizes and relocation triples are in JSON. There are no additional direct references to these ten from the other inspected emitted definitions.

## Why the header factories and inherited virtuals are emitted

The cached unrowed W3DGameClient constructor is 25 bytes: it calls GameClient's constructor and stores the primary W3DGameClient table at DIR32 +10 and its Snapshot table at +17. Its 18-byte destructor stores the same tables at +2/+9 before calling GameClient's destructor. Thus the primary table is a concrete current object provider, not merely a header declaration.

The primary table directly references the inline factories at offsets +140 createInGameUI, +144 createWindowManager, +156 createVideoPlayer and +160 createTerrainVisual. Their definitions in the resolved W3D header allocate the corresponding concrete types. It also references the unrowed friend_createDrawable, adjustLOD and notifyTerrainObjectMoved overrides at +72/+112/+132, alongside the two undefined inherited GameClient virtuals at +88/+124. This chain explains the nine unresolved references outside the five matched bodies. It is not evidence authorizing removal of any existing body or table.

The GameClient shim deliberately declares findDrawableByID out of line and contains three inline placeholder virtuals before getFrame. Its full declarations include assignSelectedDrawablesToGroup and preloadAssets, exactly matching the names found in the emitted W3D table. The actual pristine ThingFactory header declares a **two-argument** newDrawable (with default status), whereas the source's BFMEThingFactory view declares the three-argument call seen in createRayEffect. This review does not infer the real third-argument provider; the parent owns that target-level investigation.

## The five actual matched rows and the prior packet

The narrow ledger shows these five current source-owned rows:

- W3DStatusCircle::setColor: RVA0x0004C41F,31 bytes.
- W3DGameClient::setTeamColor: RVA0x0004C8BC,33 bytes.
- W3DGameClient::addScorch: RVA0x0004C7A8,72 bytes.
- W3DGameClient::createRayEffectByTemplate: RVA0x0004C7F0,148 bytes.
- W3DGameClient::createGameDisplay: RVA0x0008FCAE,53 bytes; this one is itself the header-inline virtual emitted through the table.

The cached preview separately reports createGameDisplay as both a differing COMDAT and the wrong kept definition. That is additional to the ten missing names, and the parent is tracing its W3DDisplay binding. A normal byte pass on five rows does not establish whole-object linkability when unrowed providers and selected tables remain involved.

`reverse/attempt_support/consolidation-sol-gameclient-20261026.md` already documents the status-circle data-owner repair, preservation of57 emitted providers at that time, no source move, no class-layout recovery, and the pre-existing createGameDisplay/W3DDisplay constructor identity finding. It explicitly leaves independent GameClient views and compiler-flag/composition prerequisites. The present current-object partition confirms concrete remaining mechanisms; this review neither re-runs that old proof nor treats the earlier data repair as closure of these link dependencies.

Audit complete. No body/table removal is recommended. All tracked reads stopped after this report.

## Requested direct canonical ThingFactory include boundary

The cached normal dependency receipt also resolves `reference/shims/sweep/Common/SubsystemInterface.h` (recorded MD5 4870d7dbe4a29616fdf7c2d1b5ec00cc). The source includes Common/SubsystemInterface.h at line57, the pristine two-argument Common/ThingFactory.h at135, the GameClient shim explicitly at144, and W3DGameClient.h at238.

The currently resolved SubsystemInterface is the old shim class with destructor/init/postProcessLoad/reset/update/draw and guard `__SUBSYSTEMINTERFACE_H_`. It is not the canonical Code/Libraries/Source/subsystem/SubsystemInterface.h, whose guard is `CANONICAL_SUBSYSTEMINTERFACE_H` and whose full BFME_SUBSYSTEM_SLOTS surface has fourteen slots and different data layout.

`Code/GameEngine/Include/Common/ThingFactory.h` declares the desired existing provider surface exactly as `void *newDrawable(void *tmplate, int statusBits, int randomValue)`. It uses its own guard `BFME2_THINGFACTORY_H`, sets BFME_SUBSYSTEM_SLOTS before including the canonical subsystem header, and explicitly errors only when the canonical subsystem was already read without BFME_SUBSYSTEM_SLOTS.

In the CURRENT translation-unit context, that explicit short-canonical error condition is not the first issue: the old resolved shim sets a DIFFERENT guard. Adding the canonical ThingFactory include after source line57 would therefore parse a second full SubsystemInterface class; adding it after135 would also parse a second ThingFactory class because pristine `__THINGFACTORY_H_` is distinct from `BFME2_THINGFACTORY_H`. Moving the canonical include earlier without reconciling later old headers likewise does not make their differing guards/classes disappear. A simple late include insertion is blocked by these concrete definitions. The unit needs actual include/base-interface reconciliation; this read-only audit supplies no guard-forcing workaround or private canonical-class copy.

This is header/source evidence only, not a compile result. No additional tracked reads followed this addendum.
