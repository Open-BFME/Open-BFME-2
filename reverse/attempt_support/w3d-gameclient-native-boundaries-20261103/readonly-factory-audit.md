# W3DGameClient: native drawable factory binding and remaining scope

Read-only bounded audit, 2026-11-03. No builds/compiles, edits, claims, network, fetch, admission, new names or pins. Root supplied current normal5/5 and control preview10undefined/createGameDisplaywrong-selected. Exact cached dependency and undefined-origin analysis is in readonly-header-undef-audit.md/.json.

Source: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DGameClient.cpp, SHA256 EF870785A1152CFC439514F5CA5812A0CC21180C4C6EFBA4D76845510EB4B91B. Canonical ThingFactory.h SHA256 E14B51EE78348A7C2BD69A8648400F032F943784ABF80A588D832A281710873D; provider Rva002CF21BGet.cpp F54D72EA625F637A2B48E946BEBEEDC28B97E01337E0F15A880D8A7617370B1E.

## Proven live caller and existing provider

The matched148B caller is `?createRayEffectByTemplate@W3DGameClient@@UAEXPBUCoord3D@@0PBVThingTemplate@@@Z`, RVA4C7F0. Read its current normal object with read_object_symbol_bytes (read-only) and independently read native bytes. Its REL32 field+21 (RVA4C805; E8 at+20) resolves to2CF21B. The current symbolic callee is fake `?newDrawable@BFMEThingFactory@@QAEPAVDrawable@@PBVThingTemplate@@W4DrawableStatus@@H@Z`.

The actual current matched99B owner is `?newDrawable@ThingFactory@@QAEPAXPAXHH@Z`, Code/GameEngine/Source/Common/Rva002CF21BGet.cpp. Canonical Code/GameEngine/Include/Common/ThingFactory.h declares exactly `void *newDrawable(void *tmplate,int statusBits,int randomValue)`. Native RET12 and its three-argument GameClient+70 dispatch agree. The provider null-checks the template, calls the global client virtual, visits result+154 modules, and returns that result. No receiver field is used by this body; this fact does not establish an entire factory layout beyond the registered header.

The same caller's other REL32 fields are+123 ->Drawable::setPosition at2710E7 and+137 ->RayEffectSystem::addRayEffect at2CED84. They are independent existing bindings, not new repairs proposed here.

TheThingFactory is already converged as `?TheThingFactory@@3PAVThingFactory@@A` atRVA9FF000 (data_rows VA DFF000) owned by Common/Thing/ThingFactory.cpp. Keep that real declaration; do not add a second global or bind a BFMEThingFactory* alias. Canonical consumers already exist, e.g. GameLogic.cpp explicit canonical include165 and newDrawable call4744, and InGameUIPlaceBuildAvailable.cpp explicit canonical include13. These demonstrate the current API, not a claim that their broader bodies were reverified by this audit.

## Is the fake class/receiver cast removable now?

The real3arg provider/signature are available and require no shared-header expansion or new pin. A direct ThingFactory call could replace the fake derived receiver after genuine header adoption. The current canonical opaque ABI still requires an explicit const-removal for the const ThingTemplate* passed to void*, and an explicit void*->Drawable* result conversion. Those are pointer-boundary conversions, not a fake derived-object receiver cast or container-layout cast. No original third-argument purpose is inferred; retain -1 and existing0status.

However, the CURRENT unit cannot simply add the canonical header or delete BFMEThingFactory: its normal dependency receipt resolves ThingFactory to the pristine TWO-ARG Zero Hour header, not Code's3arg header. Source57 already reads old sweep SubsystemInterface, and135 reads old ThingFactory; canonical headers have distinct guards and would redefine both classes. This is a concrete include/hierarchy prerequisite, not a missing native function or a need for guessed names. Removing the fake class alone leaves no three-arg member in the actually visible ThingFactory declaration.

The exact current resolved headers and guard/order facts are recorded in the companion report. No header-guard bypass, new private copy of registered ThingFactory, misleading function-pointer cast, alias pin or shared-header edit was tried or proposed. Supported next repair is a separately verified TU-local Subsystem/ThingFactory/include-context reconciliation against the registered native hierarchy, followed by the direct existing3argcall and normal all-provider/table/caller checks. A one-line acceptance is not claimed. No current ThingFactory queue key for this source was found; existing FontLibrary/InGameUI/Keyboard keys remain independent and must not disappear as collateral cleanup.

The fake BFMEThingFactory declaration and live source use occur only in this W3D source; one ControlBar source has a historical comment mentioning a filename. Its harvested pin atsymbols.csv5869 also names2CF21B but supplies no linker body. Only after the caller is repaired and normal name_dependents checks prove no other exact-symbol consumers remain may that superseded pin be retired with normal ledger/hatch handling. No pin was removed here.

## Ten unresolved names: actual origin partition

Only ONE unresolved name is reached directly from the5current rowed bodies: fake BFMEThingFactory::newDrawable in createRay+21.

The remaining NINE are retained current emissions:
- inline createVideoPlayer50B ->BinkVideoPlayer constructor at+34;
- inline createWindowManager50B ->W3DGameWindowManager constructor+34;
- inline createInGameUI53B ->W3DInGameUI constructor+37;
- inline createTerrainVisual50B ->W3DTerrainVisual constructor+34;
- unrowed friend_createDrawable70B ->Drawable constructor+48;
- unrowed adjustLOD122B ->BaseHeightMapRenderObjClass::setTextureLOD+114;
- unrowed notifyTerrainObjectMoved18B ->BaseHeightMapRenderObjClass::unitMoved+11;
- W3DGameClient's180B vtable DIR32+88 ->GameClient::assignSelectedDrawablesToGroup;
- same vtable DIR32+124 ->GameClient::preloadAssets.

These are exact current COFF source associations from the companion audit, not permission to remove an unrowed constructor/function/vtable or suppress a helper. Their native identities/ABI/provider closure are separate remaining work. createGameDisplay53B's wrong-kept body is also independent; the Oct26 packet already described a ctor-binding identity finding, so do not call the present failure a newly introduced regression without current before/after evidence.

## Prior packet and conclusion

reverse/attempt_support/consolidation-sol-gameclient-20261026.md records the completed static status-circle data ownership cleanup,57provider preservation,5/5row checks, two stale marker removals and one data debt retirement. It explicitly left mixed/unplaced rows, independent GameClient declarations, flags and identity findings unresolved. Preserve that completed work. The current control preview stillreports LINKED0->0; no new census or linked gain is claimed by this audit.

Small evidence-backed target: consume the existing canonical3argfactory identity once the actual include/hierarchy context is reconciled. Provider discovery is solved; current old header definitions are the explicit blocker to direct adoption. Fixing that one call alone leaves9undefined plus createGameDisplaywrong-selected. All tracked reads stopped on report completion.
